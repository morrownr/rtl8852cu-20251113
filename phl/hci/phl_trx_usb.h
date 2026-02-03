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
#ifndef _PHL_TRX_USB_H_
#define _PHL_TRX_USB_H_

#define MGMT_TID 8
#define PKT_OFFSET_DUMMY	(8)
//
// USB specific.
//
#define WLAN_IN_MPDU_PIPE_IDX			0	//EP1, RxIn Pipe
#define WLAN_IN_INTERRUPT_PIPE_IDX		1	//EP7, HISR or C2H Cmd In Pipe

struct rtw_rx_buf_ring {
	//
	// Memory block of phl_usb_rx_pkt.
	//
	struct rtw_rx_buf *rxbufblock;
	u32 	block_cnt_alloc;	// Total number of rtw_rx_buf allocated.
	u32 	total_blocks_size;	// block_cnt_alloc	*  sizeof( rtw_rx_buf )

	struct phl_queue idle_rxbuf_list;
	struct phl_queue busy_rxbuf_list;
	struct phl_queue pend_rxbuf_list;
	_os_timer deferred_timer;
};


struct phl_usb_tx_buf_resource  {
	struct phl_queue idle_txbuf_list;
	struct phl_queue mgmt_txbuf_list;
	struct phl_queue h2c_txbuf_list;
};

#ifdef CONFIG_PHL_USB_RX_AGGREGATION
enum rtw_phl_status
phl_cmd_usb_rx_agg_cfg_hdl(struct phl_info_t *phl_info, u8 *cmd);
#endif

enum rtw_phl_status
phl_hook_trx_ops_usb(struct phl_info_t *phl_info);
enum rtw_phl_status
phl_force_usb_switch(struct phl_info_t *phl_info, u32 speed);
enum rtw_phl_status
rtw_phl_cmd_force_usb_switch(void *phl, u32 speed,
				enum phl_band_idx band_idx,
				enum phl_cmd_type cmd_type, u32 cmd_timeout);
enum rtw_phl_status
rtw_phl_cmd_get_usb_speed(void *phl, u32* speed,
				enum phl_band_idx band_idx,
				enum phl_cmd_type cmd_type, u32 cmd_timeout);
/* refer enum rtw_usb_speed for definition of speed */
enum rtw_phl_status
phl_get_cur_usb_speed(struct phl_info_t *phl_info, u32 *speed);
/* refer enum phl_usb_ability for definition of ability */
enum rtw_phl_status
phl_get_usb_support_ability(struct phl_info_t *phl_info, u32 *ability);

#ifdef CONFIG_PHL_CUSTOM_FEATURE_USB
enum rtw_phl_status phl_cmd_set_usb_support_ability(struct phl_info_t *phl_info,
						u32 ability);
#endif

enum rtw_phl_status phl_cmd_get_usb_mode_status(struct phl_info_t *phl_info,
					    u32 *status);
enum rtw_phl_status phl_cmd_get_u3_perf_mode(struct phl_info_t *phl_info,
					 u32 *perf_mode);
#endif	/* _PHL_TRX_USB_H_ */
