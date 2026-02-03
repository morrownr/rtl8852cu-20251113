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
#include "_usb.h"
#include "../mac_ax.h"
#include "mac_priv.h"

#if MAC_AX_USB_SUPPORT

u32 usb_flush_mode(struct mac_ax_adapter *adapter, u8 mode)
{
	u32 reg, val32;

#if MAC_AX_8852A_SUPPORT
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A)) {
		reg = R_AX_USB_WLAN0_1;
		if (mode == MAC_AX_FUNC_DIS) {
			val32 = PLTFM_REG_R32(reg) & ~B_AX_USBRX_RST & ~B_AX_USBTX_RST;
			PLTFM_REG_W32(reg, val32);
			return MACSUCCESS;
		} else if (mode == MAC_AX_FUNC_EN) {
			val32 = PLTFM_REG_R32(reg) | B_AX_USBRX_RST | B_AX_USBTX_RST;
			PLTFM_REG_W32(reg, val32);
			return MACSUCCESS;
		} else {
			return MACLV1STEPERR;
		}
	}
#endif
#if MAC_AX_8852B_SUPPORT || MAC_AX_8851B_SUPPORT || MAC_AX_8852BT_SUPPORT
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		reg = R_AX_USB_WLAN0_1;
		if (mode == MAC_AX_FUNC_DIS) {
			val32 = PLTFM_REG_R32(reg) & ~B_AX_USBRX_RST & ~B_AX_USBTX_RST;
			PLTFM_REG_W32(reg, val32);
			return MACSUCCESS;
		} else if (mode == MAC_AX_FUNC_EN) {
			val32 = PLTFM_REG_R32(reg) | B_AX_USBRX_RST | B_AX_USBTX_RST;
			PLTFM_REG_W32(reg, val32);
			return MACSUCCESS;
		} else {
			return MACLV1STEPERR;
		}
	}
#endif
#if MAC_AX_8852C_SUPPORT
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C)) {
		reg = R_AX_USB_WLAN0_1_V1;
		if (mode == MAC_AX_FUNC_DIS) {
			val32 = PLTFM_REG_R32(reg) & ~B_AX_USBRX_RST_V1 & ~B_AX_USBTX_RST_V1;
			PLTFM_REG_W32(reg, val32);
			return MACSUCCESS;
		} else if (mode == MAC_AX_FUNC_EN) {
			val32 = PLTFM_REG_R32(reg) | B_AX_USBRX_RST_V1 | B_AX_USBTX_RST_V1;
			PLTFM_REG_W32(reg, val32);
			return MACSUCCESS;
		} else {
			return MACLV1STEPERR;
		}
	}
#endif
#if MAC_AX_8192XB_SUPPORT
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		reg = R_AX_USB_WLAN0_1_V1;
		if (mode == MAC_AX_FUNC_DIS) {
			val32 = PLTFM_REG_R32(reg) & ~B_AX_USBRX_RST_V1 & ~B_AX_USBTX_RST_V1;
			PLTFM_REG_W32(reg, val32);
			return MACSUCCESS;
		} else if (mode == MAC_AX_FUNC_EN) {
			val32 = PLTFM_REG_R32(reg) | B_AX_USBRX_RST_V1 | B_AX_USBTX_RST_V1;
			PLTFM_REG_W32(reg, val32);
			return MACSUCCESS;
		} else {
			return MACLV1STEPERR;
		}
	}
#endif
#if MAC_AX_8851B_SUPPORT
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8851B)) {
		reg = R_AX_USB_WLAN0_1;
		if (mode == MAC_AX_FUNC_DIS) {
			val32 = PLTFM_REG_R32(reg) & ~B_AX_USBRX_RST & ~B_AX_USBTX_RST;
			PLTFM_REG_W32(reg, val32);
			return MACSUCCESS;
		} else if (mode == MAC_AX_FUNC_EN) {
			val32 = PLTFM_REG_R32(reg) | B_AX_USBRX_RST | B_AX_USBTX_RST;
			PLTFM_REG_W32(reg, val32);
			return MACSUCCESS;
		} else {
			return MACLV1STEPERR;
		}
	}
