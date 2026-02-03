/******************************************************************************
 *
 * Copyright(c) 2019 Realtek Corporation.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 *****************************************************************************/
#define _PHL_CMD_BB_C_
#include "phl_headers.h"

static enum phl_mdl_ret_code _bb_cmd_init(void *phl, void *dispr, void **priv)
{
	PHL_INFO("[BBCCMD], %s(): \n", __func__);

	*priv = phl;
	return MDL_RET_SUCCESS;
}

static void _bb_cmd_deinit(void *dispr, void *priv)
{
	PHL_INFO("[BBCCMD], %s(): \n", __func__);
}

static enum phl_mdl_ret_code _bb_cmd_start(void *dispr, void *priv)
{
	PHL_INFO("[BBCCMD], %s(): \n", __func__);
	return MDL_RET_SUCCESS;
}

static enum phl_mdl_ret_code _bb_cmd_stop(void *dispr, void *priv)
{
	PHL_INFO("[BBCCMD], %s(): \n", __func__);

	return MDL_RET_SUCCESS;
}

static enum phl_mdl_ret_code
_bb_internal_post_msg_hdlr(struct phl_info_t *phl_info,
                           void *dispr,
                           struct phl_msg *msg)
{
	return MDL_RET_IGNORE;
}

static enum phl_mdl_ret_code
_bb_internal_pre_msg_hdlr(struct phl_info_t *phl_info,
                          void *dispr,
                          struct phl_msg *msg)
{
	return MDL_RET_IGNORE;
}

static void _evt_scan_end_post_hdl(struct phl_info_t *phl_info,
                                   struct phl_msg *msg)
{
	enum phl_band_idx band_idx;
	enum scan_rsn rsn = SCAN_RSN_NONE;

	if (!phl_info || !msg)
		return;

	rsn = msg->rsvd[1].value;
	band_idx = msg->band_idx;

	if (rsn == SCAN_RSN_P2P) {
		rtw_hal_notification_ex(phl_info->hal,
		                       MSG_EVT_P2P_SCAN_END,
		                       true,
		                       false, false,
		                       band_idx);
	} else {
		rtw_hal_notification_ex(phl_info->hal,
		                        MSG_EVT_SCAN_END,
		                        true,
		                        false, false,
		                        band_idx);
	}

}

static enum phl_mdl_ret_code
_bb_external_post_msg_hdlr(struct phl_info_t *phl_info, void *dispr,
                           struct phl_msg *msg)
{
	enum phl_mdl_ret_code ret = MDL_RET_IGNORE;
	enum phl_msg_evt_id evt_id = MSG_EVT_NONE;

	evt_id = MSG_EVT_ID_FIELD(msg->msg_id);

	switch(evt_id) {

	case MSG_EVT_SCAN_END:
		_evt_scan_end_post_hdl(phl_info, msg);
		break;
	default:
		break;
	}

	return ret;
}

static void _evt_scan_start_pre_hdl(struct phl_info_t *phl_info,
                                    struct phl_msg *msg)
{

	enum phl_band_idx band_idx;
	enum scan_rsn rsn = SCAN_RSN_NONE;

	if (!phl_info || !msg)
		return;

	band_idx = msg->band_idx;
	rsn = msg->rsvd[1].value;

	if (rsn == SCAN_RSN_P2P) {
		rtw_hal_notification_ex(phl_info->hal,
		                       MSG_EVT_P2P_SCAN_START,
		                       true,
		                       false, false,
		                       band_idx);
	} else {
		rtw_hal_notification_ex(phl_info->hal,
		                        MSG_EVT_SCAN_START,
		                        true,
		                        false, false,
		                        band_idx);
	}
}


static enum phl_mdl_ret_code
_bb_external_pre_msg_hdlr(struct phl_info_t *phl_info,
                          void *dispr,
                          struct phl_msg *msg)
{
	enum phl_mdl_ret_code ret = MDL_RET_IGNORE;
	enum phl_msg_evt_id evt_id = MSG_EVT_NONE;

