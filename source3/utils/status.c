/* 
   Unix SMB/CIFS implementation.
   status reporting
   Copyright (C) Andrew Tridgell 1994-1998

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   Revision History:

   12 aug 96: Erik.Devriendt@te6.siemens.be
   added support for shared memory implementation of share mode locking

   21-Jul-1998: rsharpe@ns.aus.com (Richard Sharpe)
   Added -L (locks only) -S (shares only) flags and code

*/

/*
 * This program reports current SMB connections
 */

#include "includes.h"
#include "system/filesys.h"
#include "popt_common.h"
#include "dbwrap/dbwrap.h"
#include "dbwrap/dbwrap_open.h"
#include "../libcli/security/security.h"
#include "session.h"
#include "locking/proto.h"
#include "messages.h"
#include "librpc/gen_ndr/open_files.h"
#include "smbd/smbd.h"
#include "librpc/gen_ndr/notify.h"
#include "lib/conn_tdb.h"
#include "serverid.h"
#include "status_profile.h"

#define SMB_MAXPIDS		2048
static uid_t 		Ucrit_uid = 0;               /* added by OH */
static struct server_id	Ucrit_pid[SMB_MAXPIDS];  /* Ugly !!! */   /* added by OH */
static int		Ucrit_MaxPid=0;                    /* added by OH */
static unsigned int	Ucrit_IsActive = 0;                /* added by OH */

static bool verbose, brief;
static bool shares_only;            /* Added by RJS */
static bool locks_only;            /* Added by RJS */
static bool processes_only;
static bool show_brl;
static bool numeric_only;
static bool do_checks = true;

const char *username = NULL;

/* added by OH */
static void Ucrit_addUid(uid_t uid)
{
	Ucrit_uid = uid;
	Ucrit_IsActive = 1;
}

static unsigned int Ucrit_checkUid(uid_t uid)
{
	if ( !Ucrit_IsActive ) 
		return 1;

	if ( uid == Ucrit_uid ) 
		return 1;

	return 0;
}

static unsigned int Ucrit_checkPid(struct server_id pid)
{
	int i;

	if ( !Ucrit_IsActive ) 
		return 1;

	for (i=0;i<Ucrit_MaxPid;i++) {
		if (serverid_equal(&pid, &Ucrit_pid[i])) {
			return 1;
		}
	}

	return 0;
}

static bool Ucrit_addPid( struct server_id pid )
{
	if ( !Ucrit_IsActive )
		return True;

	if ( Ucrit_MaxPid >= SMB_MAXPIDS ) {
		d_printf("ERROR: More than %d pids for user %s!\n",
			 SMB_MAXPIDS, uidtoname(Ucrit_uid));

		return False;
	}

	Ucrit_pid[Ucrit_MaxPid++] = pid;

	return True;
}

