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
#define _RTW_NAN_C_

#include <drv_types.h>
#include <sha256.h>
#include "wlancrypto_wrap.h"

#ifdef CONFIG_NAN
/* callback functions */
void rtw_core_nan_fill_ies(void *drv_priv, u8 *wrole_addr, u8 band_support,
			   u32 ie_type_bitmap, u8 *pbuf, u16 *attr_len)
{
	struct dvobj_priv *dvobj = (struct dvobj_priv *)drv_priv;
	_adapter *nan_adpt = dvobj_get_adapter_by_addr(dvobj, wrole_addr);
	/* ToDo CONFIG_RTW_MLD: [currently primary link only] */
	struct _ADAPTER_LINK *padapter_link = GET_PRIMARY_LINK(nan_adpt);
	struct nan_priv *nanpriv = dvobj_to_nan(dvobj);
	u8 SupportRate[NDIS_802_11_LENGTH_RATES_EX];
	u8 tmp_ie[MAX_IE_LEN_FOR_NAN] = {0};
	int tmp_ie_len = 0;
	u32 ratelen = 0;
	u8 i = 0;

	if (ie_type_bitmap & NAN_IE_SUPPORTED_RATES) {
		rtw_set_supported_rate(SupportRate, WLAN_MD_11AN,
				       (band_support & BAND_ON_5G) ?
					DEFAULT_NAN_5G_CH : DEFAULT_NAN_24G_CH,
				       (band_support & BAND_ON_5G) ?
					BAND_ON_5G : BAND_ON_24G);

		ratelen = rtw_get_rateset_len(SupportRate);
		for (i = 0; i < ratelen; i++)
			SupportRate[i] |= IEEE80211_BASIC_RATE_MASK;

		/* Generate SUPPORTEDRATES */
		pbuf = rtw_set_ie(pbuf, _SUPPORTEDRATES_IE_, 8, SupportRate,
				  (uint *)attr_len);
	}

	if (ie_type_bitmap & NAN_IE_EXT_SUPPORTED_RATES)
		/* Generate EXT SUPPORTEDRATES */
		if (ratelen > 8) {
			pbuf = rtw_set_ie(pbuf, _EXT_SUPPORTEDRATES_IE_,
					  ratelen - 8, SupportRate + 8,
					  (uint *)attr_len);
		}

	if (ie_type_bitmap & NAN_IE_HT_CAPABILITY) {
		/* Generate HT Capability */
		rtw_ht_use_default_setting(nan_adpt, padapter_link);
		rtw_restructure_ht_ie(nan_adpt, padapter_link, NULL, tmp_ie, 0,
				      (uint *)&tmp_ie_len, DEFAULT_NAN_24G_CH);
		_rtw_memcpy(pbuf, tmp_ie, tmp_ie_len);
		pbuf += tmp_ie_len;
		*attr_len += tmp_ie_len;
	}

	if (ie_type_bitmap & NAN_IE_VHT_CAPABILITY) {
		/* Generate VHT Capability */
		rtw_vht_get_real_setting(nan_adpt, padapter_link);
		tmp_ie_len =
			rtw_build_vht_cap_ie(nan_adpt, padapter_link, tmp_ie);
		_rtw_memcpy(pbuf, tmp_ie, tmp_ie_len);
		pbuf += tmp_ie_len;
		*attr_len += tmp_ie_len;
	}
}

enum rtw_phl_status rtw_core_nan_issue_mgnt_frame(
					void *drv_priv, u16 macid, u8 *a1,
					u8 *a2, u8 *a3, u8 *addr,
					u8 *nan_attr_buf, u16 nan_attr_buf_len,
					enum rtw_phl_nan_pkt_type nan_pkt_type)
{
	enum rtw_phl_status ret = RTW_PHL_STATUS_FAILURE;
	_adapter *nan_adpt = dvobj_get_adapter_by_addr(drv_priv, addr);
	struct phl_info_t *phl_info = GET_PHL_INFO(adapter_to_dvobj(nan_adpt));
	struct xmit_priv *pxmitpriv = &nan_adpt->xmitpriv;
	struct mlme_ext_priv *pmlmeext = &nan_adpt->mlmeextpriv;
	/* ToDo CONFIG_RTW_MLD: [currently primary link only] */
	struct _ADAPTER_LINK *padapter_link = GET_PRIMARY_LINK(nan_adpt);
	struct xmit_frame *pmgntframe;
	struct pkt_attrib *pattrib;
	struct rtw_ieee80211_hdr *pwlanhdr;
	u8 *pframe = NULL;
	u8 category = RTW_WLAN_CATEGORY_PUBLIC;
	u8 action = ACT_PUBLIC_VENDOR;
	u16 *fctrl;
	u8 *frame_body = NULL;

#ifdef CONFIG_NAN_DEBUG
	RTW_INFO("%s => len(%d), macid(%d), nan_pkt_type(%d)\n", __func__,
	         nan_attr_buf_len, macid, nan_pkt_type);
#endif

	if (alink_is_tx_blocked_by_ch_waiting(padapter_link))
		goto exit;

