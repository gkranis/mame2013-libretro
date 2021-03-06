#include "sound/msm5205.h"

class tecmo_state : public driver_device
{
public:
	tecmo_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag),
		m_txvideoram(*this, "txvideoram"),
		m_fgvideoram(*this, "fgvideoram"),
		m_bgvideoram(*this, "bgvideoram"),
		m_spriteram(*this, "spriteram"),
		m_maincpu(*this, "maincpu"),
		m_soundcpu(*this, "soundcpu"),
		m_msm(*this, "msm") { }

	int m_adpcm_pos;
	int m_adpcm_end;
	int m_adpcm_data;
	int m_video_type;
	required_shared_ptr<UINT8> m_txvideoram;
	required_shared_ptr<UINT8> m_fgvideoram;
	required_shared_ptr<UINT8> m_bgvideoram;
	tilemap_t *m_tx_tilemap;
	tilemap_t *m_fg_tilemap;
	tilemap_t *m_bg_tilemap;
	UINT8 m_fgscroll[3];
	UINT8 m_bgscroll[3];
	required_shared_ptr<UINT8> m_spriteram;
	DECLARE_WRITE8_MEMBER(tecmo_bankswitch_w);
	DECLARE_WRITE8_MEMBER(tecmo_sound_command_w);
	DECLARE_WRITE8_MEMBER(tecmo_nmi_ack_w);
	DECLARE_WRITE8_MEMBER(tecmo_adpcm_end_w);
	DECLARE_READ8_MEMBER(tecmo_dswa_l_r);
	DECLARE_READ8_MEMBER(tecmo_dswa_h_r);
	DECLARE_READ8_MEMBER(tecmo_dswb_l_r);
	DECLARE_READ8_MEMBER(tecmo_dswb_h_r);
	DECLARE_WRITE8_MEMBER(tecmo_txvideoram_w);
	DECLARE_WRITE8_MEMBER(tecmo_fgvideoram_w);
	DECLARE_WRITE8_MEMBER(tecmo_bgvideoram_w);
	DECLARE_WRITE8_MEMBER(tecmo_fgscroll_w);
	DECLARE_WRITE8_MEMBER(tecmo_bgscroll_w);
	DECLARE_WRITE8_MEMBER(tecmo_flipscreen_w);
	DECLARE_WRITE8_MEMBER(tecmo_adpcm_start_w);
	DECLARE_WRITE8_MEMBER(tecmo_adpcm_vol_w);
	DECLARE_DRIVER_INIT(silkworm);
	DECLARE_DRIVER_INIT(rygar);
	DECLARE_DRIVER_INIT(backfirt);
	DECLARE_DRIVER_INIT(gemini);
	TILE_GET_INFO_MEMBER(get_bg_tile_info);
	TILE_GET_INFO_MEMBER(get_fg_tile_info);
	TILE_GET_INFO_MEMBER(gemini_get_bg_tile_info);
	TILE_GET_INFO_MEMBER(gemini_get_fg_tile_info);
	TILE_GET_INFO_MEMBER(get_tx_tile_info);
	DECLARE_MACHINE_RESET(rygar);
	DECLARE_VIDEO_START(tecmo);
	UINT32 screen_update_tecmo(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void draw_sprites(bitmap_ind16 &bitmap,const rectangle &cliprect);
	DECLARE_WRITE_LINE_MEMBER(irqhandler);
	DECLARE_WRITE_LINE_MEMBER(tecmo_adpcm_int);
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_soundcpu;
	required_device<msm5205_device> m_msm;
};
