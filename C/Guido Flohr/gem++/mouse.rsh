#define T0OBJ 0
#define FREEBB 0
#define FREEIMG 12
#define FREESTR 6

char *rs_strings[] = {
"",
"",
"",
"",
"",
""};

int  IMAG0[] = {
0xE000, 0xFE00, 0xFE00, 0x7E00, 
0x7E00, 0x7FFE, 0x7FFE, 0x7FE, 
0x7FE, 0x7FE, 0x7FE, 0x7FE, 
0x7FE, 0x7FF, 0x7FF, 0x7};

int  IMAG1[] = {
0x0, 0x4000, 0x2400, 0x1C00, 
0x1C00, 0x3C00, 0x3FC, 0x200, 
0x2FC, 0x280, 0x2BC, 0x2B8, 
0x2B8, 0x2A4, 0x2, 0x0};

int  IMAG2[] = {
0x7CE, 0x7FE, 0x7FE, 0x7FC, 
0x7FC, 0x7FE, 0x7FE, 0x7FE, 
0x3FFE, 0x3FFE, 0x3E00, 0x7E00, 
0x7E00, 0x7000, 0x0, 0x0};

int  IMAG3[] = {
0x0, 0x284, 0x2A8, 0x2B0, 
0x2B8, 0x280, 0x2FC, 0x200, 
0x3FC, 0x1C00, 0xC00, 0x1400, 
0x2000, 0x0, 0x0, 0x0};

int  IMAG4[] = {
0xE3E0, 0xFFE0, 0xFFE0, 0x7FE0, 
0x7FE0, 0x7FE0, 0xFFE0, 0xFFE0, 
0xFFE0, 0xFFFE, 0xFFFE, 0x7E, 
0x7E, 0x7F, 0x7F, 0x7};

int  IMAG5[] = {
0x0, 0x4140, 0x2540, 0x1D40, 
0x1D40, 0x3D40, 0x140, 0x7F40, 
0x40, 0x7FC0, 0x3C, 0x38, 
0x38, 0x24, 0x2, 0x0};

int  IMAG6[] = {
0x0, 0x0, 0xE, 0x7E, 
0x7E, 0x7C, 0xFFFC, 0xFFFC, 
0xFFE0, 0xFFE0, 0xFFE0, 0x3FE0, 
0x3FE0, 0x7FE0, 0x7FE0, 0x73E0};

int  IMAG7[] = {
0x0, 0x0, 0x0, 0x4, 
0x28, 0x30, 0x38, 0x7FC0, 
0x40, 0x7F40, 0x140, 0x1D40, 
0xD40, 0x1540, 0x2140, 0x0};

int  IMAG8[] = {
0x0, 0x3E0, 0x3E0, 0x3E0, 
0x3E0, 0x1FFC, 0x1FFC, 0x7FFF, 
0x7FFF, 0x7FFF, 0x1FFC, 0x1FFC, 
0x3E0, 0x3E0, 0x3E0, 0x3E0};

int  IMAG9[] = {
0x0, 0x0, 0x140, 0x140, 
0x140, 0x140, 0x948, 0xD58, 
0x3F7E, 0xD58, 0x948, 0x140, 
0x140, 0x140, 0x140, 0x0};

int  IMAG10[] = {
0x0, 0x1C0, 0x1C0, 0x7F0, 
0x7F0, 0x7F0, 0x7FFF, 0x7FFF, 
0x7FFF, 0x7FFF, 0x7FFF, 0x7F0, 
0x7F0, 0x7F0, 0x1C0, 0x1C0};

int  IMAG11[] = {
0x0, 0x0, 0x80, 0x80, 
0x3E0, 0x1C0, 0x80, 0x3FFE, 
0x0, 0x3FFE, 0x80, 0x1C0, 
0x3E0, 0x80, 0x80, 0x0};

long rs_frstr[] = {
0};

BITBLK rs_bitblk[] = {
0};

long rs_frimg[] = {
0};

ICONBLK rs_iconblk[] = {
(int *)0L, (int *)1L, (char *)0L, 4608,0,0, 0,0,16,16, 0,0,0,8,
(int *)2L, (int *)3L, (char *)1L, 4608,0,0, 0,0,16,16, 0,0,0,8,
(int *)4L, (int *)5L, (char *)2L, 4608,0,0, 0,0,16,16, 0,0,0,8,
(int *)6L, (int *)7L, (char *)3L, 4608,0,0, 0,0,16,16, 0,0,0,8,
(int *)8L, (int *)9L, (char *)4L, 4608,0,0, 0,0,16,16, 0,0,0,8,
(int *)10L, (int *)11L, (char *)5L, 4608,0,0, 0,0,16,16, 0,0,0,8};

TEDINFO rs_tedinfo[] = {
0};

OBJECT rs_object[] = {
-1, 1, 6, G_BOX, NONE, OUTLINED, 0x21100L, 12,6, 40,9,
2, -1, -1, G_ICON, NONE, NORMAL, 0x0L, 1,0, 4096,4096,
3, -1, -1, G_ICON, NONE, NORMAL, 0x1L, 4,0, 4096,4096,
4, -1, -1, G_ICON, NONE, NORMAL, 0x2L, 7,0, 4096,4096,
5, -1, -1, G_ICON, NONE, NORMAL, 0x3L, 10,0, 4096,4096,
6, -1, -1, G_ICON, NONE, NORMAL, 0x4L, 12,0, 4096,4096,
0, -1, -1, G_ICON, LASTOB, NORMAL, 0x5L, 15,0, 4096,4096};

long rs_trindex[] = {
0L};

struct foobar {
	int 	dummy;
	int 	*image;
	} rs_imdope[] = {
0, &IMAG0[0],
0, &IMAG1[0],
0, &IMAG2[0],
0, &IMAG3[0],
0, &IMAG4[0],
0, &IMAG5[0],
0, &IMAG6[0],
0, &IMAG7[0],
0, &IMAG8[0],
0, &IMAG9[0],
0, &IMAG10[0],
0, &IMAG11[0]};

#define NUM_STRINGS 6
#define NUM_FRSTR 0
#define NUM_IMAGES 12
#define NUM_BB 0
#define NUM_FRIMG 0
#define NUM_IB 6
#define NUM_TI 0
#define NUM_OBS 7
#define NUM_TREE 1

char pname[] = "MOUSE.RSC";