/******************************************************************************
 *
 * Copyright(c) 2007 - 2025 Realtek Corporation.
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
#define _RTW_IO_RECORDS_C_

#include <drv_types.h>

#ifdef CONFIG_RTW_IO_RECORDS
#include <rtw_io_records.h>

struct rtw_io_records dbg_rtw_io_records = {
#if CONFIG_RTW_IO_RECORDS_STATIC
	.record_num = CONFIG_RTW_IO_RECORDS_NUM,
	.enable = CONFIG_RTW_IO_RECORDS_ENABLE,
	.loop = CONFIG_RTW_IO_RECORDS_LOOP,
#endif
};

bool rtw_io_records_enabled(void)
{
	return dbg_rtw_io_records.enable;
}

void rtw_io_records_clear(void)
{
	int i;

	for (i = 0; i < dbg_rtw_io_records.record_num; i++)
		dbg_rtw_io_records.record[i].valid = false;
	dbg_rtw_io_records.pos = 0;
}

bool rtw_io_record_valid(size_t seq)
{
	if (seq < dbg_rtw_io_records.record_num) {
		size_t oldest_pos = dbg_rtw_io_records.record[dbg_rtw_io_records.pos].valid ? dbg_rtw_io_records.pos : 0;
		struct rtw_io_record *record = &dbg_rtw_io_records.record[(oldest_pos + seq) % dbg_rtw_io_records.record_num];

		return record->valid;
	}
	return false;
}

int rtw_io_records_init(void)
{
#if !CONFIG_RTW_IO_RECORDS_STATIC
extern uint rtw_io_records_num;
extern uint rtw_io_records_enable;
extern uint rtw_io_records_loop;

	size_t record_num = rtw_io_records_num;
	bool enable = !!rtw_io_records_enable;
	bool loop = !!rtw_io_records_loop;

	dbg_rtw_io_records.record = rtw_zvmalloc(sizeof(struct rtw_io_record) * record_num);
	if (!dbg_rtw_io_records.record)
		return _FAIL;

	dbg_rtw_io_records.record_num = record_num;
	dbg_rtw_io_records.loop = loop;
	dbg_rtw_io_records.pos = 0;
	dbg_rtw_io_records.enable = enable;
#endif
	return _SUCCESS;
}

void rtw_io_records_deinit(void)
{
#if !CONFIG_RTW_IO_RECORDS_STATIC
	if (dbg_rtw_io_records.record)
		rtw_vmfree(dbg_rtw_io_records.record, sizeof(struct rtw_io_record) * dbg_rtw_io_records.record_num);
#endif
}
#endif /* CONFIG_RTW_IO_RECORDS */
