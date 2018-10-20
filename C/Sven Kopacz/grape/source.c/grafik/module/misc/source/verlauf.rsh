/* GEM Resource C Source */

#include <portab.h>
#include <aes.h>
#include "VERLAUF.H"

#if !defined(WHITEBAK)
#define WHITEBAK    0x0040
#endif
#if !defined(DRAW3D)
#define DRAW3D      0x0080
#endif

#define FLAGS9  0x0200
#define FLAGS10 0x0400
#define FLAGS11 0x0800
#define FLAGS12 0x1000
#define FLAGS13 0x2000
#define FLAGS14 0x4000
#define FLAGS15 0x8000
#define STATE8  0x0100
#define STATE9  0x0200
#define STATE10 0x0400
#define STATE11 0x0800
#define STATE12 0x1000
#define STATE13 0x2000
#define STATE14 0x4000
#define STATE15 0x8000

WORD RSBB0DATA[] =
{ 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x1FFF, 0xFFF8, 
  0x1000, 0x0008, 0x1000, 0x0008, 
  0x1000, 0x0008, 0x1000, 0x0008, 
  0x1000, 0x0008, 0x1000, 0x0008, 
  0x1000, 0x0008, 0x1000, 0x8008, 
  0x1000, 0x8008, 0x1000, 0x8008, 
  0x1000, 0x8008, 0x1000, 0x8008, 
  0x1003, 0xE008, 0x1001, 0xC008, 
  0x1000, 0x8008, 0x1000, 0x0008, 
  0x1000, 0x0008, 0x1000, 0x0008, 
  0x1000, 0x0008, 0x1000, 0x0008, 
  0x1000, 0x0008, 0x1000, 0x0008, 
  0x1000, 0x0008, 0x1000, 0x0008, 
  0x1FFF, 0xFFF8, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000
};

WORD RSBB1DATA[] =
{ 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x1FFF, 0xFFF8, 
  0x1000, 0x0008, 0x1000, 0x0008, 
  0x1000, 0x0008, 0x1000, 0x0008, 
  0x1000, 0x0008, 0x1000, 0x0008, 
  0x1000, 0x0008, 0x1000, 0x0008, 
  0x1000, 0x0008, 0x1000, 0x4008, 
  0x1000, 0x6008, 0x100F, 0xF008, 
  0x1000, 0x6008, 0x1000, 0x4008, 
  0x1000, 0x0008, 0x1000, 0x0008, 
  0x1000, 0x0008, 0x1000, 0x0008, 
  0x1000, 0x0008, 0x1000, 0x0008, 
  0x1000, 0x0008, 0x1000, 0x0008, 
  0x1000, 0x0008, 0x1000, 0x0008, 
  0x1FFF, 0xFFF8, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000
};

WORD RSBB2DATA[] =
{ 0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x000F, 0xE000, 
  0x0030, 0x1800, 0x00C0, 0x0600, 
  0x0100, 0x0100, 0x0201, 0x0080, 
  0x0403, 0x8040, 0x0407, 0xC040, 
  0x0801, 0x0020, 0x0801, 0x0020, 
  0x1001, 0x0010, 0x1041, 0x0410, 
  0x10C0, 0x0610, 0x11FC, 0x7F10, 
  0x10C0, 0x0610, 0x1041, 0x0410, 
  0x1001, 0x0010, 0x0801, 0x0020, 
  0x0801, 0x0020, 0x0407, 0xC040, 
  0x0403, 0x8040, 0x0201, 0x0080, 
  0x0100, 0x0100, 0x00C0, 0x0600, 
  0x0030, 0x1800, 0x000F, 0xE000, 
  0x0000, 0x0000, 0x0000, 0x0000, 
  0x0000, 0x0000, 0x0000, 0x0000
};

BITBLK rs_bitblk[] =
{ RSBB0DATA,   4,  32,   0,   0, 0x0001,
  RSBB1DATA,   4,  32,   0,   0, 0x0001,
  RSBB2DATA,   4,  32,   0,   0, 0x0001
};

USERBLK rs_userblk[] =
{ 0L, 0x00000003,
  0L, 0x00000003
};

OBJECT rs_object[] =
{ 
  /******** Tree 0 VERLAUF ****************************************************/
        -1, DOWN            , GO              , G_BOX             ,   /* Object 0  */
  FLAGS10, NORMAL, (LONG)0x00FF1100L,
  0x0000, 0x0000, 0x0028, 0x0004,
  V1              ,       -1,       -1, G_STRING          ,   /* Object 1 DOWN */
  NONE, NORMAL, (LONG)"Richtung:",
  0x0001, 0x0000, 0x0009, 0x0001,
  V2              ,       -1,       -1, G_IMAGE           ,   /* Object 2 V1 */
  SELECTABLE|EXIT|RBUTTON|TOUCHEXIT, NORMAL, (LONG)&rs_bitblk[0],
  0x000B, 0x0000, 0x0004, 0x0002,
  V3              ,       -1,       -1, G_IMAGE           ,   /* Object 3 V2 */
  SELECTABLE|EXIT|RBUTTON|TOUCHEXIT, NORMAL, (LONG)&rs_bitblk[1],
  0x0010, 0x0000, 0x0004, 0x0002,
  DOWN1           ,       -1,       -1, G_IMAGE           ,   /* Object 4 V3 */
  SELECTABLE|EXIT|RBUTTON|TOUCHEXIT, NORMAL, (LONG)&rs_bitblk[2],
  0x0015, 0x0000, 0x0004, 0x0002,
  COL1            ,       -1,       -1, G_STRING          ,   /* Object 5 DOWN1 */
  NONE, NORMAL, (LONG)"Verlauf von",
  0x0001, 0x0002, 0x000B, 0x0001,
         7,       -1,       -1, G_USERDEF         ,   /* Object 6 COL1 */
  TOUCHEXIT, NORMAL, (LONG)&rs_userblk[0],
  0x000D, 0x0002, 0x0002, 0x0001,
  COL2            ,       -1,       -1, G_STRING          ,   /* Object 7  */
  NONE, NORMAL, (LONG)"nach",
  0x0010, 0x0002, 0x0004, 0x0001,
  GO              ,       -1,       -1, G_USERDEF         ,   /* Object 8 COL2 */
  TOUCHEXIT, NORMAL, (LONG)&rs_userblk[1],
  0x0015, 0x0002, 0x0002, 0x0001,
         0,       -1,       -1, G_BUTTON          ,   /* Object 9 GO */
  SELECTABLE|DEFAULT|EXIT|LASTOB|FLAGS9|FLAGS10, NORMAL, (LONG)"Ausf\201hren",
  0x001A, 0x0002, 0x000A, 0x0001
};

OBJECT *rs_trindex[] =
{ &rs_object[0]    /* Tree  0 VERLAUF          */
};
