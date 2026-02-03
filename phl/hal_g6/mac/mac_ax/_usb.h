/** @file */
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

#ifndef _MAC_AX_USB_H_
#define _MAC_AX_USB_H_

#include "../type.h"

#ifdef CONFIG_FT_SUPPORT
#define USB_SWITCH_DELAY     0x0
#else
#define USB_SWITCH_DELAY     0xF
#endif

#define phyoffset            0x20
#define USB11                0x1
#define USB2                 0x2
#define USB3                 0x3
#define U3SWITCHU2           0x17
#define U2SWITCHU3           0xB
#define USBEPMAPERR          0xFF
#define USB11_BULKSIZE       0x2
#define USB2_BULKSIZE        0x1
#define USB3_BULKSIZE        0x0
#define EP4                  0x4
#define EP5                  0x5
#define EP6                  0x6
#define EP7                  0x7
#define EP8                  0x8
#define EP9                  0x9
#define EP10                 0xA
#define EP11                 0xB
#define EP12                 0xC
#define NUMP                 0x1
#define BULKOUTID0           0x0
#define BULKOUTID1           0x1
#define BULKOUTID2           0x2
#define BULKOUTID3           0x3
#define BULKOUTID4           0x4
#define BULKOUTID5           0x5
#define BULKOUTID6           0x6
#define USBPHYOFFSET         0x100
#define DISABLE              0x0
#define ENABLE               0x1
#define RXAGGSIZE            0x5
#define RXAGGTO              0x20
#define EFUSESIZE            0x1
#define CMAC_CLK_ALLEN       0xFFFFFFFF
#define SINGLE_MSDU_SIZE     0x600
#define SEC_FCS_SIZE         0x80
#define PLE_PAGE_SIZE        0x80
#define PINGPONG             0x2
#define RX_POLLING_PERIOD    0x40
#define USB_TX_IDLE          0x10

// Efuse
#define R_AX_EFUSE_LOG_PAGE1_REG06 0x05B8
#define B_AX_REG_CDR_RATE_SEL_SH 14
#define B_AX_REG_CDR_RATE_SEL_MSK 0x3

#define R_AX_EFUSE_LOG_PAGE1_REG06_V1 0x070C
#define B_AX_REG_CDR_RATE_SEL_V1_SH 14
#define B_AX_REG_CDR_RATE_SEL_V1_MSK 0x3

// DCDR Rate
#define DCDR_RATE_MID 0x1
#define DCDR_RATE_HIGH 0x2

/* UPHY PLL related */
#define R_AX_UPHY_SUSPENDM 0xF3
#define B_AX_FORCE_SUSPENDM BIT(5)
#define B_AX_SUSPENDM BIT(4)

#define USB_TXDMA_IDLE_POLL_TIME 10
#define USB_FLUSH_WAIT_TIME 30

#define USB_ON_IOH_SW_RST_RETRY_CNT 100
#define USB_ON_IOH_SW_RST_WAIT_US 50

/**
 * @addtogroup HCI
 * @{
 * @addtogroup USB
 * @{
 */
/**
 * @brief usb_flush_mode
 *
 * @param *adapter
 * @param mode
 * @return Please Place Description here.
 * @retval u32
 */
u32 usb_flush_mode(struct mac_ax_adapter *adapter, u8 mode);
/**
 * @}
 * @}
 */

/**
 * @addtogroup HCI
 * @{
 * @addtogroup USB
 * @{
 */

/**
 * @brief get_usb_mode_8852a
 *
 * @param *adapter
 * @return Please Place Description here.
 * @retval u32
 */
u32 get_usb_mode(struct mac_ax_adapter *adapter);
/**
 * @}
 * @}
 */

/**
 * @addtogroup HCI
 * @{
 * @addtogroup USB
 * @{
 */

/**
 * @brief dbcc_hci_ctrl_usb
 *
 * @param *adapter
 * @param *info
 * @return Please Place Description here.
 * @retval u32
 */
u32 dbcc_hci_ctrl_usb(struct mac_ax_adapter *adapter,
		      struct mac_ax_dbcc_hci_ctrl *info);
/**
 * @}
 * @}
 */

/**
 * @addtogroup HCI
 * @{
 * @addtogroup USB
 * @{
 */

/**
 * @brief ltr_set_usb
 *
 * @param *adapter
 * @param *param
 * @return Please Place Description here.
 * @retval u32
 */
u32 ltr_set_usb(struct mac_ax_adapter *adapter,
		struct mac_ax_pcie_ltr_param *param);
/**
 * @}
 * @}
 */

/**
 * @addtogroup HCI
 * @{
 * @addtogroup USB
 * @{
 */

