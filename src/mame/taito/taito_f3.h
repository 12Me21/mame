// license:BSD-3-Clause
// copyright-holders:Bryan McPhail
#ifndef MAME_TAITO_TAITO_F3_H
#define MAME_TAITO_TAITO_F3_H

#pragma once

#include "taito_en.h"
#include "machine/eepromser.h"
#include "machine/watchdog.h"
#include "sound/okim6295.h"
#include "emupal.h"
#include "screen.h"
#include "tilemap.h"
#include <bitset>

class taito_f3_state : public driver_device
{
public:
	taito_f3_state(const machine_config &mconfig, device_type type, const char *tag) :
		driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_watchdog(*this, "watchdog"),
		m_gfxdecode(*this, "gfxdecode"),
		m_screen(*this, "screen"),
		m_palette(*this, "palette"),
		m_eeprom(*this, "eeprom"),
		m_textram(*this, "textram", 0x2000, ENDIANNESS_BIG),
		m_spriteram(*this, "spriteram", 0x10000, ENDIANNESS_BIG),
		m_charram(*this, "charram", 0x2000, ENDIANNESS_BIG),
		m_line_ram(*this, "line_ram", 0x10000, ENDIANNESS_BIG),
		m_pf_ram(*this, "pf_ram", 0xc000, ENDIANNESS_BIG),
		m_pivot_ram(*this, "pivot_ram", 0x10000, ENDIANNESS_BIG),
		m_input(*this, "IN.%u", 0),
		m_dial(*this, "DIAL.%u", 0),
		m_eepromin(*this, "EEPROMIN"),
		m_eepromout(*this, "EEPROMOUT"),
		m_taito_en(*this, "taito_en"),
		m_oki(*this, "oki"),
		m_paletteram32(*this, "paletteram"),
		m_okibank(*this, "okibank")
	{ }

	void f3(machine_config &config);
	void f3_224a(machine_config &config);
	void bubsympb(machine_config &config);
	void f3_224b(machine_config &config);
	void f3_224c(machine_config &config);

	void init_commandw();
	void init_pbobble2();
	void init_puchicar();
	void init_intcup94();
	void init_landmakr();
	void init_twinqix();
	void init_elvactr();
	void init_arabianm();
	void init_bubsympb();
	void init_ktiger2();
	void init_lightbr();
	void init_gekirido();
	void init_arkretrn();
	void init_kirameki();
	void init_qtheater();
	void init_popnpop();
	void init_spcinvdj();
	void init_pbobbl2p();
	void init_landmkrp();
	void init_bubblem();
	void init_ridingf();
	void init_gseeker();
	void init_bubsymph();
	void init_hthero95();
	void init_gunlock();
	void init_pbobble4();
	void init_dariusg();
	void init_recalh();
	void init_kaiserkn();
	void init_spcinv95();
	void init_trstaroj();
	void init_ringrage();
	void init_cupfinal();
	void init_quizhuhu();
	void init_pbobble3();
	void init_cleopatr();
	void init_scfinals();
	void init_pbobbl2x();

	template <int Num> DECLARE_CUSTOM_INPUT_MEMBER(f3_analog_r);
	template <int Num> DECLARE_CUSTOM_INPUT_MEMBER(f3_coin_r);
	DECLARE_CUSTOM_INPUT_MEMBER(eeprom_read);

protected:
	struct F3config;

	/* This it the best way to allow game specific kludges until the system is fully understood */
	enum {
		/* Early F3 class games, these are not cartridge games and system features may be different */
		RINGRAGE=0, /* D21 */
		ARABIANM,   /* D29 */
		RIDINGF,    /* D34 */
		GSEEKER,    /* D40 */
		TRSTAR,     /* D53 */
		GUNLOCK,    /* D66 */
		TWINQIX,
		UNDRFIRE,   /* D67 - Heavily modified F3 hardware (different memory map) */
		SCFINALS,
		LIGHTBR,    /* D69 */

