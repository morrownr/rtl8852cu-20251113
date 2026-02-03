/******************************************************************************
 *
 * Copyright(c) 2019 Realtek Corporation. All rights reserved.
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
 ******************************************************************************/
#ifndef _DBGPKG_AUTO_GEN_H_
#define _DBGPKG_AUTO_GEN_H_

enum mac_ax_dbg_port_isr_module {
	MAC_AX_DBG_PORT_ISR_MOD_COMMON,
	MAC_AX_DBG_PORT_ISR_MOD_SCHEDULER,
	MAC_AX_DBG_PORT_ISR_MOD_PTCL,
	MAC_AX_DBG_PORT_ISR_MOD_DMA,
	MAC_AX_DBG_PORT_ISR_MOD_PHY_INTF,
	MAC_AX_DBG_PORT_ISR_MOD_TXPWR,
	MAC_AX_DBG_PORT_ISR_MOD_RMAC,
	MAC_AX_DBG_PORT_ISR_MOD_TMAC,
	MAC_AX_DBG_PORT_ISR_MOD_RX_IDLETO,
	MAC_AX_DBG_PORT_ISR_MOD_TX_IDLETO,
	MAC_AX_DBG_PORT_ISR_MOD_RESP_PKTCTL,
	MAC_AX_DBG_PORT_ISR_MOD_CMAC_FW,
	MAC_AX_DBG_PORT_ISR_MOD_DISPATCHER,
	MAC_AX_DBG_PORT_ISR_MOD_P_AXIDMA,
	MAC_AX_DBG_PORT_ISR_MOD_H_AXIDMA,
	MAC_AX_DBG_PORT_ISR_MOD_MPDU_PROCESSOR,
	MAC_AX_DBG_PORT_ISR_MOD_PKTIN,
	MAC_AX_DBG_PORT_ISR_MOD_STA_SCH,
	MAC_AX_DBG_PORT_ISR_MOD_USB,
	MAC_AX_DBG_PORT_ISR_MOD_SDIO,
	MAC_AX_DBG_PORT_ISR_MOD_BTCOEX,
	MAC_AX_DBG_PORT_ISR_MOD_WDEDLE,
	MAC_AX_DBG_PORT_ISR_MOD_PLEDLE,
	MAC_AX_DBG_PORT_ISR_MOD_TXPKTCTRL,
	MAC_AX_DBG_PORT_ISR_MOD_BBRPT,
	MAC_AX_DBG_PORT_ISR_MOD_CMACDMA,
	MAC_AX_DBG_PORT_ISR_MOD_WSEC,
	MAC_AX_DBG_PORT_ISR_MOD_WDRLS,
	MAC_AX_DBG_PORT_ISR_MOD_USBTOP,
	MAC_AX_DBG_PORT_ISR_MOD_USB3MAC,
	MAC_AX_DBG_PORT_ISR_MOD_HCITRX_BUF,
	MAC_AX_DBG_PORT_ISR_MOD_PCIE,
	MAC_AX_DBG_PORT_ISR_MOD_CMAC_SHARE,
	MAC_AX_DBG_PORT_ISR_MOD_MLO,

	/* keep last */
	MAC_AX_DBG_PORT_ISR_MOD_LAST,
	MAC_AX_DBG_PORT_ISR_MOD_MAX = MAC_AX_DBG_PORT_ISR_MOD_LAST,
	MAC_AX_DBG_PORT_ISR_MOD_INVALID = MAC_AX_DBG_PORT_ISR_MOD_LAST
};

enum mac_ax_dbg_port_reg_type {
	MAC_AX_DBG_PORT_MAC_REG = 0,
	MAC_AX_DBG_PORT_PLTFM_REG = 1,
};

struct mac_ax_dbg_port_sel_info {
	enum mac_ax_dbg_port_reg_type reg_type;
	u32 sel_addr;
	u32 sel_byte;
	u32 sel_sh;
	u32 sel_msk;
	u32 srt;
	u32 end;
	u32 inc_num;
};

struct mac_ax_dbg_port_rd_info {
	enum mac_ax_dbg_port_reg_type reg_type;
	u32 rd_addr;
	u32 rd_byte;
	u32 rd_sh;
	u32 rd_msk;
};

struct mac_ax_dbg_port_dump_info {
	struct mac_ax_dbg_port_sel_info *sel_info;
	struct mac_ax_dbg_port_rd_info *rd_info;
};

#endif /* DBGPKG_AUTO_GEN_H */