/**
 * @brief ctrl_txdma_ch_usb
 *
 * @param *adapter
 * @param *ch_map
 * @return Please Place Description here.
 * @retval u32
 */
u32 ctrl_txdma_ch_usb(struct mac_ax_adapter *adapter,
		      struct mac_ax_txdma_ch_map *ch_map);
/**
 * @}
 * @}
 */

/**
 * @addtogroup HCI
 * @{
 * @addtogroup USB
 * @{
 */

/**
 * @brief clr_idx_all_usb
 *
 * @param *adapter
 * @return Please Place Description here.
 * @retval u32
 */
u32 clr_idx_all_usb(struct mac_ax_adapter *adapter);
/**
 * @}
 * @}
 */

/**
 * @addtogroup HCI
 * @{
 * @addtogroup USB
 * @{
 */

/**
 * @brief poll_txdma_ch_idle_usb
 *
 * @param *adapter
 * @param *ch_map
 * @return Please Place Description here.
 * @retval u32
 */
u32 poll_txdma_ch_idle_usb(struct mac_ax_adapter *adapter,
			   struct mac_ax_txdma_ch_map *ch_map);
/**
 * @}
 * @}
 */

/**
 * @addtogroup HCI
 * @{
 * @addtogroup USB
 * @{
 */

/**
 * @brief set_pcie_speed_usb
 *
 * @param *adapter
 * @param speed
 * @return Please Place Description here.
 * @retval u32
 */
u32 set_pcie_speed_usb(struct mac_ax_adapter *adapter,
		       enum mac_ax_pcie_phy speed);
/**
 * @}
 * @}
 */

/**
 * @addtogroup HCI
 * @{
 * @addtogroup USB
 * @{
 */

/**
 * @brief get_pcie_speed_usb
 *
 * @param *adapter
 * @param *speed
 * @return Please Place Description here.
 * @retval u32
 */
u32 get_pcie_speed_usb(struct mac_ax_adapter *adapter,
		       u8 *speed);
/**
 * @}
 * @}
 */

/**
 * @addtogroup HCI
 * @{
 * @addtogroup USB
 * @{
 */

/**
 * @brief get_pcie_sup_speed_usb
 *
 * @param *adapter
 * @return Please Place Description here.
 * @retval u32
 */
u32 get_pcie_sup_speed_usb(struct mac_ax_adapter *adapter);
/**
 * @}
 * @}
 */

/**
 * @addtogroup HCI
 * @{
 * @addtogroup USB
 * @{
 */

/**
 * @brief poll_rxdma_ch_idle_usb
 *
 * @param *adapter
 * @param *ch_map
 * @return Please Place Description here.
 * @retval u32
 */
u32 poll_rxdma_ch_idle_usb(struct mac_ax_adapter *adapter,
			   struct mac_ax_rxdma_ch_map *ch_map);
/**
 * @}
 * @}
 */

/**
 * @addtogroup HCI
 * @{
 * @addtogroup USB
 * @{
 */

/**
 * @brief ctrl_txhci_usb
 *
 * @param *adapter
 * @param en
 * @return Please Place Description here.
 * @retval u32
 */
u32 ctrl_txhci_usb(struct mac_ax_adapter *adapter, enum mac_ax_func_sw en);
/**
 * @}
 * @}
 */

/**
 * @addtogroup HCI
 * @{
 * @addtogroup USB
 * @{
 */

/**
 * @brief ctrl_rxhci_usb
 *
 * @param *adapter
 * @param en
 * @return Please Place Description here.
 * @retval u32
 */
u32 ctrl_rxhci_usb(struct mac_ax_adapter *adapter, enum mac_ax_func_sw en);
/**
 * @}
 * @}
 */

/**
 * @addtogroup HCI
 * @{
 * @addtogroup USB
 * @{
 */

/**
 * @brief ctrl_dma_io_usb
 *
 * @param *adapter
 * @param en
 * @return Please Place Description here.
 * @retval u32
 */
u32 ctrl_dma_io_usb(struct mac_ax_adapter *adapter, enum mac_ax_func_sw en);
/**
 * @}
 * @}
 */

/**
 * @addtogroup HCI
 * @{
 * @addtogroup USB
 * @{
 */

/**
 * @brief get_io_stat_usb
 *
 * @param *adapter
 * @param *out_st
 * @return Please Place Description here.
 * @retval u32
 */
u32 get_io_stat_usb(struct mac_ax_adapter *adapter,
		    struct mac_ax_io_stat *out_st);
/**
 * @}
 * @}
 */

/**
 * @addtogroup HCI
 * @{
 * @addtogroup USB
 * @{
 */

