/* server functions auto-generated by pidl */
#include "autoconf/librpc/gen_ndr/ndr_audiosrv.h"

NTSTATUS dcerpc_server_audiosrv_init(void);

/* audiosrv - dcerpc server boilerplate generated by pidl */


static NTSTATUS audiosrv__op_bind(struct dcesrv_call_state *dce_call, const struct dcesrv_interface *iface, uint32_t if_version)
{
#ifdef DCESRV_INTERFACE_AUDIOSRV_BIND
	return DCESRV_INTERFACE_AUDIOSRV_BIND(dce_call,iface);
#else
	return NT_STATUS_OK;
#endif
}

static void audiosrv__op_unbind(struct dcesrv_connection_context *context, const struct dcesrv_interface *iface)
{
#ifdef DCESRV_INTERFACE_AUDIOSRV_UNBIND
	DCESRV_INTERFACE_AUDIOSRV_UNBIND(context, iface);
#else
	return;
#endif
}

static NTSTATUS audiosrv__op_ndr_pull(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx, struct ndr_pull *pull, void **r)
{
	enum ndr_err_code ndr_err;
	uint16_t opnum = dce_call->pkt.u.request.opnum;

	dce_call->fault_code = 0;

	if (opnum >= ndr_table_audiosrv.num_calls) {
		dce_call->fault_code = DCERPC_FAULT_OP_RNG_ERROR;
		return NT_STATUS_NET_WRITE_FAULT;
	}

	*r = talloc_named(mem_ctx,
			  ndr_table_audiosrv.calls[opnum].struct_size,
			  "struct %s",
			  ndr_table_audiosrv.calls[opnum].name);
	NT_STATUS_HAVE_NO_MEMORY(*r);

        /* unravel the NDR for the packet */
	ndr_err = ndr_table_audiosrv.calls[opnum].ndr_pull(pull, NDR_IN, *r);
	if (!NDR_ERR_CODE_IS_SUCCESS(ndr_err)) {
		dcerpc_log_packet(dce_call->conn->packet_log_dir, 
				  &ndr_table_audiosrv, opnum, NDR_IN,
				  &dce_call->pkt.u.request.stub_and_verifier);
		dce_call->fault_code = DCERPC_FAULT_NDR;
		return NT_STATUS_NET_WRITE_FAULT;
	}

	return NT_STATUS_OK;
}

