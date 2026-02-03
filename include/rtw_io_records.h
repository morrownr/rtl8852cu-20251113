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
#ifndef __RTW_IO_RECORDS_H_
#define __RTW_IO_RECORDS_H_

/*
* Data struct and utilities for HCI ops
*/
#ifdef CONFIG_RTW_IO_RECORDS
#ifndef DBG_RTW_IO_RECORD_DATA_LEN
#define DBG_RTW_IO_RECORD_DATA_LEN 4 /* record 4-byte at most by default */
#endif

#ifndef DBG_RTW_IO_RECORD_TASK_INFO
#define DBG_RTW_IO_RECORD_TASK_INFO 1
#endif

#ifndef DBG_RTW_IO_RECORD_CPU_INFO
#define DBG_RTW_IO_RECORD_CPU_INFO 1
#endif

struct rtw_io_record {
	bool valid;
	sysptime stime;
	sysptime etime;
	u8 type; /* enum, defined by each hci */
	u32 addr;
	u32 cnt;
	int err;
#if DBG_RTW_IO_RECORD_DATA_LEN
	u8 data[DBG_RTW_IO_RECORD_DATA_LEN];
#endif
#if DBG_RTW_IO_RECORD_TASK_INFO
	char task_comm[RTW_TASK_COMM_LEN]; /* get when io done */
#endif
#if DBG_RTW_IO_RECORD_CPU_INFO
	unsigned int cpu; /* get when io done */
#endif
};

struct rtw_io_records {
#if CONFIG_RTW_IO_RECORDS_STATIC
	struct rtw_io_record record[CONFIG_RTW_IO_RECORDS_NUM];
#else
	struct rtw_io_record *record;
#endif

	size_t record_num;
	size_t pos;
	bool enable;
	bool loop;
};

extern struct rtw_io_records dbg_rtw_io_records;

#define __dbg_rtw_io_record_warn(_r) do {} while (0)

#if DBG_RTW_IO_RECORD_DATA_LEN
#define __dbg_rtw_io_record_fill_data_1(_r, _data) (_r)->data[0] = *((u8 *)_data)
#define __dbg_rtw_io_record_fill_data_n(_r, _cnt, _data) _rtw_memcpy((_r)->data, _data, rtw_min(_cnt, DBG_RTW_IO_RECORD_DATA_LEN))
#define __dbg_rtw_io_record_fill_data_w(_r, _w) *((u16 *)(_r)->data) = cpu_to_le16(_w)
#define __dbg_rtw_io_record_fill_data_dw(_r, _dw) *((u32 *)(_r)->data) = cpu_to_le32(_dw)
#else
#define __dbg_rtw_io_record_fill_data_1(_r, _data) do {} while (0)
#define __dbg_rtw_io_record_fill_data_n(_r, _cnt, _data) do {} while (0)
#define __dbg_rtw_io_record_fill_data_w(_r, _w) do {} while (0)
#define __dbg_rtw_io_record_fill_data_dw(_r, _l) do {} while (0)
#endif

#if DBG_RTW_IO_RECORD_TASK_INFO
#define __dbg_rtw_io_record_fill_task_info(_r) \
	do { \
		rtw_get_task_comm((_r)->task_comm); \
	} while (0)
#else
#define __dbg_rtw_io_record_fill_task_info(_r) do {} while (0)
#endif

#if DBG_RTW_IO_RECORD_CPU_INFO
#define __dbg_rtw_io_record_fill_cpu_info(_r) \
	do { \
		(_r)->cpu = rtw_get_cpu_id(); \
	} while (0)
#else
#define __dbg_rtw_io_record_fill_cpu_info(_r) do {} while (0)
#endif

#define DECLARE_DBG_RTW_IO_RECORD_P(_r) struct rtw_io_record *_r

#define dbg_rtw_io_record_get_and_advance(_r) \
	do { \
		if (dbg_rtw_io_records.enable) { \
			if (dbg_rtw_io_records.loop || !dbg_rtw_io_records.record[dbg_rtw_io_records.pos].valid) { \
				(_r) = &dbg_rtw_io_records.record[dbg_rtw_io_records.pos]; \
				dbg_rtw_io_records.pos++; \
				if (dbg_rtw_io_records.pos >= dbg_rtw_io_records.record_num) \
					dbg_rtw_io_records.pos = 0; \
				(_r)->valid = true; \
			} else { \
				RTW_INFO("%s record full, disable\n", __func__); \
				dbg_rtw_io_records.enable = false; \
				(_r) = NULL; \
			} \
		} else \
			(_r) = NULL; \
	} while (0)