	evt_id = MSG_EVT_ID_FIELD(msg->msg_id);

	switch(evt_id) {

	case MSG_EVT_SCAN_START:
		_evt_scan_start_pre_hdl(phl_info, msg);
		break;
	default:
		break;
	}

	return ret;
}


static enum phl_mdl_ret_code
_bb_internal_msg_hdlr(struct phl_info_t *phl_info,
                       void *dispr,
                       struct phl_msg *msg)
{
	enum phl_mdl_ret_code ret = MDL_RET_FAIL;

	if (IS_MSG_IN_PRE_PHASE(msg->msg_id))
		ret = _bb_internal_pre_msg_hdlr(phl_info, dispr, msg);
	else
		ret = _bb_internal_post_msg_hdlr(phl_info, dispr, msg);

	return ret;
}

static enum phl_mdl_ret_code
_bb_external_msg_hdlr(struct phl_info_t *phl_info,
                       void *dispr,
                       struct phl_msg *msg)
{
	enum phl_mdl_ret_code ret = MDL_RET_FAIL;

	if (IS_MSG_IN_PRE_PHASE(msg->msg_id))
		ret = _bb_external_pre_msg_hdlr(phl_info, dispr, msg);
	else
		ret = _bb_external_post_msg_hdlr(phl_info, dispr, msg);

	return ret;
}

static enum phl_mdl_ret_code _bb_msg_hdlr(void *dispr, void *priv,
                                          struct phl_msg *msg)
{
	enum phl_mdl_ret_code ret = MDL_RET_IGNORE;
	struct phl_info_t *phl_info = (struct phl_info_t *)priv;

	FUNCIN();

	switch (MSG_MDL_ID_FIELD(msg->msg_id)) {
	case PHL_MDL_BB:
		ret = _bb_internal_msg_hdlr(phl_info, dispr, msg);
		break;
	default:
		ret = _bb_external_msg_hdlr(phl_info, dispr, msg);
		break;
	}

	FUNCOUT();
	return ret;
}

static enum phl_mdl_ret_code _bb_set_info(void *dispr, void *priv,
                                          struct phl_module_op_info *info)
{
	PHL_INFO("[BBCCMD], %s(): \n", __func__);

	return MDL_RET_SUCCESS;
}

static enum phl_mdl_ret_code _bb_query_info(void *dispr, void *priv,
                                            struct phl_module_op_info *info)
{
	PHL_INFO("[BBCCMD], %s(): \n", __func__);

	return MDL_RET_SUCCESS;
}

enum rtw_phl_status phl_register_bb_module(struct phl_info_t *phl_info)
{
	enum rtw_phl_status sts = RTW_PHL_STATUS_FAILURE;
	struct phl_cmd_dispatch_engine *disp_eng = NULL;
	struct phl_bk_module_ops bk_ops = {0};
	u8 i = 0;

	if (!phl_info)
		return RTW_PHL_STATUS_FAILURE;

	disp_eng = &(phl_info->disp_eng);

	PHL_INFO("[BBCMD], %s(): \n", __func__);

	bk_ops.init = _bb_cmd_init;
	bk_ops.deinit = _bb_cmd_deinit;
	bk_ops.start = _bb_cmd_start;
	bk_ops.stop = _bb_cmd_stop;
	bk_ops.msg_hdlr = _bb_msg_hdlr;
	bk_ops.set_info = _bb_set_info;
	bk_ops.query_info = _bb_query_info;

	for (i = 0; i < disp_eng->phy_num; i++) {
		sts = phl_disp_eng_register_module(phl_info, i, PHL_MDL_BB,
		                                   &bk_ops);
		if (RTW_PHL_STATUS_SUCCESS != sts) {
			PHL_TRACE(COMP_PHL_DBG, _PHL_ERR_,
				"%s register PHL_MDL_BB in cmd disp failed :%d\n",
				__func__, i);
			break;
		}
	}
	return sts;
}