	if ((nan_pkt_type != NAN_PKT_TYPE_SDF) &&
#ifdef CONFIG_NAN_R2
	    (nan_pkt_type != NAN_PKT_TYPE_NAF) &&
#endif
	    1) {
		RTW_ERR("%s Not SDF or NAF, nan_pkt_type = %d\n", __func__,
			nan_pkt_type);
		ret = RTW_PHL_STATUS_FAILURE;
	}

	pmgntframe = alloc_mgtxmitframe(pxmitpriv);
	if (pmgntframe == NULL)
		goto exit;

	/* update attribute */
	pattrib = &pmgntframe->attrib;
	update_mgntframe_attrib(nan_adpt, padapter_link, pattrib);
	pattrib->nan_pkt_type = nan_pkt_type;
	pattrib->mac_id = macid;
	pattrib->pktlen = 0;

	_rtw_memset(pmgntframe->buf_addr, 0, WLANHDR_OFFSET + TXDESC_OFFSET);
	pframe = (u8 *)(pmgntframe->buf_addr) + TXDESC_OFFSET;
	pwlanhdr = (struct rtw_ieee80211_hdr *)pframe;
	fctrl = &(pwlanhdr->frame_ctl);
	*(fctrl) = 0;

	_rtw_memcpy(pwlanhdr->addr1, (a1) ? a1 : nan_network_id, ETH_ALEN);
	_rtw_memcpy(pwlanhdr->addr2, a2, ETH_ALEN);
	_rtw_memcpy(pwlanhdr->addr3, a3, ETH_ALEN);

	SetSeqNum(pwlanhdr, pmlmeext->mgnt_seq);
	pmlmeext->mgnt_seq++;
	set_frame_sub_type(pframe, WIFI_ACTION);

	pframe += sizeof(struct rtw_ieee80211_hdr_3addr);
	frame_body = pframe;
	pattrib->pktlen = sizeof(struct rtw_ieee80211_hdr_3addr);

	/* Category */
	pframe = rtw_set_fixed_ie(pframe, 1, &(category), &(pattrib->pktlen));

	/* Action */
	pframe = rtw_set_fixed_ie(pframe, 1, &(action), &(pattrib->pktlen));

	/* NAN OUI & OUI type */
	if (nan_pkt_type == NAN_PKT_TYPE_SDF)
		pframe = rtw_set_fixed_ie(pframe, 4, NAN_OUI_SDF, &(pattrib->pktlen));
#ifdef CONFIG_NAN_R2
	else if (nan_pkt_type == NAN_PKT_TYPE_NAF)
		pframe = rtw_set_fixed_ie(pframe, 4, NAN_OUI_NAF, &(pattrib->pktlen));
#endif

	/* copy pkt content to pframe from buf */
	_rtw_memcpy(pframe, nan_attr_buf, nan_attr_buf_len);
	pframe += nan_attr_buf_len;
	pattrib->pktlen += nan_attr_buf_len;

	pattrib->last_txcmdsz = pattrib->pktlen;
#ifdef CONFIG_NAN_R2
	rtw_phl_nan_data_eng_pre_tx_mgnt(phl_info,
					 nan_pkt_type,
					 a1,
					 frame_body,
					 pattrib->pktlen - sizeof(struct rtw_ieee80211_hdr_3addr));
#endif
	dump_mgntframe(nan_adpt, pmgntframe);
	ret = RTW_PHL_STATUS_SUCCESS;

exit:
	return ret;
}

enum rtw_phl_status rtw_core_nan_get_attr_start(u8 *precv_frame,
						u16  precv_frame_len,
						u8 **ppattr_start,
						u16 *total_len)
{
	enum rtw_phl_status ret = RTW_PHL_STATUS_FAILURE;
	u8 frame_type = get_frame_sub_type(precv_frame);
	u16 attr_len = 0;
	s32 ie_len = 0, wlan_hdr_len = sizeof(struct rtw_ieee80211_hdr_3addr);
	u8 *pnan_attr_start = precv_frame + wlan_hdr_len;

	switch (frame_type) {
	case WIFI_BEACON:
		pnan_attr_start = rtw_get_ie((pnan_attr_start +
					      _BEACON_IE_OFFSET_),
					     _VENDOR_SPECIFIC_IE_, &ie_len,
					     (precv_frame_len - wlan_hdr_len -
					      _BEACON_IE_OFFSET_));
		if (_rtw_memcmp(pnan_attr_start + 2, NAN_OUI_BCN, 4)) {
			pnan_attr_start += BCN_ATTR_START_OFFSET;
			attr_len = (ie_len - 4);
			ret = RTW_PHL_STATUS_SUCCESS;
		}
		break;
	case WIFI_ACTION:
		attr_len = (precv_frame_len - wlan_hdr_len);

		if (_rtw_memcmp(pnan_attr_start + 2, NAN_OUI_SDF, 4)) {
			pnan_attr_start += SDF_ATTR_START_OFFSET;
			attr_len -= SDF_ATTR_START_OFFSET;
			ret = RTW_PHL_STATUS_SUCCESS;
		}
#ifdef CONFIG_NAN_R2
		else if (_rtw_memcmp(pnan_attr_start + 2, NAN_OUI_NAF, 4)) {
			pnan_attr_start += NAF_ATTR_START_OFFSET;
			attr_len -= NAF_ATTR_START_OFFSET;
			ret = RTW_PHL_STATUS_SUCCESS;
		}
#endif
		break;
	default:
		break;
	}

	if (ret != RTW_PHL_STATUS_SUCCESS)
		return ret;

	*ppattr_start = pnan_attr_start;
	if (total_len) *total_len = attr_len;

	return ret;
}

