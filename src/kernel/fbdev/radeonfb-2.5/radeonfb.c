/**
 * \file drivers/video/radeonfb.c
 * \brief framebuffer driver for ATI Radeon chipset video boards
 * \author Ani Joshi <ajoshi@kernel.crashing.org>
 */

/*
 *
 *	Copyright 2000	Ani Joshi <ajoshi@kernel.crashing.org>
 *
 *
 *	ChangeLog:
 *	2000-08-03	initial version 0.0.1
 *	2000-09-10	more bug fixes, public release 0.0.5
 *	2001-02-19	mode bug fixes, 0.0.7
 *	2001-07-05	fixed scrolling issues, engine initialization,
 *			and minor mode tweaking, 0.0.9
 *	2001-09-07	Radeon VE support, Nick Kurshev
 *			blanking, pan_display, and cmap fixes, 0.1.0
 *	2001-10-10	Radeon 7500 and 8500 support, and experimental
 *			flat panel support, 0.1.1
 *	2001-11-17	Radeon M6 (ppc) support, Daniel Berlin, 0.1.2
 *	2001-11-18	DFP fixes, Kevin Hendricks, 0.1.3
 *	2001-11-29	more cmap, backlight fixes, Benjamin Herrenschmidt
 *	2002-01-18	DFP panel detection via BIOS, Michael Clark, 0.1.4
 *	2002-06-02	console switching, mode set fixes, accel fixes
 *	2002-06-03	MTRR support, Peter Horton, 0.1.5
 *	2002-09-21	rv250, r300, m9 initial support,
 *			added mirror option, 0.1.6
 *
 *	Special thanks to ATI DevRel team for their hardware donations.
 *
 */


#define RADEON_VERSION	"0.1.6"


#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/tty.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/fb.h>
#include <linux/ioport.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/vmalloc.h>

#include <asm/io.h>
#include <asm/uaccess.h>

#ifdef CONFIG_MTRR
#include <asm/mtrr.h>
#endif

#include <video/radeon.h>
#include <linux/radeonfb.h>

#define DEBUG	1

#if DEBUG
#define RTRACE		printk
#else
#define RTRACE		if(0) printk
#endif

// XXX
#undef CONFIG_PMAC_PBOOK


/** Radeon chip */
enum radeon_chips {
	RADEON_QD,
	RADEON_QE,
	RADEON_QF,
	RADEON_QG,
	RADEON_QY,
	RADEON_QZ,
	RADEON_LW,
	RADEON_LX,
	RADEON_LY,
	RADEON_LZ,
	RADEON_QL,
	RADEON_QN,
	RADEON_QO,
	RADEON_Ql,
	RADEON_BB,
	RADEON_QW,
	RADEON_QX,
	RADEON_Id,
	RADEON_Ie,
	RADEON_If,
	RADEON_Ig,
	RADEON_Ld,
	RADEON_Le,
	RADEON_Lf,
	RADEON_Lg,
	RADEON_ND,
	RADEON_NE,
	RADEON_NF,
	RADEON_NG
};

/** Radeon architecture */
enum radeon_arch {
	RADEON_R100,
	RADEON_RV100,
	RADEON_R200,
	RADEON_RV200,
	RADEON_RV250,
	RADEON_R300,
	RADEON_M6,
	RADEON_M7,
	RADEON_M9
};

/** Radeon chip name/architecture table */
static struct radeon_chip_info {
	const char *name;	/**< chip model name */
	unsigned char arch;	/**< chip architecture */
} radeon_chip_info[] __devinitdata = {
	{ "QD", RADEON_R100 },
	{ "QE", RADEON_R100 },
	{ "QF", RADEON_R100 },
	{ "QG", RADEON_R100 },
	{ "VE QY", RADEON_RV100 },
	{ "VE QZ", RADEON_RV100 },
	{ "M7 LW", RADEON_M7 },
	{ "M7 LX", RADEON_M7 },
	{ "M6 LY", RADEON_M6 },
	{ "M6 LZ", RADEON_M6 },
	{ "8500 QL", RADEON_R200 },
	{ "8500 QN", RADEON_R200 },
	{ "8500 QO", RADEON_R200 },
	{ "8500 Ql", RADEON_R200 },
	{ "8500 BB", RADEON_R200 },
	{ "7500 QW", RADEON_RV200 },
	{ "7500 QX", RADEON_RV200 },
	{ "9000 Id", RADEON_RV250 },
	{ "9000 Ie", RADEON_RV250 },
	{ "9000 If", RADEON_RV250 },
	{ "9000 Ig", RADEON_RV250 },
	{ "M9 Ld", RADEON_M9 },
	{ "M9 Le", RADEON_M9 },
	{ "M9 Lf", RADEON_M9 },
	{ "M9 Lg", RADEON_M9 },
	{ "9700 ND", RADEON_R300 },
	{ "9700 NE", RADEON_R300 },
	{ "9700 NF", RADEON_R300 },
	{ "9700 NG", RADEON_R300 }
};


/** Monitor type */
enum radeon_montype
{
	MT_NONE,
	MT_CRT,		/**< CRT */
	MT_LCD,		/**< LCD */
	MT_DFP,		/**< DVI */
	MT_CTV,		/**< composite TV */
	MT_STV		/**< S-Video out */
};


/** PCI table */
static struct pci_device_id radeonfb_pci_table[] __devinitdata = {
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_QD, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_QD},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_QE, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_QE},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_QF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_QF},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_QG, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_QG},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_QY, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_QY},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_QZ, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_QZ},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_LW, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_LW},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_LX, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_LX},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_LY, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_LY},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_LZ, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_LZ},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_QL, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_QL},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_QN, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_QN},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_QO, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_QO},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_Ql, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_Ql},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_BB, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_BB},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_QW, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_QW},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_QX, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_QX},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_Id, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_Id},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_Ie, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_Ie},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_If, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_If},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_Ig, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_Ig},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_Ld, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_Ld},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_Le, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_Le},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_Lf, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_Lf},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_Lg, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_Lg},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_ND, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_ND},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_NE, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_NE},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_NF, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_NF},
	{ PCI_VENDOR_ID_ATI, PCI_DEVICE_ID_ATI_RADEON_NG, PCI_ANY_ID, PCI_ANY_ID, 0, 0, RADEON_NG},
	{ 0, }
};
MODULE_DEVICE_TABLE(pci, radeonfb_pci_table);


/**
 * \name Common registers
 *
 * These common regs are cleared before mode setting so they do not interfere
 * with anything.
 */
/*@{*/

typedef struct {
	u16 reg;
	u32 val;
} reg_val;

reg_val common_regs[] = {
	{ OVR_CLR, 0 },	
	{ OVR_WID_LEFT_RIGHT, 0 },
	{ OVR_WID_TOP_BOTTOM, 0 },
	{ OV0_SCALE_CNTL, 0 },
	{ SUBPIC_CNTL, 0 },
	{ VIPH_CONTROL, 0 },
	{ I2C_CNTL_1, 0 },
	{ GEN_INT_CNTL, 0 },
	{ CAP0_TRIG_CNTL, 0 },
};

reg_val common_regs_m6[] = {
	{ OVR_CLR,      0 },
	{ OVR_WID_LEFT_RIGHT,   0 },
	{ OVR_WID_TOP_BOTTOM,   0 },
	{ OV0_SCALE_CNTL,   0 },
	{ SUBPIC_CNTL,      0 },
	{ GEN_INT_CNTL,     0 },
	{ CAP0_TRIG_CNTL,   0 } 
};

/*@}*/


/** PLL information block */
typedef struct {
        u8 clock_chip_type;
        u8 struct_size;
        u8 accelerator_entry;
        u8 VGA_entry;
        u16 VGA_table_offset;
        u16 POST_table_offset;
        u16 XCLK;
        u16 MCLK;
        u8 num_PLL_blocks;
        u8 size_PLL_blocks;
        u16 PCLK_ref_freq;
        u16 PCLK_ref_divider;
        u32 PCLK_min_freq;
        u32 PCLK_max_freq;
        u16 MCLK_ref_freq;
        u16 MCLK_ref_divider;
        u32 MCLK_min_freq;
        u32 MCLK_max_freq;
        u16 XCLK_ref_freq;
        u16 XCLK_ref_divider;
        u32 XCLK_min_freq;
        u32 XCLK_max_freq;
} __attribute__ ((packed)) PLL_BLOCK;


/** PLL data */
struct pll_info {
	int ppll_max;
	int ppll_min;
	int xclk;
	int ref_div;
	int ref_clk;
};

/** RAM data */
struct ram_info {
	int ml;
	int mb;
	int trcd;
	int trp;
	int twr;
	int cl;
	int tr2w;
	int loop_latency;
	int rloop;
};


/** Radeon registers (state) */
struct radeon_regs {
	/** \name CRTC regs */
	/*@{*/
	u32 crtc_h_total_disp;
	u32 crtc_h_sync_strt_wid;
	u32 crtc_v_total_disp;
	u32 crtc_v_sync_strt_wid;
	u32 crtc_pitch;
	u32 crtc_gen_cntl;
	u32 crtc_ext_cntl;
	u32 dac_cntl;
	/*@}*/

	u32 crtc_more_cntl;

	u32 flags;
	u32 pix_clock;
	int xres, yres;

	/** \name DDA regs */
	/*@{*/
	u32 dda_config;
	u32 dda_on_off;
	/*@}*/

	/** \name PLL regs */
	/*@{*/
	u32 ppll_div_3;
	u32 ppll_ref_div;
	u32 vclk_ecp_cntl;
	/*@}*/
	
	/** \name Flat panel regs */
	/*@{*/
	u32 fp_crtc_h_total_disp;
	u32 fp_crtc_v_total_disp;
	u32 fp_gen_cntl;
	u32 fp_h_sync_strt_wid;
	u32 fp_horz_stretch;
	u32 fp_panel_cntl;
	u32 fp_v_sync_strt_wid;
	u32 fp_vert_stretch;
	u32 lvds_gen_cntl;
	u32 lvds_pll_cntl;
	u32 tmds_crc;
	u32 tmds_transmitter_cntl;
	/*@}*/

#if defined(__BIG_ENDIAN)
	u32 surface_cntl;
#endif
};