		/* D77 - F3 motherboard proms, all following games are 'F3 package system' */
		/* D78 I CUP */
		KAISERKN,   /* D84 */
		DARIUSG,    /* D87 */
		BUBSYMPH,   /* D90 */
		SPCINVDX,   /* D93 */
		HTHERO95,   /* D94 */
		QTHEATER,   /* D95 */
		EACTION2,   /* E02 */
		SPCINV95,   /* E06 */
		QUIZHUHU,   /* E08 */
		PBOBBLE2,   /* E10 */
		GEKIRIDO,   /* E11 */
		KTIGER2,    /* E15 */
		BUBBLEM,    /* E21 */
		CLEOPATR,   /* E28 */
		PBOBBLE3,   /* E29 */
		ARKRETRN,   /* E36 */
		KIRAMEKI,   /* E44 */
		PUCHICAR,   /* E46 */
		PBOBBLE4,   /* E49 */
		POPNPOP,    /* E51 */
		LANDMAKR,   /* E61 */
		RECALH,     /* prototype */
		COMMANDW,   /* prototype */
		TMDRILL
	};

	static const F3config f3_config_table[];

	virtual void machine_start() override;
	virtual void machine_reset() override;
	virtual void video_start() override;
	virtual void device_post_load(void) override;

	TIMER_CALLBACK_MEMBER(trigger_int3);

	required_device<cpu_device> m_maincpu;
	optional_device<watchdog_timer_device> m_watchdog;
	required_device<gfxdecode_device> m_gfxdecode;
	required_device<screen_device> m_screen;
	required_device<palette_device> m_palette;
	optional_device<eeprom_serial_base_device> m_eeprom;

	memory_share_creator<u16> m_textram;
	memory_share_creator<u16> m_spriteram;
	memory_share_creator<u16> m_charram;
	memory_share_creator<u16> m_line_ram;
	memory_share_creator<u16> m_pf_ram;
	memory_share_creator<u16> m_pivot_ram;

	optional_ioport_array<6> m_input;
	optional_ioport_array<2> m_dial;
	optional_ioport m_eepromin;
	optional_ioport m_eepromout;

	emu_timer *m_interrupt3_timer;
	u32 m_coin_word[2];
	std::unique_ptr<u8[]> m_decoded_gfx4;
	std::unique_ptr<u8[]> m_decoded_gfx5;

	struct tempsprite
	{
		int code = 0;
		u8 color = 0;
		bool flipx = 0, flipy = 0;
		int x = 0, y = 0;
		u16 zoomx = 0, zoomy = 0;
		u8 pri = 0;
	};

	static const int NUM_PLAYFIELDS = 4;
	static const int NUM_TILEMAPS = 5;
	static const int NUM_SPRITEGROUPS = 4; // high 2 bits of color
	static const int NUM_CLIPPLANES = 4;
	typedef struct {
		u16 l;
		u16 r;
		auto set_upper(u8 left, u8 right) {
			l = (l & 0xff) | left<<8;
			r = (r & 0xff) | right<<8;
			return this;
		}
		auto set_lower(u8 left, u8 right) {
			l = (l & 0x100) | left;
			r = (r & 0x100) | right;
			return this;
		}
	} clip_plane_inf;

	typedef struct mixable {// layer compositing information
		u16 mix_value;
		u8 prio() const { return mix_value & 0x000f; };
		auto clip_inv() const { return std::bitset<4>(mix_value >> 4); };
		auto clip_enable() const { return std::bitset<4>(mix_value >> 8); };
		bool clip_inv_mode() const { return mix_value & 0x1000; };
		bool layer_enable() const { return mix_value & 0x2000; };
		bool blend_a() const { return mix_value & 0x4000; };
		bool blend_b() const  { return mix_value & 0x8000; };

		inline bool operator<(const mixable& rhs) const noexcept { return this->prio() < rhs.prio(); };
		inline bool operator>(const mixable& rhs) const noexcept { return this->prio() > rhs.prio(); };
		virtual void draw(u32* dst, int x, int y) {};
	} mixable;

	typedef struct : mixable {
		// alpha mode in 6000
		// line enable, clip settings in 7400
		// priority in 7600

		// TODO: change to ind16 when rewriting draw_sprites
		bitmap_rgb32 srcbitmap{};

		bool brightness; // 7400 0xf000
		void draw(u32* dst, int x, int y) override;
	} sprite_inf;