enum rtw_phl_status rtw_core_nan_get_frame_body(u8 *precv_frame,
						u16 precv_frame_len,
						u8 **ppframe_body,
						u16 *frame_body_len)
{
	if (!precv_frame || precv_frame_len <= sizeof(struct rtw_ieee80211_hdr_3addr))
		return RTW_PHL_STATUS_FAILURE;

	if (ppframe_body)
		*ppframe_body = precv_frame + sizeof(struct rtw_ieee80211_hdr_3addr);
	if (frame_body_len)
		*frame_body_len = precv_frame_len - sizeof(struct rtw_ieee80211_hdr_3addr);

	return RTW_PHL_STATUS_SUCCESS;
}

enum rtw_phl_status rtw_core_nan_report_to_osdep(
					void *drv_priv, u8* addr,
					enum rtw_phl_nan_report_type type,
					void *param, u16 param_len)
{
	enum rtw_phl_status ret = RTW_PHL_STATUS_FAILURE;
	_adapter *nan_adpt = dvobj_get_adapter_by_addr(drv_priv, addr);

	switch (type) {
	case NAN_REPORT_RX_MATCH_SERVICE:
		RTW_INFO("%s: NAN_REPORT_RX_MATCH_SERVICE\n", __func__);
		rtw_cfg80211_nan_handle_sdf(
			nan_adpt, (struct rtw_phl_nan_rpt_match_srv *)param);
		ret = RTW_PHL_STATUS_SUCCESS;
		break;
	case NAN_REPORT_RX_DISC_RESULT:
		break;
	case NAN_REPORT_RX_MATCH_FOLLOWUP:
		break;
	case NAN_REPORT_REPLY_PUBLISH:
		break;
	case NAN_REPORT_REPLY_FOLLOWUP:
		break;
	case NAN_REPORT_RM_PUBLISH:
		break;
	case NAN_REPORT_RM_SUBSCRIBE:
		break;
#ifdef CONFIG_NAN_R2
	case NAN_REPORT_DATA_INDICATION:
		rtw_cfgvendor_nan_data_indic_evt(
			nan_adpt, (struct rtw_phl_nan_rpt_data_indication *)param);
		ret = RTW_PHL_STATUS_SUCCESS;
		break;
	case NAN_REPORT_DATA_CONFIRM:
		rtw_cfgvendor_nan_data_confirm_evt(
			nan_adpt, (struct rtw_phl_nan_rpt_data_confirm *)param);
		ret = RTW_PHL_STATUS_SUCCESS;
		break;
	case NAN_REPORT_DATA_TERMINATION:
		rtw_cfgvendor_nan_data_term_evt(
			nan_adpt, (struct rtw_phl_nan_rpt_data_termination *)param);
		ret = RTW_PHL_STATUS_SUCCESS;
		break;
#endif
	default:
		break;
	}

	return ret;
}

