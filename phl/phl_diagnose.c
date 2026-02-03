/*
 * This module is designed to collect internal diagnostic information.
 *
 *	Author: Cosa
 *	History: Created at 2023/02/03
 */
#define _PHL_DIAGNOSE_C_
#include "phl_headers.h"

#ifdef CONFIG_PHL_DIAGNOSE

static void _diag_evt_done(void* priv, struct phl_msg* msg)
{
	struct phl_info_t *phl_info = (struct phl_info_t *)priv;

	if (msg->inbuf && msg->inlen) {
		_os_kmem_free(phl_to_drvpriv(phl_info),
			msg->inbuf, msg->inlen);
	}
}

bool phl_send_diag_hub_msg(void *phl, u16 phl_evt, u8 sub_evt,
	u8 level, u8 ver, u8 *buf, u32 len)
{
	struct phl_msg msg = {0};
	struct phl_msg_attribute attr = {0};
	struct rtw_phl_diag_msg *dmsg = NULL;
	struct phl_info_t *phl_info = (struct phl_info_t *)phl;
	void *d = NULL;

	if (!phl_info || !buf)
		return false;

	if ((phl_evt >= PHL_DIAG_EVT_MAX) ||(level >= PHL_DIAG_LVL_MAX) ||
	    (len > MAX_PHL_DIAG_MSG_LEN) || !phl_info)  {
		return false;
	}

	d = phl_to_drvpriv(phl_info);
	if (!d)
		return false;

	dmsg = (struct rtw_phl_diag_msg *)_os_kmem_alloc(
			d, sizeof(struct rtw_phl_diag_msg));
	if (!dmsg)
		return false;

	SET_MSG_MDL_ID_FIELD(msg.msg_id, PHL_MDL_GENERAL);
	SET_MSG_EVT_ID_FIELD(msg.msg_id, MSG_EVT_DIAGNOSTIC);

	dmsg->type = phl_evt;
	dmsg->level = level;
	if (phl_evt == PHL_DIAG_EVT_MAC || phl_evt == PHL_DIAG_EVT_BB ||
	    phl_evt == PHL_DIAG_EVT_RF) {
		dmsg->sub_evt = sub_evt;
	} else {
		dmsg->sub_evt = INVALID_SUBMODULE_DIAG_EVT;
	}
	dmsg->ver = ver;
	dmsg->len = len;
	_os_mem_cpy(d, dmsg->buf, buf, len);

	msg.inbuf = (u8 *)dmsg;
	msg.inlen = sizeof(struct rtw_phl_diag_msg);
	attr.completion.completion = _diag_evt_done;
	attr.completion.priv = phl_info;

	if (phl_msg_hub_send(phl_info, &attr, &msg) != RTW_PHL_STATUS_SUCCESS) {
		_os_kmem_free(d, dmsg, sizeof(struct rtw_phl_diag_msg));
		return false;
	} else {
		return true;
	}
}


bool rtw_phl_send_diag_hub_msg(struct rtw_phl_com_t *phl_com,
		u16 phl_evt, u8 sub_evt, u8 level, u8 ver, u8 *buf, u32 len)
{
	struct phl_info_t *phl = NULL;

	if (!phl_com || !buf)
		return false;

	phl = phl_com->phl_priv;

	return phl_send_diag_hub_msg(phl, phl_evt, sub_evt, level, ver, buf, len);
}

bool rtw_phl_query_rf_diag_err_code(void *phl, u32 *err_code)
{
	struct phl_info_t *phl_info = (struct phl_info_t *)phl;

	if (!phl_info || !err_code)
		return false;

	if (RTW_HAL_STATUS_SUCCESS ==
		rtw_hal_rf_query_diag_err_code(phl_info->hal, err_code))
		return true;
	else
		return false;
}