static NTSTATUS audiosrv__op_dispatch(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx, void *r)
{
	uint16_t opnum = dce_call->pkt.u.request.opnum;

	switch (opnum) {
	case 0: {
		struct audiosrv_CreatezoneFactoriesList *r2 = (struct audiosrv_CreatezoneFactoriesList *)r;
		if (DEBUGLEVEL >= 10) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_CreatezoneFactoriesList, NDR_IN, r2);
		}
		dcesrv_audiosrv_CreatezoneFactoriesList(dce_call, mem_ctx, r2);
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_CreatezoneFactoriesList will reply async\n"));
		}
		break;
	}
	case 1: {
		struct audiosrv_CreateGfxFactoriesList *r2 = (struct audiosrv_CreateGfxFactoriesList *)r;
		if (DEBUGLEVEL >= 10) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_CreateGfxFactoriesList, NDR_IN, r2);
		}
		dcesrv_audiosrv_CreateGfxFactoriesList(dce_call, mem_ctx, r2);
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_CreateGfxFactoriesList will reply async\n"));
		}
		break;
	}
	case 2: {
		struct audiosrv_CreateGfxList *r2 = (struct audiosrv_CreateGfxList *)r;
		if (DEBUGLEVEL >= 10) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_CreateGfxList, NDR_IN, r2);
		}
		dcesrv_audiosrv_CreateGfxList(dce_call, mem_ctx, r2);
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_CreateGfxList will reply async\n"));
		}
		break;
	}
	case 3: {
		struct audiosrv_RemoveGfx *r2 = (struct audiosrv_RemoveGfx *)r;
		if (DEBUGLEVEL >= 10) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_RemoveGfx, NDR_IN, r2);
		}
		dcesrv_audiosrv_RemoveGfx(dce_call, mem_ctx, r2);
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_RemoveGfx will reply async\n"));
		}
		break;
	}
	case 4: {
		struct audiosrv_AddGfx *r2 = (struct audiosrv_AddGfx *)r;
		if (DEBUGLEVEL >= 10) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_AddGfx, NDR_IN, r2);
		}
		dcesrv_audiosrv_AddGfx(dce_call, mem_ctx, r2);
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_AddGfx will reply async\n"));
		}
		break;
	}
	case 5: {
		struct audiosrv_ModifyGfx *r2 = (struct audiosrv_ModifyGfx *)r;
		if (DEBUGLEVEL >= 10) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_ModifyGfx, NDR_IN, r2);
		}
		dcesrv_audiosrv_ModifyGfx(dce_call, mem_ctx, r2);
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_ModifyGfx will reply async\n"));
		}
		break;
	}
	case 6: {
		struct audiosrv_OpenGfx *r2 = (struct audiosrv_OpenGfx *)r;
		if (DEBUGLEVEL >= 10) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_OpenGfx, NDR_IN, r2);
		}
		dcesrv_audiosrv_OpenGfx(dce_call, mem_ctx, r2);
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_OpenGfx will reply async\n"));
		}
		break;
	}
	case 7: {
		struct audiosrv_Logon *r2 = (struct audiosrv_Logon *)r;
		if (DEBUGLEVEL >= 10) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_Logon, NDR_IN, r2);
		}
		dcesrv_audiosrv_Logon(dce_call, mem_ctx, r2);
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_Logon will reply async\n"));
		}
		break;
	}
	case 8: {
		struct audiosrv_Logoff *r2 = (struct audiosrv_Logoff *)r;
		if (DEBUGLEVEL >= 10) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_Logoff, NDR_IN, r2);
		}
		dcesrv_audiosrv_Logoff(dce_call, mem_ctx, r2);
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_Logoff will reply async\n"));
		}
		break;
	}
	case 9: {
		struct audiosrv_RegisterSessionNotificationEvent *r2 = (struct audiosrv_RegisterSessionNotificationEvent *)r;
		if (DEBUGLEVEL >= 10) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_RegisterSessionNotificationEvent, NDR_IN, r2);
		}
		dcesrv_audiosrv_RegisterSessionNotificationEvent(dce_call, mem_ctx, r2);
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_RegisterSessionNotificationEvent will reply async\n"));
		}
		break;
	}
	case 10: {
		struct audiosrv_UnregisterSessionNotificationEvent *r2 = (struct audiosrv_UnregisterSessionNotificationEvent *)r;
		if (DEBUGLEVEL >= 10) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_UnregisterSessionNotificationEvent, NDR_IN, r2);
		}
		dcesrv_audiosrv_UnregisterSessionNotificationEvent(dce_call, mem_ctx, r2);
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_UnregisterSessionNotificationEvent will reply async\n"));
		}
		break;
	}
	case 11: {
		struct audiosrv_SessionConnectState *r2 = (struct audiosrv_SessionConnectState *)r;
		if (DEBUGLEVEL >= 10) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_SessionConnectState, NDR_IN, r2);
		}
		dcesrv_audiosrv_SessionConnectState(dce_call, mem_ctx, r2);
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_SessionConnectState will reply async\n"));
		}
		break;
	}
	case 12: {
		struct audiosrv_DriverOpenDrvRegKey *r2 = (struct audiosrv_DriverOpenDrvRegKey *)r;
		if (DEBUGLEVEL >= 10) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_DriverOpenDrvRegKey, NDR_IN, r2);
		}
		dcesrv_audiosrv_DriverOpenDrvRegKey(dce_call, mem_ctx, r2);
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_DriverOpenDrvRegKey will reply async\n"));
		}
		break;
	}
	case 13: {
		struct audiosrv_AdvisePreferredDeviceChange *r2 = (struct audiosrv_AdvisePreferredDeviceChange *)r;
		if (DEBUGLEVEL >= 10) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_AdvisePreferredDeviceChange, NDR_IN, r2);
		}
		dcesrv_audiosrv_AdvisePreferredDeviceChange(dce_call, mem_ctx, r2);
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_AdvisePreferredDeviceChange will reply async\n"));
		}
		break;
	}
	case 14: {
		struct audiosrv_GetPnpInfo *r2 = (struct audiosrv_GetPnpInfo *)r;
		if (DEBUGLEVEL >= 10) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_GetPnpInfo, NDR_IN, r2);
		}
		dcesrv_audiosrv_GetPnpInfo(dce_call, mem_ctx, r2);
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_GetPnpInfo will reply async\n"));
		}
		break;
	}

	default:
		dce_call->fault_code = DCERPC_FAULT_OP_RNG_ERROR;
		break;
	}

	if (dce_call->fault_code != 0) {
		dcerpc_log_packet(dce_call->conn->packet_log_dir, 
		          &ndr_table_audiosrv, opnum, NDR_IN,
				  &dce_call->pkt.u.request.stub_and_verifier);
		return NT_STATUS_NET_WRITE_FAULT;
	}

	return NT_STATUS_OK;
}

