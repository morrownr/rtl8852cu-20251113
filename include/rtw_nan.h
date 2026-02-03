/******************************************************************************
 *
 * Copyright(c) 2007 - 2024 Realtek Corporation.
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
#ifndef __RTW_NAN_H_
#define __RTW_NAN_H_

#ifdef CONFIG_NAN
struct nan_service_entry {
	_list list;
	u64 cookie;
	void *p_entry;
};

struct nan_priv {
	_queue nan_func_q;
};

void rtw_core_nan_fill_ies(void *drv_priv, u8 *wrole_addr, u8 band_support,
			   u32 ie_type_bitmap, u8 *pbuf, u16 *attr_len);

/**
 * rtw_core_nan_issue_mgnt_frame - issue NAN mgnt frames
 *   - update mgntframe_attrib
 *   - fill wlan header
 *   - call dump_mgntframe
 * @macid: of nan device
 * @a1: dest addr; NULL means that the issuing frame is bcast
 * @a2: the NMI of the nan device
 * @a3: Cluster ID of current cluster which the nan device belongs to
 * @nan_attr_buf: frame conten started from the first nan attribute
 * @nan_attr_buf_len: buf len
 * (ac) construct_nan_sdf_hdr
 *
 * Returns:
 * RTW_PHL_STATUS_SUCCESS: alloc_mgtxmitframe success
 * RTW_PHL_STATUS_FAILURE: alloc_mgtxmitframe fail
 */
enum rtw_phl_status rtw_core_nan_issue_mgnt_frame(
					void *drv_priv, u16 macid, u8 *a1,
					u8 *a2, u8 *a3, u8 *addr,
					u8 *nan_attr_buf, u16 nan_attr_buf_len,
					enum rtw_phl_nan_pkt_type nan_pkt_type);

/**
 * rtw_core_nan_get_attr_start
 * - return starting address of nan attribe
 * @precv_frame: received frame; 80211 hdr included.
 * @precv_frame_len: the len of precv_frame
 * @ppattr_start: return val; starting address of nan attribe
 * @total_len: return val; the total len of attributes
 * (ac) rtw_nan_get_attr_start_from_recv_frame
 *
 * RETURN:
 * RTW_PHL_STATUS_SUCCESS: get ppattr_start successfully
 * RTW_PHL_STATUS_FAILURE: mis-match frame_type or NAN OUI
 */
enum rtw_phl_status rtw_core_nan_get_attr_start(u8 *precv_frame,
						u16  precv_frame_len,
						u8 **ppattr_start,
						u16 *total_len);

/**
 * rtw_core_nan_get_frame_body:
 * return the starting address of frame body
 * todo: merge with rtw_core_nan_get_attr_start
 */
enum rtw_phl_status rtw_core_nan_get_frame_body(u8 *precv_frame,
						u16 precv_frame_len,
						u8 **ppframe_body,
						u16 *frame_body_len);

/**
 * rtw_core_nan_report_to_osdep
 * - report event to os layer with specific parameters
 * @type: report type
 * @para: ptr of para
 * @para_len: the len of para
 *
 * RETURN:
 * RTW_PHL_STATUS_SUCCESS: get ppattr_start successfully
 * RTW_PHL_STATUS_FAILURE: mis-match frame_type or NAN OUI
 */
enum rtw_phl_status rtw_core_nan_report_to_osdep(
					void *drv_priv, u8* addr,
					enum rtw_phl_nan_report_type type,
					void *param, u16 param_len);

/** rtw_core_nan_alloc_peer_sta_info: allocate peer sta info
 * @drv_priv: drvpriv
 * @nan_addr: self nmi
 * @peer_addr: peer's addr (nmi or ndi)
 * @ht_cap:
 * @vht_cap:
 * @macid:
 * @is_ndi:
 * note: currently nmi and ndi will have there own macid
 *
 * (ac) rtw_nan_alloc_ndi_stainfo
 */
enum rtw_phl_status rtw_core_nan_alloc_peer_sta_info(void *drv_priv,
						     u8 *nan_addr,
						     u8 *peer_addr, u8 *ht_cap,
						     u8 *vht_cap, u8 *macid,
						     u8 is_ndi);

/** rtw_core_nan_free_peer_sta_info:
 * free peer sta info
 * @drv_priv: drvpriv
 * @nan_addr: self nmi
 * @peer_phl_sta_info: peer's sta info to be free
 */
enum rtw_phl_status rtw_core_nan_free_peer_sta_info(
				void *drv_priv,
				u8 *nan_addr,
				struct rtw_phl_stainfo_t *peer_phl_sta_info);

#ifdef CONFIG_NAN_R2
/** rtw_core_nan_set_pairwise_key:
 * add or remove key for the specified peer ndi
 * @drv_priv: drvpriv
 * @nan_addr: self nmi
 * @key: for adding key, point to the buffer of the specified key
 *       for removing key, use NULL pointer to indicate removing key setting
 * @key_len: the length of key
 * @peer_ndi: the pointer to the peer ndi
 * (ac) nan_set_pairwise_key, nan_clear_pairwise_key */
enum rtw_phl_status rtw_core_nan_set_pairwise_key(void *drv_priv, u8 *nan_addr,
						  u8 *key, u8 key_len,
						  u8 *peer_ndi);

