#include "video/bufsprite.h"
#include "machine/eepromser.h"

#define MASTER_CLOCK 57272700   // main oscillator frequency

/* Psikyo PS6406B */
#define FLIPSCREEN (((m_vidregs[3] & 0x0000c000) == 0x0000c000) ? 1:0)
#define DISPLAY_DISABLE (((m_vidregs[2] & 0x0000000f) == 0x00000006) ? 1:0)
#define BG_LARGE(n) (((m_vidregs[7] << (4*n)) & 0x00001000 ) ? 1:0)
#define BG_DEPTH_8BPP(n) (((m_vidregs[7] << (4*n)) & 0x00004000 ) ? 1:0)
#define BG_LAYER_ENABLE(n) (((m_vidregs[7] << (4*n)) & 0x00008000 ) ? 1:0)

#define BG_TYPE(n) (((m_vidregs[6] << (8*n)) & 0x7f000000 ) >> 24)
#define BG_LINE(n) (((m_vidregs[6] << (8*n)) & 0x80000000 ) ? 1:0)

#define BG_TRANSPEN MAKE_ARGB(0x00,0xff,0x00,0xff) // used for representing transparency in temporary bitmaps

#define SPRITE_PRI(n) (((m_vidregs[2] << (4*n)) & 0xf0000000 ) >> 28)


class psikyosh_state : public driver_device
{
public:
	psikyosh_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
			m_spriteram(*this, "spriteram") ,
		m_bgram(*this, "bgram"),
		m_paletteram(*this, "paletteram"),
		m_zoomram(*this, "zoomram"),
		m_vidregs(*this, "vidregs"),
		m_ram(*this, "ram"),
		m_maincpu(*this, "maincpu"),
		m_eeprom(*this, "eeprom"){ }

	/* memory pointers */
	required_device<buffered_spriteram32_device> m_spriteram;
	required_shared_ptr<UINT32> m_bgram;
	required_shared_ptr<UINT32> m_paletteram;
	required_shared_ptr<UINT32> m_zoomram;
	required_shared_ptr<UINT32> m_vidregs;
	required_shared_ptr<UINT32> m_ram;

	/* video-related */
	bitmap_ind8 m_zoom_bitmap;
	bitmap_ind16 m_z_bitmap;
	bitmap_rgb32   m_bg_bitmap;
	UINT16         *m_bg_zoom;
	UINT8          m_alphatable[256];

	/* devices */
	required_device<cpu_device> m_maincpu;
	required_device<eeprom_serial_93cxx_device> m_eeprom;

	DECLARE_WRITE32_MEMBER(psikyosh_irqctrl_w);
	DECLARE_WRITE32_MEMBER(paletteram32_RRRRRRRRGGGGGGGGBBBBBBBBxxxxxxxx_dword_w);
	DECLARE_WRITE32_MEMBER(psikyosh_vidregs_w);
	DECLARE_READ32_MEMBER(mjgtaste_input_r);
	DECLARE_WRITE32_MEMBER(psh_eeprom_w);
	DECLARE_READ32_MEMBER(psh_eeprom_r);
	DECLARE_DRIVER_INIT(gnbarich);
	DECLARE_DRIVER_INIT(daraku);
	DECLARE_DRIVER_INIT(soldivid);
	DECLARE_DRIVER_INIT(s1945iii);
	DECLARE_DRIVER_INIT(mjgtaste);
	DECLARE_DRIVER_INIT(tgm2);
	DECLARE_DRIVER_INIT(sbomberb);
	DECLARE_DRIVER_INIT(dragnblz);
	DECLARE_DRIVER_INIT(gunbird2);
	DECLARE_DRIVER_INIT(s1945ii);
	virtual void machine_start();
	virtual void video_start();
	UINT32 screen_update_psikyosh(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	INTERRUPT_GEN_MEMBER(psikyosh_interrupt);
	void draw_scanline32_alpha(bitmap_rgb32 &bitmap, INT32 destx, INT32 desty, INT32 length, const UINT32 *srcptr, int alpha);
	void draw_scanline32_argb(bitmap_rgb32 &bitmap, INT32 destx, INT32 desty, INT32 length, const UINT32 *srcptr);
	void draw_scanline32_transpen(bitmap_rgb32 &bitmap, INT32 destx, INT32 desty, INT32 length, const UINT32 *srcptr);
	void draw_bglayer( int layer, bitmap_rgb32 &bitmap, const rectangle &cliprect, UINT8 req_pri );
	void cache_bitmap(int scanline, gfx_element *gfx, int size, int tilebank, int alpha, int *last_bank);
	void draw_bglayerscroll( int layer, bitmap_rgb32 &bitmap, const rectangle &cliprect, UINT8 req_pri );
	void draw_background( bitmap_rgb32 &bitmap, const rectangle &cliprect, UINT8 req_pri );
	void draw_sprites(bitmap_rgb32 &bitmap, const rectangle &cliprect, UINT8 req_pri);
	void psikyosh_prelineblend( bitmap_rgb32 &bitmap, const rectangle &cliprect );
	void psikyosh_postlineblend( bitmap_rgb32 &bitmap, const rectangle &cliprect, UINT8 req_pri );
	void psikyosh_drawgfxzoom( bitmap_rgb32 &dest_bmp,const rectangle &clip,gfx_element *gfx,
			UINT32 code,UINT32 color,int flipx,int flipy,int offsx,int offsy,
			int alpha, int zoomx, int zoomy, int wide, int high, UINT32 z);
	DECLARE_WRITE_LINE_MEMBER(irqhandler);
};