static NTSTATUS audiosrv__op_reply(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx, void *r)
{
	uint16_t opnum = dce_call->pkt.u.request.opnum;

	switch (opnum) {
	case 0: {
		struct audiosrv_CreatezoneFactoriesList *r2 = (struct audiosrv_CreatezoneFactoriesList *)r;
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_CreatezoneFactoriesList replied async\n"));
		}
		if (DEBUGLEVEL >= 10 && dce_call->fault_code == 0) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_CreatezoneFactoriesList, NDR_OUT | NDR_SET_VALUES, r2);
		}
		if (dce_call->fault_code != 0) {
			DEBUG(2,("dcerpc_fault %s in audiosrv_CreatezoneFactoriesList\n", dcerpc_errstr(mem_ctx, dce_call->fault_code)));
		}
		break;
	}
	case 1: {
		struct audiosrv_CreateGfxFactoriesList *r2 = (struct audiosrv_CreateGfxFactoriesList *)r;
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_CreateGfxFactoriesList replied async\n"));
		}
		if (DEBUGLEVEL >= 10 && dce_call->fault_code == 0) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_CreateGfxFactoriesList, NDR_OUT | NDR_SET_VALUES, r2);
		}
		if (dce_call->fault_code != 0) {
			DEBUG(2,("dcerpc_fault %s in audiosrv_CreateGfxFactoriesList\n", dcerpc_errstr(mem_ctx, dce_call->fault_code)));
		}
		break;
	}
	case 2: {
		struct audiosrv_CreateGfxList *r2 = (struct audiosrv_CreateGfxList *)r;
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_CreateGfxList replied async\n"));
		}
		if (DEBUGLEVEL >= 10 && dce_call->fault_code == 0) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_CreateGfxList, NDR_OUT | NDR_SET_VALUES, r2);
		}
		if (dce_call->fault_code != 0) {
			DEBUG(2,("dcerpc_fault %s in audiosrv_CreateGfxList\n", dcerpc_errstr(mem_ctx, dce_call->fault_code)));
		}
		break;
	}
	case 3: {
		struct audiosrv_RemoveGfx *r2 = (struct audiosrv_RemoveGfx *)r;
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_RemoveGfx replied async\n"));
		}
		if (DEBUGLEVEL >= 10 && dce_call->fault_code == 0) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_RemoveGfx, NDR_OUT | NDR_SET_VALUES, r2);
		}
		if (dce_call->fault_code != 0) {
			DEBUG(2,("dcerpc_fault %s in audiosrv_RemoveGfx\n", dcerpc_errstr(mem_ctx, dce_call->fault_code)));
		}
		break;
	}
	case 4: {
		struct audiosrv_AddGfx *r2 = (struct audiosrv_AddGfx *)r;
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_AddGfx replied async\n"));
		}
		if (DEBUGLEVEL >= 10 && dce_call->fault_code == 0) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_AddGfx, NDR_OUT | NDR_SET_VALUES, r2);
		}
		if (dce_call->fault_code != 0) {
			DEBUG(2,("dcerpc_fault %s in audiosrv_AddGfx\n", dcerpc_errstr(mem_ctx, dce_call->fault_code)));
		}
		break;
	}
	case 5: {
		struct audiosrv_ModifyGfx *r2 = (struct audiosrv_ModifyGfx *)r;
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_ModifyGfx replied async\n"));
		}
		if (DEBUGLEVEL >= 10 && dce_call->fault_code == 0) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_ModifyGfx, NDR_OUT | NDR_SET_VALUES, r2);
		}
		if (dce_call->fault_code != 0) {
			DEBUG(2,("dcerpc_fault %s in audiosrv_ModifyGfx\n", dcerpc_errstr(mem_ctx, dce_call->fault_code)));
		}
		break;
	}
	case 6: {
		struct audiosrv_OpenGfx *r2 = (struct audiosrv_OpenGfx *)r;
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_OpenGfx replied async\n"));
		}
		if (DEBUGLEVEL >= 10 && dce_call->fault_code == 0) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_OpenGfx, NDR_OUT | NDR_SET_VALUES, r2);
		}
		if (dce_call->fault_code != 0) {
			DEBUG(2,("dcerpc_fault %s in audiosrv_OpenGfx\n", dcerpc_errstr(mem_ctx, dce_call->fault_code)));
		}
		break;
	}
	case 7: {
		struct audiosrv_Logon *r2 = (struct audiosrv_Logon *)r;
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_Logon replied async\n"));
		}
		if (DEBUGLEVEL >= 10 && dce_call->fault_code == 0) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_Logon, NDR_OUT | NDR_SET_VALUES, r2);
		}
		if (dce_call->fault_code != 0) {
			DEBUG(2,("dcerpc_fault %s in audiosrv_Logon\n", dcerpc_errstr(mem_ctx, dce_call->fault_code)));
		}
		break;
	}
	case 8: {
		struct audiosrv_Logoff *r2 = (struct audiosrv_Logoff *)r;
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_Logoff replied async\n"));
		}
		if (DEBUGLEVEL >= 10 && dce_call->fault_code == 0) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_Logoff, NDR_OUT | NDR_SET_VALUES, r2);
		}
		if (dce_call->fault_code != 0) {
			DEBUG(2,("dcerpc_fault %s in audiosrv_Logoff\n", dcerpc_errstr(mem_ctx, dce_call->fault_code)));
		}
		break;
	}
	case 9: {
		struct audiosrv_RegisterSessionNotificationEvent *r2 = (struct audiosrv_RegisterSessionNotificationEvent *)r;
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_RegisterSessionNotificationEvent replied async\n"));
		}
		if (DEBUGLEVEL >= 10 && dce_call->fault_code == 0) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_RegisterSessionNotificationEvent, NDR_OUT | NDR_SET_VALUES, r2);
		}
		if (dce_call->fault_code != 0) {
			DEBUG(2,("dcerpc_fault %s in audiosrv_RegisterSessionNotificationEvent\n", dcerpc_errstr(mem_ctx, dce_call->fault_code)));
		}
		break;
	}
	case 10: {
		struct audiosrv_UnregisterSessionNotificationEvent *r2 = (struct audiosrv_UnregisterSessionNotificationEvent *)r;
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_UnregisterSessionNotificationEvent replied async\n"));
		}
		if (DEBUGLEVEL >= 10 && dce_call->fault_code == 0) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_UnregisterSessionNotificationEvent, NDR_OUT | NDR_SET_VALUES, r2);
		}
		if (dce_call->fault_code != 0) {
			DEBUG(2,("dcerpc_fault %s in audiosrv_UnregisterSessionNotificationEvent\n", dcerpc_errstr(mem_ctx, dce_call->fault_code)));
		}
		break;
	}
	case 11: {
		struct audiosrv_SessionConnectState *r2 = (struct audiosrv_SessionConnectState *)r;
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_SessionConnectState replied async\n"));
		}
		if (DEBUGLEVEL >= 10 && dce_call->fault_code == 0) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_SessionConnectState, NDR_OUT | NDR_SET_VALUES, r2);
		}
		if (dce_call->fault_code != 0) {
			DEBUG(2,("dcerpc_fault %s in audiosrv_SessionConnectState\n", dcerpc_errstr(mem_ctx, dce_call->fault_code)));
		}
		break;
	}
	case 12: {
		struct audiosrv_DriverOpenDrvRegKey *r2 = (struct audiosrv_DriverOpenDrvRegKey *)r;
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_DriverOpenDrvRegKey replied async\n"));
		}
		if (DEBUGLEVEL >= 10 && dce_call->fault_code == 0) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_DriverOpenDrvRegKey, NDR_OUT | NDR_SET_VALUES, r2);
		}
		if (dce_call->fault_code != 0) {
			DEBUG(2,("dcerpc_fault %s in audiosrv_DriverOpenDrvRegKey\n", dcerpc_errstr(mem_ctx, dce_call->fault_code)));
		}
		break;
	}
	case 13: {
		struct audiosrv_AdvisePreferredDeviceChange *r2 = (struct audiosrv_AdvisePreferredDeviceChange *)r;
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_AdvisePreferredDeviceChange replied async\n"));
		}
		if (DEBUGLEVEL >= 10 && dce_call->fault_code == 0) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_AdvisePreferredDeviceChange, NDR_OUT | NDR_SET_VALUES, r2);
		}
		if (dce_call->fault_code != 0) {
			DEBUG(2,("dcerpc_fault %s in audiosrv_AdvisePreferredDeviceChange\n", dcerpc_errstr(mem_ctx, dce_call->fault_code)));
		}
		break;
	}
	case 14: {
		struct audiosrv_GetPnpInfo *r2 = (struct audiosrv_GetPnpInfo *)r;
		if (dce_call->state_flags & DCESRV_CALL_STATE_FLAG_ASYNC) {
			DEBUG(5,("function audiosrv_GetPnpInfo replied async\n"));
		}
		if (DEBUGLEVEL >= 10 && dce_call->fault_code == 0) {
			NDR_PRINT_FUNCTION_DEBUG(audiosrv_GetPnpInfo, NDR_OUT | NDR_SET_VALUES, r2);
		}
		if (dce_call->fault_code != 0) {
			DEBUG(2,("dcerpc_fault %s in audiosrv_GetPnpInfo\n", dcerpc_errstr(mem_ctx, dce_call->fault_code)));
		}
		break;
	}

	default:
		dce_call->fault_code = DCERPC_FAULT_OP_RNG_ERROR;
		break;
	}

	if (dce_call->fault_code != 0) {
		dcerpc_log_packet(dce_call->conn->packet_log_dir,
		          &ndr_table_audiosrv, opnum, NDR_IN,
				  &dce_call->pkt.u.request.stub_and_verifier);
		return NT_STATUS_NET_WRITE_FAULT;
	}

	return NT_STATUS_OK;
}