#endif
#if MAC_AX_8852D_SUPPORT
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852D)) {
		reg = R_AX_USB_WLAN0_1_V1;
		if (mode == MAC_AX_FUNC_DIS) {
			val32 = PLTFM_REG_R32(reg) & ~B_AX_USBRX_RST_V1 & ~B_AX_USBTX_RST_V1;
			PLTFM_REG_W32(reg, val32);
			return MACSUCCESS;
		} else if (mode == MAC_AX_FUNC_EN) {
			val32 = PLTFM_REG_R32(reg) | B_AX_USBRX_RST_V1 | B_AX_USBTX_RST_V1;
			PLTFM_REG_W32(reg, val32);
			return MACSUCCESS;
		} else {
			return MACLV1STEPERR;
		}
	}
#endif
#if MAC_AX_8852BT_SUPPORT
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		reg = R_AX_USB_WLAN0_1;
		if (mode == MAC_AX_FUNC_DIS) {
			val32 = PLTFM_REG_R32(reg) & ~B_AX_USBRX_RST & ~B_AX_USBTX_RST;
			PLTFM_REG_W32(reg, val32);
			return MACSUCCESS;
		} else if (mode == MAC_AX_FUNC_EN) {
			val32 = PLTFM_REG_R32(reg) | B_AX_USBRX_RST | B_AX_USBTX_RST;
			PLTFM_REG_W32(reg, val32);
			return MACSUCCESS;
		} else {
			return MACLV1STEPERR;
		}
	}
#endif
	return MACCHIPID;
}

u32 get_usb_mode(struct mac_ax_adapter *adapter)
{
	u32 reg, val32, hs;

#if MAC_AX_8852A_SUPPORT
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A)) {
		reg = R_AX_USB_STATUS;
		val32 = PLTFM_REG_R32(reg) & B_AX_R_USB2_SEL;
		hs = PLTFM_REG_R32(reg) & B_AX_MODE_HS;
		if (val32 == B_AX_R_USB2_SEL)
			val32 = MAC_AX_USB3;
		else if ((val32 != B_AX_R_USB2_SEL) && (hs == B_AX_MODE_HS))
			val32 = MAC_AX_USB2;
		else
			val32 = MAC_AX_USB11;
		return val32;
	}
#endif

#if MAC_AX_8852B_SUPPORT || MAC_AX_8851B_SUPPORT || MAC_AX_8852BT_SUPPORT
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		reg = R_AX_USB_STATUS;
		val32 = PLTFM_REG_R32(reg) & B_AX_R_USB2_SEL;
		hs = PLTFM_REG_R32(reg) & B_AX_MODE_HS;
		if (val32 == B_AX_R_USB2_SEL)
			val32 = MAC_AX_USB3;
		else if ((val32 != B_AX_R_USB2_SEL) && (hs == B_AX_MODE_HS))
			val32 = MAC_AX_USB2;
		else
			val32 = MAC_AX_USB11;
		return val32;
	}
#endif

#if MAC_AX_8852C_SUPPORT
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C)) {
		reg = R_AX_USB_STATUS_V1;
		val32 = PLTFM_REG_R32(reg) & B_AX_R_USB2_SEL_V1;
		hs = PLTFM_REG_R32(reg) & B_AX_MODE_HS_V1;
		if (val32 == B_AX_R_USB2_SEL_V1)
			val32 = MAC_AX_USB3;
		else if ((val32 != B_AX_R_USB2_SEL_V1) && (hs == B_AX_MODE_HS_V1))
			val32 = MAC_AX_USB2;
		else
			val32 = MAC_AX_USB11;
		return val32;
	}
#endif

#if MAC_AX_8192XB_SUPPORT
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB)) {
		reg = R_AX_USB_STATUS_V1;
		val32 = PLTFM_REG_R32(reg) & B_AX_R_USB2_SEL_V1;
		hs = PLTFM_REG_R32(reg) & B_AX_MODE_HS_V1;
		if (val32 == B_AX_R_USB2_SEL_V1)
			val32 = MAC_AX_USB3;
		else if ((val32 != B_AX_R_USB2_SEL_V1) && (hs == B_AX_MODE_HS_V1))
			val32 = MAC_AX_USB2;
		else
			val32 = MAC_AX_USB11;
		return val32;
	}
#endif

#if MAC_AX_8851B_SUPPORT
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8851B)) {
		reg = R_AX_USB_STATUS;
		val32 = PLTFM_REG_R32(reg) & B_AX_R_USB2_SEL;
		hs = PLTFM_REG_R32(reg) & B_AX_MODE_HS;
		if (val32 == B_AX_R_USB2_SEL)
			val32 = MAC_AX_USB3;
		else if ((val32 != B_AX_R_USB2_SEL) && (hs == B_AX_MODE_HS))
			val32 = MAC_AX_USB2;
		else
			val32 = MAC_AX_USB11;
		return val32;
	}