static int print_share_mode(const struct share_mode_entry *e,
			    const char *sharepath,
			    const char *fname,
			    void *dummy)
{
	static int count;

	if (do_checks && !is_valid_share_mode_entry(e)) {
		return 0;
	}

	if (count==0) {
		d_printf("Locked files:\n");
		d_printf("Pid          Uid        DenyMode   Access      R/W        Oplock           SharePath   Name   Time\n");
		d_printf("--------------------------------------------------------------------------------------------------\n");
	}
	count++;

	if (do_checks && !serverid_exists(&e->pid)) {
		/* the process for this entry does not exist any more */
		return 0;
	}

	if (Ucrit_checkPid(e->pid)) {
		d_printf("%-11s  ",procid_str_static(&e->pid));
		d_printf("%-9u  ", (unsigned int)e->uid);
		switch (map_share_mode_to_deny_mode(e->share_access,
						    e->private_options)) {
			case DENY_NONE: d_printf("DENY_NONE  "); break;
			case DENY_ALL:  d_printf("DENY_ALL   "); break;
			case DENY_DOS:  d_printf("DENY_DOS   "); break;
			case DENY_READ: d_printf("DENY_READ  "); break;
			case DENY_WRITE:printf("DENY_WRITE "); break;
			case DENY_FCB:  d_printf("DENY_FCB "); break;
			default: {
				d_printf("unknown-please report ! "
					 "e->share_access = 0x%x, "
					 "e->private_options = 0x%x\n",
					 (unsigned int)e->share_access,
					 (unsigned int)e->private_options );
				break;
			}
		}
		d_printf("0x%-8x  ",(unsigned int)e->access_mask);
		if ((e->access_mask & (FILE_READ_DATA|FILE_WRITE_DATA))==
				(FILE_READ_DATA|FILE_WRITE_DATA)) {
			d_printf("RDWR       ");
		} else if (e->access_mask & FILE_WRITE_DATA) {
			d_printf("WRONLY     ");
		} else {
			d_printf("RDONLY     ");
		}

		if((e->op_type & (EXCLUSIVE_OPLOCK|BATCH_OPLOCK)) == 
					(EXCLUSIVE_OPLOCK|BATCH_OPLOCK)) {
			d_printf("EXCLUSIVE+BATCH ");
		} else if (e->op_type & EXCLUSIVE_OPLOCK) {
			d_printf("EXCLUSIVE       ");
		} else if (e->op_type & BATCH_OPLOCK) {
			d_printf("BATCH           ");
		} else if (e->op_type & LEVEL_II_OPLOCK) {
			d_printf("LEVEL_II        ");
		} else if (e->op_type == LEASE_OPLOCK) {
			uint32_t lstate = e->lease->current_state;
			d_printf("LEASE(%s%s%s)%s%s%s      ",
				 (lstate & SMB2_LEASE_READ)?"R":"",
				 (lstate & SMB2_LEASE_WRITE)?"W":"",
				 (lstate & SMB2_LEASE_HANDLE)?"H":"",
				 (lstate & SMB2_LEASE_READ)?"":" ",
				 (lstate & SMB2_LEASE_WRITE)?"":" ",
				 (lstate & SMB2_LEASE_HANDLE)?"":" ");
		} else {
			d_printf("NONE            ");
		}

		d_printf(" %s   %s   %s",sharepath, fname, time_to_asc((time_t)e->time.tv_sec));
	}

	return 0;
}

static void print_brl(struct file_id id,
			struct server_id pid, 
			enum brl_type lock_type,
			enum brl_flavour lock_flav,
			br_off start,
			br_off size,
			void *private_data)
{
	static int count;
	unsigned int i;
	static const struct {
		enum brl_type lock_type;
		const char *desc;
	} lock_types[] = {
		{ READ_LOCK, "R" },
		{ WRITE_LOCK, "W" },
		{ PENDING_READ_LOCK, "PR" },
		{ PENDING_WRITE_LOCK, "PW" },
		{ UNLOCK_LOCK, "U" }
	};
	const char *desc="X";
	const char *sharepath = "";
	char *fname = NULL;
	struct share_mode_lock *share_mode;

	if (count==0) {
		d_printf("Byte range locks:\n");
		d_printf("Pid        dev:inode       R/W  start     size      SharePath               Name\n");
		d_printf("--------------------------------------------------------------------------------\n");
	}
	count++;

	share_mode = fetch_share_mode_unlocked(NULL, id);
	if (share_mode) {
		bool has_stream = share_mode->data->stream_name != NULL;

		fname = talloc_asprintf(NULL, "%s%s%s",
					share_mode->data->base_name,
					has_stream ? ":" : "",
					has_stream ?
					share_mode->data->stream_name :
					"");
	} else {
		fname = talloc_strdup(NULL, "");
		if (fname == NULL) {
			return;
		}
	}

	for (i=0;i<ARRAY_SIZE(lock_types);i++) {
		if (lock_type == lock_types[i].lock_type) {
			desc = lock_types[i].desc;
		}
	}

	d_printf("%-10s %-15s %-4s %-9jd %-9jd %-24s %-24s\n",
		 procid_str_static(&pid), file_id_string_tos(&id),
		 desc,
		 (intmax_t)start, (intmax_t)size,
		 sharepath, fname);

	TALLOC_FREE(fname);
	TALLOC_FREE(share_mode);
}

static int traverse_connections(const struct connections_key *key,
				const struct connections_data *crec,
				void *state)
{
	if (crec->cnum == TID_FIELD_INVALID)
		return 0;

	if (do_checks &&
	    (!process_exists(crec->pid) || !Ucrit_checkUid(crec->uid))) {
		return 0;
	}

	d_printf("%-10s   %s   %-12s  %s",
		 crec->servicename,procid_str_static(&crec->pid),
		 crec->machine,
		 time_to_asc(crec->start));

	return 0;
}