/**
 * rtw_core_nan_pmk_to_ptk:
 * calculate PTK from PMK, addresses, and nonces
 * @cipher_suite: enum rtw_phl_nan_cipher_suite (NCS-SK-128 or NCS-SK-256)
 * @pmk: pairwise master key
 * @pmk_len: length of PMK
 * @label: Label to use in derivation
 * @i_addr: IAddr
 * @r_addr: RAddr
 * @i_nonce: INonce
 * @r_nonce: RNonce
 * @ptk: Buffer for pairwise transient key
 *
 * NAN spec 7.1.4.1 NAN Shared Key Cipher Suite:
 * NAN Pairwise key derivation shall use the RSNA pairwise key hierarchy using
 * Nonce values obtained from NDP negotiation messages
 * where the mapping from PMK to PTK shall be accomplished using
 * PRF-Length (PMK, “NAN Pairwise key expansion”, IAddr || RAddr || INonce || RNonce)
 * Where IAddr and RAddr are initiator and responder MAC addresses respectively
 * INonce and RNonce are Nonce values sent by the initiator and responder respectively
 *
 * (ac) nan_pmk_to_ptk
 **/
enum rtw_phl_status rtw_core_nan_pmk_to_ptk(u8 cipher_suite, u8 *pmk,
					    size_t pmk_len, char *label,
					    u8 *i_addr, u8 *r_addr,
					    u8 *i_nonce, u8 *r_nonce,
					    struct rtw_phl_nan_wpa_ptk *ptk);

/**
 * rtw_core_nan_get_key_mic:
 * calculate nan key mic
 * @cipher_suite: enum rtw_phl_nan_cipher_suite (NCS-SK-128 or NCS-SK-256)
 * @key: eapolL-key key confirmation key (KCK)
 * @auth_token: nan authentication token
 * @auth_token_len: nan authentication token length
 * @data: pointer to the beginning of the frame body (after 802.11 MAC header)
 * @data_len: length of the frame body (after 802.11 MAC header)
 * @mic: buffer for nan key mic
 *
 * note:
 * CMAC is a keyed hash function that is based on a symmetric key block cipher,
 * such as the Advanced Encryption Standard (AES).
 * CMAC is equivalent to the One-Key CBC MAC1 (OMAC1).
 *
 * (ac) nan_key_mic
 */
enum rtw_phl_status rtw_core_nan_get_key_mic(u8 cipher_suite, u8 *key,
					     u8 *auth_token, u32 auth_token_len,
					     u8 *data, u32 data_len, u8 *mic);

/**
 * rtw_core_nan_get_auth_token:
 * calculate NAN Authentication Token
 * @key: eapol-key key confirmation key (KCK)
 * @key_len: KCK length in octets
 * @buf: pointer to the beginning of the frame body (after 802.11 MAC header)
 * @len: length of the frame body (after 802.11 MAC header)
 * @auth_token: buffer for auth token
 *
 * note: auth token = L(NCS-SK-HASH(Authentication Token Data), 0, 128)
 * (ac) nan_auth_token
 */
enum rtw_phl_status rtw_core_nan_get_auth_token(u8 *buf, size_t buf_len,
						u8 *auth_token);

/**
 * rtw_core_nan_get_pmkid:
 * calculate NAN PMK identifier
 * @pmk: pairwise master key
 * @pmk_len: length of pmk in bytes
 * @iaddr: initiator address
 * @raddr: responder address
 * @srvc_id: nan service id
 * @pmkid: buffer for pmkid
 * note:
 * PMKID = L( HMAC-Hash(PMK, "NAN PMK Name"|| IAddr || RAddr || Service ID), 0, 128)
 * (ac) nan_pmkid
 */
enum rtw_phl_status rtw_core_nan_get_pmkid(u8 *pmk, size_t pmk_len, u8 *iaddr,
					   u8 *raddr, u8 *srvc_id, u8 *pmkid);

/* (ac) IS_ANY_DATA_LINK_EXIST */
u8 rtw_core_nan_is_any_ndl_exist(_adapter *adapter);

u8 rtw_core_nan_updt_tx_pkt_attr(_adapter *adapter, struct pkt_attrib *pattrib);

/**
 * rtw_core_nan_updt_tx_wlanhdr:
 * fill wlan gdr according to the nan_pkt_type pre-fiilled in pattrib
 * @adapter: adapter
 * @pattrib: pkt_attrib in xmit_frame
 * @pwlanhdr: the pointer for updating wlan header
 */
void rtw_core_nan_updt_tx_wlanhdr(_adapter *adapter, struct pkt_attrib *pattrib,
				  struct rtw_ieee80211_hdr *pwlanhdr);

u8 rtw_core_nan_rx_data_validate_hdr(_adapter *adapter,
				     union recv_frame *rframe,
				     struct sta_info **sta);
#endif /* CONFIG_NAN_R2 */

int rtw_core_nan_priv_init(_adapter *adapter);
int rtw_core_nan_priv_deinit(_adapter *adapter);

int rtw_nan_start_stop_cmd(_adapter *adapter, u8 start, u8 is_rmmod,
			   enum rtw_phl_nan_cmd_type cmd_type, u8 master_pref,
			   u8 bands);
#endif /* CONFIG_NAN */
#endif