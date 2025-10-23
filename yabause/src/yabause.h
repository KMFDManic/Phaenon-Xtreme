/*  Copyright 2003-2005 Guillaume Duhamel
    Copyright 2004-2006 Theo Berkau
    Copyright 2006      Anders Montonen

    This file is part of Yabause.

    Yabause is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Yabause is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Yabause; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*/

#ifndef YABAUSE_H
#define YABAUSE_H

#include "core.h"
#include "sh2core.h"

typedef struct
{
   int percoretype;
   int sh1coretype;
   int sh2coretype;
   int vidcoretype;
   int sndcoretype;
   int m68kcoretype;
   int cdcoretype;
   int carttype;
   u8 regionid;
   const char *biospath;
   const char *cdpath;
   const char *ssfpath;
   const char *buppath;
   const char *mpegpath;
   const char *cartpath;
   const char *modemip;
   const char *modemport;
   const char *sh1rompath;
   int videoformattype;
   int frameskip;
   int clocksync;  // 1 = sync internal clock to emulation, 0 = realtime clock
   u32 basetime;   // Initial time in clocksync mode (0 = start w/ system time)
   int usethreads;
   int numthreads;
   int osdcoretype;
   int skip_load;//skip loading in YabauseInit so tests can be run without a bios
   int play_ssf;
   int use_new_scsp;
   int use_cd_block_lle;
   int use_sh2_dma_timing;
   int use_scu_dma_timing;
   int sh2_cache_enabled;
   int use_scsp_dsp_dynarec;
   int use_scu_dsp_jit;
} yabauseinit_struct;

#define CLKTYPE_1MHZ            0
#define CLKTYPE_2MHZ            1
#define CLKTYPE_3MHZ            2
#define CLKTYPE_4MHZ            3
#define CLKTYPE_5MHZ            4
#define CLKTYPE_6MHZ            5
#define CLKTYPE_7MHZ            6
#define CLKTYPE_8MHZ            7
#define CLKTYPE_9MHZ            8
#define CLKTYPE_10MHZ           9
#define CLKTYPE_11MHZ           10
#define CLKTYPE_12MHZ           11
#define CLKTYPE_13MHZ           12
#define CLKTYPE_14MHZ           13
#define CLKTYPE_15MHZ           14
#define CLKTYPE_16MHZ           15
#define CLKTYPE_17MHZ           16
#define CLKTYPE_18MHZ           17
#define CLKTYPE_19MHZ           18
#define CLKTYPE_20MHZ           19
#define CLKTYPE_21MHZ           20
#define CLKTYPE_22MHZ           21
#define CLKTYPE_23MHZ           22
#define CLKTYPE_24MHZ           23
#define CLKTYPE_25MHZ           24
#define CLKTYPE_26MHZ           25
#define CLKTYPE_27MHZ           26
#define CLKTYPE_28MHZ           27
#define CLKTYPE_29MHZ           28
#define CLKTYPE_30MHZ           29
#define CLKTYPE_31MHZ           30
#define CLKTYPE_32MHZ           31
#define CLKTYPE_33MHZ           32
#define CLKTYPE_34MHZ           33
#define CLKTYPE_35MHZ           34
#define CLKTYPE_36MHZ           35
#define CLKTYPE_37MHZ           36
#define CLKTYPE_38MHZ           37
#define CLKTYPE_39MHZ           38

#define VIDEOFORMATTYPE_NTSC    0
#define VIDEOFORMATTYPE_PAL     1

#ifndef NO_CLI
void print_usage(const char *program_name);
#endif

void YabauseChangeTiming(int freqtype);
int YabauseInit(yabauseinit_struct *init, int selected_clock);
void YabFlushBackups(void);
void YabauseDeInit(void);
void YabauseSetDecilineMode(int on);
void YabauseResetNoLoad(void);
void YabauseReset(void);
void YabauseResetButton(void);
int YabauseExec(void);
void YabauseStartSlave(void);
void YabauseStopSlave(void);
u64 YabauseGetTicks(void);
void YabauseSetVideoFormat(int type);
void YabauseSpeedySetup(void);
int YabauseQuickLoadGame(void);

#define YABSYS_TIMING_BITS  20
#define YABSYS_TIMING_MASK  ((1 << YABSYS_TIMING_BITS) - 1)

typedef struct
{
   int DecilineMode;
   int DecilineCount;
   int LineCount;
   int VBlankLineCount;
   int MaxLineCount;
   u32 DecilineStop;  // Fixed point
   u32 SH2CycleFrac;  // Fixed point
   u32 DecilineUsec;  // Fixed point
   u32 UsecFrac;      // Fixed point
   int CurSH2FreqType;
   int IsPal;
   u8 UseThreads;
   int NumThreads;
   u8 IsSSH2Running;
   u64 OneFrameTime;
   u64 tickfreq;
   int emulatebios;
   int usequickload;
   int playing_ssf;
   int use_cd_block_lle;
   int use_sh2_dma_timing;
   int use_scu_dma_timing;
   int sh2_cache_enabled;
   int use_scsp_dsp_jit;
   int use_scu_dsp_jit;
} yabsys_struct;

extern yabsys_struct yabsys;

int YabauseEmulate(void);

#endif
