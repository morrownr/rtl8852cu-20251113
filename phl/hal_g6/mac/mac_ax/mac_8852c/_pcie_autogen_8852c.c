#include "_pcie_8852c.h"

#if MAC_AX_8852C_SUPPORT
#if MAC_AX_FEATURE_DBGPKG
#if MAC_AX_PCIE_SUPPORT

static u32 pcie_RASDES_START(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x178, &val);
	val = SET_CLR_WOR3(val, 0x14, 0xFF);
	PLTFM_PCIE_CFG_W32(0x178, &val);
	return MACSUCCESS;
}

static u32 pcie_RASDES_L1_to_recovery(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x178, &val);
	val = SET_CLR_WOR3(val, 0x05010000, 0xFFFF0000);
	PLTFM_PCIE_CFG_W32(0x178, &val);

	PLTFM_PCIE_CFG_R32(0x17C, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "L1 to recovery: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_RASDES_L0_to_Recovery(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x178, &val);
	val = SET_CLR_WOR3(val, 0x05000000, 0xFFFF0000);
	PLTFM_PCIE_CFG_W32(0x178, &val);

	PLTFM_PCIE_CFG_R32(0x17C, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "L0 to Recovery: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_RASDES_L1_entry(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x178, &val);
	val = SET_CLR_WOR3(val, 0x05050000, 0xFFFF0000);
	PLTFM_PCIE_CFG_W32(0x178, &val);

	PLTFM_PCIE_CFG_R32(0x17C, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "L1 entry: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_RASDES_L1_2_entry(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x178, &val);
	val = SET_CLR_WOR3(val, 0x05080000, 0xFFFF0000);
	PLTFM_PCIE_CFG_W32(0x178, &val);

	PLTFM_PCIE_CFG_R32(0x17C, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "L1.2 entry: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_RASDES_Rx_Nak_DLLP(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x178, &val);
	val = SET_CLR_WOR3(val, 0x02050000, 0xFFFF0000);
	PLTFM_PCIE_CFG_W32(0x178, &val);

	PLTFM_PCIE_CFG_R32(0x17C, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "Rx Nak DLLP: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_RASDES_Tx_Nak_DLLP(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x178, &val);
	val = SET_CLR_WOR3(val, 0x02060000, 0xFFFF0000);
	PLTFM_PCIE_CFG_W32(0x178, &val);

	PLTFM_PCIE_CFG_R32(0x17C, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "Tx Nak DLLP: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_RASDES_Retry_TLP(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x178, &val);
	val = SET_CLR_WOR3(val, 0x02070000, 0xFFFF0000);
	PLTFM_PCIE_CFG_W32(0x178, &val);

	PLTFM_PCIE_CFG_R32(0x17C, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "Retry TLP: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_RASDES_END(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x178, &val);
	val = SET_CLR_WOR3(val, 0x3, 0x3);
	PLTFM_PCIE_CFG_W32(0x178, &val);

	PLTFM_PCIE_CFG_R32(0x178, &val);
	val = SET_CLR_WOR3(val, 0x1C, 0xFF);
	PLTFM_PCIE_CFG_W32(0x178, &val);
	return MACSUCCESS;
}

static u32 pcie_PCIe_cfg_spc_bus_master(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x4, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "bus_master: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_PCIe_cfg_spc_BAR(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x18, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "BAR: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_PCIe_cfg_spc_D_State(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x44, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "D_State: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_PCIe_cfg_spc_MSI_Ctrl(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x50, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "MSI_Ctrl: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_PCIe_cfg_spc_Device_Cap(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x74, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "Device Cap: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_PCIe_cfg_spc_Device_Ctrl(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x78, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "Device Ctrl: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_PCIe_cfg_spc_Link_Cap(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x7C, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "Link Cap: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_PCIe_cfg_spc_Link_Ctrl(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x80, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "Link Ctrl: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_PCIe_cfg_spc_Device_Ctrl_2(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x98, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "Device Ctrl 2: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_PCIe_cfg_spc_Target_speed(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0xA0, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "Target_speed: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_PCIe_cfg_spc_AER_UNCORR_ERR_STS(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x104, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "AER_UNCORR_ERR_STS: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_PCIe_cfg_spc_AER_CORR_ERR_STS(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x11C, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "AER_CORR_ERR_STS: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_PCIe_cfg_spc_AER_hdr_log_1(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x120, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "AER hdr log 1: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_PCIe_cfg_spc_AER_hdr_log_2(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x124, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "AER hdr log 2: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_PCIe_cfg_spc_AER_hdr_log_3(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x128, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "AER hdr log 3: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_PCIe_cfg_spc_AER_hdr_log_4(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x110, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "AER hdr log 4: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_PCIe_cfg_spc_L1ss(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;

	PLTFM_PCIE_CFG_R32(0x168, &val);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "L1ss: %x\n", val);
	return MACSUCCESS;
}

static u32 pcie_PCIe_local_L1_local(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;
	u32 shift = 0;
	u32 mask = 0xffffffff;
	u32 temp = mask;

	while ((temp & 1) == 0) {
		shift++;
		temp >>= 1;
	}
	val = adapter->ops->intf_ops->reg_read32(adapter, 0x300C);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "L1_local: %x\n", (val & mask) >> shift);
	return MACSUCCESS;
}

static u32 pcie_PCIe_local_clkpm_local(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;
	u32 shift = 0;
	u32 mask = 0x3;
	u32 temp = mask;

	while ((temp & 1) == 0) {
		shift++;
		temp >>= 1;
	}
	val = adapter->ops->intf_ops->reg_read32(adapter, 0x3010);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "clkpm_local: %x\n", (val & mask) >> shift);
	return MACSUCCESS;
}

static u32 pcie_PCIe_local_EMAC_delay(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	u32 val = 0;
	u32 shift = 0;
	u32 mask = 0xF0;
	u32 temp = mask;

	while ((temp & 1) == 0) {
		shift++;
		temp >>= 1;
	}
	val = adapter->ops->intf_ops->reg_read32(adapter, 0x3044);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "EMAC delay: %x\n", (val & mask) >> shift);
	return MACSUCCESS;
}

static u32 pcie_mon_RASDES(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "\n----- RASDES -----\n");
	pcie_RASDES_START(adapter, output, out_len, used);
	pcie_RASDES_L1_to_recovery(adapter, output, out_len, used);
	pcie_RASDES_L0_to_Recovery(adapter, output, out_len, used);
	pcie_RASDES_L1_entry(adapter, output, out_len, used);
	pcie_RASDES_L1_2_entry(adapter, output, out_len, used);
	pcie_RASDES_L1_2_entry(adapter, output, out_len, used);
	pcie_RASDES_Rx_Nak_DLLP(adapter, output, out_len, used);
	pcie_RASDES_Tx_Nak_DLLP(adapter, output, out_len, used);
	pcie_RASDES_Retry_TLP(adapter, output, out_len, used);
	pcie_RASDES_END(adapter, output, out_len, used);

	return MACSUCCESS;
}

static u32 pcie_mon_PCIe_cfg_spc(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "\n----- PCIe_cfg_spc -----\n");
	pcie_PCIe_cfg_spc_bus_master(adapter, output, out_len, used);
	pcie_PCIe_cfg_spc_BAR(adapter, output, out_len, used);
	pcie_PCIe_cfg_spc_D_State(adapter, output, out_len, used);
	pcie_PCIe_cfg_spc_MSI_Ctrl(adapter, output, out_len, used);
	pcie_PCIe_cfg_spc_Device_Cap(adapter, output, out_len, used);
	pcie_PCIe_cfg_spc_Device_Ctrl(adapter, output, out_len, used);
	pcie_PCIe_cfg_spc_Link_Cap(adapter, output, out_len, used);
	pcie_PCIe_cfg_spc_Link_Ctrl(adapter, output, out_len, used);
	pcie_PCIe_cfg_spc_Device_Ctrl_2(adapter, output, out_len, used);
	pcie_PCIe_cfg_spc_Target_speed(adapter, output, out_len, used);
	pcie_PCIe_cfg_spc_AER_UNCORR_ERR_STS(adapter, output, out_len, used);
	pcie_PCIe_cfg_spc_AER_CORR_ERR_STS(adapter, output, out_len, used);
	pcie_PCIe_cfg_spc_AER_hdr_log_1(adapter, output, out_len, used);
	pcie_PCIe_cfg_spc_AER_hdr_log_2(adapter, output, out_len, used);
	pcie_PCIe_cfg_spc_AER_hdr_log_3(adapter, output, out_len, used);
	pcie_PCIe_cfg_spc_AER_hdr_log_4(adapter, output, out_len, used);
	pcie_PCIe_cfg_spc_L1ss(adapter, output, out_len, used);

	return MACSUCCESS;
}

static u32 pcie_mon_PCIe_local(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "\n----- PCIe_local -----\n");
	pcie_PCIe_local_L1_local(adapter, output, out_len, used);
	pcie_PCIe_local_clkpm_local(adapter, output, out_len, used);
	pcie_PCIe_local_EMAC_delay(adapter, output, out_len, used);

	return MACSUCCESS;
}

u32 pcie_mon_8852c(struct mac_ax_adapter *adapter, char *output, u32 out_len, u32 *used)
{
	pcie_mon_RASDES(adapter, output, out_len, used);
	pcie_mon_PCIe_cfg_spc(adapter, output, out_len, used);
	pcie_mon_PCIe_local(adapter, output, out_len, used);

	return MACSUCCESS;
}
#endif /* MAC_AX_PCIE_SUPPORT */
#endif /* MAC_AX_FEATURE_DBGPKG */
#endif /* MAC_AX_8852C_SUPPORT */