bool rtw_phl_query_rf_diag_info_len(u32 *len)
{
	if (!len)
		return false;

	if (RTW_HAL_STATUS_SUCCESS ==
		rtw_hal_rf_query_diag_info_len(len))
		return true;
	else
		return false;
}

bool rtw_phl_query_bb_diag_info_len_ver(u32 *len, u8 *ver, u8 type)
{
	if (!len || !ver)
		return false;

	if (RTW_HAL_STATUS_SUCCESS ==
		rtw_hal_bb_query_diag_info_len_ver(len, ver, type))
		return true;
	else
		return false;
}

bool rtw_phl_query_rf_diag_info(void *phl,
	struct rtw_phl_diag_rf_info *info)
{
	struct phl_info_t *phl_info = (struct phl_info_t *)phl;

	if (!phl_info || !info)
		return false;

	if (RTW_HAL_STATUS_SUCCESS ==
		rtw_hal_rf_query_diag_info(phl_info->hal, info))
		return true;
	else
		return false;
}

static void _diag_cmd_done(
	void *drv_priv, u8 *cmd, u32 cmd_len,
	enum rtw_phl_status status)
{
	if (cmd) {
		_os_kmem_free(drv_priv, cmd, cmd_len);
		PHL_INFO("%s...\n", __func__);
	}
}

#define PHL_RF_DIAG_RFCR_CUR_VER 1
enum rtw_phl_status
phl_cmd_diag_rfcr_chk(void *phl, u8 *param)
{
	struct phl_info_t *phl_info = NULL;
	struct rtw_phl_diag_rfcr_v1 output = {0};
	enum rtw_phl_status sts = RTW_PHL_STATUS_FAILURE;
	u8 ver = 0;
	u8 lvl = PHL_DIAG_LVL_DEBUG;

	if (!phl || !param) {
		PHL_ERR("%s fail, param is null\n", __func__);
		return sts;
	}
	phl_info = (struct phl_info_t *)phl;
	ver = *param;

	if (ver != PHL_RF_DIAG_RFCR_CUR_VER) {
		PHL_ERR("%s fail, mismatch ver(%d, tgt %d)\n",
			__func__, ver, PHL_RF_DIAG_RFCR_CUR_VER);
		return sts;
	}

	if (RTW_HAL_STATUS_SUCCESS ==
		rtw_hal_rf_query_diag_rfcr(phl_info->hal, (u8 *)&output, ver)) {
		/* query success */
		sts = RTW_PHL_STATUS_SUCCESS;
		/* result valid & err detected */
		if (output.is_valid && output.rfcr_err)
			lvl = PHL_DIAG_LVL_WARNING;
		/* send msg to core layer */
		phl_send_diag_hub_msg(phl, PHL_DIAG_EVT_RFCR_CHK, 0,
			lvl, ver, (u8 *)&output, sizeof(struct rtw_phl_diag_rfcr_v1));
	}

	return sts;
}

enum rtw_phl_status
rtw_phl_cmd_diag_rfcr_chk(void *phl,
	u8 ver, enum phl_cmd_type cmd_type, u32 cmd_timeout)
{
#if 0
	struct phl_info_t *phl_info = (struct phl_info_t *)phl;
	enum rtw_phl_status sts = RTW_PHL_STATUS_FAILURE;
	u8 *cmd_param = NULL;
	u32 cmd_param_len = 0;

	if (!phl) {
		PHL_ERR("%s fail, param is null\n", __func__);
		return sts;
	}

	if (cmd_type == PHL_CMD_DIRECTLY)
		return phl_cmd_diag_rfcr_chk(phl, &ver);

	cmd_param_len = sizeof(u8);
	cmd_param = _os_kmem_alloc(phl_to_drvpriv(phl_info), cmd_param_len);
	if (cmd_param == NULL) {
		PHL_ERR("%s: alloc cmd_param failed!\n", __func__);
		return sts;
	} else {
		_os_mem_cpy(phl_to_drvpriv(phl_info), cmd_param,
			&ver, cmd_param_len);
	}

	sts = phl_cmd_enqueue(phl,
			HW_BAND_0,
			MSG_EVT_DIAG_RFCR_CHK,
			(u8 *)cmd_param, cmd_param_len,
			_diag_cmd_done,
			cmd_type, cmd_timeout);

	if (is_cmd_failure(sts)) {
		/* Send cmd success, but wait cmd fail*/
		sts = RTW_PHL_STATUS_FAILURE;
	} else if (sts != RTW_PHL_STATUS_SUCCESS) {
		/* Send cmd fail */
		_os_kmem_free(phl_to_drvpriv(phl_info), cmd_param, cmd_param_len);
		sts = RTW_PHL_STATUS_FAILURE;
	}

	return sts;
#endif
	return RTW_PHL_STATUS_FAILURE;
}