enum rtw_phl_status rtw_core_nan_alloc_peer_sta_info(void *drv_priv,
						     u8 *nan_addr,
						     u8 *peer_addr, u8 *ht_cap,
						     u8 *vht_cap, u8 *macid,
						     u8 is_ndi)
{
	_adapter *nan_adp = dvobj_get_adapter_by_addr(drv_priv, nan_addr);
	void *phl = GET_PHL_INFO(adapter_to_dvobj(nan_adp));
	struct sta_priv	*pstapriv = &nan_adp->stapriv;
	/* ToDo CONFIG_RTW_MLD: [currently primary link only] */
	struct _ADAPTER_LINK *padapter_link = GET_PRIMARY_LINK(nan_adp);
	struct link_mlme_ext_priv *pmlmeext = &padapter_link->mlmeextpriv;
	struct rtw_phl_mld_t *mld = NULL;
	struct sta_info *peer_sta = NULL;
	u8 *pcap_mcs = NULL;
	u8 null_arr[VHT_CAP_IE_LEN] = {0};
	u8 peer_band = 0;

	peer_sta = rtw_get_stainfo(pstapriv, peer_addr);
	if (NULL == peer_sta) {
		mld = rtw_phl_alloc_mld(phl, nan_adp->phl_role, peer_addr, DTYPE);
		if (NULL == mld) {
			RTW_ERR("[%s] rtw_phl_alloc_mld fail\n", __func__);
			return RTW_PHL_STATUS_FAILURE;
		}
		/* Allocate stainfo on the link where AP receives the auth req */
		peer_sta = rtw_alloc_stainfo_sw(pstapriv, DTYPE,
						rtw_phl_get_macid_max_num(phl),
						padapter_link->wrlink->id,
						peer_addr);
		if (NULL == peer_sta) {
			RTW_ERR("[%s] rtw_alloc_stainfo_sw fail\n", __func__);
			rtw_free_mld_stainfo(nan_adp, mld);
			return RTW_PHL_STATUS_FAILURE;
		}

		rtw_phl_link_mld_stainfo(mld, peer_sta->phl_sta);
	}

	if (macid)
		*macid = peer_sta->phl_sta->macid;

	/* set ht/vht/he cap */
#ifdef CONFIG_80211AX_HE
	peer_sta->hepriv.he_option == _FALSE;
#endif
#ifdef CONFIG_80211AC_VHT
	if (_FALSE == _rtw_memcmp(vht_cap, null_arr, VHT_CAP_IE_LEN)) {
		peer_sta->vhtpriv.vht_option = _TRUE;
		pcap_mcs = GET_VHT_CAPABILITY_ELE_RX_MCS(vht_cap);
		_rtw_memcpy(peer_sta->vhtpriv.vht_mcs_map, pcap_mcs, 2);
	}
#endif
#ifdef CONFIG_80211N_HT
	peer_sta->htpriv.ht_option = _TRUE;
	_rtw_memcpy((void *)&peer_sta->htpriv.ht_cap,
		    &ht_cap,
		    sizeof(struct rtw_ieee80211_ht_cap));
#endif

	/* set as connected */
	rtw_alloc_stainfo_hw(pstapriv, peer_sta);
	update_sta_ra_info(nan_adp, peer_sta);

#ifdef CONFIG_80211N_HT
#ifdef CONFIG_80211AC_VHT
#ifdef CONFIG_80211AX_HE
	if (peer_sta->hepriv.he_option == _TRUE)
		peer_band = WLAN_MD_11AX;
	else
#endif
	if (peer_sta->vhtpriv.vht_option == _TRUE)
		peer_band = WLAN_MD_11AC;
	else
#endif
	if (peer_sta->htpriv.ht_option == _TRUE)
		peer_band = WLAN_MD_11N;
#endif
	if (pmlmeext->chandef.chan > 14) {
		peer_band |= WLAN_MD_11A;
	} else {
		if ((cckratesonly_included(peer_sta->bssrateset,
					   peer_sta->bssratelen)) == _TRUE)
			peer_band |= WLAN_MD_11B;
		else if ((cckrates_included(peer_sta->bssrateset,
					    peer_sta->bssratelen)) == _TRUE)
			peer_band |= WLAN_MD_11BG;
		else
			peer_band |= WLAN_MD_11G;
	}
	peer_sta->phl_sta->wmode = peer_band & nan_adp->registrypriv.wireless_mode;

	return RTW_PHL_STATUS_SUCCESS;
}

enum rtw_phl_status rtw_core_nan_free_peer_sta_info(
				void *drv_priv,
				u8 *nan_addr,
				struct rtw_phl_stainfo_t *peer_phl_sta_info)
{
	enum rtw_phl_status ret = RTW_PHL_STATUS_FAILURE;
	_adapter *nan_adp = dvobj_get_adapter_by_addr(drv_priv, nan_addr);
	void *phl = GET_PHL_INFO(adapter_to_dvobj(nan_adp));

	ret = rtw_phl_cmd_update_media_status(phl, peer_phl_sta_info,
					      peer_phl_sta_info->mac_addr, false,
					      PHL_CMD_DIRECTLY, 0);

	/* Free sta info : core sta, phl sta and mld */
	rtw_free_mld_stainfo(nan_adp, peer_phl_sta_info->mld);

	return ret;
}

#ifdef CONFIG_NAN_R2
enum rtw_phl_status rtw_core_nan_set_pairwise_key(void *drv_priv, u8 *nan_addr,
						  u8 *key, u8 key_len,
						  u8 *peer_ndi)
{
	_adapter *nan_adp = dvobj_get_adapter_by_addr(drv_priv, nan_addr);
	struct sta_priv	*pstapriv = &nan_adp->stapriv;
	struct sta_info *peer_sta = NULL;

	peer_sta = rtw_get_stainfo(pstapriv, peer_ndi);
	if (!peer_sta || key_len > NCS_SK_128_TK_LEN) {
		RTW_ERR("%s fail, check peer sta["MAC_FMT"] or key_len(%d)\n",
			__func__, MAC_ARG(peer_ndi), key_len);
		return RTW_PHL_STATUS_FAILURE;
	}

	_rtw_memset(peer_sta->dot118021x_UncstKey.skey, 0, NCS_SK_128_TK_LEN);

	if (NULL == key || 0 == key_len) {
		/* nan_adp->securitypriv.dot11wCipher = _NO_PRIVACY_; */
		nan_adp->securitypriv.dot11PrivacyAlgrthm = _NO_PRIVACY_;
		peer_sta->dot118021XPrivacy = _NO_PRIVACY_;
		peer_sta->flags &= ~WLAN_STA_MFP;
		peer_sta->bpairwise_key_installed = _FALSE;
		RTW_INFO("%s rmv key for peer sta["MAC_FMT"]\n",
			 __func__, MAC_ARG(peer_ndi));
	} else {
		/* nan_adp->securitypriv.dot11wCipher = _AES_; */
		nan_adp->securitypriv.dot11PrivacyAlgrthm = _AES_;
		nan_adp->securitypriv.dot11AuthAlgrthm = dot11AuthAlgrthm_8021X;
		_rtw_memcpy(peer_sta->dot118021x_UncstKey.skey, key, key_len);
		peer_sta->dot118021XPrivacy = _AES_;
		peer_sta->flags |= WLAN_STA_MFP;
		peer_sta->dot11txpn.val = 0;
		peer_sta->bpairwise_key_installed = _TRUE;

		RTW_INFO("%s add key for peer_ndi["MAC_FMT"]\n",
			 __func__, MAC_ARG(peer_ndi));
	}

	rtw_ap_set_pairwise_key(nan_adp, peer_sta);

	return RTW_PHL_STATUS_SUCCESS;
}