#define dbg_rtw_io_record_fill_stime(_r) \
	do { \
		if (_r) { \
			(_r)->stime = rtw_sptime_get_raw(); \
		} \
	} while (0)

#define dbg_rtw_io_record_fill_1(_r, _type, _addr, _err, _data) \
	do { \
		if (_r) { \
			(_r)->etime = rtw_sptime_get_raw(); \
			(_r)->type = _type; \
			(_r)->addr = _addr; \
			(_r)->cnt = 1; \
			(_r)->err = _err; \
			__dbg_rtw_io_record_fill_task_info(_r); \
			__dbg_rtw_io_record_fill_cpu_info(_r); \
			__dbg_rtw_io_record_fill_data_1(_r, _data); \
			__dbg_rtw_io_record_warn(_r); \
		} \
	} while (0)

#define dbg_rtw_io_record_fill_n(_r, _type, _addr, _cnt, _err, _data) \
	do { \
		if (_r) { \
			(_r)->etime = rtw_sptime_get_raw(); \
			(_r)->type = _type; \
			(_r)->addr = _addr; \
			(_r)->cnt = _cnt; \
			(_r)->err = _err; \
			__dbg_rtw_io_record_fill_task_info(_r); \
			__dbg_rtw_io_record_fill_cpu_info(_r); \
			__dbg_rtw_io_record_fill_data_n(_r, _cnt, _data); \
			__dbg_rtw_io_record_warn(_r); \
		} \
	} while (0)

#define dbg_rtw_io_record_fill_w(_r, _type, _addr, _err, _w) \
	do { \
		if (_r) { \
			(_r)->etime = rtw_sptime_get_raw(); \
			(_r)->type = _type; \
			(_r)->addr = _addr; \
			(_r)->cnt = 2; \
			(_r)->err = _err; \
			__dbg_rtw_io_record_fill_task_info(_r); \
			__dbg_rtw_io_record_fill_cpu_info(_r); \
			__dbg_rtw_io_record_fill_data_w(_r, _w); \
			__dbg_rtw_io_record_warn(_r); \
		} \
	} while (0)

#define dbg_rtw_io_record_fill_dw(_r, _type, _addr, _err, _dw) \
	do { \
		if (_r) { \
			(_r)->etime = rtw_sptime_get_raw(); \
			(_r)->type = _type; \
			(_r)->addr = _addr; \
			(_r)->cnt = 4; \
			(_r)->err = _err; \
			__dbg_rtw_io_record_fill_task_info(_r); \
			__dbg_rtw_io_record_fill_cpu_info(_r); \
			__dbg_rtw_io_record_fill_data_dw(_r, _dw); \
			__dbg_rtw_io_record_warn(_r); \
		} \
	} while (0)
#else
#define DECLARE_DBG_RTW_IO_RECORD_P(_r)
#define dbg_rtw_io_record_get_and_advance(_r) do {} while (0)
#define dbg_rtw_io_record_fill_stime(_r) do {} while (0)
#define dbg_rtw_io_record_fill_1(_r, _type, _addr, _err, _data) do {} while (0)
#define dbg_rtw_io_record_fill_n(_r, _type, _addr, _cnt, _err, _data) do {} while (0)
#define dbg_rtw_io_record_fill_w(_r, _type, _addr, _err, _w) do {} while (0)
#define dbg_rtw_io_record_fill_dw(_r, _type, _addr, _err, _dw) do {} while (0)
#endif /* CONFIG_RTW_IO_RECORDS */

/*
* APIs for common code
*/
#ifdef CONFIG_RTW_IO_RECORDS
static inline void rtw_io_records_dump_title(void *sel, bool tab) { _io_records_dump_title(sel, tab); }
static inline void rtw_io_records_dump_value_by_seq(void *sel, bool tab, size_t seq) { _io_records_dump_value_by_seq(sel, tab, seq); }
static inline void rtw_io_records_summary_dump(void *sel) { _io_records_summary_dump(sel); }
static inline void rtw_io_records_claim_and_enable(struct dvobj_priv *d, bool enable) { _io_records_claim_and_enable(d, enable); }

bool rtw_io_records_enabled(void);
void rtw_io_records_clear(void);
bool rtw_io_record_valid(size_t seq);
int rtw_io_records_init(void);
void rtw_io_records_deinit(void);
#else
static inline int rtw_io_records_init(void) {return _FAIL;}
static inline void rtw_io_records_deinit(void) {}
#endif

#endif /* __RTW_IO_RECORDS_H_ */
