/* (c) GPL 2007 Karel 'Clock' Kulhavy, Twibright Labs */

#define MIN(x,y) ((x)<(y)?(x):(y))
#define MAX(x,y) ((x)>(y)?(x):(y))

#define BORDER 2 /* In pixels. Thickness of the border */
#define CHALF 3 /* Size of the cross half. Size of the cross is CHALF*2 x CHALF*2. */
#define CPITCH 24 /* Distance between cross centers */

#define TEXT_WIDTH 13 /* Width of a single letter */
#define TEXT_HEIGHT 24

/* Definitions for seq2xy */

/* Properties of the narrow horizontal strip, with crosses */
#define NARROWHEIGHT (2*CHALF)
#define GAPWIDTH (CPITCH-2*CHALF)

/* Properties of the wide horizontal strip, without crosses */
#define WIDEHEIGHT GAPWIDTH

/* Amount of raw payload pixels in one narrow-wide strip pair */
#define REPHEIGHT (NARROWHEIGHT+WIDEHEIGHT)

/* Hamming codes with parity */
#define FEC_ORDER 1 /* Can be 2 to 5 inclusive. 
			   5 is 26/32,
			   4 is 11/16,
			   3 is 4/8,
			   2 is 4/1
			   1 is golay codes */
#if FEC_ORDER==1
/* Golay */
#define FEC_LARGEBITS 24
#define FEC_SMALLBITS 12
#else
/* Hamming */
#define FEC_LARGEBITS (1<<FEC_ORDER)
#define FEC_SMALLBITS (FEC_LARGEBITS-1-FEC_ORDER)
#endif

/* Functions from common.c */
extern unsigned long parity(unsigned long in);
extern int is_cross(unsigned x, unsigned y);
extern void seq2xy(int *x, int *y, unsigned seq);

/* Counts number of '1' bits */
unsigned ones(unsigned long in);

/* Golay codes */
unsigned long golay(unsigned long in);
extern unsigned long golay_codes[4096];