/** Radeon framebuffer device information */
struct radeonfb_info {
	struct fb_info info;		/**< framebuffer device information */

	struct radeon_regs state;	/**< current state */
	struct radeon_regs init_state;	/**< initial state */

	char name[32];
	char ram_type[12];

	unsigned long mmio_base_phys;	/**< MMIO region base physical offset */
	unsigned long fb_base_phys;	/**< framebuffer base physical offset */

	unsigned long mmio_base;	/**< MMIO region base offset */
	unsigned long fb_base;		/**< framebuffer base offset */

	struct pci_dev *pdev;		/**< PCI device information */

	unsigned char *EDID;
	unsigned char *bios_seg;

	u32 pseudo_palette[17];
	struct { u8 red, green, blue, pad; } palette[256];

	int chipset;
	unsigned char arch;
	int video_ram;
	u8 rev;
	int pitch, bpp, depth;
	int xres, yres, pixclock;
	int xres_virtual, yres_virtual;
/* 	u32 accel_flags; */

	int use_default_var;
	int got_dfpinfo;

	int hasCRTC2;
	int crtDisp_type;
	int dviDisp_type;

	int panel_xres, panel_yres;
	int clock;
	int hOver_plus, hSync_width, hblank;
	int vOver_plus, vSync_width, vblank;
	int hAct_high, vAct_high, interlaced;
	int synct, misc;

	u32 dp_gui_master_cntl;

	struct pll_info pll;
	int pll_output_freq, post_div, fb_div;

	struct ram_info ram;

	int mtrr_hdl;

	int asleep;
	
	struct radeonfb_info *next;	/**< Multiple devices as a single linked list */
};


static struct fb_var_screeninfo radeonfb_default_var = {
        640, 480, 640, 480, 0, 0, 8, 0,
        {0, 6, 0}, {0, 6, 0}, {0, 6, 0}, {0, 0, 0},
        0, 0, -1, -1, 0, 39721, 40, 24, 32, 11, 96, 2,
        0, FB_VMODE_NONINTERLACED
};

/**
 * \name IO macros
 */
/*@{*/

/** Read a 8 bit register */
#define INREG8(addr)		readb((rinfo->mmio_base)+addr)
/** Write a 8 bit register */
#define OUTREG8(addr,val)	writeb(val, (rinfo->mmio_base)+addr)
/** Read a 32 bit register */
#define INREG(addr)		readl((rinfo->mmio_base)+addr)
/** Write a 32 bit register */
#define OUTREG(addr,val)	writel(val, (rinfo->mmio_base)+addr)

/** Write a PLL register */
#define OUTPLL(addr,val)	\
	do {	\
		OUTREG8(CLOCK_CNTL_INDEX, (addr & 0x0000003f) | 0x00000080); \
		OUTREG(CLOCK_CNTL_DATA, val); \
	} while(0)

/** Write a PLL register with mask */
#define OUTPLLP(addr,val,mask)  					\
	do {								\
		unsigned int _tmp = INPLL(addr);			\
		_tmp &= (mask);						\
		_tmp |= (val);						\
		OUTPLL(addr, _tmp);					\
	} while (0)

/** Write a 32 bit register with mask */
#define OUTREGP(addr,val,mask)  					\
	do {								\
		unsigned int _tmp = INREG(addr);			\
		_tmp &= (mask);						\
		_tmp |= (val);						\
		OUTREG(addr, _tmp);					\
	} while (0)


/** Read a PLL register */
static __inline__ u32 _INPLL(struct radeonfb_info *rinfo, u32 addr)
{
	OUTREG8(CLOCK_CNTL_INDEX, addr & 0x0000003f);
	return (INREG(CLOCK_CNTL_DATA));
}

/** Read a PLL register (macro) */
#define INPLL(addr)		_INPLL(rinfo, addr)

/*@}*/


#define PRIMARY_MONITOR(rinfo)	((rinfo->dviDisp_type != MT_NONE) &&	\
				 (rinfo->dviDisp_type != MT_STV) &&	\
				 (rinfo->dviDisp_type != MT_CTV) ?	\
				 rinfo->dviDisp_type : rinfo->crtDisp_type)

/** 
 * Get monitor name.
 *
 * \param type monitor type.
 * \return pointer to a string describing the monitor type, or NULL if an
 * invalid type.
 */
static char *GET_MON_NAME(int type)
{
	char *pret = NULL;

	switch (type) {
		case MT_NONE:
			pret = "no";
			break;
		case MT_CRT:
			pret = "CRT";
			break;
		case MT_DFP:
			pret = "DFP";
			break;
		case MT_LCD:
			pret = "LCD";
			break;
		case MT_CTV:
			pret = "CTV";
			break;
		case MT_STV:
			pret = "STV";
			break;
	}

	return pret;
}


/**
 * \name Helper routines
 */
/*@{*/

/** Determine */
static __inline__ u32 radeon_get_dstbpp(u16 depth)
{
	switch (depth) {
		case 8:
			return DST_8BPP;
		case 15:
			return DST_15BPP;
		case 16:
			return DST_16BPP;
		case 32:
			return DST_32BPP;
		default:
			return 0;
	}
}

static inline int var_to_depth(const struct fb_var_screeninfo *var)
{
	if (var->bits_per_pixel != 16)
		return var->bits_per_pixel;
	return (var->green.length == 6) ? 16 : 15;
}

static __inline__ u8 radeon_get_post_div_bitval(int post_div)
{
        switch (post_div) {
                case 1:
                        return 0x00;
                case 2: 
                        return 0x01;
                case 3: 
                        return 0x04;
                case 4:
                        return 0x02;
                case 6:
                        return 0x06;
                case 8:
                        return 0x03;
                case 12:
                        return 0x07;
                default:
                        return 0x02;
        }
}

static __inline__ int round_div(int num, int den)
{
        return (num + (den / 2)) / den;
}

static __inline__ int min_bits_req(int val)
{
        int bits_req = 0;
                
        if (val == 0)
                bits_req = 1;
                        
        while (val) {
                val >>= 1;
                bits_req++;
        }       

        return (bits_req);
}

/** Maximum between two integers */
static __inline__ int _max(int val1, int val2)
{
        if (val1 >= val2)
                return val1;
        else
                return val2;
}                       

/*@}*/


/**
 * \name Globals
 */
/*@{*/
        
static char *mode_option __initdata;
static char mirror = 0;
static int panel_yres __initdata = 0;
static char force_dfp __initdata = 0;
static struct radeonfb_info *board_list = NULL;
static char nomtrr __initdata = 0;

/*@}*/


/**
 * \name Prototypes
 */

static void radeon_save_state (struct radeonfb_info *rinfo,
                               struct radeon_regs *save);
static void radeon_write_mode (struct radeonfb_info *rinfo,
                               struct radeon_regs *mode);
static int __devinit radeon_set_fbinfo (struct radeonfb_info *rinfo);
static int __devinit radeon_init_disp (struct radeonfb_info *rinfo);
static int radeon_init_disp_var (struct radeonfb_info *rinfo, struct fb_var_screeninfo *var);
static char *radeon_find_rom(struct radeonfb_info *rinfo);
static void radeon_get_pllinfo(struct radeonfb_info *rinfo, char *bios_seg);
static void radeon_get_moninfo (struct radeonfb_info *rinfo);
static int radeon_get_dfpinfo (struct radeonfb_info *rinfo);
static int radeon_get_dfpinfo_BIOS(struct radeonfb_info *rinfo);
static void radeon_get_EDID(struct radeonfb_info *rinfo);
static int radeon_dfp_parse_EDID(struct radeonfb_info *rinfo);
static void radeon_update_default_var(struct radeonfb_info *rinfo);


/*@}*/


static char *radeon_find_rom(struct radeonfb_info *rinfo)
{       
#if defined(__i386__)
        u32  segstart;
        char *rom_base;
        char *rom;
        int  stage;
        int  i,j;       
        char aty_rom_sig[] = "761295520";
        char *radeon_sig[] = {
          "RG6",
          "RADEON"
        };
                                                
        for(segstart=0x000c0000; segstart<0x000f0000; segstart+=0x00001000) {
                        
                stage = 1;
                
                rom_base = (char *)ioremap(segstart, 0x1000);

                if ((*rom_base == 0x55) && (((*(rom_base + 1)) & 0xff) == 0xaa))
                        stage = 2;
                
                    
                if (stage != 2) {
                        iounmap(rom_base);
                        continue;
                }
                                              
                rom = rom_base;
                     
                for (i = 0; (i < 128 - strlen(aty_rom_sig)) && (stage != 3); i++) {
                        if (aty_rom_sig[0] == *rom)
                                if (strncmp(aty_rom_sig, rom,
                                                strlen(aty_rom_sig)) == 0)
                                        stage = 3;
                        rom++;
                }
                if (stage != 3) {
                        iounmap(rom_base);
                        continue;
                }
                rom = rom_base;
        
                for (i = 0; (i < 512) && (stage != 4); i++) {
                    for(j = 0;j < sizeof(radeon_sig)/sizeof(char *);j++) {
                        if (radeon_sig[j][0] == *rom)
                                if (strncmp(radeon_sig[j], rom,
                                            strlen(radeon_sig[j])) == 0) {
                                              stage = 4;
                                              break;
                                            }
                    }                           
                        rom++;
                }       
                if (stage != 4) {
                        iounmap(rom_base);
                        continue;
                }       
                
                return rom_base;
        }
#endif          
        return NULL;
}




