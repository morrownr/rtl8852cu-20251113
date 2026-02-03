/*
 * This module is designed to collect internal diagnostic information.
 *
 *	Author: Cosa
 *	History: Created at 2023/02/03
 */

#ifndef _PHL_DIAGNOSE_H_
#define _PHL_DIAGNOSE_H_

#define MAX_PHL_DIAG_MSG_LEN 1024
#define INVALID_SUBMODULE_DIAG_EVT 0xff

enum rtw_phl_diag_evt_level {
	PHL_DIAG_LVL_FATAL = 0x0, /* unrecoverable error */
	PHL_DIAG_LVL_CRITICAL = 0x1, /* severe error events */
	PHL_DIAG_LVL_ERROR = 0x2, /* non-severe error events */
	PHL_DIAG_LVL_WARNING = 0x3, /* warning events */
	PHL_DIAG_LVL_IMPORTANT = 0x4, /* important information events */
	PHL_DIAG_LVL_DEBUG = 0x5, /* debug information events */
	PHL_DIAG_LVL_MAX
};

enum rtw_phl_diag_evt_type {
	PHL_DIAG_EVT_MAC = 0,
	PHL_DIAG_EVT_BB,
	PHL_DIAG_EVT_RF,
	PHL_DIAG_EVT_BTC,
	PHL_DIAG_EVT_PS_FAIL,
	PHL_DIAG_EVT_SER,
	PHL_DIAG_EVT_WOW,
	PHL_DIAG_EVT_MCC,
	PHL_DIAG_EVT_RFCR_CHK,
	PHL_DIAG_EVT_TID_RX,
	PHL_DIAG_EVT_MAX
};
/* backward compatibility */
#define PHL_DIAG_EVT_LEAVE_PS_FAIL PHL_DIAG_EVT_PS_FAIL

enum rtw_phl_diag_mcc_err_type {
	PHL_DIAG_MCC_ERR_UNDEF = 0,
	PHL_DIAG_MCC_ERR_FW_DIS_FAIL = 1,
	PHL_DIAG_MCC_ERR_FW_EN_FAIL = 2,
	PHL_DIAG_MCC_ERR_MAX = 0xFF
};

enum rtw_phl_diag_bb_evt_type {
	PHL_DIAG_BB_EVT_UNDEF = 0,
	PHL_DIAG_BB_EVT_FA_CNT = 1,
	PHL_DIAG_BB_EVT_DIG = 2,
	PHL_DIAG_BB_EVT_EDCCA = 3,
	PHL_DIAG_BB_EVT_MAX = 0xFF
};

enum rtw_phl_rfk_err_type {
	PHL_RFK_ERR_IQK = BIT(0),
	PHL_RFK_ERR_DPK = BIT(1),
	PHL_RFK_ERR_DACK = BIT(2),
	PHL_RFK_ERR_RXDCK = BIT(3),
	PHL_RFK_ERR_TXGAPK = BIT(4),
	PHL_RFK_ERR_TSSI = BIT(5),
};

enum rtw_phl_rfcr_err_type {
	PHL_RFCR_ERR_MODE = BIT(0),
	PHL_RFCR_ERR_CH = BIT(1),
	PHL_RFCR_ERR_HWSI = BIT(2),
	PHL_RFCR_ERR_RADIO = BIT(3),
};

enum rtw_phl_diag_tid_rx_evt_type {
	PHL_DIAG_TID_RX_DROP_OUT_OF_DATE = 0,
	PHL_DIAG_TID_RX_DROP_ALREADY_STORED = 1,
	PHL_DIAG_TID_RX_DROP_IV_REPLAY = 2,
	PHL_DIAG_TID_RX_DROP_OUT_OF_WINDOW = 3
};

enum rtw_phl_diag_ser_type {
	PHL_DIAG_SER_L1,
	PHL_DIAG_SER_L2,
	PHL_DIAG_SER_UNKNOWN,
};

enum rtw_phl_diag_ps_mode {
	PHL_DIAG_PS_LPS,
	PHL_DIAG_PS_IPS,
	PHL_DIAG_PS_UNKNOWN,
};

enum rtw_phl_diag_ps_op {
	PHL_DIAG_PS_OP_ENTER,
	PHL_DIAG_PS_OP_LEAVE,
	PHL_DIAG_PS_OP_UNKNOWN,
};

