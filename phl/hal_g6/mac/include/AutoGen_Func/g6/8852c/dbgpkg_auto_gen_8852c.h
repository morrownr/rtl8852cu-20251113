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
#ifndef _MAC_AX_DBGPKG_AUTO_GEN_8852C_H_
#define _MAC_AX_DBGPKG_AUTO_GEN_8852C_H_

#include "../../../../mac_def.h"
#include "../../../mac_top.h"

#if MAC_AX_FEATURE_DBGPKG
#if MAC_AX_8852C_SUPPORT

// svn reversion
#define DBG_PORT_REV_8852C 0

u32 dbg_port_cmac_8852c(struct mac_ax_adapter *adapter,
			u32 isr_mod, u8 band);

u32 dbg_port_dmac_8852c(struct mac_ax_adapter *adapter,
			u32 isr_mod);

#endif /* MAC_AX_8852C_SUPPORT */
#endif /* _MAC_AX_FEATURE_DBGPKG  */
#endif /* _MAC_AX_DBGPKG_AUTO_GEN_8852C_H_ */