static void radeon_get_pllinfo(struct radeonfb_info *rinfo, char *bios_seg)
{
        void *bios_header;
        void *header_ptr;
        u16 bios_header_offset, pll_info_offset;
        PLL_BLOCK pll;

	if (bios_seg) {
	        bios_header = bios_seg + 0x48L;
       		header_ptr  = bios_header;
        
        	bios_header_offset = readw(header_ptr);
	        bios_header = bios_seg + bios_header_offset;
        	bios_header += 0x30;
        
        	header_ptr = bios_header;
        	pll_info_offset = readw(header_ptr);
        	header_ptr = bios_seg + pll_info_offset;
        
        	memcpy_fromio(&pll, header_ptr, 50);
        
        	rinfo->pll.xclk = (u32)pll.XCLK;
        	rinfo->pll.ref_clk = (u32)pll.PCLK_ref_freq;
        	rinfo->pll.ref_div = (u32)pll.PCLK_ref_divider;
        	rinfo->pll.ppll_min = pll.PCLK_min_freq;
        	rinfo->pll.ppll_max = pll.PCLK_max_freq;

		printk("radeonfb: ref_clk=%d, ref_div=%d, xclk=%d from BIOS\n",
			rinfo->pll.ref_clk, rinfo->pll.ref_div, rinfo->pll.xclk);
	} else {
		/* no BIOS or BIOS not found, use defaults */
		switch (rinfo->chipset) {
			case PCI_DEVICE_ID_ATI_RADEON_QW:
			case PCI_DEVICE_ID_ATI_RADEON_QX:
				rinfo->pll.ppll_max = 35000;
				rinfo->pll.ppll_min = 12000;
				rinfo->pll.xclk = 23000;
				rinfo->pll.ref_div = 12;
				rinfo->pll.ref_clk = 2700;
				break;
			case PCI_DEVICE_ID_ATI_RADEON_QL:
			case PCI_DEVICE_ID_ATI_RADEON_QN:
			case PCI_DEVICE_ID_ATI_RADEON_QO:
			case PCI_DEVICE_ID_ATI_RADEON_Ql:
			case PCI_DEVICE_ID_ATI_RADEON_BB:
				rinfo->pll.ppll_max = 35000;
				rinfo->pll.ppll_min = 12000;
				rinfo->pll.xclk = 27500;
				rinfo->pll.ref_div = 12;
				rinfo->pll.ref_clk = 2700;
				break;
			case PCI_DEVICE_ID_ATI_RADEON_Id:
			case PCI_DEVICE_ID_ATI_RADEON_Ie:
			case PCI_DEVICE_ID_ATI_RADEON_If:
			case PCI_DEVICE_ID_ATI_RADEON_Ig:
				rinfo->pll.ppll_max = 35000;
				rinfo->pll.ppll_min = 12000;
				rinfo->pll.xclk = 25000;
				rinfo->pll.ref_div = 12;
				rinfo->pll.ref_clk = 2700;
				break;
			case PCI_DEVICE_ID_ATI_RADEON_QD:
			case PCI_DEVICE_ID_ATI_RADEON_QE:
			case PCI_DEVICE_ID_ATI_RADEON_QF:
			case PCI_DEVICE_ID_ATI_RADEON_QG:
			default:
				rinfo->pll.ppll_max = 35000;
				rinfo->pll.ppll_min = 12000;
				rinfo->pll.xclk = 16600;
				rinfo->pll.ref_div = 67;
				rinfo->pll.ref_clk = 2700;
				break;
		}

		printk("radeonfb: ref_clk=%d, ref_div=%d, xclk=%d defaults\n",
			rinfo->pll.ref_clk, rinfo->pll.ref_div, rinfo->pll.xclk);
	}
}


static void radeon_get_moninfo (struct radeonfb_info *rinfo)
{
	unsigned int tmp;

	if (force_dfp) {
		rinfo->dviDisp_type = MT_DFP;
		return;
	}

	tmp = INREG(RADEON_BIOS_4_SCRATCH);
	printk(KERN_DEBUG "radeon_get_moninfo: bios 4 scratch = %x\n", tmp);
	
	if (rinfo->hasCRTC2) {
		/* primary DVI port */
		if (tmp & 0x08)
			rinfo->dviDisp_type = MT_DFP;
		else if (tmp & 0x4)
			rinfo->dviDisp_type = MT_LCD;
		else if (tmp & 0x200)
			rinfo->dviDisp_type = MT_CRT;
		else if (tmp & 0x10)
			rinfo->dviDisp_type = MT_CTV;
		else if (tmp & 0x20)
			rinfo->dviDisp_type = MT_STV;

		/* secondary CRT port */
		if (tmp & 0x2)
			rinfo->crtDisp_type = MT_CRT;
		else if (tmp & 0x800)
			rinfo->crtDisp_type = MT_DFP;
		else if (tmp & 0x400)
			rinfo->crtDisp_type = MT_LCD;
		else if (tmp & 0x1000)
			rinfo->crtDisp_type = MT_CTV;
		else if (tmp & 0x2000)
			rinfo->crtDisp_type = MT_STV;
	} else {
		rinfo->dviDisp_type = MT_NONE;

		tmp = INREG(FP_GEN_CNTL);

		if (tmp & FP_EN_TMDS)
			rinfo->crtDisp_type = MT_DFP;
		else
			rinfo->crtDisp_type = MT_CRT;
	}
}



static void radeon_get_EDID(struct radeonfb_info *rinfo)
{
	/* XXX use other methods later */
}



static int radeon_dfp_parse_EDID(struct radeonfb_info *rinfo)
{
	unsigned char *block = rinfo->EDID;

	if (!block)
		return 0;

	/* jump to the detailed timing block section */
	block += 54;

	rinfo->clock = (block[0] + (block[1] << 8));
	rinfo->panel_xres = (block[2] + ((block[4] & 0xf0) << 4));
	rinfo->hblank = (block[3] + ((block[4] & 0x0f) << 8));
	rinfo->panel_yres = (block[5] + ((block[7] & 0xf0) << 4));
	rinfo->vblank = (block[6] + ((block[7] & 0x0f) << 8));
	rinfo->hOver_plus = (block[8] + ((block[11] & 0xc0) << 2));
	rinfo->hSync_width = (block[9] + ((block[11] & 0x30) << 4));
	rinfo->vOver_plus = ((block[10] >> 4) + ((block[11] & 0x0c) << 2));
	rinfo->vSync_width = ((block[10] & 0x0f) + ((block[11] & 0x03) << 4));
	rinfo->interlaced = ((block[17] & 0x80) >> 7);
	rinfo->synct = ((block[17] & 0x18) >> 3);
	rinfo->misc = ((block[17] & 0x06) >> 1);
	rinfo->hAct_high = rinfo->vAct_high = 0;
	if (rinfo->synct == 3) {
		if (rinfo->misc & 2)
			rinfo->hAct_high = 1;
		if (rinfo->misc & 1)
			rinfo->vAct_high = 1;
	}

	printk("radeonfb: detected DFP panel size from EDID: %dx%d\n",
		rinfo->panel_xres, rinfo->panel_yres);

	rinfo->got_dfpinfo = 1;

	return 1;
}


static void radeon_update_default_var(struct radeonfb_info *rinfo)
{
	struct fb_var_screeninfo *var = &radeonfb_default_var;

	var->xres = rinfo->panel_xres;
	var->yres = rinfo->panel_yres;
	var->xres_virtual = rinfo->panel_xres;
	var->yres_virtual = rinfo->panel_yres;
	var->xoffset = var->yoffset = 0;
	var->bits_per_pixel = 8;
	var->pixclock = 100000000 / rinfo->clock;
	var->left_margin = (rinfo->hblank - rinfo->hOver_plus - rinfo->hSync_width);
	var->right_margin = rinfo->hOver_plus;
	var->upper_margin = (rinfo->vblank - rinfo->vOver_plus - rinfo->vSync_width);
	var->lower_margin = rinfo->vOver_plus;
	var->hsync_len = rinfo->hSync_width;
	var->vsync_len = rinfo->vSync_width;
	var->sync = 0;
	if (rinfo->synct == 3) {
		if (rinfo->hAct_high)
			var->sync |= FB_SYNC_HOR_HIGH_ACT;
		if (rinfo->vAct_high)
			var->sync |= FB_SYNC_VERT_HIGH_ACT;
	}

	var->vmode = 0;
	if (rinfo->interlaced)
		var->vmode |= FB_VMODE_INTERLACED;

	rinfo->use_default_var = 1;
}


static int radeon_get_dfpinfo_BIOS(struct radeonfb_info *rinfo)
{
	char *fpbiosstart, *tmp, *tmp0;
	char stmp[30];
	int i;

	if (!rinfo->bios_seg)
		return 0;

	if (!(fpbiosstart = rinfo->bios_seg + readw(rinfo->bios_seg + 0x48))) {
		printk("radeonfb: Failed to detect DFP panel info using BIOS\n");
		return 0;
	}

	if (!(tmp = rinfo->bios_seg + readw(fpbiosstart + 0x40))) {
		printk("radeonfb: Failed to detect DFP panel info using BIOS\n");
		return 0;
	}

	for(i=0; i<24; i++)
		stmp[i] = readb(tmp+i+1);
	stmp[24] = 0;
	printk("radeonfb: panel ID string: %s\n", stmp);
	rinfo->panel_xres = readw(tmp + 25);
	rinfo->panel_yres = readw(tmp + 27);
	printk("radeonfb: detected DFP panel size from BIOS: %dx%d\n",
		rinfo->panel_xres, rinfo->panel_yres);

	for(i=0; i<20; i++) {
		tmp0 = rinfo->bios_seg + readw(tmp+64+i*2);
		if (tmp0 == 0)
			break;
		if ((readw(tmp0) == rinfo->panel_xres) &&
		    (readw(tmp0+2) == rinfo->panel_yres)) {
			rinfo->hblank = (readw(tmp0+17) - readw(tmp0+19)) * 8;
			rinfo->hOver_plus = ((readw(tmp0+21) - readw(tmp0+19) -1) * 8) & 0x7fff;
			rinfo->hSync_width = readb(tmp0+23) * 8;
			rinfo->vblank = readw(tmp0+24) - readw(tmp0+26);
			rinfo->vOver_plus = (readw(tmp0+28) & 0x7ff) - readw(tmp0+26);
			rinfo->vSync_width = (readw(tmp0+28) & 0xf800) >> 11;
			rinfo->clock = readw(tmp0+9);

			rinfo->got_dfpinfo = 1;
			return 1;
		}
	}

	return 0;
}