static int traverse_sessionid(const char *key, struct sessionid *session,
			      void *private_data)
{
	fstring uid_str, gid_str;

	if (do_checks &&
	    (!process_exists(session->pid) ||
	     !Ucrit_checkUid(session->uid))) {
		return 0;
	}

	Ucrit_addPid(session->pid);

	fstrcpy(uid_str, "-1");

	if (session->uid != -1) {
		if (numeric_only) {
			fstr_sprintf(uid_str, "%u", (unsigned int)session->uid);
		} else {
			fstrcpy(uid_str, uidtoname(session->uid));
		}
	}

	fstrcpy(gid_str, "-1");

	if (session->gid != -1) {
		if (numeric_only) {
			fstr_sprintf(gid_str, "%u", (unsigned int)session->gid);
		} else {
			fstrcpy(gid_str, gidtoname(session->gid));
		}
	}

	d_printf("%-7s   %-12s  %-12s  %-12s (%s) %-12s\n",
		 procid_str_static(&session->pid),
		 uid_str, gid_str,
		 session->remote_machine, session->hostname, session->protocol_ver);

	return 0;
}


static void print_notify_recs(const char *path,
			      struct notify_db_entry *entries,
			      size_t num_entries,
			      time_t deleted_time, void *private_data)
{
	size_t i;
	d_printf("%s\n", path);

	if (num_entries == 0) {
		d_printf("deleted %s\n", time_to_asc(deleted_time));
	}

	for (i=0; i<num_entries; i++) {
		struct notify_db_entry *e = &entries[i];
		char *str;

		str = server_id_str(talloc_tos(), &e->server);
		printf("%s %x %x\n", str, (unsigned)e->filter,
		       (unsigned)e->subdir_filter);
		TALLOC_FREE(str);
	}
	printf("\n");
}

