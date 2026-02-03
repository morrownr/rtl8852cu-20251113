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

#include "ser_auto_gen_8852c.h"
#if MAC_AX_8852C_SUPPORT

static u32 cmac_dma_top_imr_enable_8852c(struct mac_ax_adapter *adapter, u8 band)
{
	u32 reg, ret;

	/* cmac_dma_top 0x1860c804 R_AX_RX_ERR_FLAG_IMR  */
	/* cmac_dma_top 0x1860e804 R_AX_RX_ERR_FLAG_IMR_C1  */
	reg = (band == MAC_AX_BAND_0) ?
		R_AX_RX_ERR_FLAG_IMR : R_AX_RX_ERR_FLAG_IMR_C1;
	//clear mask: 0x7fffff06, set value: 0x7fffff06
	ret = write_mac_reg_auto_ofld(adapter, reg,
				      CMAC_DMA_TOP_IMR0_MSK_8852C,
				      CMAC_DMA_TOP_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	/* cmac_dma_top 0x1860c870 R_AX_TX_ERR_FLAG_IMR  */
	/* cmac_dma_top 0x1860e870 R_AX_TX_ERR_FLAG_IMR_C1  */
	reg = (band == MAC_AX_BAND_0) ?
		R_AX_TX_ERR_FLAG_IMR : R_AX_TX_ERR_FLAG_IMR_C1;
	//clear mask: 0xff00c000, set value: 0xff00c000
	ret = write_mac_reg_auto_ofld(adapter, reg,
				      CMAC_DMA_TOP_IMR1_MSK_8852C,
				      CMAC_DMA_TOP_IMR1_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	return MACSUCCESS;
}

static u32 ptcltop_imr_enable_8852c(struct mac_ax_adapter *adapter, u8 band)
{
	u32 reg, ret;

	/* ptcltop 0x1860c6c0 R_AX_PTCL_IMR0  */
	/* ptcltop 0x1860e6c0 R_AX_PTCL_IMR0_C1  */
	reg = (band == MAC_AX_BAND_0) ?
		R_AX_PTCL_IMR0 : R_AX_PTCL_IMR0_C1;
	//clear mask: 0x3, set value: 0x3
	ret = write_mac_reg_auto_ofld(adapter, reg,
				      PTCLTOP_IMR0_MSK_8852C,
				      PTCLTOP_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	return MACSUCCESS;
}

static u32 schedulertop_imr_enable_8852c(struct mac_ax_adapter *adapter, u8 band)
{
	u32 reg, ret;

	/* schedulertop 0x1860c3e8 R_AX_SCHEDULE_ERR_IMR  */
	/* schedulertop 0x1860e3e8 R_AX_SCHEDULE_ERR_IMR_C1  */
	reg = (band == MAC_AX_BAND_0) ?
		R_AX_SCHEDULE_ERR_IMR : R_AX_SCHEDULE_ERR_IMR_C1;
	//clear mask: 0x3, set value: 0x1
	ret = write_mac_reg_auto_ofld(adapter, reg,
				      SCHEDULERTOP_IMR0_MSK_8852C,
				      SCHEDULERTOP_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	return MACSUCCESS;
}

static u32 phyintf_imr_enable_8852c(struct mac_ax_adapter *adapter, u8 band)
{
	u32 reg, ret;

	/* phyintf 0x1860ccf8 R_AX_PHYINFO_ERR_IMR_V1  */
	/* phyintf 0x1860ecf8 R_AX_PHYINFO_ERR_IMR_V1_C1  */
	reg = (band == MAC_AX_BAND_0) ?
		R_AX_PHYINFO_ERR_IMR_V1 : R_AX_PHYINFO_ERR_IMR_V1_C1;
	//clear mask: 0x3f, set value: 0x31
	ret = write_mac_reg_auto_ofld(adapter, reg,
				      PHYINTF_IMR0_MSK_8852C,
				      PHYINTF_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	return MACSUCCESS;
}

static u32 rmac_imr_enable_8852c(struct mac_ax_adapter *adapter, u8 band)
{
	u32 reg, ret;

	/* rmac 0x1860cef8 R_AX_RX_ERR_IMR  */
	/* rmac 0x1860eef8 R_AX_RX_ERR_IMR_C1  */
	reg = (band == MAC_AX_BAND_0) ?
		R_AX_RX_ERR_IMR : R_AX_RX_ERR_IMR_C1;
	//clear mask: 0x3ff, set value: 0x3d8
	ret = write_mac_reg_auto_ofld(adapter, reg,
				      RMAC_IMR0_MSK_8852C,
				      RMAC_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	return MACSUCCESS;
}

static u32 tmac_imr_enable_8852c(struct mac_ax_adapter *adapter, u8 band)
{
	u32 reg, ret;

	/* tmac 0x1860ccbc R_AX_TRXPTCL_ERROR_INDICA_MASK  */
	/* tmac 0x1860ecbc R_AX_TRXPTCL_ERROR_INDICA_MASK_C1  */
	reg = (band == MAC_AX_BAND_0) ?
		R_AX_TRXPTCL_ERROR_INDICA_MASK : R_AX_TRXPTCL_ERROR_INDICA_MASK_C1;
	//clear mask: 0x1ff, set value: 0x17f
	ret = write_mac_reg_auto_ofld(adapter, reg,
				      TMAC_IMR0_MSK_8852C,
				      TMAC_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	return MACSUCCESS;
}

static u32 sta_scheduler_imr_enable_8852c(struct mac_ax_adapter *adapter)
{
	u32 ret;

	/* STA scheduler 0x18609ef0 R_AX_STA_SCHEDULER_ERR_IMR  */
	//clear mask: 0x7, set value: 0x7
	ret = write_mac_reg_auto_ofld(adapter,
				      R_AX_STA_SCHEDULER_ERR_IMR,
				      STA_SCHEDULER_IMR0_MSK_8852C,
				      STA_SCHEDULER_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	return MACSUCCESS;
}

static u32 mpdu_tx_processor_imr_enable_8852c(struct mac_ax_adapter *adapter)
{
	u32 ret;

	/* MPDU TX Processor 0x18609bf4 R_AX_MPDU_TX_ERR_IMR  */
	//clear mask: 0x3fe, set value: 0x36e
	ret = write_mac_reg_auto_ofld(adapter,
				      R_AX_MPDU_TX_ERR_IMR,
				      MPDU_TX_PROCESSOR_IMR0_MSK_8852C,
				      MPDU_TX_PROCESSOR_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	return MACSUCCESS;
}

static u32 mpdu_rx_processor_imr_enable_8852c(struct mac_ax_adapter *adapter)
{
	u32 ret;

	/* MPDU RX Processor 0x18609cf4 R_AX_MPDU_RX_ERR_IMR  */
	//clear mask: 0x3, set value: 0x0
	ret = write_mac_reg_auto_ofld(adapter,
				      R_AX_MPDU_RX_ERR_IMR,
				      MPDU_RX_PROCESSOR_IMR0_MSK_8852C,
				      MPDU_RX_PROCESSOR_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	return MACSUCCESS;
}

static u32 wsec_imr_enable_8852c(struct mac_ax_adapter *adapter)
{
	u32 ret;

	/* WSEC 0x18609d2c R_AX_SEC_ERROR_FLAG_IMR  */
	//clear mask: 0x3, set value: 0x3
	ret = write_mac_reg_auto_ofld(adapter,
				      R_AX_SEC_ERROR_FLAG_IMR,
				      WSEC_IMR0_MSK_8852C,
				      WSEC_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	return MACSUCCESS;
}

static u32 pktin_imr_enable_8852c(struct mac_ax_adapter *adapter)
{
	u32 ret;

	/* PKTIN 0x18609a20 R_AX_PKTIN_ERR_IMR  */
	//clear mask: 0x1, set value: 0x1
	ret = write_mac_reg_auto_ofld(adapter,
				      R_AX_PKTIN_ERR_IMR,
				      PKTIN_IMR0_MSK_8852C,
				      PKTIN_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	return MACSUCCESS;
}

static u32 host_dispatcher_imr_enable_8852c(struct mac_ax_adapter *adapter)
{
	u32 ret;

	/* Host Dispatcher 0x18608850 R_AX_HOST_DISPATCHER_ERR_IMR  */
	//clear mask: 0xffd7ffff, set value: 0xc100060
	ret = write_mac_reg_auto_ofld(adapter,
				      R_AX_HOST_DISPATCHER_ERR_IMR,
				      HOST_DISPATCHER_IMR0_MSK_8852C,
				      HOST_DISPATCHER_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	return MACSUCCESS;
}

static u32 cpu_dispatcher_imr_enable_8852c(struct mac_ax_adapter *adapter)
{
	u32 ret;

	/* CPU Dispatcher 0x18608854 R_AX_CPU_DISPATCHER_ERR_IMR  */
	//clear mask: 0x7f7bfffd, set value: 0x36000060
	ret = write_mac_reg_auto_ofld(adapter,
				      R_AX_CPU_DISPATCHER_ERR_IMR,
				      CPU_DISPATCHER_IMR0_MSK_8852C,
				      CPU_DISPATCHER_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	return MACSUCCESS;
}

static u32 dispatcher_dle_interface_imr_enable_8852c(struct mac_ax_adapter *adapter)
{
	u32 ret;

	/* Dispatcher DLE interface 0x18608858 R_AX_OTHER_DISPATCHER_ERR_IMR  */
	//clear mask: 0xffffdfdf, set value: 0x303cc000
	ret = write_mac_reg_auto_ofld(adapter,
				      R_AX_OTHER_DISPATCHER_ERR_IMR,
				      DISPATCHER_DLE_INTERFACE_IMR0_MSK_8852C,
				      DISPATCHER_DLE_INTERFACE_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	return MACSUCCESS;
}

static u32 dle_cpuio_imr_enable_8852c(struct mac_ax_adapter *adapter)
{
	u32 ret;

	/* dle_cpuio 0x18609840 R_AX_CPUIO_ERR_IMR  */
	//clear mask: 0x1111, set value: 0x1111
	ret = write_mac_reg_auto_ofld(adapter,
				      R_AX_CPUIO_ERR_IMR,
				      DLE_CPUIO_IMR0_MSK_8852C,
				      DLE_CPUIO_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	return MACSUCCESS;
}

static u32 wde_dle_imr_enable_8852c(struct mac_ax_adapter *adapter)
{
	u32 ret;

	/* wde_dle 0x18608c38 R_AX_WDE_ERR_IMR  */
	//clear mask: 0x3f0ff3ff, set value: 0x3f0ff3ff
	ret = write_mac_reg_auto_ofld(adapter,
				      R_AX_WDE_ERR_IMR,
				      WDE_DLE_IMR0_MSK_8852C,
				      WDE_DLE_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	return MACSUCCESS;
}

static u32 ple_dle_imr_enable_8852c(struct mac_ax_adapter *adapter)
{
	u32 ret;

	/* ple_dle 0x18609038 R_AX_PLE_ERR_IMR  */
	//clear mask: 0x3f0ff3ff, set value: 0x3f0ff3ff
	ret = write_mac_reg_auto_ofld(adapter,
				      R_AX_PLE_ERR_IMR,
				      PLE_DLE_IMR0_MSK_8852C,
				      PLE_DLE_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	return MACSUCCESS;
}

static u32 wdrls_imr_enable_8852c(struct mac_ax_adapter *adapter)
{
	u32 ret;

	/* wdrls 0x18609430 R_AX_WDRLS_ERR_IMR  */
	//clear mask: 0x3337, set value: 0x3327
	ret = write_mac_reg_auto_ofld(adapter,
				      R_AX_WDRLS_ERR_IMR,
				      WDRLS_IMR0_MSK_8852C,
				      WDRLS_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	return MACSUCCESS;
}

static u32 txpktctl_imr_enable_8852c(struct mac_ax_adapter *adapter)
{
	u32 ret;

	/* txpktctl 0x18609f78 R_AX_TXPKTCTL_B0_ERRFLAG_IMR  */
	//clear mask: 0x350f0f, set value: 0x350b03
	ret = write_mac_reg_auto_ofld(adapter,
				      R_AX_TXPKTCTL_B0_ERRFLAG_IMR,
				      TXPKTCTL_IMR0_MSK_8852C,
				      TXPKTCTL_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	/* txpktctl 0x18609fb8 R_AX_TXPKTCTL_B1_ERRFLAG_IMR  */
	//clear mask: 0x350f0f, set value: 0x350b03
	ret = write_mac_reg_auto_ofld(adapter,
				      R_AX_TXPKTCTL_B1_ERRFLAG_IMR,
				      TXPKTCTL_IMR1_MSK_8852C,
				      TXPKTCTL_IMR1_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	return MACSUCCESS;
}

static u32 bbrpt_imr_enable_8852c(struct mac_ax_adapter *adapter)
{
	u32 ret;

	/* bbrpt 0x18609608 R_AX_BBRPT_COM_ERR_IMR  */
	//clear mask: 0x3, set value: 0x0
	ret = write_mac_reg_auto_ofld(adapter,
				      R_AX_BBRPT_COM_ERR_IMR,
				      BBRPT_IMR0_MSK_8852C,
				      BBRPT_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	/* bbrpt 0x18609628 R_AX_BBRPT_CHINFO_ERR_IMR  */
	//clear mask: 0xff, set value: 0xff
	ret = write_mac_reg_auto_ofld(adapter,
				      R_AX_BBRPT_CHINFO_ERR_IMR,
				      BBRPT_IMR1_MSK_8852C,
				      BBRPT_IMR1_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	/* bbrpt 0x18609638 R_AX_BBRPT_DFS_ERR_IMR  */
	//clear mask: 0x1, set value: 0x1
	ret = write_mac_reg_auto_ofld(adapter,
				      R_AX_BBRPT_DFS_ERR_IMR,
				      BBRPT_IMR2_MSK_8852C,
				      BBRPT_IMR2_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	/* bbrpt 0x18609668 R_AX_LA_ERRFLAG_IMR  */
	//clear mask: 0x1, set value: 0x1
	ret = write_mac_reg_auto_ofld(adapter,
				      R_AX_LA_ERRFLAG_IMR,
				      BBRPT_IMR3_MSK_8852C,
				      BBRPT_IMR3_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

	return MACSUCCESS;
}

static u32 h_axidma_imr_enable_8852c(struct mac_ax_adapter *adapter)
{
	u32 ret;

	/* H_AXIDMA 0x186010b8 R_AX_HAXI_IDCT_MSK  */
	//clear mask: 0xf, set value: 0xf
	ret = write_mac_reg_auto_ofld(adapter,
				      R_AX_HAXI_IDCT_MSK,
				      H_AXIDMA_IMR0_MSK_8852C,
				      H_AXIDMA_IMR0_SET_8852C,
				      IMR_IO_OFLD_NON_FLUSH);

	if (ret) {
		PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
		return ret;
	}

#if MAC_AX_USB_SUPPORT
	if (adapter->env_info.intf == MAC_AX_INTF_USB) {
		/* H_AXIDMA 0x186010b8 R_AX_HAXI_IDCT_MSK  */
		//clear mask: 0xf, set value: 0xd
		ret = write_mac_reg_auto_ofld(adapter,
					      R_AX_HAXI_IDCT_MSK,
					      H_AXIDMA_IMR0_USB_MSK_8852C,
					      H_AXIDMA_IMR0_USB_SET_8852C,
					      IMR_IO_OFLD_NON_FLUSH);

		if (ret) {
			PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
			return ret;
		}
	}
#endif

#if MAC_AX_SDIO_SUPPORT
	if (adapter->env_info.intf == MAC_AX_INTF_SDIO) {
		/* H_AXIDMA 0x186010b8 R_AX_HAXI_IDCT_MSK  */
		//clear mask: 0xf, set value: 0xd
		ret = write_mac_reg_auto_ofld(adapter,
					      R_AX_HAXI_IDCT_MSK,
					      H_AXIDMA_IMR0_SDIO_MSK_8852C,
					      H_AXIDMA_IMR0_SDIO_SET_8852C,
					      IMR_IO_OFLD_NON_FLUSH);

		if (ret) {
			PLTFM_MSG_ERR("[ERR]%s IO ofld fail", __func__);
			return ret;
		}
	}
#endif

	return MACSUCCESS;
}

u32 ser_imr_config_8852c(struct mac_ax_adapter *adapter, u8 band,
			 enum mac_ax_hwmod_sel sel)
{
	u32 ret;

	ret = check_mac_en(adapter, band, sel);
	if (ret) {
		PLTFM_MSG_ERR("MAC%d band%d is not ready\n", sel, band);
		return ret;
	}

	if (sel == MAC_AX_CMAC_SEL) {
		ret = cmac_dma_top_imr_enable_8852c(adapter, band);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]cmac_dma_top_imr_enable %d\n", ret);
			return ret;
		}

		ret = ptcltop_imr_enable_8852c(adapter, band);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]ptcltop_imr_enable %d\n", ret);
			return ret;
		}

		ret = schedulertop_imr_enable_8852c(adapter, band);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]schedulertop_imr_enable %d\n", ret);
			return ret;
		}

		ret = phyintf_imr_enable_8852c(adapter, band);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]phyintf_imr_enable %d\n", ret);
			return ret;
		}

		ret = rmac_imr_enable_8852c(adapter, band);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]rmac_imr_enable %d\n", ret);
			return ret;
		}

		ret = tmac_imr_enable_8852c(adapter, band);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]tmac_imr_enable %d\n", ret);
			return ret;
		}
	} else if (sel == MAC_AX_DMAC_SEL) {
		ret = sta_scheduler_imr_enable_8852c(adapter);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]sta_scheduler_imr_enable %d\n", ret);
			return ret;
		}

		ret = mpdu_tx_processor_imr_enable_8852c(adapter);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]mpdu_tx_processor_imr_enable %d\n", ret);
			return ret;
		}

		ret = mpdu_rx_processor_imr_enable_8852c(adapter);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]mpdu_rx_processor_imr_enable %d\n", ret);
			return ret;
		}

		ret = wsec_imr_enable_8852c(adapter);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]wsec_imr_enable %d\n", ret);
			return ret;
		}

		ret = pktin_imr_enable_8852c(adapter);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]pktin_imr_enable %d\n", ret);
			return ret;
		}

		ret = host_dispatcher_imr_enable_8852c(adapter);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]host_dispatcher_imr_enable %d\n", ret);
			return ret;
		}

		ret = cpu_dispatcher_imr_enable_8852c(adapter);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]cpu_dispatcher_imr_enable %d\n", ret);
			return ret;
		}

		ret = dispatcher_dle_interface_imr_enable_8852c(adapter);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]dispatcher_dle_interface_imr_enable %d\n", ret);
			return ret;
		}

		ret = dle_cpuio_imr_enable_8852c(adapter);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]dle_cpuio_imr_enable %d\n", ret);
			return ret;
		}

		ret = wde_dle_imr_enable_8852c(adapter);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]wde_dle_imr_enable %d\n", ret);
			return ret;
		}

		ret = ple_dle_imr_enable_8852c(adapter);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]ple_dle_imr_enable %d\n", ret);
			return ret;
		}

		ret = wdrls_imr_enable_8852c(adapter);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]wdrls_imr_enable %d\n", ret);
			return ret;
		}

		ret = txpktctl_imr_enable_8852c(adapter);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]txpktctl_imr_enable %d\n", ret);
			return ret;
		}

		ret = bbrpt_imr_enable_8852c(adapter);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]bbrpt_imr_enable %d\n", ret);
			return ret;
		}

		ret = h_axidma_imr_enable_8852c(adapter);
		if (ret) {
			PLTFM_MSG_ERR("[ERR]h_axidma_imr_enable %d\n", ret);
			return ret;
		}
	} else {
		PLTFM_MSG_ERR("illegal sel %d\n", sel);
		return MACNOITEM;
	}
	return ret;
}
#endif /* #if MAC_AX_8852C_SUPPORT */