static int radeon_get_dfpinfo (struct radeonfb_info *rinfo)
{
	unsigned int tmp;
	unsigned short a, b;

	if (radeon_get_dfpinfo_BIOS(rinfo))
		radeon_update_default_var(rinfo);

	if (radeon_dfp_parse_EDID(rinfo))
		radeon_update_default_var(rinfo);

	if (!rinfo->got_dfpinfo) {
		/*
		 * it seems all else has failed now and we
		 * resort to probing registers for our DFP info
	         */
		if (panel_yres) {
			rinfo->panel_yres = panel_yres;
		} else {
			tmp = INREG(FP_VERT_STRETCH);
			tmp &= 0x00fff000;
			rinfo->panel_yres = (unsigned short)(tmp >> 0x0c) + 1;
		}

		switch (rinfo->panel_yres) {
			case 480:
				rinfo->panel_xres = 640;
				break;
			case 600:
				rinfo->panel_xres = 800;
				break;
			case 768:
				rinfo->panel_xres = 1024;
				break;
			case 1024:
				rinfo->panel_xres = 1280;
				break;
			case 1050:
				rinfo->panel_xres = 1400;
				break;
			case 1200:
				rinfo->panel_xres = 1600;
				break;
			default:
				printk("radeonfb: Failed to detect DFP panel size\n");
				return 0;
		}

		printk("radeonfb: detected DFP panel size from registers: %dx%d\n",
			rinfo->panel_xres, rinfo->panel_yres);

		tmp = INREG(FP_CRTC_H_TOTAL_DISP);
		a = (tmp & FP_CRTC_H_TOTAL_MASK) + 4;
		b = (tmp & 0x01ff0000) >> FP_CRTC_H_DISP_SHIFT;
		rinfo->hblank = (a - b + 1) * 8;

		tmp = INREG(FP_H_SYNC_STRT_WID);
		rinfo->hOver_plus = (unsigned short) ((tmp & FP_H_SYNC_STRT_CHAR_MASK) >>
					FP_H_SYNC_STRT_CHAR_SHIFT) - b - 1;
		rinfo->hOver_plus *= 8;
		rinfo->hSync_width = (unsigned short) ((tmp & FP_H_SYNC_WID_MASK) >>
					FP_H_SYNC_WID_SHIFT);
		rinfo->hSync_width *= 8;
		tmp = INREG(FP_CRTC_V_TOTAL_DISP);
		a = (tmp & FP_CRTC_V_TOTAL_MASK) + 1;
		b = (tmp & FP_CRTC_V_DISP_MASK) >> FP_CRTC_V_DISP_SHIFT;
		rinfo->vblank = a - b /* + 24 */ ;

		tmp = INREG(FP_V_SYNC_STRT_WID);
		rinfo->vOver_plus = (unsigned short) (tmp & FP_V_SYNC_STRT_MASK)
					- b + 1;
		rinfo->vSync_width = (unsigned short) ((tmp & FP_V_SYNC_WID_MASK) >>
					FP_V_SYNC_WID_SHIFT);

		return 1;
	}

	return 1;
}





static int __devinit radeon_init_disp (struct radeonfb_info *rinfo)
{
        struct fb_info *info = &rinfo->info;
	struct fb_var_screeninfo var;

        var = radeonfb_default_var;
        if ((radeon_init_disp_var(rinfo, &var)) < 0)
                return -1;

	rinfo->depth = var_to_depth(&var);
	rinfo->bpp = var.bits_per_pixel;
        
	info->var = var;
	fb_alloc_cmap(&info->cmap, 256, 0);

	var.activate = FB_ACTIVATE_NOW;
	fb_set_var(&var, info);
        return 0;
}


static int radeon_init_disp_var (struct radeonfb_info *rinfo,
				 struct fb_var_screeninfo *var)
{
#ifndef MODULE
        if (mode_option)
                fb_find_mode (var, &rinfo->info, mode_option,
                              NULL, 0, NULL, 8);
        else
#endif
	if (rinfo->use_default_var)
		/* We will use the modified default far */
		*var = radeonfb_default_var;
	else

                fb_find_mode (var, &rinfo->info, "640x480-8@60",
                              NULL, 0, NULL, 0);

	var->accel_flags &= ~FB_ACCELF_TEXT;
 
        return 0;
}


static int radeon_do_maximize(struct radeonfb_info *rinfo,
                                struct fb_var_screeninfo *var,
                                struct fb_var_screeninfo *v,
                                int nom, int den)
{
        static struct {
                int xres, yres;
        } modes[] = {
                {1600, 1280},
                {1280, 1024},
                {1024, 768},
                {800, 600},
                {640, 480},
                {-1, -1}
        };
        int i;
  
        /* use highest possible virtual resolution */
        if (v->xres_virtual == -1 && v->yres_virtual == -1) {
                printk("radeonfb: using max available virtual resolution\n");
                for (i=0; modes[i].xres != -1; i++) {
                        if (modes[i].xres * nom / den * modes[i].yres <
                            rinfo->video_ram / 2)
                                break;
                }
                if (modes[i].xres == -1) {
                        printk("radeonfb: could not find virtual resolution that fits into video memory!\n");
                        return -EINVAL;
                }
                v->xres_virtual = modes[i].xres;  
                v->yres_virtual = modes[i].yres;
                
                printk("radeonfb: virtual resolution set to max of %dx%d\n",
                        v->xres_virtual, v->yres_virtual);
        } else if (v->xres_virtual == -1) {
                v->xres_virtual = (rinfo->video_ram * den /   
                                (nom * v->yres_virtual * 2)) & ~15;
        } else if (v->yres_virtual == -1) {
                v->xres_virtual = (v->xres_virtual + 15) & ~15;
                v->yres_virtual = rinfo->video_ram * den /
                        (nom * v->xres_virtual *2);
        } else {
                if (v->xres_virtual * nom / den * v->yres_virtual >
                        rinfo->video_ram) {
                        return -EINVAL;
                }
        }
                
        if (v->xres_virtual * nom / den >= 8192) {
                v->xres_virtual = 8192 * den / nom - 16;
        }       
        
        if (v->xres_virtual < v->xres)
                return -EINVAL;
                
        if (v->yres_virtual < v->yres)
                return -EINVAL;
                                
        return 0;
}


static int radeonfb_check_var (struct fb_var_screeninfo *var, struct fb_info *info)
{
        struct radeonfb_info *rinfo = (struct radeonfb_info *) info->par;
        struct fb_var_screeninfo v;
        int nom, den;

        memcpy (&v, var, sizeof (v));

        switch (v.bits_per_pixel) {
		case 0 ... 8:
			v.bits_per_pixel = 8;
			break;
		case 9 ... 16:
			v.bits_per_pixel = 16;
			break;
		case 17 ... 24:
#if 0 /* Doesn't seem to work */
			v.bits_per_pixel = 24;
			break;
#endif			
			return -EINVAL;
		case 25 ... 32:
			v.bits_per_pixel = 32;
			break;
		default:
			return -EINVAL;
	}

	switch (var_to_depth(&v)) {
                case 8:
                        nom = den = 1;
                        v.red.offset = v.green.offset = v.blue.offset = 0;
                        v.red.length = v.green.length = v.blue.length = 8;
                        v.transp.offset = v.transp.length = 0;
                        break;
		case 15:
			nom = 2;
			den = 1;
			v.red.offset = 10;
			v.green.offset = 5;
			v.red.offset = 0;
			v.red.length = v.green.length = v.blue.length = 5;
			v.transp.offset = v.transp.length = 0;
			break;
                case 16:
                        nom = 2;
                        den = 1;
                        v.red.offset = 11;
                        v.green.offset = 5;
                        v.blue.offset = 0;
                        v.red.length = 5;
                        v.green.length = 6;
                        v.blue.length = 5;
                        v.transp.offset = v.transp.length = 0;
                        break;                          
                case 24:
                        nom = 4;
                        den = 1;
                        v.red.offset = 16;
                        v.green.offset = 8;
                        v.blue.offset = 0;
                        v.red.length = v.blue.length = v.green.length = 8;
                        v.transp.offset = v.transp.length = 0;
                        break;
                case 32:
                        nom = 4;
                        den = 1;
                        v.red.offset = 16;
                        v.green.offset = 8;
                        v.blue.offset = 0;
                        v.red.length = v.blue.length = v.green.length = 8;
                        v.transp.offset = 24;
                        v.transp.length = 8;
                        break;
                default:
                        printk ("radeonfb: mode %dx%dx%d rejected, color depth invalid\n",
                                var->xres, var->yres, var->bits_per_pixel);
                        return -EINVAL;
        }

        if (radeon_do_maximize(rinfo, var, &v, nom, den) < 0)
                return -EINVAL;  
                
        if (v.xoffset < 0)
                v.xoffset = 0;
        if (v.yoffset < 0)
                v.yoffset = 0;
         
        if (v.xoffset > v.xres_virtual - v.xres)
                v.xoffset = v.xres_virtual - v.xres - 1;
                        
        if (v.yoffset > v.yres_virtual - v.yres)
                v.yoffset = v.yres_virtual - v.yres - 1;
         
        v.red.msb_right = v.green.msb_right = v.blue.msb_right =
                          v.transp.offset = v.transp.length =
                          v.transp.msb_right = 0;

	v.accel_flags = 0;
			
        memcpy(var, &v, sizeof(v));
        
        return 0;
}


static int radeonfb_pan_display (struct fb_var_screeninfo *var,
                                 struct fb_info *info)
{
        struct radeonfb_info *rinfo = (struct radeonfb_info *) info;

        if ((var->xoffset + var->xres > var->xres_virtual)
	    || (var->yoffset + var->yres > var->yres_virtual))
               return -EINVAL;
                
        if (rinfo->asleep)
        	return 0;

        OUTREG(CRTC_OFFSET, ((var->yoffset * var->xres_virtual + var->xoffset)
			     * var->bits_per_pixel / 8) & ~7);
        return 0;
}


