/******************************************************************************
 *
 * Copyright(c) 2019 - 2020 Realtek Corporation.
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
#ifndef __PHL_SCAN_H__
#define __PHL_SCAN_H__

/* Header file for application to invoke scan service */
#define PHL_SSID_LEN 32

#ifdef CONFIG_PHL_CMD_SCAN

enum _CMD_SCAN_STATE {
	CMD_SCAN_INIT = 0,
	CMD_SCAN_ACQUIRE = BIT0,
	CMD_SCAN_STARTED = BIT1,
	CMD_SCAN_DF_IO = BIT2, /* Disable Function : IO */
	CMD_SCAN_END = BIT3, /* End/ Cancel (Abort isn't included) */
};
/**   Scan Flag Format (1Byte):
 *    7                    4                    0
 *    +--------------------+--------------------+
 *    | Flags of HW_BAND_1 | Flags of HW_BAND_0 |
 *    +--------------------+--------------------+
**/

#define SET_SCAN_FLAG(_status, _band_idx, _flags) \
	((_status) |= ((_flags) << (_band_idx*4)))
#define TEST_SCAN_FLAG(_status, _band_idx, _flags)\
	(((_status) & ((_flags) << (_band_idx*4)))==((_flags) << (_band_idx*4)))
#define TEST_SCAN_FLAGS(_status, _flags)\
	((((_status) & (_flags))==(_flags)) || \
	(((_status) & ((_flags) << 4))==((_flags) << 4)))
#endif


/* scan resources */
struct phl_scan_band_rsc_t {
	struct rtw_wifi_role_t *role; /* scan_timer would use wrole->hw_band*/
	_os_timer scan_timer; /* init in phl_cmd_scan.acquired */
};

struct phl_scan_rsc_t {
	struct phl_scan_band_rsc_t info[HW_BAND_MAX];
};

u8 phl_cmd_chk_ext_act_scan(struct rtw_phl_scan_param *param, u8 sctrl_idx);
u8 phl_cmd_scan_ctrl(struct rtw_phl_scan_param *param, u8 band_idx,
		     struct cmd_scan_ctrl **sctrl);
enum rtw_phl_status phl_scan_rsc_init(struct phl_info_t *phl_info);
void phl_scan_rsc_deinit(struct phl_info_t *phl_info);
#ifdef CONFIG_PHL_SCANOFLD
void phl_cmd_scanofld_end(void *drv, void *param, u8 band_idx);
enum phl_mdl_ret_code
phl_cmd_scanofld_hdl_internal_evt(void *dispr, void *priv, void *msg);
#endif
#endif /* __PHL_SCAN_H__ */

