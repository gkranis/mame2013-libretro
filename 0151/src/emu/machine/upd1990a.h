// license:BSD-3-Clause
// copyright-holders:Curt Coder
/**********************************************************************

    NEC uPD1990AC Serial I/O Calendar & Clock emulation

    Copyright MESS Team.
    Visit http://mamedev.org for licensing and usage restrictions.

**********************************************************************
                            _____   _____
                    C2   1 |*    \_/     | 14  Vdd
                    C1   2 |             | 13  XTAL
                    C0   3 |             | 12  _XTAL
                   STB   4 |  uPD1990AC  | 11  OUT ENBL
                    CS   5 |             | 10  TP
               DATA IN   6 |             | 9   DATA OUT
                   GND   7 |_____________| 8   CLK

**********************************************************************/

#pragma once

#ifndef __UPD1990A__
#define __UPD1990A__

#include "emu.h"



//**************************************************************************
//  INTERFACE CONFIGURATION MACROS
//**************************************************************************

#define MCFG_UPD1990A_ADD(_tag, _clock, _data, _tp) \
	MCFG_DEVICE_ADD((_tag), UPD1990A, _clock) \
	downcast<upd1990a_device *>(device)->set_data_callback(DEVCB2_##_data); \
	downcast<upd1990a_device *>(device)->set_tp_callback(DEVCB2_##_tp);

#define MCFG_UPD4990A_ADD(_tag, _clock, _data, _tp) \
	MCFG_DEVICE_ADD((_tag), UPD4990A, _clock) \
	downcast<upd1990a_device *>(device)->set_data_callback(DEVCB2_##_data); \
	downcast<upd1990a_device *>(device)->set_tp_callback(DEVCB2_##_tp);



//**************************************************************************
//  TYPE DEFINITIONS
//**************************************************************************

// ======================> upd1990a_device

class upd1990a_device : public device_t,
						public device_rtc_interface
{
public:
	// construction/destruction
	upd1990a_device(const machine_config &mconfig, device_type type, const char *name, const char *tag, device_t *owner, UINT32 clock, UINT32 variant, const char *shortname, const char *source);
	upd1990a_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);

	template<class _data> void set_data_callback(_data data) { m_write_data.set_callback(data); }
	template<class _tp> void set_tp_callback(_tp tp) { m_write_tp.set_callback(tp); }

	DECLARE_WRITE_LINE_MEMBER( oe_w );
	DECLARE_WRITE_LINE_MEMBER( cs_w );
	DECLARE_WRITE_LINE_MEMBER( stb_w );
	DECLARE_WRITE_LINE_MEMBER( clk_w );
	DECLARE_WRITE_LINE_MEMBER( c0_w );
	DECLARE_WRITE_LINE_MEMBER( c1_w );
	DECLARE_WRITE_LINE_MEMBER( c2_w );
	DECLARE_WRITE_LINE_MEMBER( data_in_w );
	DECLARE_READ_LINE_MEMBER( data_out_r );
	DECLARE_READ_LINE_MEMBER( tp_r );

protected:
	// device-level overrides
	virtual void device_start();
	virtual void device_reset();
	virtual void device_timer(emu_timer &timer, device_timer_id id, int param, void *ptr);

	// device_rtc_interface overrides
	virtual void rtc_clock_updated(int year, int month, int day, int day_of_week, int hour, int minute, int second);

	enum
	{
		TYPE_1990A = 0,
		TYPE_4990A
	};

private:
	enum
	{
		TIMER_CLOCK,
		TIMER_TP,
		TIMER_DATA_OUT,
		TIMER_TEST_MODE
	};

	enum
	{
		MODE_REGISTER_HOLD = 0,
		MODE_SHIFT,
		MODE_TIME_SET,
		MODE_TIME_READ,
		MODE_TP_64HZ_SET,
		MODE_TP_256HZ_SET,
		MODE_TP_2048HZ_SET,
		MODE_TEST
	};

	devcb2_write_line   m_write_data;
	devcb2_write_line   m_write_tp;

	UINT8 m_time_counter[5];    // time counter
	UINT8 m_shift_reg[5];       // shift register

	int m_oe;                   // output enable
	int m_cs;                   // chip select
	int m_stb;                  // strobe
	int m_data_in;              // data in
	int m_data_out;             // data out
	int m_c;                    // command
	int m_clk;                  // shift clock
	int m_tp;                   // time pulse
	int m_c_unlatched;          // command waiting for STB

	int m_variant;

	// timers
	emu_timer *m_timer_clock;
	emu_timer *m_timer_tp;
	emu_timer *m_timer_data_out;
	emu_timer *m_timer_test_mode;
};


// ======================> upd4990a_device

class upd4990a_device : public upd1990a_device
{
public:
	upd4990a_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock);
};


// device type definitions
extern const device_type UPD1990A;
extern const device_type UPD4990A;



#endif