#endif

#if MAC_AX_8852D_SUPPORT
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852D)) {
		reg = R_AX_USB_STATUS_V1;
		val32 = PLTFM_REG_R32(reg) & B_AX_R_USB2_SEL_V1;
		hs = PLTFM_REG_R32(reg) & B_AX_MODE_HS_V1;
		if (val32 == B_AX_R_USB2_SEL_V1)
			val32 = MAC_AX_USB3;
		else if ((val32 != B_AX_R_USB2_SEL_V1) && (hs == B_AX_MODE_HS_V1))
			val32 = MAC_AX_USB2;
		else
			val32 = MAC_AX_USB11;
		return val32;
	}
#endif

#if MAC_AX_8852BT_SUPPORT
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT)) {
		reg = R_AX_USB_STATUS;
		val32 = PLTFM_REG_R32(reg) & B_AX_R_USB2_SEL;
		hs = PLTFM_REG_R32(reg) & B_AX_MODE_HS;
		if (val32 == B_AX_R_USB2_SEL)
			val32 = MAC_AX_USB3;
		else if ((val32 != B_AX_R_USB2_SEL) && (hs == B_AX_MODE_HS))
			val32 = MAC_AX_USB2;
		else
			val32 = MAC_AX_USB11;
		return val32;
	}
#endif
	return MACCHIPID;
}

u32 dbcc_hci_ctrl_usb(struct mac_ax_adapter *adapter,
		      struct mac_ax_dbcc_hci_ctrl *info)
{
	enum mac_ax_func_sw en;
	struct mac_ax_priv_ops *p_ops = adapter_to_priv_ops(adapter);
	struct mac_ax_usb_ep cfg;
	u32 ret, cnt, val32, reg = 0;
	u8 pause, val8;

	if (!info)
		return MACNPTR;

	pause = info->pause;
	en = pause ? MAC_AX_FUNC_EN : MAC_AX_FUNC_DIS;

	if (en) {
		cfg.ep4 = MAC_AX_USB_EP_RELEASE;
		cfg.ep5 = MAC_AX_USB_EP_PAUSE;
		cfg.ep6 = MAC_AX_USB_EP_PAUSE;
		cfg.ep7 = MAC_AX_USB_EP_RELEASE;
		cfg.ep8 = MAC_AX_USB_EP_RELEASE;
		cfg.ep9 = MAC_AX_USB_EP_PAUSE;
		cfg.ep10 = MAC_AX_USB_EP_PAUSE;
		cfg.ep11 = MAC_AX_USB_EP_PAUSE;
		cfg.ep12 = MAC_AX_USB_EP_PAUSE;
	} else {
		cfg.ep4 = MAC_AX_USB_EP_RELEASE;
		cfg.ep5 = MAC_AX_USB_EP_RELEASE;
		cfg.ep6 = MAC_AX_USB_EP_RELEASE;
		cfg.ep7 = MAC_AX_USB_EP_RELEASE;
		cfg.ep8 = MAC_AX_USB_EP_RELEASE;
		cfg.ep9 = MAC_AX_USB_EP_RELEASE;
		cfg.ep10 = MAC_AX_USB_EP_RELEASE;
		cfg.ep11 = MAC_AX_USB_EP_RELEASE;
		cfg.ep12 = MAC_AX_USB_EP_RELEASE;
	}

	ret = p_ops->usb_ep_cfg(adapter, &cfg);
	if (ret != MACSUCCESS) {
		PLTFM_MSG_ERR("dbcc usb_ep_cfg %d fail %d\n", en, ret);
		return ret;
	}

#if MAC_AX_8852A_SUPPORT
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852A))
		reg = R_AX_USB_DEBUG_3;
#endif
#if MAC_AX_8852B_SUPPORT || MAC_AX_8851B_SUPPORT || MAC_AX_8852BT_SUPPORT
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8851B) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852BT))
		reg = R_AX_USB_DEBUG_3;
#endif
#if MAC_AX_8852C_SUPPORT
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C))
		reg = R_AX_USB_DEBUG_3_V1;
#endif
#if MAC_AX_8192XB_SUPPORT
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8192XB))
		reg = R_AX_USB_DEBUG_3_V1;