int main(int argc, const char *argv[])
{
	int c;
	int profile_only = 0;
	bool show_processes, show_locks, show_shares;
	bool show_notify = false;
	poptContext pc;
	struct poptOption long_options[] = {
		POPT_AUTOHELP
		{"processes",	'p', POPT_ARG_NONE,	NULL, 'p', "Show processes only" },
		{"verbose",	'v', POPT_ARG_NONE, 	NULL, 'v', "Be verbose" },
		{"locks",	'L', POPT_ARG_NONE,	NULL, 'L', "Show locks only" },
		{"shares",	'S', POPT_ARG_NONE,	NULL, 'S', "Show shares only" },
		{"notify",	'N', POPT_ARG_NONE,	NULL, 'N', "Show notifies" },
		{"user", 	'u', POPT_ARG_STRING,	&username, 'u', "Switch to user" },
		{"brief",	'b', POPT_ARG_NONE, 	NULL, 'b', "Be brief" },
		{"profile",     'P', POPT_ARG_NONE, NULL, 'P', "Do profiling" },
		{"profile-rates", 'R', POPT_ARG_NONE, NULL, 'R', "Show call rates" },
		{"byterange",	'B', POPT_ARG_NONE,	NULL, 'B', "Include byte range locks"},
		{"numeric",	'n', POPT_ARG_NONE,	NULL, 'n', "Numeric uid/gid"},
		{"fast",	'f', POPT_ARG_NONE,	NULL, 'f', "Skip checks if processes still exist"},
		POPT_COMMON_SAMBA
		POPT_TABLEEND
	};
	TALLOC_CTX *frame = talloc_stackframe();
	int ret = 0;
	struct messaging_context *msg_ctx;
	char *db_path;
	bool ok;

	sec_init();
	load_case_tables();

	setup_logging(argv[0], DEBUG_STDERR);

	if (getuid() != geteuid()) {
		d_printf("smbstatus should not be run setuid\n");
		ret = 1;
		goto done;
	}

	if (getuid() != 0) {
		d_printf("smbstatus only works as root!\n");
		ret = 1;
		goto done;
	}


	pc = poptGetContext(NULL, argc, argv, long_options,
			    POPT_CONTEXT_KEEP_FIRST);

	while ((c = poptGetNextOpt(pc)) != -1) {
		switch (c) {
		case 'p':
			processes_only = true;
			break;
		case 'v':
			verbose = true;
			break;
		case 'L':
			locks_only = true;
			break;
		case 'S':
			shares_only = true;
			break;
		case 'N':
			show_notify = true;
			break;
		case 'b':
			brief = true;
			break;
		case 'u':
			Ucrit_addUid(nametouid(poptGetOptArg(pc)));
			break;
		case 'P':
		case 'R':
			profile_only = c;
			break;
		case 'B':
			show_brl = true;
			break;
		case 'n':
			numeric_only = true;
			break;
		case 'f':
			do_checks = false;
			break;
		}
	}

	/* setup the flags based on the possible combincations */

	show_processes = !(shares_only || locks_only || profile_only) || processes_only;
	show_locks     = !(shares_only || processes_only || profile_only) || locks_only;
	show_shares    = !(processes_only || locks_only || profile_only) || shares_only;

	if ( username )
		Ucrit_addUid( nametouid(username) );

	if (verbose) {
		d_printf("using configfile = %s\n", get_dyn_CONFIGFILE());
	}

	if (!lp_load_initial_only(get_dyn_CONFIGFILE())) {
		fprintf(stderr, "Can't load %s - run testparm to debug it\n",
			get_dyn_CONFIGFILE());
		ret = -1;
		goto done;
	}


	if (lp_clustering()) {
		/*
		 * This implicitly initializes the global ctdbd
		 * connection, usable by the db_open() calls further
		 * down.
		 */
		msg_ctx = messaging_init(NULL, samba_tevent_context_init(NULL));
		if (msg_ctx == NULL) {
			fprintf(stderr, "messaging_init failed\n");
			ret = -1;
			goto done;
		}
	}

	if (!lp_load_global(get_dyn_CONFIGFILE())) {
		fprintf(stderr, "Can't load %s - run testparm to debug it\n",
			get_dyn_CONFIGFILE());
		ret = -1;
		goto done;
	}

	switch (profile_only) {
		case 'P':
			/* Dump profile data */
			ok = status_profile_dump(verbose);
			return ok ? 0 : 1;
		case 'R':
			/* Continuously display rate-converted data */
			ok = status_profile_rates(verbose);
			return ok ? 0 : 1;
		default:
			break;
	}

	if ( show_processes ) {
		d_printf("\nSamba version %s\n",samba_version_string());
		d_printf("PID     Username      Group         Machine            Protocol Version       \n");
		d_printf("------------------------------------------------------------------------------\n");

		sessionid_traverse_read(traverse_sessionid, NULL);

		if (processes_only) {
			goto done;
		}
	}

	if ( show_shares ) {
		if (verbose) {
			db_path = lock_path("connections.tdb");
			if (db_path == NULL) {
				d_printf("Out of memory - exiting\n");
				ret = -1;
				goto done;
			}
			d_printf("Opened %s\n", db_path);
			TALLOC_FREE(db_path);
		}

		if (brief) {
			goto done;
		}

		d_printf("\nService      pid     machine       Connected at\n");
		d_printf("-------------------------------------------------------\n");

		connections_forall_read(traverse_connections, NULL);

		d_printf("\n");

		if ( shares_only ) {
			goto done;
		}
	}

	if ( show_locks ) {
		int result;
		struct db_context *db;

		db_path = lock_path("locking.tdb");
		if (db_path == NULL) {
			d_printf("Out of memory - exiting\n");
			ret = -1;
			goto done;
		}

		db = db_open(NULL, db_path, 0,
			     TDB_CLEAR_IF_FIRST|TDB_INCOMPATIBLE_HASH, O_RDONLY, 0,
			     DBWRAP_LOCK_ORDER_1, DBWRAP_FLAG_NONE);

		if (!db) {
			d_printf("%s not initialised\n", db_path);
			d_printf("This is normal if an SMB client has never "
				 "connected to your server.\n");
			TALLOC_FREE(db_path);
			exit(0);
		} else {
			TALLOC_FREE(db);
			TALLOC_FREE(db_path);
		}

		if (!locking_init_readonly()) {
			d_printf("Can't initialise locking module - exiting\n");
			ret = 1;
			goto done;
		}

		result = share_entry_forall(print_share_mode, NULL);

		if (result == 0) {
			d_printf("No locked files\n");
		} else if (result < 0) {
			d_printf("locked file list truncated\n");
		}

		d_printf("\n");

		if (show_brl) {
			brl_forall(print_brl, NULL);
		}

		locking_end();
	}

	if (show_notify) {
		struct notify_context *n;

		n = notify_init(talloc_tos(), NULL, NULL);
		if (n == NULL) {
			goto done;
		}
		notify_walk(n, print_notify_recs, NULL);
		TALLOC_FREE(n);
	}

done:
	TALLOC_FREE(frame);
	return ret;
}
