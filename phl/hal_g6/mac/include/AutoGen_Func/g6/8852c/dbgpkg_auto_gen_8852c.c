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
#include "dbgpkg_auto_gen_8852c.h"
#include "../../../../mac_ax/mac_priv.h"

#if MAC_AX_FEATURE_DBGPKG
#if MAC_AX_8852C_SUPPORT

u32 dbg_port_cmac_8852c(struct mac_ax_adapter *adapter,
			u32 isr_mod, u8 band)
{
	return MACSUCCESS;
}

u32 dbg_port_dmac_8852c(struct mac_ax_adapter *adapter,
			u32 isr_mod)
{
	return MACSUCCESS;
}

#endif /* MAC_AX_8852C_SUPPORT */
#endif /* _MAC_AX_FEATURE_DBGPKG  */