#endif
#if MAC_AX_8852D_SUPPORT
	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852D))
		reg = R_AX_USB_DEBUG_3_V1;
#endif

	cnt = 2000;
	while (--cnt) {
		val32 = PLTFM_REG_R32(reg);
		PLTFM_REG_W32(reg, val32 | BIT20);
		val8 = GET_FIELD(PLTFM_REG_R32(reg), B_AX_TX_STATE_MACHINE);
		if (val8 == USB_TX_IDLE)
			break;
		PLTFM_DELAY_US(1);
	}
	if (!cnt)
		return MACUSBPAUSEERR;
	return ret;
}

u32 ltr_set_usb(struct mac_ax_adapter *adapter,
		struct mac_ax_pcie_ltr_param *param)
{
	return MACNOTSUP;
}

u32 ctrl_txdma_ch_usb(struct mac_ax_adapter *adapter,
		      struct mac_ax_txdma_ch_map *ch_map)
{
	return MACNOTSUP;
}

u32 clr_idx_all_usb(struct mac_ax_adapter *adapter)
{
	return MACNOTSUP;
}

u32 poll_txdma_ch_idle_usb(struct mac_ax_adapter *adapter,
			   struct mac_ax_txdma_ch_map *ch_map)
{
	return MACNOTSUP;
}

u32 set_pcie_speed_usb(struct mac_ax_adapter *adapter,
		       enum mac_ax_pcie_phy speed)
{
	return MACNOTSUP;
}

u32 get_pcie_speed_usb(struct mac_ax_adapter *adapter,
		       u8 *speed)
{
	return MACNOTSUP;
}

u32 get_pcie_sup_speed_usb(struct mac_ax_adapter *adapter)
{
	return MACNOTSUP;
}

u32 poll_rxdma_ch_idle_usb(struct mac_ax_adapter *adapter,
			   struct mac_ax_rxdma_ch_map *ch_map)
{
	return MACNOTSUP;
}

u32 ctrl_txhci_usb(struct mac_ax_adapter *adapter, enum mac_ax_func_sw en)
{
	struct mac_ax_priv_ops *p_ops = adapter_to_priv_ops(adapter);
	struct mac_ax_usb_ep cfg;
	u32 ret;

	if (en == MAC_AX_FUNC_EN) {
		cfg.ep5 = MAC_AX_USB_EP_RELEASE;
		cfg.ep6 = MAC_AX_USB_EP_RELEASE;
		cfg.ep7 = MAC_AX_USB_EP_RELEASE;
		cfg.ep8 = MAC_AX_USB_EP_RELEASE;
		cfg.ep9 = MAC_AX_USB_EP_RELEASE;
		cfg.ep10 = MAC_AX_USB_EP_RELEASE;
		cfg.ep11 = MAC_AX_USB_EP_RELEASE;
		cfg.ep12 = MAC_AX_USB_EP_RELEASE;
	} else {
		cfg.ep5 = MAC_AX_USB_EP_PAUSE;
		cfg.ep6 = MAC_AX_USB_EP_PAUSE;
		cfg.ep7 = MAC_AX_USB_EP_PAUSE;
		cfg.ep8 = MAC_AX_USB_EP_PAUSE;
		cfg.ep9 = MAC_AX_USB_EP_PAUSE;
		cfg.ep10 = MAC_AX_USB_EP_PAUSE;
		cfg.ep11 = MAC_AX_USB_EP_PAUSE;
		cfg.ep12 = MAC_AX_USB_EP_PAUSE;
	}
	cfg.ep4 = MAC_AX_USB_EP_IGNORE;

	ret = p_ops->usb_ep_cfg(adapter, &cfg);
	if (ret != MACSUCCESS) {
		PLTFM_MSG_ERR("%s: usb_ep_cfg tx %d fail %d\n", __func__, en, ret);
		return ret;
	}
	return MACSUCCESS;
}