	typedef struct : mixable {
		bitmap_ind16* srcbitmap_pixel;
		bitmap_ind8*  flagsbitmap_pixel;
		bitmap_ind16* srcbitmap_vram;
		bitmap_ind8*  flagsbitmap_vram;

		u8 pivot_control; // 6000
		u16 pivot_enable; // 7000
		// mix info from 7200
		bool use_pix() const { return pivot_control & 0xa0; };
	} pivot_inf;

	typedef struct : mixable {
		bitmap_ind16* srcbitmap;
		bitmap_ind8*  flagsbitmap;

		int colscroll;        // 4000
		bool alt_tilemap;     // 4000
		bool x_sample_enable; // 6400 x_sample_mask
		u8 x_scale;           // 8000
		u8 y_scale;           // 8000
		u16 pal_add;          // 9000
		u16 rowscroll;        // a000
	} playfield_inf;

	typedef struct f3_line_inf {
		// 5000/4000
		clip_plane_inf clip[NUM_CLIPPLANES];
		// 6000 - don't store sync reg ?
		// pivot_control, sprite alpha
		// 6200 - define this type better
		u16 blend;
		// 6400
		u8 x_sample; // mosaic effect
		u8 fx_6400; // unemulated other effects
		// 6600
		u16 bg_palette; // unemulated, needs investigation, bad name?
		// 7000
		// pivot_enable here // what is in this word?
		// 7200
		pivot_inf pivot;
		sprite_inf sp[NUM_SPRITEGROUPS];
		playfield_inf pf[NUM_PLAYFIELDS];
	} f3_line_inf;


	struct f3_playfield_line_inf
	{
		u8 alpha_mode[256]{};
		u16 pri[256]{};

		/* use for draw_scanlines */
		u16 *src[256]{}, *src_s[256]{}, *src_e[256]{};
		u8 *tsrc[256]{}, *tsrc_s[256]{};
		int x_count[256]{};
		u32 x_zoom[256]{};
		u32 clip_in[256]{};
		u32 clip_ex[256]{};
		u16 pal_add[256]{};
	};

	struct f3_spritealpha_line_inf
	{
		u16 alpha_level[256]{};
		u16 spri[256]{};
		u16 sprite_alpha[256]{};
		u32 sprite_clip_in[256]{};
		u32 sprite_clip_ex[256]{};
		s16 clip_l[4][256]{};
		s16 clip_r[4][256]{};
	};