enum rtw_phl_status rtw_core_nan_pmk_to_ptk(u8 cipher_suite, u8 *pmk,
					    size_t pmk_len, char *label,
					    u8 *i_addr, u8 *r_addr,
					    u8 *i_nonce, u8 *r_nonce,
					    struct rtw_phl_nan_wpa_ptk *ptk)
{
	enum rtw_phl_status ret_stat = RTW_PHL_STATUS_FAILURE;
	u8 data[2 * ETH_ALEN + 2 * WPA_NONCE_LEN] = {0};
	u8 tmp[MAX_WPA_KCK_LEN + MAX_WPA_KEK_LEN + MAX_WPA_TK_LEN] = {0};
	size_t ptk_len = 0;

	/* concatenation MAC address */
	_rtw_memcpy(data, i_addr, ETH_ALEN);
	_rtw_memcpy(data + ETH_ALEN, r_addr, ETH_ALEN);

	/* concatenation NONCE */
	_rtw_memcpy(data + 2 * ETH_ALEN, i_nonce, WPA_NONCE_LEN);
	_rtw_memcpy(data + 2 * ETH_ALEN + WPA_NONCE_LEN, r_nonce, WPA_NONCE_LEN);

	switch (cipher_suite) {
	case NCS_SK_128:
		/* default use SHA-256 for NAN Security only */
		ptk->kck_len = NCS_SK_128_KCK_LEN;
		ptk->kek_len = NCS_SK_128_KEK_LEN;
		ptk->tk_len = NCS_SK_128_TK_LEN;
		ptk_len = ptk->kck_len + ptk->kek_len + ptk->tk_len;

		sha256_prf(pmk, pmk_len, label, data, sizeof(data), tmp, ptk_len);

		RTW_INFO("NAN: PTK derivation - Initiator="MAC_FMT" Responder="MAC_FMT,
		         MAC_ARG(i_addr), MAC_ARG(r_addr));
		RTW_INFO_DUMP("NAN: INonce\n", (void *)i_nonce, WPA_NONCE_LEN);
		RTW_INFO_DUMP("NAN: RNonce\n", (void *)r_nonce, WPA_NONCE_LEN);
		RTW_INFO_DUMP("NAN: PMK\n", (void *)pmk, pmk_len);
		RTW_INFO_DUMP("NAN: PTK\n", (void *)tmp, ptk_len);

		_rtw_memcpy(ptk->kck, tmp, ptk->kck_len);
		_rtw_memcpy(ptk->kek, tmp + ptk->kck_len, ptk->kek_len);
		_rtw_memcpy(ptk->tk, tmp + ptk->kck_len + ptk->kek_len, ptk->tk_len);

		_rtw_memset(tmp, 0, MAX_WPA_KCK_LEN + MAX_WPA_KEK_LEN + MAX_WPA_TK_LEN);

		ret_stat = RTW_PHL_STATUS_SUCCESS;
		break;
	default:
		RTW_WARN("%s: cipher suite(%d) not support!\n", __func__, cipher_suite);
		break;
	}

	return ret_stat;
}

enum rtw_phl_status rtw_core_nan_get_key_mic(u8 cipher_suite, u8 *key,
					     u8 *auth_token, u32 auth_token_len,
					     u8 *data, u32 data_len, u8 *mic)
{
	enum rtw_phl_status ret_stat = RTW_PHL_STATUS_SUCCESS;
	const u8 *addr[2];
	size_t len[2] = {0};
	u8 empty_auth[AUTH_TOKEN_LEN] = {0};
	u8 hash[SHA256_MAC_LEN] = {0};

	if (cipher_suite != NCS_SK_128) {
		RTW_WARN("%s: cipher suite(%d) not support!\n", __func__, cipher_suite);
		return RTW_PHL_STATUS_FAILURE;
	}

	/* cal mic without auth token */
	if (0 == auth_token_len ||
	    _TRUE == _rtw_memcmp(empty_auth, auth_token, AUTH_TOKEN_LEN)) {
		if (0 != hmac_sha256(key, NCS_SK_128_KCK_LEN, data, data_len, hash)) {
			RTW_ERR("%s: hmac_sha256 fail!\n", __func__);
			ret_stat = RTW_PHL_STATUS_FAILURE;
		}
		goto exit;
	}

	/* cal mic with auth token */
	addr[0] = auth_token;
	len[0] = auth_token_len;
	addr[1] = data;
	len[1] = data_len;
	if (0 != hmac_sha256_vector(key, NCS_SK_128_KCK_LEN, 2, addr, len, hash)) {
		RTW_ERR("%s: hmac_sha256_vector fail!\n", __func__);
		ret_stat = RTW_PHL_STATUS_FAILURE;
	}

exit:
	if (RTW_PHL_STATUS_SUCCESS == ret_stat)
		_rtw_memcpy(mic, hash, NCS_SK_128_KEY_MIC_LEN);

	RTW_INFO_DUMP("NAN: MIC\n", (void *)mic, NCS_SK_128_KEY_MIC_LEN);

	return ret_stat;
}