u32 ctrl_rxhci_usb(struct mac_ax_adapter *adapter, enum mac_ax_func_sw en)
{
	struct mac_ax_priv_ops *p_ops = adapter_to_priv_ops(adapter);
	struct mac_ax_usb_ep cfg;
	u32 ret;

	if (en == MAC_AX_FUNC_EN) {
		cfg.ep4 = MAC_AX_USB_EP_RELEASE;
	} else {
		cfg.ep4 = MAC_AX_USB_EP_PAUSE;
	}
	cfg.ep5 = MAC_AX_USB_EP_IGNORE;
	cfg.ep6 = MAC_AX_USB_EP_IGNORE;
	cfg.ep7 = MAC_AX_USB_EP_IGNORE;
	cfg.ep8 = MAC_AX_USB_EP_IGNORE;
	cfg.ep9 = MAC_AX_USB_EP_IGNORE;
	cfg.ep10 = MAC_AX_USB_EP_IGNORE;
	cfg.ep11 = MAC_AX_USB_EP_IGNORE;
	cfg.ep12 = MAC_AX_USB_EP_IGNORE;

	ret = p_ops->usb_ep_cfg(adapter, &cfg);
	if (ret != MACSUCCESS) {
		PLTFM_MSG_ERR("%s: usb_ep_cfg rx %d fail %d\n", __func__, en, ret);
		return ret;
	}
	return MACSUCCESS;
}

u32 ctrl_dma_io_usb(struct mac_ax_adapter *adapter, enum mac_ax_func_sw en)
{
	return MACNOTSUP;
}

u32 get_io_stat_usb(struct mac_ax_adapter *adapter,
		    struct mac_ax_io_stat *out_st)
{
	return MACNOTSUP;
}

u32 get_avail_txbd_usb(struct mac_ax_adapter *adapter, u8 ch_idx,
		       u16 *host_idx, u16 *hw_idx, u16 *avail_txbd)
{
	return MACNOTSUP;
}

u32 get_avail_rxbd_usb(struct mac_ax_adapter *adapter, u8 ch_idx,
		       u16 *host_idx, u16 *hw_idx, u16 *avail_rxbd)
{
	return MACNOTSUP;
}

u32 trigger_txdma_usb(struct mac_ax_adapter *adapter,
		      struct tx_base_desc *txbd_ring, u8 ch_idx)
{
	return MACNOTSUP;
}

u32 notify_rxdone_usb(struct mac_ax_adapter *adapter,
		      struct rx_base_desc *rxbd, u8 ch)
{
	return MACNOTSUP;
}

u32 usb_autok_counter_avg(struct mac_ax_adapter *adapter)
{
	return MACSUCCESS;
}

u32 usb_tp_adjust(struct mac_ax_adapter *adapter, struct mac_ax_tp_param tp)
{
	return MACSUCCESS;
}

u32 ctrl_txdma_usb(struct mac_ax_adapter *adapter, u8 opt)
{
	struct mac_ax_priv_ops *p_ops = adapter_to_priv_ops(adapter);
	struct mac_ax_usb_ep cfg;
	u32 ret = MACSUCCESS;

	if (opt == RTW_MAC_CTRL_TXDMA_DIS_ALL) {
		cfg.ep4 = MAC_AX_USB_EP_PAUSE;
		cfg.ep5 = MAC_AX_USB_EP_PAUSE;
		cfg.ep6 = MAC_AX_USB_EP_PAUSE;
		cfg.ep7 = MAC_AX_USB_EP_PAUSE;
		cfg.ep8 = MAC_AX_USB_EP_PAUSE;
		cfg.ep9 = MAC_AX_USB_EP_PAUSE;
		cfg.ep10 = MAC_AX_USB_EP_PAUSE;
		cfg.ep11 = MAC_AX_USB_EP_PAUSE;
		cfg.ep12 = MAC_AX_USB_EP_PAUSE;
	} else if (opt == RTW_MAC_CTRL_TXDMA_H2C2H_ONLY) {
		cfg.ep4 = MAC_AX_USB_EP_RELEASE;
		cfg.ep5 = MAC_AX_USB_EP_PAUSE;
		cfg.ep6 = MAC_AX_USB_EP_PAUSE;
		cfg.ep7 = MAC_AX_USB_EP_RELEASE;
		cfg.ep8 = MAC_AX_USB_EP_PAUSE;
		cfg.ep9 = MAC_AX_USB_EP_PAUSE;
		cfg.ep10 = MAC_AX_USB_EP_PAUSE;
		cfg.ep11 = MAC_AX_USB_EP_PAUSE;
		cfg.ep12 = MAC_AX_USB_EP_PAUSE;
	} else if (opt == RTW_MAC_CTRL_TXDMA_EN_ALL) {
		cfg.ep4 = MAC_AX_USB_EP_RELEASE;
		cfg.ep5 = MAC_AX_USB_EP_RELEASE;
		cfg.ep6 = MAC_AX_USB_EP_RELEASE;
		cfg.ep7 = MAC_AX_USB_EP_RELEASE;
		cfg.ep8 = MAC_AX_USB_EP_RELEASE;
		cfg.ep9 = MAC_AX_USB_EP_RELEASE;
		cfg.ep10 = MAC_AX_USB_EP_RELEASE;
		cfg.ep11 = MAC_AX_USB_EP_RELEASE;
		cfg.ep12 = MAC_AX_USB_EP_RELEASE;
	} else {
		PLTFM_MSG_ERR("%s: unknown option %d\n", __func__, opt);
		return MACNOITEM;
	}

	ret = p_ops->usb_ep_cfg(adapter, &cfg);
	if (ret != MACSUCCESS) {
		PLTFM_MSG_ERR("%s: usb_ep_cfg fail %d\n", __func__, ret);
		return ret;
	}
	return MACSUCCESS;
}

