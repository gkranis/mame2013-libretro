// license:BSD-3-Clause
// copyright-holders:Curt Coder, Olivier Galibert
#ifndef _VIDEO_ATARIST_H_
#define _VIDEO_ATARIST_H_

// 32028400 also exists
#define Y2      32084988.0
#define Y2_NTSC 32042400.0

#define ATARIST_HBSTART_PAL     128*4
#define ATARIST_HBEND_PAL       0
#define ATARIST_HBSTART_NTSC    127*4
#define ATARIST_HBEND_NTSC      0
#define ATARIST_HTOT_PAL        129*4
#define ATARIST_HTOT_NTSC       128*4

#define ATARIST_HBDEND_PAL      14*4
#define ATARIST_HBDSTART_PAL    94*4
#define ATARIST_HBDEND_NTSC     13*4
#define ATARIST_HBDSTART_NTSC   93*4

#define ATARIST_VBEND_PAL       0
#define ATARIST_VBEND_NTSC      0
#define ATARIST_VBSTART_PAL     312
#define ATARIST_VBSTART_NTSC    262
#define ATARIST_VTOT_PAL        313
#define ATARIST_VTOT_NTSC       263

#define ATARIST_VBDEND_PAL      63
#define ATARIST_VBDSTART_PAL    263
#define ATARIST_VBDEND_NTSC     34
#define ATARIST_VBDSTART_NTSC   234

#define ATARIST_BLITTER_SKEW_NFSR   0x40
#define ATARIST_BLITTER_SKEW_FXSR   0x80

#define ATARIST_BLITTER_CTRL_SMUDGE 0x20
#define ATARIST_BLITTER_CTRL_HOG    0x40
#define ATARIST_BLITTER_CTRL_BUSY   0x80

#endif