	int m_game = 0;
	tilemap_t *m_tilemap[8]{};
	tilemap_t *m_pixel_layer = nullptr;
	tilemap_t *m_vram_layer = nullptr;
	std::unique_ptr<u16[]> m_spriteram16_buffered;
	u16 m_control_0[8]{};
	u16 m_control_1[8]{};
	bool m_flipscreen = false;
	u8 m_sprite_extra_planes = 0;
	u8 m_sprite_pen_mask = 0;
	u16 *m_pf_data[8]{};
	int m_sprite_lag = 0;
	u8 m_sprite_pri_usage = 0;
	bitmap_ind8 m_pri_alp_bitmap;
	u8 m_alpha_level_2as = 0;
	u8 m_alpha_level_2ad = 0;
	u8 m_alpha_level_3as = 0;
	u8 m_alpha_level_3ad = 0;
	u8 m_alpha_level_2bs = 0;
	u8 m_alpha_level_2bd = 0;
	u8 m_alpha_level_3bs = 0;
	u8 m_alpha_level_3bd = 0;
	u16 m_alpha_level_last = 0;
	u16 m_width_mask = 0;
	u8 m_twidth_mask = 0;
	u8 m_twidth_mask_bit = 0;
	std::unique_ptr<u8[]> m_tile_opaque_sp;
	std::unique_ptr<u8[]> m_tile_opaque_pf[8];
	int m_alpha_s_1_1 = 0;
	int m_alpha_s_1_2 = 0;
	int m_alpha_s_1_4 = 0;
	int m_alpha_s_1_5 = 0;
	int m_alpha_s_1_6 = 0;
	int m_alpha_s_1_8 = 0;
	int m_alpha_s_1_9 = 0;
	int m_alpha_s_1_a = 0;
	int m_alpha_s_2a_0 = 0;
	int m_alpha_s_2a_4 = 0;
	int m_alpha_s_2a_8 = 0;
	int m_alpha_s_2b_0 = 0;
	int m_alpha_s_2b_4 = 0;
	int m_alpha_s_2b_8 = 0;
	int m_alpha_s_3a_0 = 0;
	int m_alpha_s_3a_1 = 0;
	int m_alpha_s_3a_2 = 0;
	int m_alpha_s_3b_0 = 0;
	int m_alpha_s_3b_1 = 0;
	int m_alpha_s_3b_2 = 0;
	u32 m_dval = 0;
	u8 m_pval = 0;
	u8 m_tval = 0;
	u8 m_pdest_2a = 0;
	u8 m_pdest_2b = 0;
	s8 m_tr_2a = 0;
	s8 m_tr_2b = 0;
	u8 m_pdest_3a = 0;
	u8 m_pdest_3b = 0;
	s8 m_tr_3a = 0;
	s8 m_tr_3b = 0;
	u16 *m_src[5]{};
	u16 *m_src_s[5]{};
	u16 *m_src_e[5]{};
	u16 m_clip_al[5]{};
	u16 m_clip_ar[5]{};
	u16 m_clip_bl[5]{};
	u16 m_clip_br[5]{};
	u8 *m_tsrc[5]{};
	u8 *m_tsrc_s[5]{};
	u32 m_x_count[5]{};
	u32 m_x_zoom[5]{};
	u16 m_pal_add[5]{};
	std::unique_ptr<tempsprite[]> m_spritelist;
	const tempsprite *m_sprite_end = nullptr;
	std::unique_ptr<f3_line_inf[]> m_line_inf;
	std::unique_ptr<f3_playfield_line_inf[]> m_pf_line_inf;
	std::unique_ptr<f3_spritealpha_line_inf[]> m_sa_line_inf;
	const F3config *m_game_config = nullptr;
	bool (taito_f3_state::*m_dpix_n[8][16])(u32 s_pix);
	bool (taito_f3_state::**m_dpix_lp[5])(u32 s_pix);
	bool (taito_f3_state::**m_dpix_sp[9])(u32 s_pix);

	u16 pf_ram_r(offs_t offset);
	void pf_ram_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	void control_0_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	void control_1_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	u16 spriteram_r(offs_t offset);
	void spriteram_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	u16 textram_r(offs_t offset);
	void textram_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	u16 charram_r(offs_t offset);
	void charram_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	u16 pivot_r(offs_t offset);
	void pivot_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	u16 lineram_r(offs_t offset);
	void lineram_w(offs_t offset, u16 data, u16 mem_mask = ~0);

	template<unsigned Layer> TILE_GET_INFO_MEMBER(get_tile_info);
	TILE_GET_INFO_MEMBER(get_tile_info_text);
	TILE_GET_INFO_MEMBER(get_tile_info_pixel);
	u32 screen_update(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);
	void screen_vblank(int state);

	void bubsympb_map(address_map &map);
	void f3_map(address_map &map);

	void tile_decode();