u32 poll_txdma_idle_usb(struct mac_ax_adapter *adapter)
{
	PLTFM_SLEEP_US(USB_TXDMA_IDLE_POLL_TIME);
	return MACSUCCESS;
}

u32 clr_hci_trx_usb(struct mac_ax_adapter *adapter)
{
	u32 ret;

	ret = usb_flush_mode(adapter, MAC_AX_FUNC_EN);
	if (ret) {
		PLTFM_MSG_ERR("%s: usb_flush_mode en fail\n", __func__);
		return ret;
	}

	PLTFM_DELAY_US(USB_FLUSH_WAIT_TIME);

	ret = usb_flush_mode(adapter, MAC_AX_FUNC_DIS);
	if (ret != MACSUCCESS) {
		PLTFM_MSG_ERR("%s: usb_flush_mode dis fail %d\n", __func__, ret);
		return ret;
	}
	return MACSUCCESS;
}

u32 usb_uphy_pll_cfg(struct mac_ax_adapter *adapter,
		     u8 force_keep_en)
{
	struct mac_ax_priv_ops *p_ops = adapter_to_priv_ops(adapter);
	u8 val8;

	if (chk_patch_usb_on_ioh_sw_rst(adapter) == PATCH_DISABLE)
		return MACSUCCESS;

	if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
	    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D)) {
		val8 = (u8)p_ops->read_usb2phy_para(adapter, R_AX_UPHY_SUSPENDM);
		if (force_keep_en)
			val8 |= B_AX_FORCE_SUSPENDM | B_AX_SUSPENDM;
		else
			val8 &= ~(u32)B_AX_FORCE_SUSPENDM & ~(u32)B_AX_SUSPENDM;
		p_ops->write_usb2phy_para(adapter, R_AX_UPHY_SUSPENDM, val8);
		return MACSUCCESS;
	}
	return MACNOTSUP;
}

u32 lv2rst_stop_dma_usb(struct mac_ax_adapter *adapter)
{
	return MACSUCCESS;
}

u32 set_usb_support_ability(struct mac_ax_adapter *adapter, enum usb_support_ability ability)
{
	struct mac_ax_ops *mac_ops = adapter_to_mac_ops(adapter);
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	enum usb_support_ability cur_ability;
	u32 ret;
	u16 val16 = 0;
	u8 shift_byte = 0, B_idx;

	if (ability != FORCEUSB3MODE) {
		PLTFM_MSG_ERR("[ERR] %s: only allow FORCEUSB3MODE for now: %d\n", __func__,
			      ability);
		return MACNOTSUP;
	}

	cur_ability = ops->get_usb_support_ability(adapter);
	if (cur_ability != SWITCHMODE) {
		PLTFM_MSG_ERR("[ERR] %s: currently not SWITCHMODE: %d\n", __func__, cur_ability);
		return MACNOTSUP;
	}

	shift_byte = (B_AX_USB3_USB2_TRANSITION >> 16) ? 2 : 0;
	ret = mac_ops->read_log_efuse(adapter, R_AX_PAD_CTRL2 + shift_byte,
				      sizeof(val16), (u8 *)&val16);
	if (ret != MACSUCCESS) {
		PLTFM_MSG_ERR("[ERR] %s: read efuse fail %d\n", __func__, ret);
		return ret;
	}

	if (val16 == 0xFFFF) {
		PLTFM_MSG_TRACE("[TRACE] %s: %x not burned, use reg val\n", __func__,
				R_AX_PAD_CTRL2 + shift_byte);
		val16 = MAC_REG_R16(R_AX_PAD_CTRL2 + shift_byte);
	}
	if (val16 & (B_AX_USB3_USB2_TRANSITION >> (shift_byte * 8)))
		val16 &= ~(u16)(B_AX_USB3_USB2_TRANSITION >> (shift_byte * 8));
	else {
		PLTFM_MSG_ERR("[ERR] %s: already FORCEUSB3MODE\n", __func__);
		return MACNOTSUP;
	}
	for (B_idx = 0; B_idx < sizeof(val16); B_idx++) {
		ret = mac_ops->write_log_efuse(adapter, R_AX_PAD_CTRL2 + shift_byte + B_idx,
				*(((u8*)&val16) + B_idx));
		if (ret != MACSUCCESS) {
			PLTFM_MSG_ERR("[ERR] %s: chk efuse %x fail %d\n", __func__,
				      R_AX_PAD_CTRL2 + shift_byte + B_idx, ret);
			return ret;
		}
	}
	return MACSUCCESS;
}