static NTSTATUS audiosrv__op_ndr_push(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx, struct ndr_push *push, const void *r)
{
	enum ndr_err_code ndr_err;
	uint16_t opnum = dce_call->pkt.u.request.opnum;

	ndr_err = ndr_table_audiosrv.calls[opnum].ndr_push(push, NDR_OUT, r);
	if (!NDR_ERR_CODE_IS_SUCCESS(ndr_err)) {
		dce_call->fault_code = DCERPC_FAULT_NDR;
		return NT_STATUS_NET_WRITE_FAULT;
	}

	return NT_STATUS_OK;
}

const struct dcesrv_interface dcesrv_audiosrv_interface = {
	.name		= "audiosrv",
	.syntax_id  = {{0x0a74ef1c,0x41a4,0x4e06,{0x83,0xae},{0xdc,0x74,0xfb,0x1c,0xdd,0x53}},1.0},
	.bind		= audiosrv__op_bind,
	.unbind		= audiosrv__op_unbind,
	.ndr_pull	= audiosrv__op_ndr_pull,
	.dispatch	= audiosrv__op_dispatch,
	.reply		= audiosrv__op_reply,
	.ndr_push	= audiosrv__op_ndr_push
};


static NTSTATUS audiosrv__op_init_server(struct dcesrv_context *dce_ctx, const struct dcesrv_endpoint_server *ep_server)
{
	int i;

	for (i=0;i<ndr_table_audiosrv.endpoints->count;i++) {
		NTSTATUS ret;
		const char *name = ndr_table_audiosrv.endpoints->names[i];

		ret = dcesrv_interface_register(dce_ctx, name, &dcesrv_audiosrv_interface, NULL);
		if (!NT_STATUS_IS_OK(ret)) {
			DEBUG(1,("audiosrv_op_init_server: failed to register endpoint '%s'\n",name));
			return ret;
		}
	}

	return NT_STATUS_OK;
}