enum rtw_phl_status rtw_core_nan_get_auth_token(u8 *buf, size_t buf_len,
						u8 *auth_token)
{
	enum rtw_phl_status ret_stat = RTW_PHL_STATUS_SUCCESS;
	unsigned char hash[SHA256_MAC_LEN] = {0};
	const u8 *addr[1];
	size_t len[1];

	addr[0] = buf;
	len[0] = buf_len;
	if (0 != sha256_vector(1, addr, len, hash)) {
		RTW_ERR("%s: sha256_vector fail!\n", __func__);
		ret_stat = RTW_PHL_STATUS_FAILURE;
	} else {
		_rtw_memcpy(auth_token, hash, AUTH_TOKEN_LEN);
	}

	RTW_INFO_DUMP("NAN: Auth Token\n", (void *)auth_token, AUTH_TOKEN_LEN);

	return ret_stat;
}

enum rtw_phl_status rtw_core_nan_get_pmkid(u8 *pmk, size_t pmk_len, u8 *iaddr,
					   u8 *raddr, u8 *srvc_id, u8 *pmkid)
{
	enum rtw_phl_status ret_stat = RTW_PHL_STATUS_SUCCESS;
	char *title = "NAN PMK Name";
	const u8 *addr[4];
	size_t len[4] = {12, ETH_ALEN, ETH_ALEN, SDA_SERVICE_ID_LEN};
	unsigned char hash[SHA256_MAC_LEN] = {0};

	addr[0] = (u8 *)title;
	addr[1] = iaddr;
	addr[2] = raddr;
	addr[3] = srvc_id;
	if (0 != hmac_sha256_vector(pmk, pmk_len, 4, addr, len, hash)) {
		RTW_ERR("%s: hmac_sha256_vector fail!\n", __func__);
		ret_stat = RTW_PHL_STATUS_FAILURE;
	} else {
		_rtw_memcpy(pmkid, hash, PMKID_LEN);
	}

	return ret_stat;
}

u8 rtw_core_nan_is_any_ndl_exist(_adapter *adapter)
{
	struct rtw_wifi_role_t *wrole = adapter->phl_role;
	struct phl_info_t *phl_info = GET_PHL_INFO(adapter_to_dvobj(adapter));
	u8 *self_nmi = NULL;

	self_nmi = rtw_phl_nan_get_wrole_addr(phl_info);
	if (_FALSE == _rtw_memcmp(self_nmi, adapter->mac_addr, ETH_ALEN)) {
		RTW_DBG("%s: not nan adapter, "MAC_FMT" role_type(%d)\n",
			__func__, MAC_ARG(adapter->mac_addr), wrole->type);
		return _FALSE;
	}

	if (_FALSE == rtw_phl_nan_schdlr_is_any_ndl_exist(phl_info)) {
		RTW_DBG("%s: ndl does not exist\n", __func__);
		return _FALSE;
	}

	return _TRUE;
}

u8 rtw_core_nan_updt_tx_pkt_attr(_adapter *adapter, struct pkt_attrib *pattrib)
{
	struct phl_info_t *phl_info = GET_PHL_INFO(adapter_to_dvobj(adapter));
	void *peer_info = NULL;
	u8 *self_nmi = NULL;

	/* get dst ip addr from IPv6 header to decide is nan frame or not */
	peer_info = rtw_phl_nan_chk_ndl_exist(phl_info, pattrib->dst);
	if (NULL == peer_info) {
#ifdef CONFIG_NAN_PAIRING
		if (IS_IPV6_MCAST(pattrib->dst) &&
		    rtw_nan_get_first_peer_info_entry(adapter_to_nan_priv(adapter),
						      &peer_info, _TRUE)) {
			goto updt;
		}
#endif
		return _FALSE;
	}
updt:
	self_nmi = rtw_phl_nan_get_wrole_addr(phl_info);
	_rtw_memcpy(pattrib->ra, pattrib->dst, ETH_ALEN);
	_rtw_memcpy(pattrib->ta, self_nmi, ETH_ALEN);
	pattrib->peer_info = peer_info;
	pattrib->nan_pkt_type = NAN_PKT_TYPE_DATA;

	return _TRUE;
}

void rtw_core_nan_updt_tx_wlanhdr(_adapter *adapter, struct pkt_attrib *pattrib,
				  struct rtw_ieee80211_hdr *pwlanhdr)
{
	struct phl_info_t *phl_info = GET_PHL_INFO(adapter_to_dvobj(adapter));
	u8 *clus_id = NULL;
	u8 *self_nmi = NULL;