	inline void f3_drawgfx(bitmap_rgb32 &dest_bmp, const rectangle &clip, gfx_element *gfx, int code, u8 color, bool flipx, bool flipy, int sx, int sy, u16 scalex, u16 scaley, u8 pri_dst);
	void draw_sprites(bitmap_rgb32 &bitmap, const rectangle &cliprect);
	void get_sprite_info(const u16 *spriteram16_ptr);
	void print_debug_info(bitmap_rgb32 &bitmap);
	inline void alpha_set_level();
	inline void alpha_blend32_s(int alphas, u32 s);
	inline void alpha_blend32_d(int alphas, u32 s);
	inline void alpha_blend_1_1(u32 s);
	inline void alpha_blend_1_2(u32 s);
	inline void alpha_blend_1_4(u32 s);
	inline void alpha_blend_1_5(u32 s);
	inline void alpha_blend_1_6(u32 s);
	inline void alpha_blend_1_8(u32 s);
	inline void alpha_blend_1_9(u32 s);
	inline void alpha_blend_1_a(u32 s);
	inline void alpha_blend_2a_0(u32 s);
	inline void alpha_blend_2a_4(u32 s);
	inline void alpha_blend_2a_8(u32 s);
	inline void alpha_blend_2b_0(u32 s);
	inline void alpha_blend_2b_4(u32 s);
	inline void alpha_blend_2b_8(u32 s);
	inline void alpha_blend_3a_0(u32 s);
	inline void alpha_blend_3a_1(u32 s);
	inline void alpha_blend_3a_2(u32 s);
	inline void alpha_blend_3b_0(u32 s);
	inline void alpha_blend_3b_1(u32 s);
	inline void alpha_blend_3b_2(u32 s);
	bool dpix_1_noalpha(u32 s_pix);
	inline bool dpix_ret1(u32 s_pix);
	inline bool dpix_ret0(u32 s_pix);
	bool dpix_1_1(u32 s_pix);
	bool dpix_1_2(u32 s_pix);
	bool dpix_1_4(u32 s_pix);
	bool dpix_1_5(u32 s_pix);
	bool dpix_1_6(u32 s_pix);
	bool dpix_1_8(u32 s_pix);
	bool dpix_1_9(u32 s_pix);
	bool dpix_1_a(u32 s_pix);
	bool dpix_2a_0(u32 s_pix);
	bool dpix_2a_4(u32 s_pix);
	bool dpix_2a_8(u32 s_pix);
	bool dpix_3a_0(u32 s_pix);
	bool dpix_3a_1(u32 s_pix);
	bool dpix_3a_2(u32 s_pix);
	bool dpix_2b_0(u32 s_pix);
	bool dpix_2b_4(u32 s_pix);
	bool dpix_2b_8(u32 s_pix);
	bool dpix_3b_0(u32 s_pix);
	bool dpix_3b_1(u32 s_pix);
	bool dpix_3b_2(u32 s_pix);
	bool dpix_2_0(u32 s_pix);
	bool dpix_2_4(u32 s_pix);
	bool dpix_2_8(u32 s_pix);
	bool dpix_3_0(u32 s_pix);
	bool dpix_3_1(u32 s_pix);
	bool dpix_3_2(u32 s_pix);
	void dpix_1_sprite(u32 s_pix);
	void dpix_bg(u32 bgcolor);
	void init_alpha_blend_func();
	void get_pixmap_pointer(int skip_layer_num, const f3_playfield_line_inf **line_t, int y);
	void culc_pixmap_pointer(int skip_layer_num);
	void draw_scanlines(bitmap_rgb32 &bitmap, int xsize, s16 *draw_line_num, const f3_playfield_line_inf **line_t, const u8 *sprite, u32 orient, int skip_layer_num);
	void visible_tile_check(f3_playfield_line_inf *line_t, int line, u32 x_index_fx, u32 y_index, const u16 *pf_data_n);
	void calculate_clip(int y, u16 pri, u32 &clip_in, u32 &clip_ex, u8 &line_enable);
	void read_line_ram(f3_line_inf &line, int y);
	void get_spritealphaclip_info();
	void get_line_ram_info(tilemap_t *tmap, int sx, int sy, int pos, const u16 *pf_data_n);
	void get_vram_info(tilemap_t *vram_tilemap, tilemap_t *pixel_tilemap, int sx, int sy);
	void scanline_draw(bitmap_rgb32 &bitmap, const rectangle &cliprect);
	void scanline_draw_TWO(bitmap_rgb32 &bitmap, const rectangle &cliprect);

private:
	optional_device<taito_en_device> m_taito_en;
	optional_device<okim6295_device> m_oki;

	optional_shared_ptr<u32> m_paletteram32;
	optional_memory_bank m_okibank;

	void bubsympb_oki_w(u8 data);
	u32 f3_control_r(offs_t offset);
	void f3_control_w(offs_t offset, u32 data, u32 mem_mask = ~0);
	void f3_unk_w(offs_t offset, u16 data);
	void sound_reset_0_w(u32 data);
	void sound_reset_1_w(u32 data);
	void sound_bankswitch_w(offs_t offset, u32 data, u32 mem_mask = ~0);
	void palette_24bit_w(offs_t offset, u32 data, u32 mem_mask = ~0);

	INTERRUPT_GEN_MEMBER(interrupt2);

	void bubsympb_oki_map(address_map &map);
};

#endif // MAME_TAITO_TAITO_F3_H