static int radeonfb_ioctl (struct inode *inode, struct file *file, unsigned int cmd,
                           unsigned long arg, struct fb_info *info)
{
        struct radeonfb_info *rinfo = (struct radeonfb_info *) info;
	unsigned int tmp;
	u32 value = 0;
	int rc;

	switch (cmd) {
		/*
		 * TODO:  set mirror accordingly for non-Mobility chipsets with 2 CRTC's
		 */
		case FBIO_RADEON_SET_MIRROR:
			switch (rinfo->arch) {
				case RADEON_R100:
				case RADEON_RV100:
				case RADEON_R200:
				case RADEON_RV200:
				case RADEON_RV250:
				case RADEON_R300:
					return -EINVAL;
				default:
					/* RADEON M6, RADEON_M7, RADEON_M9 */
					break;
			}

			rc = get_user(value, (__u32*)arg);

			if (rc)
				return rc;

			if (value & 0x01) {
				tmp = INREG(LVDS_GEN_CNTL);

				tmp |= (LVDS_ON | LVDS_BLON);
			} else {
				tmp = INREG(LVDS_GEN_CNTL);

				tmp &= ~(LVDS_ON | LVDS_BLON);
			}

			OUTREG(LVDS_GEN_CNTL, tmp);

			if (value & 0x02) {
				tmp = INREG(CRTC_EXT_CNTL);
				tmp |= CRTC_CRT_ON;

				mirror = 1;
			} else {
				tmp = INREG(CRTC_EXT_CNTL);
				tmp &= ~CRTC_CRT_ON;

				mirror = 0;
			}

			OUTREG(CRTC_EXT_CNTL, tmp);

			break;
		case FBIO_RADEON_GET_MIRROR:
			switch (rinfo->arch) {
				case RADEON_R100:
				case RADEON_RV100:
				case RADEON_R200:
				case RADEON_RV200:
				case RADEON_RV250:
				case RADEON_R300:
					return -EINVAL;
				default:
					/* RADEON M6, RADEON_M7, RADEON_M9 */
					break;
			}

			tmp = INREG(LVDS_GEN_CNTL);
			if ((LVDS_ON | LVDS_BLON) & tmp)
				value |= 0x01;

			tmp = INREG(CRTC_EXT_CNTL);
			if (CRTC_CRT_ON & tmp)
				value |= 0x02;

			return put_user(value, (__u32*)arg);
		default:
			return -EINVAL;
	}

	return -EINVAL;
}


static int radeonfb_blank (int blank, struct fb_info *info)
{
        struct radeonfb_info *rinfo = (struct radeonfb_info *) info;
        u32 val = INREG(CRTC_EXT_CNTL);
	u32 val2 = INREG(LVDS_GEN_CNTL);

	if (rinfo->asleep)
		return 0;
		
                        
        /* reset it */
        val &= ~(CRTC_DISPLAY_DIS | CRTC_HSYNC_DIS |
                 CRTC_VSYNC_DIS);
	val2 &= ~(LVDS_DISPLAY_DIS);

        switch (blank) {
                case VESA_NO_BLANKING:
                        break;
                case VESA_VSYNC_SUSPEND:
                        val |= (CRTC_DISPLAY_DIS | CRTC_VSYNC_DIS);
                        break;
                case VESA_HSYNC_SUSPEND:
                        val |= (CRTC_DISPLAY_DIS | CRTC_HSYNC_DIS);
                        break;
                case VESA_POWERDOWN:
                        val |= (CRTC_DISPLAY_DIS | CRTC_VSYNC_DIS | 
                                CRTC_HSYNC_DIS);
			val2 |= (LVDS_DISPLAY_DIS);
                        break;
        }

	switch (rinfo->dviDisp_type) {
		case MT_LCD:
			OUTREG(LVDS_GEN_CNTL, val2);
			break;
		case MT_CRT:
		default:
		        OUTREG(CRTC_EXT_CNTL, val);
			break;
	}

	return 0;
}


static int radeonfb_setcolreg (unsigned regno, unsigned red, unsigned green,
                             unsigned blue, unsigned transp, struct fb_info *info)
{
        struct radeonfb_info *rinfo = (struct radeonfb_info *) info;
	u32 pindex, vclk_cntl;
	unsigned int i;
	
	if (regno > 255)
		return 1;

	red >>= 8;
	green >>= 8;
	blue >>= 8;
	rinfo->palette[regno].red = red;
	rinfo->palette[regno].green = green;
	rinfo->palette[regno].blue = blue;

        /* default */
        pindex = regno;

        if (!rinfo->asleep) {
		vclk_cntl = INPLL(VCLK_ECP_CNTL);
		OUTPLL(VCLK_ECP_CNTL, vclk_cntl & ~PIXCLK_DAC_ALWAYS_ONb);

		if (rinfo->bpp == 16) {
			pindex = regno * 8;

			if (rinfo->depth == 16 && regno > 63)
				return 1;
			if (rinfo->depth == 15 && regno > 31)
				return 1;

			/* For 565, the green component is mixed one order below */
			if (rinfo->depth == 16) {
		                OUTREG(PALETTE_INDEX, pindex>>1);
	       	         	OUTREG(PALETTE_DATA, (rinfo->palette[regno>>1].red << 16) |
	                        	(green << 8) | (rinfo->palette[regno>>1].blue));
	                	green = rinfo->palette[regno<<1].green;
	        	}
		}

		if (rinfo->depth != 16 || regno < 32) {
			OUTREG(PALETTE_INDEX, pindex);
			OUTREG(PALETTE_DATA, (red << 16) | (green << 8) | blue);
		}

		OUTPLL(VCLK_ECP_CNTL, vclk_cntl);
	}
 	if (regno < 16) {
        	switch (rinfo->depth) {
		case 15:
			((u16 *) (info->pseudo_palette))[regno] =
			    (regno << 10) | (regno << 5) | regno;
			break;
		case 16:
			((u16 *) (info->pseudo_palette))[regno] =
			    (regno << 11) | (regno << 6) | regno;
			break;
		case 24:
			((u32 *) (info->pseudo_palette))[regno] =
			    (regno << 16) | (regno << 8) | regno;
			break;
		case 32:
			i = (regno << 8) | regno;
			((u32 *) (info->pseudo_palette))[regno] =
			    (i << 16) | i;
			break;
		}
        }
	return 0;
}



static void radeon_save_state (struct radeonfb_info *rinfo,
                               struct radeon_regs *save)
{
	/* CRTC regs */
	save->crtc_gen_cntl = INREG(CRTC_GEN_CNTL);
	save->crtc_ext_cntl = INREG(CRTC_EXT_CNTL);
	save->dac_cntl = INREG(DAC_CNTL);
        save->crtc_h_total_disp = INREG(CRTC_H_TOTAL_DISP);
        save->crtc_h_sync_strt_wid = INREG(CRTC_H_SYNC_STRT_WID);
        save->crtc_v_total_disp = INREG(CRTC_V_TOTAL_DISP);
        save->crtc_v_sync_strt_wid = INREG(CRTC_V_SYNC_STRT_WID);
	save->crtc_pitch = INREG(CRTC_PITCH);
#if defined(__BIG_ENDIAN)
	save->surface_cntl = INREG(SURFACE_CNTL);
#endif

	/* FP regs */
	save->fp_crtc_h_total_disp = INREG(FP_CRTC_H_TOTAL_DISP);
	save->fp_crtc_v_total_disp = INREG(FP_CRTC_V_TOTAL_DISP);
	save->fp_gen_cntl = INREG(FP_GEN_CNTL);
	save->fp_h_sync_strt_wid = INREG(FP_H_SYNC_STRT_WID);
	save->fp_horz_stretch = INREG(FP_HORZ_STRETCH);
	save->fp_v_sync_strt_wid = INREG(FP_V_SYNC_STRT_WID);
	save->fp_vert_stretch = INREG(FP_VERT_STRETCH);
	save->lvds_gen_cntl = INREG(LVDS_GEN_CNTL);
	save->lvds_pll_cntl = INREG(LVDS_PLL_CNTL);
	save->tmds_crc = INREG(TMDS_CRC);
	save->tmds_transmitter_cntl = INREG(TMDS_TRANSMITTER_CNTL);
	save->vclk_ecp_cntl = INPLL(VCLK_ECP_CNTL);
}