	switch (pattrib->nan_pkt_type) {
	case NAN_PKT_TYPE_DATA:
		/* NAN data transfer, ToDS=0, FrDs=0 */
		self_nmi = rtw_phl_nan_get_wrole_addr(phl_info);
		clus_id = rtw_phl_nan_get_clus_id(phl_info);
		_rtw_memcpy(pwlanhdr->addr1, pattrib->dst, ETH_ALEN);
		_rtw_memcpy(pwlanhdr->addr2, self_nmi, ETH_ALEN);
		_rtw_memcpy(pwlanhdr->addr3, clus_id, ETH_ALEN);
		RTW_INFO("%s: bssid "MAC_FMT"\n", __func__, MAC_ARG(pwlanhdr->addr3));
		break;
	default:
		RTW_INFO("%s: not support nan pkt type(%d)\n",
			 __func__, pattrib->nan_pkt_type);
		break;
	}
}

u8 rtw_core_nan_rx_data_validate_hdr(_adapter *adapter,
				     union recv_frame *rframe,
				     struct sta_info **sta)
{
	u8 ret = _TRUE;
	u8 *ptr = rframe->u.hdr.rx_data;
	struct rx_pkt_attrib *attrib = &rframe->u.hdr.attrib;
	struct sta_priv *stapriv = &adapter->stapriv;

	switch (attrib->to_fr_ds) {
	case 0:
		_rtw_memcpy(attrib->ra, GetAddr1Ptr(ptr), ETH_ALEN);
		_rtw_memcpy(attrib->ta, get_addr2_ptr(ptr), ETH_ALEN);
		_rtw_memcpy(attrib->dst, GetAddr1Ptr(ptr), ETH_ALEN);
		_rtw_memcpy(attrib->src, get_addr2_ptr(ptr), ETH_ALEN);
		_rtw_memcpy(attrib->bssid, GetAddr3Ptr(ptr), ETH_ALEN);
		*sta = rtw_get_stainfo(stapriv, attrib->src);
		break;
	case 1:
		_rtw_memcpy(attrib->ra, GetAddr1Ptr(ptr), ETH_ALEN);
		_rtw_memcpy(attrib->ta, get_addr2_ptr(ptr), ETH_ALEN);
		_rtw_memcpy(attrib->dst, GetAddr1Ptr(ptr), ETH_ALEN);
		_rtw_memcpy(attrib->src, GetAddr3Ptr(ptr), ETH_ALEN);
		_rtw_memcpy(attrib->bssid, get_addr2_ptr(ptr), ETH_ALEN);
		*sta = rtw_get_stainfo(stapriv, attrib->src);
		break;
	case 2:
		_rtw_memcpy(attrib->ra, GetAddr1Ptr(ptr), ETH_ALEN);
		_rtw_memcpy(attrib->ta, get_addr2_ptr(ptr), ETH_ALEN);
		_rtw_memcpy(attrib->dst, GetAddr3Ptr(ptr), ETH_ALEN);
		_rtw_memcpy(attrib->src, get_addr2_ptr(ptr), ETH_ALEN);
		_rtw_memcpy(attrib->bssid, GetAddr1Ptr(ptr), ETH_ALEN);
		*sta = rtw_get_stainfo(stapriv, attrib->src);
		break;
	default:
		/* WDS is not supported */
		RTW_INFO("%s: to_fr_ds(%d) not support\n", __func__, attrib->to_fr_ds);
		ret = _FALSE;
		break;
	}

	if (NULL == *sta)
		ret = _FALSE;

	if (_TRUE != ret)
		RTW_INFO("%s: to_fr_ds(%d), ret(%d)\n", __func__, attrib->to_fr_ds, ret);

	return ret;
}
#endif

int rtw_core_nan_priv_init(_adapter *adapter) {
	struct dvobj_priv *dvobj = adapter_to_dvobj(adapter);
	struct nan_priv *nanpriv = dvobj_to_nan(dvobj);

	_rtw_init_queue(&nanpriv->nan_func_q);

	return _SUCCESS;
}

int rtw_core_nan_priv_deinit(_adapter *adapter) {
	struct dvobj_priv *dvobj = adapter_to_dvobj(adapter);
	struct nan_priv *nanpriv = dvobj_to_nan(dvobj);

	_rtw_deinit_queue(&nanpriv->nan_func_q);

	return _SUCCESS;
}

static int nan_ss_complete_notify_cb(struct rtw_phl_nan_ss_param *param)
{
	_adapter *nan_adpt = (_adapter*)param->priv;

	if (nan_adpt->nan_start_stop_sctx &&
	    nan_adpt->nan_start_stop_sctx->status == RTW_SCTX_SUBMITTED)
		rtw_sctx_done(&nan_adpt->nan_start_stop_sctx);

	rtw_mfree(param, sizeof(*param));

	return 0;
}

static int nan_ss_stop_prepare_notify_cb(struct rtw_phl_nan_ss_param *param)
{
	return 0;
}

static struct rtw_phl_nan_ss_ops nan_start_stop_cb = {
	.nan_start_complete_notify = nan_ss_complete_notify_cb,
	.nan_stop_prepare_notify = nan_ss_stop_prepare_notify_cb,
	.nan_stop_complete_notify = nan_ss_complete_notify_cb,
};