enum rtw_phl_status rtw_phl_query_bb_diag_info(void *phl,
		struct rtw_wifi_role_link_t *rlink, u8 *bb_comp_buf,
		u32 len, enum rtw_phl_bb_dbg_type type)
{
	struct phl_info_t *phl_info = (struct phl_info_t *)phl;
	void *d = NULL;
	enum rtw_phl_status pstatus = RTW_PHL_STATUS_SUCCESS;

	if (!phl_info || !rlink || !bb_comp_buf)
		return RTW_PHL_STATUS_FAILURE;

	d = phl_to_drvpriv(phl_info);
	if (!d) {
		PHL_WARN("rtw_phl_query_bb_diag_info(): NULL D\n");
		return RTW_PHL_STATUS_FAILURE;
	}

	PHL_WARN("rtw_phl_query_bb_diag_info(): rlink hw_band %d\n", rlink->hw_band);
	if (type & PHL_BB_PMAC) {
		if (RTW_HAL_STATUS_SUCCESS != rtw_hal_get_pmac_info(
				phl_info->hal, rlink->hw_band, bb_comp_buf, len)) {
			pstatus	= RTW_PHL_STATUS_FAILURE;
			PHL_WARN("rtw_phl_query_bb_diag_info(): get pmac failure\n");
		}
	} else if (type & PHL_BB_UTILITY) {
		if (RTW_HAL_STATUS_SUCCESS != rtw_hal_get_utility_info(
				phl_info->hal, rlink->hw_band, bb_comp_buf, len)) {
			pstatus	= RTW_PHL_STATUS_FAILURE;
			PHL_WARN("rtw_phl_query_bb_diag_info(): get utility failure\n");
		}
	} else {
		pstatus = RTW_PHL_STATUS_FAILURE;
		PHL_WARN("rtw_phl_query_bb_diag_info(): unkonw query type\n");
	}

	return pstatus;
}

void rtw_phl_set_bb_auto_dbg_comp(void *phl)
{
	struct phl_info_t *phl_info = NULL;

	if (!phl)
		return;
	phl_info = (struct phl_info_t *)phl;

	rtw_hal_bb_auto_debug_en_phy_pmac(phl_info->hal, true);
	rtw_hal_bb_auto_debug_en_phy_util(phl_info->hal, true);
}

enum rtw_phl_status rtw_phl_parse_bb_diag_info(void *phl,
	struct rtw_phl_diag_bb_stat_v1 *stat, u8 *pmac_buf, u8 *util_buf)
{
	struct phl_info_t *phl_info = NULL;

	if (!phl || !stat || !pmac_buf || !util_buf)
		return RTW_PHL_STATUS_FAILURE;
	phl_info = (struct phl_info_t *)phl;

	if (RTW_HAL_STATUS_SUCCESS ==
		rtw_hal_bb_parse_diag_info(phl_info->hal, stat, pmac_buf, util_buf))
		return RTW_PHL_STATUS_SUCCESS;
	else
		return RTW_PHL_STATUS_FAILURE;
}

#endif