/**
 * @brief get_avail_txbd_usb
 *
 * @param *adapter
 * @param ch_idx
 * @param *host_idx
 * @param *hw_idx
 * @param *avail_txbd
 * @return Please Place Description here.
 * @retval u32
 */
u32 get_avail_txbd_usb(struct mac_ax_adapter *adapter, u8 ch_idx,
		       u16 *host_idx, u16 *hw_idx, u16 *avail_txbd);
/**
 * @}
 * @}
 */

/**
 * @addtogroup HCI
 * @{
 * @addtogroup USB
 * @{
 */

/**
 * @brief get_avail_rxbd_usb
 *
 * @param *adapter
 * @param ch_idx
 * @param *host_idx
 * @param *hw_idx
 * @param *avail_rxbd
 * @return Please Place Description here.
 * @retval u32
 */
u32 get_avail_rxbd_usb(struct mac_ax_adapter *adapter, u8 ch_idx,
		       u16 *host_idx, u16 *hw_idx, u16 *avail_rxbd);
/**
 * @}
 * @}
 */

/**
 * @addtogroup HCI
 * @{
 * @addtogroup USB
 * @{
 */

/**
 * @brief trigger_txdma_usb
 *
 * @param *adapter
 * @param *txbd_ring
 * @param ch_idx
 * @return Please Place Description here.
 * @retval u32
 */
u32 trigger_txdma_usb(struct mac_ax_adapter *adapter,
		      struct tx_base_desc *txbd_ring, u8 ch_idx);
/**
 * @}
 * @}
 */

/**
 * @addtogroup HCI
 * @{
 * @addtogroup USB
 * @{
 */

/**
 * @brief notify_rxdone_usb
 *
 * @param *adapter
 * @param *rxbd
 * @param ch
 * @return Please Place Description here.
 * @retval u32
 */
u32 notify_rxdone_usb(struct mac_ax_adapter *adapter,
		      struct rx_base_desc *rxbd, u8 ch);
/**
 * @}
 * @}
 */

/**
 * @brief usb_autok_counter_avg
 *
 * @param *adapter
 * @return Please Place Description here.
 * @retval u32
 */
u32 usb_autok_counter_avg(struct mac_ax_adapter *adapter);
/**
 * @}
 * @}
 */

/**
 * @brief usb_tp_adjust
 *
 * @param *adapter
 * @param tp
 * @return Please Place Description here.
 * @retval u32
 */
u32 usb_tp_adjust(struct mac_ax_adapter *adapter, struct mac_ax_tp_param tp);
/**
 * @}
 * @}
 */

/**
 * @brief ctrl_txdma_usb
 *
 * @param *adapter
 * @param opt
 * @return Please Place Description here.
 * @retval u32
 */
u32 ctrl_txdma_usb(struct mac_ax_adapter *adapter, u8 opt);
/**
 * @}
 * @}
 */

/**
 * @brief poll_txdma_idle_usb
 *
 * @param *adapter
 * @return Please Place Description here.
 * @retval u32
 */
u32 poll_txdma_idle_usb(struct mac_ax_adapter *adapter)
;
/**
 * @}
 * @}
 */

/**
 * @brief clr_hci_trx_usb
 *
 * @param *adapter
 * @return Please Place Description here.
 * @retval u32
 */
u32 clr_hci_trx_usb(struct mac_ax_adapter *adapter);
/**
 * @}
 * @}
 */

/**
 * @addtogroup HCI
 * @{
 * @addtogroup USB
 * @{
 */

/**
 * @brief usb_uphy_pll_cfg
 *
 * @param *adapter
 * @param keep_pll
 * @return Please Place Description here.
 * @retval u32
 */
u32 usb_uphy_pll_cfg(struct mac_ax_adapter *adapter,
		     u8 keep_pll);
/**
 * @}
 * @}
 */

/**
 * @brief set_usb_support_ability
 *
 * @param *adapter
 * @param ability
 * @return Please Place Description here.
 * @retval u32
 */
u32 set_usb_support_ability(struct mac_ax_adapter *adapter, enum usb_support_ability ability);
/**
 * @}
 * @}
 */

/**
 * @brief get_usb_mode_status
 *
 * @param *adapter
 * @param status
 * @return Please Place Description here.
 * @retval u32
 */
u32 get_usb_mode_status(struct mac_ax_adapter *adapter, enum usb_mode_status *status);
/**
 * @}
 * @}
 */

/**
 * @brief usb_ioh_sw_rst
 *
 * @param *adapter
 * @return Please Place Description here.
 * @retval u32
 */
u32 usb_ioh_sw_rst(struct mac_ax_adapter *adapter);
/**
 * @}
 * @}
 */
u32 lv2rst_stop_dma_usb(struct mac_ax_adapter *adapter);

#endif
