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

#include "ser_8852c.h"
#include "../../type.h"
#if MAC_AX_8852C_SUPPORT

static u32 phy_intf_imr_enable_patch_8852c(struct mac_ax_adapter *adapter, u8 band)
{
	u32 ret, reg;
	u32 msk = 0;

	msk = SET_CLR_WORD(msk, B_AX_PHYINTF_TIMEOUT_THR_V1_MSK, B_AX_PHYINTF_TIMEOUT_THR_V1);
	reg = band == MAC_AX_BAND_0 ?
	      R_AX_PHYINFO_ERR_IMR_V1 : R_AX_PHYINFO_ERR_IMR_V1_C1;
	ret = write_mac_reg_auto_ofld(adapter, reg,
				      msk,
				      0x00070000,
				      IMR_IO_OFLD_NON_FLUSH);
	if (ret)
		PLTFM_MSG_ERR("[ERR]%sIO ofld fail", __func__);

	return ret;
}

static u32 rmac_imr_enable_patch_8852c(struct mac_ax_adapter *adapter, u8 band)
{
#if MAC_AX_USB_SUPPORT
	u32 ret, reg;
	u32 msk = 0;

	if (adapter->env_info.intf == MAC_AX_INTF_USB) {
		if (!chk_patch_snd_fifofull_err(adapter))
			return MACSUCCESS;

		if (get_usb_mode(adapter) == MAC_AX_USB2) {
			msk |= B_AX_RX_ERR_CSI_ACT_TO_MSK;
			reg = band == MAC_AX_BAND_0 ?
				R_AX_RX_ERR_IMR : R_AX_RX_ERR_IMR_C1;
			ret = write_mac_reg_auto_ofld(adapter, reg,
						      msk,
						      0x0,
						      IMR_IO_OFLD_NON_FLUSH);
			if (ret) {
				PLTFM_MSG_ERR("[ERR]%sIO ofld fail", __func__);
				return ret;
			}
		}
	}
#endif
	return MACSUCCESS;
}

static u32 haxidma_imr_enable_patch_8852c(struct mac_ax_adapter *adapter)
{
#if MAC_AX_USB_SUPPORT || MAC_AX_SDIO_SUPPORT
	u32 ret = MACSUCCESS, msk;

	/* 8852C H_AXIDMA SER IMR Patch code */
	if (chk_patch_haxidma_ind(adapter) == PATCH_DISABLE) {
		return MACSUCCESS;
	} else {
		if (adapter->env_info.intf == MAC_AX_INTF_USB ||
		    adapter->env_info.intf == MAC_AX_INTF_SDIO) {
			msk = (B_AX__TXBD_LEN0_ERR_IDCT_MSK |
			       B_AX__TXBD_4KBOUND_ERR_IDCT_MSK);
			ret = write_mac_reg_auto_ofld(adapter, R_AX_HAXI_IDCT_MSK,
						      msk,
						      0x0,
						      IMR_IO_OFLD_NON_FLUSH);
			if (ret) {
				PLTFM_MSG_ERR("[ERR]%sIO ofld fail", __func__);
				return ret;
			}
		}
	}
#endif

	return MACSUCCESS;
}

u32 ser_imr_config_patch_8852c(struct mac_ax_adapter *adapter, u8 band,
			       enum mac_ax_hwmod_sel sel)
{
	u32 ret = MACSUCCESS;
#if MAC_USB_IO_ACC_ON
	u32 ofldcap;
	struct mac_ax_ops *mops = adapter_to_mac_ops(adapter);
#endif

	ret = check_mac_en(adapter, band, sel);
	if (ret) {
		PLTFM_MSG_ERR("MAC%d band%d is not ready\n", sel, band);
		return ret;
	}

	if (sel == MAC_AX_DMAC_SEL) {
		ret = haxidma_imr_enable_patch_8852c(adapter);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]haxidma_imr_enable %d\n", ret);
			return ret;
		}
	} else if (sel == MAC_AX_CMAC_SEL) {
		ret = phy_intf_imr_enable_patch_8852c(adapter, band);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]phy_intf_imr_enable %d\n", ret);
			return ret;
		}

		ret = rmac_imr_enable_patch_8852c(adapter, band);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]rmac_imr_enable %d\n", ret);
			return ret;
		}
	} else {
		PLTFM_MSG_ERR("illegal sel %d\n", sel);
		return MACNOITEM;
	}
#if MAC_USB_IO_ACC_ON
	if (adapter->sm.fwdl == MAC_AX_FWDL_INIT_RDY) {
		ret = mops->get_hw_value(adapter, MAC_AX_HW_GET_FW_CAP, &ofldcap);
		if (ret != MACSUCCESS) {
			PLTFM_MSG_ERR("Get MAC_AX_HW_GET_FW_CAP fail %d\n", ret);
			return ret;
		}
		if (ofldcap == IO_OFLD_DIS)
			return MACSUCCESS;
		ret = mac_cmd_ofld(adapter);
		if (ret != MACSUCCESS)
			PLTFM_MSG_ERR("[ERR]mac_cmd_ofld fail : %d\n", ret);
	}
#endif
	return ret;
}
#endif /* #if MAC_AX_8852C_SUPPORT */