enum rtw_phl_diag_pwr_lvl {
	PHL_DIAG_PWR_LVL_PWROFF,
	PHL_DIAG_PWR_LVL_PWR_GATED,
	PHL_DIAG_PWR_LVL_CLK_GATED,
	PHL_DIAG_PWR_LVL_RF_OFF,
	PHL_DIAG_PWR_LVL_PWR_ON,
	PHL_DIAG_PWR_LVL_UNKNOWN
};

enum rtw_phl_diag_mcc_tdmra_mode {
	PHL_DIAG_MCC_TDMRA_MODE_NONE,
	PHL_DIAG_MCC_TDMRA_MODE_AP_CLIENT,
	PHL_DIAG_MCC_TDMRA_MODE_2CLIENTS,
	PHL_DIAG_MCC_TDMRA_MODE_AP,
	PHL_DIAG_MCC_TDMRA_MODE_UNKNOWN
};

enum rtw_phl_bb_dbg_type {
	PHL_BB_PMAC = BIT(0),
	PHL_BB_UTILITY = BIT(1),
};

/* version control of phl diagnose event */
struct rtw_phl_diag_bb_stat_v1 {
	u8 valid;
	u16 rx_util;
	u16 rx_avg_phy_rate;
	u16 rx_rate_plur;
	u16 tx_rate;
	u8 evm_1ss;
	u8 evm_min;
	u8 evm_max;
	u8 snr;
	u32 cck_mac_txen;
	u32 cck_phy_txon;
	u32 ofdm_mac_txen;
	u32 ofdm_phy_txon;
	u32 cck_cca;
	u32 ofdm_cca;
	u32 cck_fa;
	u32 ofdm_fa;
};

struct diag_ser_content_v1 {
	u8 diag_ser_type;
}; /* named rtw_phl_diag_ser_content_v2 for next version */

/* deprecated */
struct diag_leave_ps_fail_content_v1 {
	u8 diag_ps_mode;
};

/* rename and update from "struct diag_leave_ps_fail_content_v1" */
struct diag_ps_fail_content_v2 {
	u8 diag_ps_mode;
	u8 diag_pwr_lvl;
	u8 diag_ps_op;
	u32 diag_u_proto_cfg;
	u8 diag_u_pwr_cfg;
}; /* named rtw_phl_diag_ps_fail_v3 for next version */

/* wow */
enum rtw_phl_diag_wow_evt {
	PHL_DIAG_WOW_UNEXPECTED_PWR_STATE = BIT(0),
	PHL_DIAG_WOW_INIT_CFG_FAIL = BIT(1),
	PHL_DIAG_WOW_DEINIT_CFG_FAIL = BIT(2),
	PHL_DIAG_WOW_WAKE_RSN_REINIT = BIT(3)
};

enum rtw_phl_diag_wow_op_mode {
	PHL_DIAG_WOW_OP_PWR_DOWN,
	PHL_DIAG_WOW_OP_DISCONNECT_STBY,
	PHL_DIAG_WOW_OP_CONNECT_STBY,
	PHL_DIAG_WOW_OP_UNKNOWN
};

enum rtw_phl_diag_mac_pwr_state {
	PHL_DIAG_MAC_PWR_OFF,
	PHL_DIAG_MAC_PWR_ON,
	PHL_DIAG_MAC_PWR_LPS,
	PHL_DIAG_MAC_PWR_UNKNOWN
};