static int radeonfb_set_par (struct fb_info *info)
{
	struct radeonfb_info *rinfo = (struct radeonfb_info *)info->par;
	struct fb_var_screeninfo *mode = &info->var;
	struct radeon_regs newmode;
	int hTotal, vTotal, hSyncStart, hSyncEnd,
	    hSyncPol, vSyncStart, vSyncEnd, vSyncPol, cSync;
	u8 hsync_adj_tab[] = {0, 0x12, 9, 9, 6, 5};
	u8 hsync_fudge_fp[] = {2, 2, 0, 0, 5, 5};
	u32 dotClock = 1000000000 / mode->pixclock,
	    sync, h_sync_pol, v_sync_pol;
	int freq = dotClock / 10;  /* x 100 */
        int xclk_freq, vclk_freq, xclk_per_trans, xclk_per_trans_precise;
        int useable_precision, roff, ron;
        int min_bits, format = 0;
	int hsync_start, hsync_fudge, bytpp, hsync_wid, vsync_wid;
	int primary_mon = PRIMARY_MONITOR(rinfo);
	int depth = var_to_depth(mode);

	rinfo->xres = mode->xres;
	rinfo->yres = mode->yres;
	rinfo->xres_virtual = mode->xres_virtual;
	rinfo->yres_virtual = mode->yres_virtual;
	rinfo->pixclock = mode->pixclock;

	hSyncStart = mode->xres + mode->right_margin;
	hSyncEnd = hSyncStart + mode->hsync_len;
	hTotal = hSyncEnd + mode->left_margin;

	vSyncStart = mode->yres + mode->lower_margin;
	vSyncEnd = vSyncStart + mode->vsync_len;
	vTotal = vSyncEnd + mode->upper_margin;

	if ((primary_mon == MT_DFP) || (primary_mon == MT_LCD)) {
		if (rinfo->panel_xres < mode->xres)
			rinfo->xres = mode->xres = rinfo->panel_xres;
		if (rinfo->panel_yres < mode->yres)
			rinfo->yres = mode->yres = rinfo->panel_yres;

		hTotal = mode->xres + rinfo->hblank;
		hSyncStart = mode->xres + rinfo->hOver_plus;
		hSyncEnd = hSyncStart + rinfo->hSync_width;

		vTotal = mode->yres + rinfo->vblank;
		vSyncStart = mode->yres + rinfo->vOver_plus;
		vSyncEnd = vSyncStart + rinfo->vSync_width;
	}

	sync = mode->sync;
	h_sync_pol = sync & FB_SYNC_HOR_HIGH_ACT ? 0 : 1;
	v_sync_pol = sync & FB_SYNC_VERT_HIGH_ACT ? 0 : 1;

	RTRACE("hStart = %d, hEnd = %d, hTotal = %d\n",
		hSyncStart, hSyncEnd, hTotal);
	RTRACE("vStart = %d, vEnd = %d, vTotal = %d\n",
		vSyncStart, vSyncEnd, vTotal);

	hsync_wid = (hSyncEnd - hSyncStart) / 8;
	vsync_wid = vSyncEnd - vSyncStart;
	if (hsync_wid == 0)
		hsync_wid = 1;
	else if (hsync_wid > 0x3f)	/* max */
		hsync_wid = 0x3f;

	if (vsync_wid == 0)
		vsync_wid = 1;
	else if (vsync_wid > 0x1f)	/* max */
		vsync_wid = 0x1f;

	hSyncPol = mode->sync & FB_SYNC_HOR_HIGH_ACT ? 0 : 1;
	vSyncPol = mode->sync & FB_SYNC_VERT_HIGH_ACT ? 0 : 1;

	cSync = mode->sync & FB_SYNC_COMP_HIGH_ACT ? (1 << 4) : 0;

	format = radeon_get_dstbpp(depth);
	bytpp = mode->bits_per_pixel >> 3;

	if ((primary_mon == MT_DFP) || (primary_mon == MT_LCD))
		hsync_fudge = hsync_fudge_fp[format-1];
	else
		hsync_fudge = hsync_adj_tab[format-1];

	hsync_start = hSyncStart - 8 + hsync_fudge;

	newmode.crtc_gen_cntl = CRTC_EXT_DISP_EN | CRTC_EN |
				(format << 8);

	if ((primary_mon == MT_DFP) || (primary_mon == MT_LCD)) {
		newmode.crtc_ext_cntl = VGA_ATI_LINEAR | XCRT_CNT_EN;
		if (mirror)
			newmode.crtc_ext_cntl |= CRTC_CRT_ON;

		newmode.crtc_gen_cntl &= ~(CRTC_DBL_SCAN_EN |
					   CRTC_INTERLACE_EN);
	} else {
		newmode.crtc_ext_cntl = VGA_ATI_LINEAR | XCRT_CNT_EN |
					CRTC_CRT_ON;
	}

	newmode.dac_cntl = /* INREG(DAC_CNTL) | */ DAC_MASK_ALL | DAC_VGA_ADR_EN |
			   DAC_8BIT_EN;

	newmode.crtc_h_total_disp = ((((hTotal / 8) - 1) & 0x3ff) |
				     (((mode->xres / 8) - 1) << 16));

	newmode.crtc_h_sync_strt_wid = ((hsync_start & 0x1fff) |
					(hsync_wid << 16) | (h_sync_pol << 23));

	newmode.crtc_v_total_disp = ((vTotal - 1) & 0xffff) |
				    ((mode->yres - 1) << 16);

	newmode.crtc_v_sync_strt_wid = (((vSyncStart - 1) & 0xfff) |
					 (vsync_wid << 16) | (v_sync_pol  << 23));

	newmode.crtc_pitch = (mode->xres_virtual >> 3);
	newmode.crtc_pitch |= (newmode.crtc_pitch << 16);

#if defined(__BIG_ENDIAN)
	/*
	 * It looks like recent chips have a problem with SURFACE_CNTL,
	 * setting SURF_TRANSLATION_DIS completely disables the
	 * swapper as well, so we leave it unset now.
	 */
	newmode.surface_cntl = 0;

	/* Setup swapping on both apertures, though we currently
	 * only use aperture 0, enabling swapper on aperture 1
	 * won't harm
	 */
	switch (mode->bits_per_pixel) {
		case 16:
			newmode.surface_cntl |= NONSURF_AP0_SWP_16BPP;
			newmode.surface_cntl |= NONSURF_AP1_SWP_16BPP;
			break;
		case 24:	
		case 32:
			newmode.surface_cntl |= NONSURF_AP0_SWP_32BPP;
			newmode.surface_cntl |= NONSURF_AP1_SWP_32BPP;
			break;
	}
#endif

	rinfo->pitch = ((mode->xres_virtual * ((mode->bits_per_pixel + 1) / 8) + 0x3f)
 			& ~(0x3f)) / 64;

	RTRACE("h_total_disp = 0x%x\t   hsync_strt_wid = 0x%x\n",
		newmode.crtc_h_total_disp, newmode.crtc_h_sync_strt_wid);
	RTRACE("v_total_disp = 0x%x\t   vsync_strt_wid = 0x%x\n",
		newmode.crtc_v_total_disp, newmode.crtc_v_sync_strt_wid);

	newmode.xres = mode->xres;
	newmode.yres = mode->yres;

	rinfo->bpp = mode->bits_per_pixel;
	rinfo->depth = depth;

	if (freq > rinfo->pll.ppll_max)
		freq = rinfo->pll.ppll_max;
	if (freq*12 < rinfo->pll.ppll_min)
		freq = rinfo->pll.ppll_min / 12;

	{
		struct {
			int divider;
			int bitvalue;
		} *post_div,
		  post_divs[] = {
			{ 1,  0 },
			{ 2,  1 },
			{ 4,  2 },
			{ 8,  3 },
			{ 3,  4 },
			{ 16, 5 },
			{ 6,  6 },
			{ 12, 7 },
			{ 0,  0 },
		};

		for (post_div = &post_divs[0]; post_div->divider; ++post_div) {
			rinfo->pll_output_freq = post_div->divider * freq;
			if (rinfo->pll_output_freq >= rinfo->pll.ppll_min  &&
			    rinfo->pll_output_freq <= rinfo->pll.ppll_max)
				break;
		}

		rinfo->post_div = post_div->divider;
		rinfo->fb_div = round_div(rinfo->pll.ref_div*rinfo->pll_output_freq,
					  rinfo->pll.ref_clk);
		newmode.ppll_ref_div = rinfo->pll.ref_div;
		newmode.ppll_div_3 = rinfo->fb_div | (post_div->bitvalue << 16);
	}
	newmode.vclk_ecp_cntl = rinfo->init_state.vclk_ecp_cntl;


	RTRACE("post div = 0x%x\n", rinfo->post_div);
	RTRACE("fb_div = 0x%x\n", rinfo->fb_div);
	RTRACE("ppll_div_3 = 0x%x\n", newmode.ppll_div_3);

	/* DDA */
	vclk_freq = round_div(rinfo->pll.ref_clk * rinfo->fb_div,
			      rinfo->pll.ref_div * rinfo->post_div);
	xclk_freq = rinfo->pll.xclk;

	xclk_per_trans = round_div(xclk_freq * 128, vclk_freq * mode->bits_per_pixel);

	min_bits = min_bits_req(xclk_per_trans);
	useable_precision = min_bits + 1;

	xclk_per_trans_precise = round_div((xclk_freq * 128) << (11 - useable_precision),
					   vclk_freq * mode->bits_per_pixel);

	ron = (4 * rinfo->ram.mb + 3 * _max(rinfo->ram.trcd - 2, 0) +
	       2 * rinfo->ram.trp + rinfo->ram.twr + rinfo->ram.cl + rinfo->ram.tr2w +
	       xclk_per_trans) << (11 - useable_precision);
	roff = xclk_per_trans_precise * (32 - 4);

	RTRACE("ron = %d, roff = %d\n", ron, roff);
	RTRACE("vclk_freq = %d, per = %d\n", vclk_freq, xclk_per_trans_precise);

	if ((ron + rinfo->ram.rloop) >= roff) {
		printk("radeonfb: error ron out of range\n");
		return -EINVAL;
	}

	newmode.dda_config = (xclk_per_trans_precise |
			      (useable_precision << 16) |
			      (rinfo->ram.rloop << 20));
	newmode.dda_on_off = (ron << 16) | roff;

	if ((primary_mon == MT_DFP) || (primary_mon == MT_LCD)) {
		unsigned int hRatio, vRatio;

		/* We force the pixel clock to be always enabled. Allowing it
		 * to be power managed during blanking would save power, but has
		 * nasty interactions with the 2D engine & sleep code that haven't
		 * been solved yet. --BenH
		 */
		newmode.vclk_ecp_cntl &= ~PIXCLK_DAC_ALWAYS_ONb;
		
		if (mode->xres > rinfo->panel_xres)
			mode->xres = rinfo->panel_xres;
		if (mode->yres > rinfo->panel_yres)
			mode->yres = rinfo->panel_yres;

		newmode.fp_horz_stretch = (((rinfo->panel_xres / 8) - 1)
					   << HORZ_PANEL_SHIFT);
		newmode.fp_vert_stretch = ((rinfo->panel_yres - 1)
					   << VERT_PANEL_SHIFT);

		if (mode->xres != rinfo->panel_xres) {
			hRatio = round_div(mode->xres * HORZ_STRETCH_RATIO_MAX,
					   rinfo->panel_xres);
			newmode.fp_horz_stretch = (((((unsigned long)hRatio) & HORZ_STRETCH_RATIO_MASK)) |
						   (newmode.fp_horz_stretch &
						    (HORZ_PANEL_SIZE | HORZ_FP_LOOP_STRETCH |
						     HORZ_AUTO_RATIO_INC)));
			newmode.fp_horz_stretch |= (HORZ_STRETCH_BLEND |
						    HORZ_STRETCH_ENABLE);
		}
		newmode.fp_horz_stretch &= ~HORZ_AUTO_RATIO;

		if (mode->yres != rinfo->panel_yres) {
			vRatio = round_div(mode->yres * VERT_STRETCH_RATIO_MAX,
					   rinfo->panel_yres);
			newmode.fp_vert_stretch = (((((unsigned long)vRatio) & VERT_STRETCH_RATIO_MASK)) |
						   (newmode.fp_vert_stretch &
						   (VERT_PANEL_SIZE | VERT_STRETCH_RESERVED)));
			newmode.fp_vert_stretch |= (VERT_STRETCH_BLEND |
						    VERT_STRETCH_ENABLE);
		}
		newmode.fp_vert_stretch &= ~VERT_AUTO_RATIO_EN;

		newmode.fp_gen_cntl = (rinfo->init_state.fp_gen_cntl & (u32)
				       ~(FP_SEL_CRTC2 |
					 FP_RMX_HVSYNC_CONTROL_EN |
					 FP_DFP_SYNC_SEL |
					 FP_CRT_SYNC_SEL |
					 FP_CRTC_LOCK_8DOT |
					 FP_USE_SHADOW_EN |
					 FP_CRTC_USE_SHADOW_VEND |
					 FP_CRT_SYNC_ALT));

		newmode.fp_gen_cntl |= (FP_CRTC_DONT_SHADOW_VPAR |
					FP_CRTC_DONT_SHADOW_HEND);

		newmode.lvds_gen_cntl = rinfo->init_state.lvds_gen_cntl;
		newmode.lvds_pll_cntl = rinfo->init_state.lvds_pll_cntl;
		newmode.tmds_crc = rinfo->init_state.tmds_crc;
		newmode.tmds_transmitter_cntl = rinfo->init_state.tmds_transmitter_cntl;

		if (primary_mon == MT_LCD) {
			newmode.lvds_gen_cntl |= (LVDS_ON | LVDS_BLON);
			newmode.fp_gen_cntl &= ~(FP_FPON | FP_TMDS_EN);
		} else {
			/* DFP */
			newmode.fp_gen_cntl |= (FP_FPON | FP_TMDS_EN);
			newmode.tmds_transmitter_cntl = (TMDS_RAN_PAT_RST |
							 ICHCSEL | TMDS_PLL_EN) &
							 ~(TMDS_PLLRST);
			newmode.crtc_ext_cntl &= ~CRTC_CRT_ON;
		}

		newmode.fp_crtc_h_total_disp = (((rinfo->hblank / 8) & 0x3ff) |
				(((mode->xres / 8) - 1) << 16));
		newmode.fp_crtc_v_total_disp = (rinfo->vblank & 0xffff) |
				((mode->yres - 1) << 16);
		newmode.fp_h_sync_strt_wid = ((rinfo->hOver_plus & 0x1fff) |
				(hsync_wid << 16) | (h_sync_pol << 23));
		newmode.fp_v_sync_strt_wid = ((rinfo->vOver_plus & 0xfff) |
				(vsync_wid << 16) | (v_sync_pol  << 23));
	}

	/* do it! */
	if (!rinfo->asleep) {
		radeon_write_mode (rinfo, &newmode);
	
	}
	/* Update fix */
        info->fix.line_length = rinfo->pitch*64;
        info->fix.visual = rinfo->depth == 8 ? FB_VISUAL_PSEUDOCOLOR : FB_VISUAL_DIRECTCOLOR;

#ifdef CONFIG_BOOTX_TEXT
	/* Update debug text engine */
	btext_update_display(rinfo->fb_base_phys, mode->xres, mode->yres,
			     rinfo->depth, rinfo->pitch*64);
#endif

	return 0;
}


