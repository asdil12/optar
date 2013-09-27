#include "opts.h"

int paper_format_a4 = 1;
unsigned paper_dpis = 600;

unsigned XCROSSES, YCROSSES, DATA_WIDTH, DATA_HEIGHT, WIDTH, HEIGHT, NARROWWIDTH, NARROWPIXELS, WIDEWIDTH, WIDEPIXELS, REPPIXELS;
unsigned FEC_SYMS, NETBITS, USEDBITS;
unsigned long TOTALBITS;

void calc_opts(void)
{
	/* XCROSSES A4 65, US Letter 67. */
	/* YCROSSES A4 93, US Letter 87. */
	if(paper_format_a4)
	{
		XCROSSES = 65; /* Number of crosses horizontally */
		YCROSSES = 93; /* Number of crosses vertically */

	}
	else
	{
		XCROSSES = 67; /* Number of crosses horizontally */
		YCROSSES = 87; /* Number of crosses vertically */
	}

	XCROSSES = (XCROSSES * paper_dpis) / 600;
	YCROSSES = (YCROSSES * paper_dpis) / 600;

	DATA_WIDTH = (CPITCH*(XCROSSES-1)+2*CHALF); /* The rectangle occupied by the data and crosses */
	DATA_HEIGHT = (CPITCH*(YCROSSES-1)+2*CHALF);

	WIDTH = (2*BORDER+DATA_WIDTH); /* In pixels, including the border and the label */
	HEIGHT = (2*BORDER+DATA_HEIGHT+TEXT_HEIGHT);

	/* Properties of the narrow horizontal strip, with crosses */
	NARROWWIDTH = (GAPWIDTH*(XCROSSES-1)); /* Useful width */
	NARROWPIXELS = (NARROWHEIGHT*NARROWWIDTH); /* Useful pixels */

	/* Properties of the wide horizontal strip, without crosses */
	WIDEWIDTH = (WIDTH-2*BORDER);
	WIDEPIXELS = (WIDEHEIGHT*WIDEWIDTH);

	/* Amount of raw payload pixels in one narrow-wide strip pair */
	REPPIXELS = (WIDEPIXELS+NARROWPIXELS);

	/* Total bits before hamming including the unused */
	TOTALBITS = ((long)REPPIXELS*(YCROSSES-1)+NARROWPIXELS);

	/* Hamming net channel capacity */
	FEC_SYMS = (TOTALBITS/FEC_LARGEBITS);
	NETBITS = (FEC_SYMS*FEC_SMALLBITS); /* Net payload bits */
	USEDBITS = (FEC_SYMS*FEC_LARGEBITS); /* Used raw bits to store Hamming symbols */
}