enum rtw_phl_diag_wow_cfg_step {
	/* suspend */
	PHL_DIAG_WOW_INIT_PRECONFIG = BIT(0),
	PHL_DIAG_WOW_INIT = BIT(1),
	PHL_DIAG_WOW_FUNC_EN = BIT(2),
	PHL_DIAG_WOW_FUNC_START = BIT(3),
	PHL_DIAG_WOW_INIT_POSTCONFIG = BIT(4),
	/* resume */
	PHL_DIAG_WOW_PHL_START = BIT(5),
	PHL_DIAG_WOW_GET_PWR_STATE = BIT(6),
	PHL_DIAG_WOW_HANDLE_WAKE_RSN = BIT(7),
	PHL_DIAG_WOW_MODULE_START = BIT(8),
	PHL_DIAG_WOW_HANDLE_AOAC_RPT_PHASE0 = BIT(9),
	PHL_DIAG_WOW_HANDLE_AOAC_RPT_PHASE1 = BIT(10),
	PHL_DIAG_WOW_FUNC_DIS = BIT(11),
	PHL_DIAG_WOW_FUNC_STOP = BIT(12),
	PHL_DIAG_WOW_DEINIT = BIT(13),
	/* both */
	PHL_DIAG_WOW_PS_PWR_CFG = BIT(14),
	PHL_DIAG_WOW_SER_CTRL = BIT(15),
	PHL_DIAG_WOW_SET_WOWLAN = BIT(16),
	PHL_DIAG_WOW_CFG_WOW_SLEEP = BIT(17),
	PHL_DIAG_WOW_PS_PROTO_CFG = BIT(18),
	PHL_DIAG_WOW_PPDU_STS_CFG = BIT(19),
	PHL_DIAG_WOW_DBG_DUMP = BIT(20)
};

struct diag_phl_wow_content_v1 {
	u8 diag_wow_evt; /* enum rtw_phl_diag_wow_evt */
	u8 diag_wake_rsn; /* raw data */
	u8 diag_wow_op_mode; /* enum rtw_phl_diag_wow_op_mode */
	u8 diag_mac_pwr_state; /* enum rtw_phl_diag_mac_pwr_state */
	u32 diag_init_err; /* enum rtw_phl_diag_wow_cfg_step */
	u32 diag_deinit_err; /* enum rtw_phl_diag_wow_cfg_step */
};

struct rtw_phl_diag_tid_rx_info_v1 {
	u8 evt; /* enum rtw_phl_diag_tid_rx_evt_type */
	u8 mac_addr[6];
	u16 tid;
	/* drop info */
	u16 cnt; /* drop packet count */
	u32 duration; /* us */
	u16 drop_start_seq;
	u16 drop_recover_seq;
	u16 current_head_seq;
};

struct rtw_phl_diag_mcc_info_v1 {
	u8 err_type; /* enum rtw_phl_diag_mcc_err_type */
	u8 tdmra_mode; /* enum rtw_phl_diag_mcc_tdmra_mode */
};

struct rtw_phl_rfk_err_code_v1 {
	u32 iqk;
	u32 dpk;
	u32 dack;
	u32 rxdck;
	u32 txgapk;
	u32 tssi;
};

struct rtw_phl_diag_hal_buf {
	u8 ver;
	u32 len;
	u8 *buf;
};

struct rtw_phl_diag_rf_info {
	u8 ver;
	u32 len; /* length of raw data */
	u8 *buf; /* raw data, alloc by upper layer */
	struct rtw_phl_rfk_err_code_v1 err_code;
	struct rtw_phl_diag_hal_buf iqk_rpt; /* point to raw data's iqk section */
	struct rtw_phl_diag_hal_buf dpk_rpt; /* point to raw data's dpk section */
	struct rtw_phl_diag_hal_buf rt_rpt; /* point to raw data's rt section */
	struct rtw_phl_diag_hal_buf txgapk_rpt; /* point to raw data's txgapk section */
};

struct rtw_phl_diag_rfcr_v1 {
	u8 is_valid;
	u8 rfcr_err; /* enum rtw_phl_rfcr_err_type */
	u32 rf_0x0[2];
	u32 rf_0x3[2];
	u32 rf_0x5[2];
	u32 rf_0x18[2];
	u32 rf_radio_ver[2];
};

struct rtw_phl_diag_msg {
	enum rtw_phl_diag_evt_type type;
	enum rtw_phl_diag_evt_level level;
	u8 sub_evt; /* submodule event id */
	u8 ver; /* version of debug content */
	u32 len;
	u8 buf[MAX_PHL_DIAG_MSG_LEN];
};

bool phl_send_diag_hub_msg(void *phl, u16 phl_evt, u8 sub_evt,
	u8 level, u8 ver, u8 *buf, u32 len);

enum rtw_phl_status phl_cmd_diag_rfcr_chk(void *phl, u8 *param);

#endif /* _PHL_DIAGNOSE_H_ */