static void radeon_write_mode (struct radeonfb_info *rinfo,
                               struct radeon_regs *mode)
{
	int i;
	int primary_mon = PRIMARY_MONITOR(rinfo);

	radeonfb_blank(VESA_POWERDOWN, (struct fb_info *)rinfo);


	if (rinfo->arch == RADEON_M6) {
		for (i=0; i<8; i++)
			OUTREG(common_regs_m6[i].reg, common_regs_m6[i].val);
	} else {
		for (i=0; i<9; i++)
			OUTREG(common_regs[i].reg, common_regs[i].val);
	}

	OUTREG(CRTC_GEN_CNTL, mode->crtc_gen_cntl);
	OUTREGP(CRTC_EXT_CNTL, mode->crtc_ext_cntl,
		CRTC_HSYNC_DIS | CRTC_VSYNC_DIS | CRTC_DISPLAY_DIS);
	OUTREGP(DAC_CNTL, mode->dac_cntl, DAC_RANGE_CNTL | DAC_BLANKING);
	OUTREG(CRTC_H_TOTAL_DISP, mode->crtc_h_total_disp);
	OUTREG(CRTC_H_SYNC_STRT_WID, mode->crtc_h_sync_strt_wid);
	OUTREG(CRTC_V_TOTAL_DISP, mode->crtc_v_total_disp);
	OUTREG(CRTC_V_SYNC_STRT_WID, mode->crtc_v_sync_strt_wid);
	OUTREG(CRTC_OFFSET, 0);
	OUTREG(CRTC_OFFSET_CNTL, 0);
	OUTREG(CRTC_PITCH, mode->crtc_pitch);

#if defined(__BIG_ENDIAN)
	OUTREG(SURFACE_CNTL, mode->surface_cntl);
#endif

	while ((INREG(CLOCK_CNTL_INDEX) & PPLL_DIV_SEL_MASK) !=
	       PPLL_DIV_SEL_MASK) {
		OUTREGP(CLOCK_CNTL_INDEX, PPLL_DIV_SEL_MASK, 0xffff);
	}

	OUTPLLP(PPLL_CNTL, PPLL_RESET, 0xffff);

	while ((INPLL(PPLL_REF_DIV) & PPLL_REF_DIV_MASK) !=
	       (mode->ppll_ref_div & PPLL_REF_DIV_MASK)) {
		OUTPLLP(PPLL_REF_DIV, mode->ppll_ref_div, ~PPLL_REF_DIV_MASK);
	}

	while ((INPLL(PPLL_DIV_3) & PPLL_FB3_DIV_MASK) !=
	       (mode->ppll_div_3 & PPLL_FB3_DIV_MASK)) {
		OUTPLLP(PPLL_DIV_3, mode->ppll_div_3, ~PPLL_FB3_DIV_MASK);
	}

	while ((INPLL(PPLL_DIV_3) & PPLL_POST3_DIV_MASK) !=
	       (mode->ppll_div_3 & PPLL_POST3_DIV_MASK)) {
		OUTPLLP(PPLL_DIV_3, mode->ppll_div_3, ~PPLL_POST3_DIV_MASK);
	}

	OUTPLL(HTOTAL_CNTL, 0);

	OUTPLLP(PPLL_CNTL, 0, ~PPLL_RESET);

//	OUTREG(DDA_CONFIG, mode->dda_config);
//	OUTREG(DDA_ON_OFF, mode->dda_on_off);

	if ((primary_mon == MT_DFP) || (primary_mon == MT_LCD)) {
		OUTREG(FP_CRTC_H_TOTAL_DISP, mode->fp_crtc_h_total_disp);
		OUTREG(FP_CRTC_V_TOTAL_DISP, mode->fp_crtc_v_total_disp);
		OUTREG(FP_H_SYNC_STRT_WID, mode->fp_h_sync_strt_wid);
		OUTREG(FP_V_SYNC_STRT_WID, mode->fp_v_sync_strt_wid);
		OUTREG(FP_HORZ_STRETCH, mode->fp_horz_stretch);
		OUTREG(FP_VERT_STRETCH, mode->fp_vert_stretch);
		OUTREG(FP_GEN_CNTL, mode->fp_gen_cntl);
		OUTREG(TMDS_CRC, mode->tmds_crc);
		OUTREG(TMDS_TRANSMITTER_CNTL, mode->tmds_transmitter_cntl);

		if (primary_mon == MT_LCD) {
			unsigned int tmp = INREG(LVDS_GEN_CNTL);

			mode->lvds_gen_cntl &= ~LVDS_STATE_MASK;
			mode->lvds_gen_cntl |= (rinfo->init_state.lvds_gen_cntl & LVDS_STATE_MASK);

			if ((tmp & (LVDS_ON | LVDS_BLON)) ==
			    (mode->lvds_gen_cntl & (LVDS_ON | LVDS_BLON))) {
				OUTREG(LVDS_GEN_CNTL, mode->lvds_gen_cntl);
			} else {
				if (mode->lvds_gen_cntl & (LVDS_ON | LVDS_BLON)) {
					udelay(1000);
					OUTREG(LVDS_GEN_CNTL, mode->lvds_gen_cntl);
				} else {
					OUTREG(LVDS_GEN_CNTL, mode->lvds_gen_cntl |
					       LVDS_BLON);
					udelay(1000);
					OUTREG(LVDS_GEN_CNTL, mode->lvds_gen_cntl);
				}
			}
		}
	}

	radeonfb_blank(VESA_NO_BLANKING, (struct fb_info *)rinfo);

	OUTPLL(VCLK_ECP_CNTL, mode->vclk_ecp_cntl);
	
	return;
}

static struct fb_ops radeonfb_ops = {
	.owner			= THIS_MODULE,
	.fb_check_var		= radeonfb_check_var,
	.fb_set_par		= radeonfb_set_par,
	.fb_setcolreg		= radeonfb_setcolreg,
	.fb_pan_display 	= radeonfb_pan_display,
	.fb_blank		= radeonfb_blank,
	.fb_ioctl		= radeonfb_ioctl,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
	.fb_cursor	= soft_cursor,
};


static int __devinit radeon_set_fbinfo (struct radeonfb_info *rinfo)
{
	struct fb_info *info;

	info = &rinfo->info;

	info->currcon = -1;
	info->par = rinfo;
	info->pseudo_palette = rinfo->pseudo_palette;
        info->node = NODEV;
        info->flags = FBINFO_FLAG_DEFAULT;
        info->fbops = &radeonfb_ops;
        info->display_fg = NULL;
        info->screen_base = (char *)rinfo->fb_base;

	/* Fill fix common fields */
	strncpy(info->fix.id, rinfo->name, sizeof(info->fix.id));
	info->fix.id[sizeof(info->fix.id) - 1] = '\0';
        info->fix.smem_start = rinfo->fb_base_phys;
        info->fix.smem_len = rinfo->video_ram;
        info->fix.type = FB_TYPE_PACKED_PIXELS;
        info->fix.visual = FB_VISUAL_PSEUDOCOLOR;
        info->fix.xpanstep = 8;
        info->fix.ypanstep = 1;
        info->fix.ywrapstep = 0;
        info->fix.type_aux = 0;
        info->fix.mmio_start = rinfo->mmio_base_phys;
        info->fix.mmio_len = RADEON_REGSIZE;
	info->fix.accel = FB_ACCEL_NONE;

        if (radeon_init_disp (rinfo) < 0)
                return -1;   

        return 0;
}