u32 get_usb_mode_status(struct mac_ax_adapter *adapter, enum usb_mode_status *status)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 val32 = 0;

	val32 = MAC_REG_R32(R_AX_SYS_CHIPINFO);
	if ((val32 & B_AX_USB2_SEL) == B_AX_USB2_SEL) {
		if ((val32 & B_AX_U3_TERM_DETECT) == B_AX_U3_TERM_DETECT) {
			if ((val32 & B_AX_U3PHY_RST_V1) == B_AX_U3PHY_RST_V1) {
				*status = USB_MODE_U2_SWITCH_FAIL;
			} else {
				*status = USB_MODE_U2_SUPPORT_U2U3;
			}
		} else {
			if ((val32 & B_AX_U3PHY_RST_V1) == B_AX_U3PHY_RST_V1) {
				*status = USB_MODE_U2_ENV_LIMIT;
			} else {
				*status = USB_MODE_U2_PURE_U2;
			}
		}
	} else {
		if ((val32 & B_AX_U3_TERM_DETECT) == B_AX_U3_TERM_DETECT) {
			if ((val32 & B_AX_U3PHY_RST_V1) == B_AX_U3PHY_RST_V1) {
				PLTFM_MSG_ERR("[ERR] %s: invalid status! val %x = %x\n", __func__,
					      R_AX_SYS_CHIPINFO, val32);
				return MACNOITEM;
			} else {
				*status = USB_MODE_U3_SWITCH_SUCCESS;
			}
		} else {
			PLTFM_MSG_ERR("[ERR] %s: invalid status! val %x = %x\n", __func__,
				      R_AX_SYS_CHIPINFO, val32);
			return MACNOITEM;
		}
	}

	return MACSUCCESS;
}

u32 usb_ioh_sw_rst(struct mac_ax_adapter *adapter)
{
	struct mac_ax_intf_ops *ops = adapter_to_intf_ops(adapter);
	u32 val32, cnt;
	if (adapter->env_info.intf == MAC_AX_INTF_USB) {
		if (chk_patch_usb_on_ioh_sw_rst(adapter) == PATCH_DISABLE)
			return MACSUCCESS;
		if (is_chip_id(adapter, MAC_AX_CHIP_ID_8852C) ||
		    is_chip_id(adapter, MAC_AX_CHIP_ID_8852D)) {
			val32 = MAC_REG_R32(R_AX_USB_IO_OFFREG_WDT_V1) |
					    B_AX_ON_IOH_SW_RST_V1;
			MAC_REG_W32(R_AX_USB_IO_OFFREG_WDT_V1, val32);
			cnt = USB_ON_IOH_SW_RST_RETRY_CNT;
			while (--cnt) {
				val32 = MAC_REG_R32(R_AX_USB_IO_OFFREG_WDT_V1);
				if (!(val32 & B_AX_OFF_IOH_RST_STS_V1))
					break;
				PLTFM_DELAY_US(USB_ON_IOH_SW_RST_WAIT_US);
			}
			if (!cnt)
				PLTFM_MSG_ERR("%s: reset off wrapper polling timeout!!\n",
					      __func__);
			return MACSUCCESS;
		}
		PLTFM_MSG_ERR("%s: unexpected IC!!\n", __func__);
	}
	return MACNOTSUP;
}

#endif /* #if MAC_AX_USB_SUPPORT */