static bool audiosrv__op_interface_by_uuid(struct dcesrv_interface *iface, const struct GUID *uuid, uint32_t if_version)
{
	if (dcesrv_audiosrv_interface.syntax_id.if_version == if_version &&
		GUID_equal(&dcesrv_audiosrv_interface.syntax_id.uuid, uuid)) {
		memcpy(iface,&dcesrv_audiosrv_interface, sizeof(*iface));
		return true;
	}

	return false;
}

static bool audiosrv__op_interface_by_name(struct dcesrv_interface *iface, const char *name)
{
	if (strcmp(dcesrv_audiosrv_interface.name, name)==0) {
		memcpy(iface, &dcesrv_audiosrv_interface, sizeof(*iface));
		return true;
	}

	return false;
}

NTSTATUS dcerpc_server_audiosrv_init(void)
{
	NTSTATUS ret;
	struct dcesrv_endpoint_server ep_server;

	/* fill in our name */
	ep_server.name = "audiosrv";

	/* fill in all the operations */
	ep_server.init_server = audiosrv__op_init_server;

	ep_server.interface_by_uuid = audiosrv__op_interface_by_uuid;
	ep_server.interface_by_name = audiosrv__op_interface_by_name;

	/* register ourselves with the DCERPC subsystem. */
	ret = dcerpc_register_ep_server(&ep_server);

	if (!NT_STATUS_IS_OK(ret)) {
		DEBUG(0,("Failed to register 'audiosrv' endpoint server!\n"));
		return ret;
	}

	return ret;
}