static int radeonfb_pci_register (struct pci_dev *pdev,
				  const struct pci_device_id *ent)
{
	struct radeonfb_info *rinfo;
	struct radeon_chip_info *rci = &radeon_chip_info[ent->driver_data];
	u32 tmp;

	printk("radeonfb_pci_register BEGIN\n");

	/* Enable device in PCI config */
	if (pci_enable_device(pdev) != 0) {
		printk(KERN_ERR "radeonfb: Cannot enable PCI device\n");
		return -ENODEV;
	}

	rinfo = kmalloc (sizeof (struct radeonfb_info), GFP_KERNEL);
	if (!rinfo) {
		printk ("radeonfb: could not allocate memory\n");
		return -ENODEV;
	}

	memset (rinfo, 0, sizeof (struct radeonfb_info));
	//info = &rinfo->info;
	rinfo->pdev = pdev;
	strcpy(rinfo->name, rci->name);
	rinfo->arch = rci->arch;

	/* Set base addrs */
	rinfo->fb_base_phys = pci_resource_start (pdev, 0);
	rinfo->mmio_base_phys = pci_resource_start (pdev, 2);

	/* request the mem regions */
	if (!request_mem_region (rinfo->fb_base_phys,
				 pci_resource_len(pdev, 0), "radeonfb")) {
		printk ("radeonfb: cannot reserve FB region\n");
		kfree (rinfo);
		return -ENODEV;
	}

	if (!request_mem_region (rinfo->mmio_base_phys,
				 pci_resource_len(pdev, 2), "radeonfb")) {
		printk ("radeonfb: cannot reserve MMIO region\n");
		release_mem_region (rinfo->fb_base_phys,
				    pci_resource_len(pdev, 0));
		kfree (rinfo);
		return -ENODEV;
	}

	/* map the regions */
	rinfo->mmio_base = (u32) ioremap (rinfo->mmio_base_phys,
				    		    RADEON_REGSIZE);
	if (!rinfo->mmio_base) {
		printk ("radeonfb: cannot map MMIO\n");
		release_mem_region (rinfo->mmio_base_phys,
				    pci_resource_len(pdev, 2));
		release_mem_region (rinfo->fb_base_phys,
				    pci_resource_len(pdev, 0));
		kfree (rinfo);
		return -ENODEV;
	}

	rinfo->chipset = pdev->device;

	switch (rinfo->arch) {
		case RADEON_R100:
			rinfo->hasCRTC2 = 0;
			break;
		default:
			/* all the rest have it */
			rinfo->hasCRTC2 = 1;
			break;
	}

	if (mirror)
		printk("radeonfb: mirroring display to CRT\n");

	/* framebuffer size */
	tmp = INREG(CONFIG_MEMSIZE);

	/* mem size is bits [28:0], mask off the rest */
	rinfo->video_ram = tmp & CONFIG_MEMSIZE_MASK;

	/* ram type */
	tmp = INREG(MEM_SDRAM_MODE_REG);
	switch ((MEM_CFG_TYPE & tmp) >> 30) {
		case 0:
			/* SDR SGRAM (2:1) */
			strcpy(rinfo->ram_type, "SDR SGRAM");
			rinfo->ram.ml = 4;
			rinfo->ram.mb = 4;
			rinfo->ram.trcd = 1;
			rinfo->ram.trp = 2;
			rinfo->ram.twr = 1;
			rinfo->ram.cl = 2;
			rinfo->ram.loop_latency = 16;
			rinfo->ram.rloop = 16;
	
			break;
		case 1:
			/* DDR SGRAM */
			strcpy(rinfo->ram_type, "DDR SGRAM");
			rinfo->ram.ml = 4;
			rinfo->ram.mb = 4;
			rinfo->ram.trcd = 3;
			rinfo->ram.trp = 3;
			rinfo->ram.twr = 2;
			rinfo->ram.cl = 3;
			rinfo->ram.tr2w = 1;
			rinfo->ram.loop_latency = 16;
			rinfo->ram.rloop = 16;

			break;
		default:
			/* 64-bit SDR SGRAM */
			strcpy(rinfo->ram_type, "SDR SGRAM 64");
			rinfo->ram.ml = 4;
			rinfo->ram.mb = 8;
			rinfo->ram.trcd = 3;
			rinfo->ram.trp = 3;
			rinfo->ram.twr = 1;
			rinfo->ram.cl = 3;
			rinfo->ram.tr2w = 1;
			rinfo->ram.loop_latency = 17;
			rinfo->ram.rloop = 17;

			break;
	}

	rinfo->bios_seg = radeon_find_rom(rinfo);
	radeon_get_pllinfo(rinfo, rinfo->bios_seg);

	/*
	 * Hack to get around some busted production M6's
	 * reporting no ram
	 */
	if (rinfo->video_ram == 0) {
		switch (pdev->device) {
			case PCI_DEVICE_ID_ATI_RADEON_LY:
			case PCI_DEVICE_ID_ATI_RADEON_LZ:
				rinfo->video_ram = 8192;
				break;
			default:
				break;
		}
	}


	RTRACE("radeonfb: probed %s %dk videoram\n", (rinfo->ram_type), (rinfo->video_ram/1024));

	radeon_get_moninfo(rinfo);

	radeon_get_EDID(rinfo);

	if ((rinfo->dviDisp_type == MT_DFP) || (rinfo->dviDisp_type == MT_LCD) ||
	    (rinfo->crtDisp_type == MT_DFP)) {
		if (!radeon_get_dfpinfo(rinfo)) {
			iounmap ((void*)rinfo->mmio_base);
			release_mem_region (rinfo->mmio_base_phys,
					    pci_resource_len(pdev, 2));
			release_mem_region (rinfo->fb_base_phys,
					    pci_resource_len(pdev, 0));
			kfree (rinfo);
			return -ENODEV;
		}
	}

	rinfo->fb_base = (u32) ioremap (rinfo->fb_base_phys,
				  		  rinfo->video_ram);
	if (!rinfo->fb_base) {
		printk ("radeonfb: cannot map FB\n");
		iounmap ((void*)rinfo->mmio_base);
		release_mem_region (rinfo->mmio_base_phys,
				    pci_resource_len(pdev, 2));
		release_mem_region (rinfo->fb_base_phys,
				    pci_resource_len(pdev, 0));
		kfree (rinfo);
		return -ENODEV;
	}


	/* save current mode regs before we switch into the new one
	 * so we can restore this upon __exit
	 */
	radeon_save_state (rinfo, &rinfo->init_state);

	/* set all the vital stuff */
	radeon_set_fbinfo (rinfo);

	pci_set_drvdata(pdev, rinfo);
	rinfo->next = board_list;
	board_list = rinfo;

	if (register_framebuffer ((struct fb_info *) rinfo) < 0) {
		printk ("radeonfb: could not register framebuffer\n");
		iounmap ((void*)rinfo->fb_base);
		iounmap ((void*)rinfo->mmio_base);
		release_mem_region (rinfo->mmio_base_phys,
				    pci_resource_len(pdev, 2));
		release_mem_region (rinfo->fb_base_phys,
				    pci_resource_len(pdev, 0));
		kfree (rinfo);
		return -ENODEV;
	}

#ifdef CONFIG_MTRR
	rinfo->mtrr_hdl = nomtrr ? -1 : mtrr_add(rinfo->fb_base_phys,
						 rinfo->video_ram,
						 MTRR_TYPE_WRCOMB, 1);
#endif

	printk ("radeonfb: ATI Radeon %s %s %d MB\n", rinfo->name, rinfo->ram_type,
		(rinfo->video_ram/(1024*1024)));

	if (rinfo->hasCRTC2) {
		printk("radeonfb: DVI port %s monitor connected\n",
			GET_MON_NAME(rinfo->dviDisp_type));
		printk("radeonfb: CRT port %s monitor connected\n",
			GET_MON_NAME(rinfo->crtDisp_type));
	} else {
		printk("radeonfb: CRT port %s monitor connected\n",
			GET_MON_NAME(rinfo->crtDisp_type));
	}

	printk("radeonfb_pci_register END\n");

	return 0;
}



static void __devexit radeonfb_pci_unregister (struct pci_dev *pdev)
{
        struct radeonfb_info *rinfo = pci_get_drvdata(pdev);
 
        if (!rinfo)
                return;
 
	/* restore original state
	 * 
	 * Doesn't quite work yet, possibly because of the PPC hacking
	 * I do on startup, disable for now. --BenH
	 */
        radeon_write_mode (rinfo, &rinfo->init_state);
 
#ifdef CONFIG_MTRR
	if (rinfo->mtrr_hdl >= 0)
		mtrr_del(rinfo->mtrr_hdl, 0, 0);
#endif

        unregister_framebuffer ((struct fb_info *) rinfo);
                
        iounmap ((void*)rinfo->mmio_base);
        iounmap ((void*)rinfo->fb_base);
 
	release_mem_region (rinfo->mmio_base_phys,
			    pci_resource_len(pdev, 2));
	release_mem_region (rinfo->fb_base_phys,
			    pci_resource_len(pdev, 0));
        
        kfree (rinfo);
}


static struct pci_driver radeonfb_driver = {
	name:		"radeonfb",
	id_table:	radeonfb_pci_table,
	probe:		radeonfb_pci_register,
	remove:		__devexit_p(radeonfb_pci_unregister),
};


int __init radeonfb_init (void)
{
	return pci_module_init (&radeonfb_driver);
}


void __exit radeonfb_exit (void)
{
	pci_unregister_driver (&radeonfb_driver);
}


int __init radeonfb_setup (char *options)
{
        char *this_opt;

        if (!options || !*options)
                return 0;
 
	while ((this_opt = strsep (&options, ",")) != NULL) {
		if (!*this_opt)
			continue;
		if (!strncmp(this_opt, "mirror", 6)) {
			mirror = 1;
		} else if (!strncmp(this_opt, "dfp", 3)) {
			force_dfp = 1;
		} else if (!strncmp(this_opt, "panel_yres:", 11)) {
			panel_yres = simple_strtoul((this_opt+11), NULL, 0);
		} else if (!strncmp(this_opt, "nomtrr", 6)) {
			nomtrr = 1;
                } else
			mode_option = this_opt;
        }

	return 0;
}

#ifdef MODULE
module_init(radeonfb_init);
module_exit(radeonfb_exit);
#endif


MODULE_AUTHOR("Ani Joshi");
MODULE_DESCRIPTION("framebuffer driver for ATI Radeon chipset");
MODULE_LICENSE("GPL");