int rtw_nan_start_stop_cmd(_adapter *adapter, u8 start, u8 is_rmmod,
			   enum rtw_phl_nan_cmd_type cmd_type, u8 master_pref,
			   u8 bands)
{
	struct dvobj_priv *dvobj = adapter_to_dvobj(adapter);
	void *phl_info = GET_PHL_INFO(dvobj);
	struct rtw_phl_com_t *phl_com = GET_PHL_COM(dvobj);
	/* ToDo CONFIG_RTW_MLD: [currently primary link only] */
	struct _ADAPTER_LINK *adapter_link = GET_PRIMARY_LINK(adapter);
	struct rtw_phl_nan_ss_param *phl_param = NULL;
	struct submit_ctx sctx;
	int ret = 0;

	if (phl_com->dev_cap.nan_sup != _TRUE) {
		RTW_ERR("%s: Driver does not support NAN mode!\n", __func__);
		return -ENOTCONN;
	}

	if (adapter->phl_role == NULL) {
		RTW_ERR("%s phl_role is NULL\n", __func__);
		return -ENOTCONN;
	}

	/* TODO: we should use the PHL API to get the token, and if the token is
	 * non-zero, we should return a fail to ensure that only 1 nan ss fg cmd
	 * exists.
	 */

	if (ATOMIC_ADD_RETURN(&adapter->nan_ss_in_progress, 1) != 1) {
		RTW_INFO("%s: func is executing, skip nan %s cmd\n",
			 __func__, start ? "start" : "stop");
		ATOMIC_DEC(&adapter->nan_ss_in_progress);
		return 0;
	}

	if (start == _TRUE) {
		if (rtw_phl_nan_if_session_on(phl_info)) {
			RTW_WARN("%s: previous nan may start successfully but timed out, return success\n", __func__);
			goto exit;
		} else if (rtw_phl_nan_if_session_init(phl_info)) {
			RTW_ERR("%s: nan initialized but not started, unknown case!\n", __func__);
			ret = -ENOTCONN;
			goto exit;
		}
	} else {
		if (!rtw_phl_nan_if_session_on(phl_info)) {
			RTW_INFO("%s nan session is not started\n", __func__);
			goto exit;
		}

		if (_FALSE == _rtw_memcmp(adapter->mac_addr,
					  rtw_phl_nan_get_wrole_addr(phl_info),
					  ETH_ALEN)) {
			RTW_ERR("%s not nan adapter\n", __func__);
			goto exit;
		}
	}

	if (dev_is_surprise_removed(dvobj) && start == _FALSE) {
		struct rtw_phl_nan_ss_param temp_param;

		RTW_INFO("%s stop nan directly when the device is superise removed\n", __func__);

		temp_param.priv = (void*)adapter;
		nan_ss_stop_prepare_notify_cb(&temp_param);

		rtw_phl_nan_stop_directly(phl_info);
		goto exit;
	}

	phl_param = rtw_zmalloc(sizeof(struct rtw_phl_nan_ss_param));
	if (phl_param == NULL) {
		RTW_ERR("%s alloc phl_param fail\n", __func__);
		ret = -ENOTCONN;
		goto exit;
	}

	phl_param->phl_role = adapter->phl_role;
	phl_param->rlink = adapter_link->wrlink;

	if (start == _TRUE) {
		phl_param->nan_cmd_type = cmd_type;
		phl_param->master_pref = master_pref;
		phl_param->bands = bands;
	} else {
		phl_param->is_rmmod = is_rmmod;
	}

	phl_param->start = start;

	phl_param->ops = &nan_start_stop_cb;
	phl_param->priv = adapter;

	if (rtw_phl_cmd_nan_ss_req(phl_info, phl_param) != RTW_PHL_STATUS_SUCCESS) {
		RTW_ERR("%s request nan %s failed\n",
			__func__, start ? "start" : "stop");
		if (!start) {
			nan_ss_stop_prepare_notify_cb(phl_param);
			rtw_phl_nan_stop_directly(phl_info);
		}
		rtw_mfree(phl_param, sizeof(*phl_param));
		ret = -ENOTCONN;
		goto exit;
	}

	adapter->nan_start_stop_sctx = &sctx;
	rtw_sctx_init(&sctx, 2000);
	rtw_sctx_wait(&sctx, __func__);
	adapter->nan_start_stop_sctx = NULL;
	if (sctx.status == RTW_SCTX_DONE_TIMEOUT)
		RTW_ERR("%s: nan start stop cmd timeout\n", __func__);

	if (start == _TRUE) {
		if (!rtw_phl_nan_if_session_on(phl_info)) {
			/* TODO: if the FG cmd completes at this point, then
			 * phl_param has been freed. Therefore, we should
			 * additionally record the token in PHL and use the PHL
			 * API to obtain the token value.
			 */
			rtw_phl_cancel_cmd_token(phl_info,
						 adapter_link->wrlink->hw_band,
						 &phl_param->token);
			ret = -ENOTCONN;
			goto exit;
		}
	}

exit:
	ATOMIC_DEC(&adapter->nan_ss_in_progress);

	return ret;
}
#endif /* CONFIG_NAN */
