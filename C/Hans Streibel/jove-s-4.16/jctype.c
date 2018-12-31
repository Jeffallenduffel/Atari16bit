/************************************************************************
 * This program is Copyright (C) 1986-1996 by Jonathan Payne.  JOVE is  *
 * provided to you without charge, and with no warranty.  You may give  *
 * away copies of JOVE, including sources, provided that this notice is *
 * included in all the files.                                           *
 ************************************************************************/

#include "jove.h"
#include "jctype.h"

#define cU	(C_UPPER | C_WORD | C_PRINT)	/* Upper case  => Word => Printable */
#define cL	(C_LOWER | C_WORD | C_PRINT)	/* Lower case => Word => Printable */
#define cN	(C_DIGIT | C_WORD | C_PRINT)	/* Numeric => Word => Printable */
#define cP	(C_PUNCT | C_PRINT)	/* Punctuation => Printable */
#define cV	C_PRINT	/* printable (Visible) */
#define cW	(C_WORD | C_PRINT)	/* Word => Printable */
#define cO	(C_BRA | C_PUNCT | C_PRINT)	/* Open parenthesis => Punctuation => Printable */
#define cC	(C_KET | C_PUNCT | C_PRINT)	/* Close parenthesis => Punctuation => Printable */

const unsigned char CharTable[NCHARS] = {
	0,	0,	0,	0,	0,	0,	0,	0,	/* 000 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 010 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 020 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 030 */

	cP,	cP,	cP,	cP,	cP,	cP,	cP,	cP,	/* 040 */
	cO,	cC,	cP,	cP,	cP,	cP,	cP,	cP,	/* 050 */
	cN,	cN,	cN,	cN,	cN,	cN,	cN,	cN,	/* 060 */
	cN,	cN,	cP,	cP,	cP,	cP,	cP,	cP,	/* 070 */

	cP,	cU,	cU,	cU,	cU,	cU,	cU,	cU,	/* 100 */
	cU,	cU,	cU,	cU,	cU,	cU,	cU,	cU,	/* 110 */
	cU,	cU,	cU,	cU,	cU,	cU,	cU,	cU,	/* 120 */
	cU,	cU,	cU,	cO,	cP,	cC,	cP,	cP,	/* 130 */

	cP,	cL,	cL,	cL,	cL,	cL,	cL,	cL,	/* 140 */
	cL,	cL,	cL,	cL,	cL,	cL,	cL,	cL,	/* 150 */
	cL,	cL,	cL,	cL,	cL,	cL,	cL,	cL,	/* 160 */
	cL,	cL,	cL,	cO,	cP,	cC,	cP,	0,	/* 170 */
#if NCHARS != 128
# ifdef ISO_8859_1
	0,	0,	0,	0,	0,	0,	0,	0,	/* 200 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 210 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 220 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 230 */

	cP,	cP,	cP,	cP,	cP,	cP,	cP,	cP,	/* 240 */
	cP,	cP,	cP,	cP,	cP,	cP,	cP,	cP,	/* 250 */
	cP,	cP,	cP,	cP,	cP,	cP,	cP,	cP,	/* 260 */
	cP,	cP,	cP,	cP,	cP,	cP,	cP,	cP,	/* 270 */

	cU,	cU,	cU,	cU,	cU,	cU,	cU,	cU,	/* 300 */
	cU,	cU,	cU,	cU,	cU,	cU,	cU,	cU,	/* 310 */
	cU,	cU,	cU,	cU,	cU,	cU,	cU,	cP,	/* 320 */
	cU,	cU,	cU,	cU,	cU,	cU,	cU,	cL,	/* 330 */

	cL,	cL,	cL,	cL,	cL,	cL,	cL,	cL,	/* 340 */
	cL,	cL,	cL,	cL,	cL,	cL,	cL,	cL,	/* 350 */
	cL,	cL,	cL,	cL,	cL,	cL,	cL,	cP,	/* 360 */
	cL,	cL,	cL,	cL,	cL,	cL,	cL,	cL,	/* 370 */
# else /* !ISO_8859_1 */
#  ifdef CODEPAGE437
	cU,	cL,	cL,	cL,	cL,	cL,	cL,	cL,	/* 200 */
	cL,	cL,	cL,	cL,	cL,	cL,	cU,	cU,	/* 210 */
	cU,	cL,	cU,	cL,	cL,	cL,	cL,	cL,	/* 220 */
	cL,	cU,	cU,	cP,	cP,	cP,	cP,	cP,	/* 230 */

	cL,	cL,	cL,	cL,	cL,	cU,	cP,	cP,	/* 240 */
	cP,	cP,	cP,	cP,	cP,	cP,	cP,	cP,	/* 250 */
	cP,	cP,	cP,	cP,	cP,	cP,	cP,	cP,	/* 260 */
	cP,	cP,	cP,	cP,	cP,	cP,	cP,	cP,	/* 270 */

	cP,	cP,	cP,	cP,	cP,	cP,	cP,	cP,	/* 300 */
	cP,	cP,	cP,	cP,	cP,	cP,	cP,	cP,	/* 310 */
	cP,	cP,	cP,	cP,	cP,	cP,	cP,	cP,	/* 320 */
	cP,	cP,	cP,	cP,	cP,	cP,	cP,	cP,	/* 330 */

	cP,	cP,	cP,	cP,	cP,	cP,	cP,	cP,	/* 340 */
	cP,	cP,	cP,	cP,	cP,	cP,	cP,	cP,	/* 350 */
	cP,	cP,	cP,	cP,	cP,	cP,	cP,	cP,	/* 360 */
	cP,	cP,	cP,	cP,	cP,	cP,	cP,	cP,	/* 370 */
#  else /* !CODEPAGE437 */
#   ifdef MAC	/* See Inside Macintosh Vol One p. 247 */
	cU,	cU,	cU,	cU,	cU,	cU,	cU,	cL,	/* 200 */
	cL,	cL,	cL,	cL,	cL,	cL,	cL,	cL,	/* 210 */
	cL,	cL,	cL,	cL,	cL,	cL,	cL,	cL,	/* 220 */
	cL,	cL,	cL,	cL,	cL,	cL,	cL,	cL,	/* 230 */

	cP,	cP,	cP,	cP,	cP,	cP,	cP,	cP,	/* 240 */
	cP,	cP,	cP,	cP,	cP,	cP,	cU,	cU,	/* 250 */
	cP,	cP,	cP,	cP,	cP,	cU,	cL,	cU,	/* 260 */
	cU,	cL,	cP,	cP,	cP,	cU,	cL,	cL,	/* 270 */

	cP,	cP,	cP,	cP,	cP,	cP,	cU,	cP,	/* 300 */
	cP,	cP,	cP,	cU,	cU,	cU,	cU,	cU,	/* 310 */
	cP,	cP,	cP,	cP,	cP,	cP,	cP,	cP,	/* 320 */
	cU,	0,	0,	0,	0,	0,	0,	0,	/* 330 */

	0,	0,	0,	0,	0,	0,	0,	0,	/* 340 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 350 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 360 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 370 */
#   else /* !MAC */
	/* control, by default */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 200 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 210 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 220 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 230 */

	0,	0,	0,	0,	0,	0,	0,	0,	/* 240 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 250 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 260 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 270 */

	0,	0,	0,	0,	0,	0,	0,	0,	/* 300 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 310 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 320 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 330 */

	0,	0,	0,	0,	0,	0,	0,	0,	/* 340 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 350 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 360 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 370 */
#   endif /* !MAC */
#  endif /* !CODEPAGE437 */
# endif /* !ISO_8859_1 */
#endif /* NCHARS != 128 */
};

#undef cU
#undef cL
#undef cN
#undef cP
#undef cV
#undef cW
#undef cO
#undef cC

/* Which characters are legal in an identifier (word)?
 * This depends on the major mode.  Anything considered
 * part of an identifier in Fundamental mode is considered to
 * be a part of an identifier in any other mode (this is
 * an assumption of the USE_LCTYPE code).  For other modes,
 * more characters are considered to be part of identifiers:
 * - text mode adds '
 * - C mode adds _
 * - lisp mode adds !$%& *+-/ :<=>? @ ^_{|}~
 * Note that none of these modes currently adds anything in the
 * upper half of an 8-bit character set.
 */

#define wF	(1 << FUNDAMENTAL)
#define wT	(1 << TEXTMODE)
#define wC	(1 << CMODE)
#ifdef LISP
# define wL	(1 << LISPMODE)
#else
# define wL	0
#endif
#define w	(wF|wT|wC|wL)

private const unsigned char IdChartable[NCHARS] = {
	0,	0,	0,	0,	0,	0,	0,	0,	/* 000 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 010 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 020 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 030 */

	0,	wL,	0,	0,	wL,	wL,	wL,	wT,	/* 040 */
	0,	0,	wL,	wL,	0,	wL,	0,	wL,	/* 050 */
	w,	w,	w,	w,	w,	w,	w,	w,	/* 060 */
	w,	w,	wL,	0,	wL,	wL,	wL,	wL,	/* 070 */

	wL,	w,	w,	w,	w,	w,	w,	w,	/* 100 */
	w,	w,	w,	w,	w,	w,	w,	w,	/* 110 */
	w,	w,	w,	w,	w,	w,	w,	w,	/* 120 */
	w,	w,	w,	0,	0,	0,	wL,	wC|wL,	/* 130 */

	0,	w,	w,	w,	w,	w,	w,	w,	/* 140 */
	w,	w,	w,	w,	w,	w,	w,	w,	/* 150 */
	w,	w,	w,	w,	w,	w,	w,	w,	/* 160 */
	w,	w,	w,	wL,	wL,	wL,	wL,	wL,	/* 170 */
#if NCHARS != 128
# ifdef ISO_8859_1
	0,	0,	0,	0,	0,	0,	0,	0,	/* 200 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 210 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 220 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 230 */

	0,	0,	0,	0,	0,	0,	0,	0,	/* 240 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 250 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 260 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 270 */

	w,	w,	w,	w,	w,	w,	w,	w,	/* 300 */
	w,	w,	w,	w,	w,	w,	w,	w,	/* 310 */
	w,	w,	w,	w,	w,	w,	w,	0,	/* 320 */
	w,	w,	w,	w,	w,	w,	w,	w,	/* 330 */

	w,	w,	w,	w,	w,	w,	w,	w,	/* 340 */
	w,	w,	w,	w,	w,	w,	w,	w,	/* 350 */
	w,	w,	w,	w,	w,	w,	w,	0,	/* 360 */
	w,	w,	w,	w,	w,	w,	w,	w,	/* 370 */
# else /* !ISO_8859_1 */
#  ifdef CODEPAGE437
	w,	w,	w,	w,	w,	w,	w,	w,	/* 200 */
	w,	w,	w,	w,	w,	w,	w,	w,	/* 210 */
	w,	w,	w,	w,	w,	w,	w,	w,	/* 220 */
	w,	w,	w,	0,	0,	0,	0,	0,	/* 230 */

	w,	w,	w,	w,	w,	w,	0,	0,	/* 240 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 250 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 260 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 270 */

	0,	0,	0,	0,	0,	0,	0,	0,	/* 300 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 310 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 320 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 330 */

	0,	0,	0,	0,	0,	0,	0,	0,	/* 340 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 350 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 360 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 370 */
#  else /* !CODEPAGE437 */
#   ifdef MAC	/* See Inside Macintosh Vol One p. 247 */
	w,	w,	w,	w,	w,	w,	w,	w,	/* 200 */
	w,	w,	w,	w,	w,	w,	w,	w,	/* 210 */
	w,	w,	w,	w,	w,	w,	w,	w,	/* 220 */
	w,	w,	w,	w,	w,	w,	w,	w,	/* 230 */

	0,	0,	0,	0,	0,	0,	0,	0,	/* 240 */
	0,	0,	0,	0,	0,	0,	w,	w,	/* 250 */
	0,	0,	0,	0,	0,	w,	w,	w,	/* 260 */
	w,	w,	0,	0,	0,	w,	w,	w,	/* 270 */

	0,	0,	0,	0,	0,	0,	w,	0,	/* 300 */
	0,	0,	0,	w,	w,	w,	w,	w,	/* 310 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 320 */
	w,	0,	0,	0,	0,	0,	0,	0,	/* 330 */

	0,	0,	0,	0,	0,	0,	0,	0,	/* 340 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 350 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 360 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 370 */
#   else /* !MAC */
	/* control, by default */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 200 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 210 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 220 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 230 */

	0,	0,	0,	0,	0,	0,	0,	0,	/* 240 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 250 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 260 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 270 */

	0,	0,	0,	0,	0,	0,	0,	0,	/* 300 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 310 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 320 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 330 */

	0,	0,	0,	0,	0,	0,	0,	0,	/* 340 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 350 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 360 */
	0,	0,	0,	0,	0,	0,	0,	0,	/* 370 */
#   endif /* !MAC */
#  endif /* !CODEPAGE437 */
# endif /* !ISO_8859_1 */
#endif /* NCHARS != 128 */
};

#undef wF
#undef wT
#undef wC
#undef wL
#undef w

bool
jisident(c)
char	c;
{
#ifdef USE_CTYPE
	return (IdChartable[ZXC(c)] & (1 << curbuf->b_major)) != 0 || jisword(c);
#else
	return (IdChartable[ZXC(c)] & (1 << curbuf->b_major)) != 0;
#endif
}

#ifdef USE_CTYPE

# ifndef NO_SETLOCALE

#  include <locale.h>

char	LcCtype[32] = "";	/* VAR: lc-ctype, for use in setlocale */

/* adjust the locale to reflect possible change to LcCtype */

void
locale_adjust()
{
	char	*res = setlocale(LC_CTYPE, LcCtype);

	if (res != NULL) {
		/* success: if it fits, record result */
		if (strlen(res) < sizeof(LcCtype))
			strcpy(LcCtype, res);
	} else if (LcCtype[0] != '\0') {
		/* Failure, but not for "".  Complain, after recovering.
		 * Note: We don't try to print a message if "" fails because it
		 * might be the initializing call, too early for "complain",
		 * or it might be the recursive call.
		 */
		char	temp[sizeof(LcCtype)];

		strcpy(temp, LcCtype);
		res = setlocale(LC_CTYPE, (char *)NULL);
		if (res != NULL && strlen(res) < sizeof(LcCtype)) {
			strcpy(LcCtype, res);
		} else {
			LcCtype[0] = '\0';	/* default */
			locale_adjust();	/* note: this will recurse only one level */
		}
		complain("Unrecognized lc-ctype: %s", temp);
	}
}

# endif /* !NO_SETLOCALE */

#else /* !USE_CTYPE */

/* Map lower case characters to upper case and the rest to themselves. */

const char	RaiseTable[NCHARS] = {
	'\000',	'\001',	'\002',	'\003',	'\004',	'\005',	'\006',	'\007',
	'\010',	'\011',	'\012',	'\013',	'\014',	'\015',	'\016',	'\017',
	'\020',	'\021',	'\022',	'\023',	'\024',	'\025',	'\026',	'\027',
	'\030',	'\031',	'\032',	'\033',	'\034',	'\035',	'\036',	'\037',
	'\040',	'!',	'"',	'#',	'$',	'%',	'&',	'\'',
	'(',	')',	'*',	'+',	',',	'-',	'.',	'/',
	'0',	'1',	'2',	'3',	'4',	'5',	'6',	'7',
	'8',	'9',	':',	';',	'<',	'=',	'>',	'?',
	'@',	'A',	'B',	'C',	'D',	'E',	'F',	'G',
	'H',	'I',	'J',	'K',	'L',	'M',	'N',	'O',
	'P',	'Q',	'R',	'S',	'T',	'U',	'V',	'W',
	'X',	'Y',	'Z',	'[',	'\\',	']',	'^',	'_',
	'`',	'A',	'B',	'C',	'D',	'E',	'F',	'G',
	'H',	'I',	'J',	'K',	'L',	'M',	'N',	'O',
	'P',	'Q',	'R',	'S',	'T',	'U',	'V',	'W',
	'X',	'Y',	'Z',	'{',	'|',	'}',	'~',	'\177',
# if NCHARS != 128
#  ifdef ISO_8859_1
	'\200',	'\201',	'\202',	'\203',	'\204',	'\205',	'\206',	'\207',
	'\210',	'\211',	'\212',	'\213',	'\214',	'\215',	'\216',	'\217',
	'\220',	'\221',	'\222',	'\223',	'\224',	'\225',	'\226',	'\227',
	'\230',	'\231',	'\232',	'\233',	'\234',	'\235',	'\236',	'\237',
	'\240',	'\241',	'\242',	'\243',	'\244',	'\245',	'\246',	'\247',
	'\250',	'\251',	'\252',	'\253',	'\254',	'\255',	'\256',	'\257',
	'\260',	'\261',	'\262',	'\263',	'\264',	'\265',	'\266',	'\267',
	'\270',	'\271',	'\272',	'\273',	'\274',	'\275',	'\276',	'\277',
	'\300',	'\301',	'\302',	'\303',	'\304',	'\305',	'\306',	'\307',
	'\310',	'\311',	'\312',	'\313',	'\314',	'\315',	'\316',	'\317',
	'\320',	'\321',	'\322',	'\323',	'\324',	'\325',	'\326',	'\327',
	'\330',	'\331',	'\332',	'\333',	'\334',	'\335',	'\336',	'\337',
	'\300',	'\301',	'\302',	'\303',	'\304',	'\305',	'\306',	'\307',
	'\310',	'\311',	'\312',	'\313',	'\314',	'\315',	'\316',	'\317',
	'\320',	'\321',	'\322',	'\323',	'\324',	'\325',	'\326',	'\367',
	'\330',	'\331',	'\332',	'\333',	'\334',	'\335',	'\336',	'\377',
#  else /* !ISO_8859_1 */
#   ifdef CODEPAGE437
	/* Only codes changed are lowercase Umlauted letters (indented):
	 *	Ae '\216'; ae '\204'
	 *	Oe '\231'; oe '\224'
	 *	Ue '\232'; ue '\201'
	 */
	'\200',	 '\232',	'\202',	'\203',	 '\216',	'\205',	'\206',	'\207',
	'\210',	'\211',	'\212',	'\213',	'\214',	'\215',	'\216',	'\217',
	'\220',	'\221',	'\222',	'\223',	 '\231',	'\225',	'\226',	'\227',
	'\230',	'\231',	'\232',	'\233',	'\234',	'\235',	'\236',	'\237',
	'\240',	'\241',	'\242',	'\243',	'\244',	'\245',	'\246',	'\247',
	'\250',	'\251',	'\252',	'\253',	'\254',	'\255',	'\256',	'\257',
	'\260',	'\261',	'\262',	'\263',	'\264',	'\265',	'\266',	'\267',
	'\270',	'\271',	'\272',	'\273',	'\274',	'\275',	'\276',	'\277',
	'\300',	'\301',	'\302',	'\303',	'\304',	'\305',	'\306',	'\307',
	'\310',	'\311',	'\312',	'\313',	'\314',	'\315',	'\316',	'\317',
	'\320',	'\321',	'\322',	'\323',	'\324',	'\325',	'\326',	'\327',
	'\330',	'\331',	'\332',	'\333',	'\334',	'\335',	'\336',	'\337',
	'\340',	'\341',	'\342',	'\343',	'\344',	'\345',	'\346',	'\347',
	'\350',	'\351',	'\352',	'\353',	'\354',	'\355',	'\356',	'\357',
	'\360',	'\361',	'\362',	'\363',	'\364',	'\365',	'\366',	'\367',
	'\370',	'\371',	'\372',	'\373',	'\374',	'\375',	'\376',	'\377',
#   else /* !CODEPAGE437 */
#    ifdef MAC
	/* '\230' -> '\313'
	 * '\212' -> '\200'
	 * '\213' -> '\314'
	 * '\214' -> '\201'
	 * '\215' -> '\202'
	 * '\216' -> '\203'
	 * '\226' -> '\204'
	 * '\232' -> '\205'
	 * '\233' -> '\315'
	 * '\237' -> '\206'
	 * '\271' -> '\270'
	 * '\317' -> '\316'
	 */
	'\200',	'\201',	'\202',	'\203',	'\204',	'\205',	'\206',	'\207',
	 '\313',	'\211',	 '\200',	 '\314',	 '\201',	 '\202',	 '\203',	'\217',
	'\220',	'\221',	'\222',	'\223',	'\224',	'\225',	 '\204',	'\227',
	'\230',	'\231',	 '\205',	 '\315',	'\234',	'\235',	'\236',	 '\206',
	'\240',	'\241',	'\242',	'\243',	'\244',	'\245',	'\246',	'\247',
	'\250',	'\251',	'\252',	'\253',	'\254',	'\255',	'\256',	'\257',
	'\260',	'\261',	'\262',	'\263',	'\264',	'\265',	'\306',	'\267',
	'\270',	 '\270',	'\272',	'\273',	'\274',	'\275',	'\256',	'\257',
	'\300',	'\301',	'\302',	'\303',	'\304',	'\305',	'\306',	'\307',
	'\310',	'\311',	'\312',	'\313',	'\314',	'\315',	'\316',	 '\316',
	'\320',	'\321',	'\322',	'\323',	'\324',	'\325',	'\326',	'\327',
	'\330',	'\331',	'\332',	'\333',	'\334',	'\335',	'\336',	'\337',
	'\340',	'\341',	'\342',	'\343',	'\344',	'\345',	'\346',	'\347',
	'\350',	'\351',	'\352',	'\353',	'\354',	'\355',	'\356',	'\357',
	'\360',	'\361',	'\362',	'\363',	'\364',	'\365',	'\366',	'\367',
	'\370',	'\371',	'\372',	'\373',	'\374',	'\375',	'\376',	'\377',
#    else /* !MAC */
	/* identity, by default */
	'\200',	'\201',	'\202',	'\203',	'\204',	'\205',	'\206',	'\207',
	'\210',	'\211',	'\212',	'\213',	'\214',	'\215',	'\216',	'\217',
	'\220',	'\221',	'\222',	'\223',	'\224',	'\225',	'\226',	'\227',
	'\230',	'\231',	'\232',	'\233',	'\234',	'\235',	'\236',	'\237',
	'\240',	'\241',	'\242',	'\243',	'\244',	'\245',	'\246',	'\247',
	'\250',	'\251',	'\252',	'\253',	'\254',	'\255',	'\256',	'\257',
	'\260',	'\261',	'\262',	'\263',	'\264',	'\265',	'\266',	'\267',
	'\270',	'\271',	'\272',	'\273',	'\274',	'\275',	'\276',	'\277',
	'\300',	'\301',	'\302',	'\303',	'\304',	'\305',	'\306',	'\307',
	'\310',	'\311',	'\312',	'\313',	'\314',	'\315',	'\316',	'\317',
	'\320',	'\321',	'\322',	'\323',	'\324',	'\325',	'\326',	'\327',
	'\330',	'\331',	'\332',	'\333',	'\334',	'\335',	'\336',	'\337',
	'\340',	'\341',	'\342',	'\343',	'\344',	'\345',	'\346',	'\347',
	'\350',	'\351',	'\352',	'\353',	'\354',	'\355',	'\356',	'\357',
	'\360',	'\361',	'\362',	'\363',	'\364',	'\365',	'\366',	'\367',
	'\370',	'\371',	'\372',	'\373',	'\374',	'\375',	'\376',	'\377',
#    endif /* !MAC */
#   endif /* !CODEPAGE437 */
#  endif /* !ISO_8859_1 */
# endif /* NCHARS != 128*/
};

/* Map upper case characters to lower case and the rest to themselves. */

const char	LowerTable[NCHARS] = {
	'\000',	'\001',	'\002',	'\003',	'\004',	'\005',	'\006',	'\007',
	'\010',	'\011',	'\012',	'\013',	'\014',	'\015',	'\016',	'\017',
	'\020',	'\021',	'\022',	'\023',	'\024',	'\025',	'\026',	'\027',
	'\030',	'\031',	'\032',	'\033',	'\034',	'\035',	'\036',	'\037',
	'\040',	'!',	'"',	'#',	'$',	'%',	'&',	'\'',
	'(',	')',	'*',	'+',	',',	'-',	'.',	'/',
	'0',	'1',	'2',	'3',	'4',	'5',	'6',	'7',
	'8',	'9',	':',	';',	'<',	'=',	'>',	'?',
	'@',	'a',	'b',	'c',	'd',	'e',	'f',	'g',
	'h',	'i',	'j',	'k',	'l',	'm',	'n',	'o',
	'p',	'q',	'r',	's',	't',	'u',	'v',	'w',
	'x',	'y',	'z',	'[',	'\\',	']',	'^',	'_',
	'`',	'a',	'b',	'c',	'd',	'e',	'f',	'g',
	'h',	'i',	'j',	'k',	'l',	'm',	'n',	'o',
	'p',	'q',	'r',	's',	't',	'u',	'v',	'w',
	'x',	'y',	'z',	'{',	'|',	'}',	'~',	'\177',
# if NCHARS != 128
#  ifdef ISO_8859_1
	'\200',	'\201',	'\202',	'\203',	'\204',	'\205',	'\206',	'\207',
	'\210',	'\211',	'\212',	'\213',	'\214',	'\215',	'\216',	'\217',
	'\220',	'\221',	'\222',	'\223',	'\224',	'\225',	'\226',	'\227',
	'\230',	'\231',	'\232',	'\233',	'\234',	'\235',	'\236',	'\237',
	'\240',	'\241',	'\242',	'\243',	'\244',	'\245',	'\246',	'\247',
	'\250',	'\251',	'\252',	'\253',	'\254',	'\255',	'\256',	'\257',
	'\260',	'\261',	'\262',	'\263',	'\264',	'\265',	'\266',	'\267',
	'\270',	'\271',	'\272',	'\273',	'\274',	'\275',	'\276',	'\277',
	'\340',	'\341',	'\342',	'\343',	'\344',	'\345',	'\346',	'\347',
	'\350',	'\351',	'\352',	'\353',	'\354',	'\355',	'\356',	'\357',
	'\360',	'\361',	'\362',	'\363',	'\364',	'\365',	'\366',	'\327',
	'\370',	'\371',	'\372',	'\373',	'\374',	'\375',	'\376',	'\337',
	'\340',	'\341',	'\342',	'\343',	'\344',	'\345',	'\346',	'\347',
	'\350',	'\351',	'\352',	'\353',	'\354',	'\355',	'\356',	'\357',
	'\360',	'\361',	'\362',	'\363',	'\364',	'\365',	'\366',	'\367',
	'\370',	'\371',	'\372',	'\373',	'\374',	'\375',	'\376',	'\377',
#  else /* !ISO_8859_1 */
#   ifdef CODEPAGE437
	/* Only codes changed are uppercase Umlauted letters (indented):
	 *	Ae '\216'; ae '\204'
	 *	Oe '\231'; oe '\224'
	 *	Ue '\232'; ue '\201'
	 */
	'\200',	'\201',	'\202',	'\203',	'\204',	'\205',	'\206',	'\207',
	'\210',	'\211',	'\212',	'\213',	'\214',	'\215',	 '\204',	'\217',
	'\220',	'\221',	'\222',	'\223',	'\224',	'\225',	'\226',	'\227',
	'\230',	 '\224',	 '\201',	'\233',	'\234',	'\235',	'\236',	'\237',
	'\240',	'\241',	'\242',	'\243',	'\244',	'\245',	'\246',	'\247',
	'\250',	'\251',	'\252',	'\253',	'\254',	'\255',	'\256',	'\257',
	'\260',	'\261',	'\262',	'\263',	'\264',	'\265',	'\266',	'\267',
	'\270',	'\271',	'\272',	'\273',	'\274',	'\275',	'\276',	'\277',
	'\300',	'\301',	'\302',	'\303',	'\304',	'\305',	'\306',	'\307',
	'\310',	'\311',	'\312',	'\313',	'\314',	'\315',	'\316',	'\317',
	'\320',	'\321',	'\322',	'\323',	'\324',	'\325',	'\326',	'\327',
	'\330',	'\331',	'\332',	'\333',	'\334',	'\335',	'\336',	'\337',
	'\340',	'\341',	'\342',	'\343',	'\344',	'\345',	'\346',	'\347',
	'\350',	'\351',	'\352',	'\353',	'\354',	'\355',	'\356',	'\357',
	'\360',	'\361',	'\362',	'\363',	'\364',	'\365',	'\366',	'\367',
	'\370',	'\371',	'\372',	'\373',	'\374',	'\375',	'\376',	'\377',
#   else /* !CODEPAGE437 */
#    ifdef MAC
	/* '\200' -> '\212'
	 * '\201' -> '\214'
	 * '\202' -> '\215'
	 * '\203' -> '\216'
	 * '\204' -> '\226'
	 * '\205' -> '\232'
	 * '\206' -> '\237'
	 * '\270' -> '\271'
	 * '\313' -> '\230'
	 * '\314' -> '\213'
	 * '\315' -> '\233'
	 * '\316' -> '\317'
	 */
	 '\212',	 '\214',	 '\215',	 '\216',	 '\226',	 '\232',	 '\237',	'\207',
	'\210',	'\211',	'\212',	'\213',	'\214',	'\215',	'\216',	'\217',
	'\220',	'\221',	'\222',	'\223',	'\224',	'\225',	'\226',	'\227',
	'\230',	'\231',	'\232',	'\233',	'\234',	'\235',	'\236',	'\237',
	'\240',	'\241',	'\242',	'\243',	'\244',	'\245',	'\246',	'\247',
	'\250',	'\251',	'\252',	'\253',	'\254',	'\255',	'\256',	'\257',
	'\260',	'\261',	'\262',	'\263',	'\264',	'\265',	'\266',	'\267',
	 '\271',	'\271',	'\272',	'\273',	'\274',	'\275',	'\276',	'\277',
	'\300',	'\301',	'\302',	'\303',	'\304',	'\305',	'\306',	'\307',
	'\310',	'\311',	'\312',	 '\230',	 '\213',	 '\233',	 '\317',	'\317',
	'\320',	'\321',	'\322',	'\323',	'\324',	'\325',	'\326',	'\327',
	'\330',	'\331',	'\332',	'\333',	'\334',	'\335',	'\336',	'\337',
	'\340',	'\341',	'\342',	'\343',	'\344',	'\345',	'\346',	'\347',
	'\350',	'\351',	'\352',	'\353',	'\354',	'\355',	'\356',	'\357',
	'\360',	'\361',	'\362',	'\363',	'\364',	'\365',	'\366',	'\367',
	'\370',	'\371',	'\372',	'\373',	'\374',	'\375',	'\376',	'\377',
#    else /* !MAC */
	/* identity, by default */
	'\200',	'\201',	'\202',	'\203',	'\204',	'\205',	'\206',	'\207',
	'\210',	'\211',	'\212',	'\213',	'\214',	'\215',	'\216',	'\217',
	'\220',	'\221',	'\222',	'\223',	'\224',	'\225',	'\226',	'\227',
	'\230',	'\231',	'\232',	'\233',	'\234',	'\235',	'\236',	'\237',
	'\240',	'\241',	'\242',	'\243',	'\244',	'\245',	'\246',	'\247',
	'\250',	'\251',	'\252',	'\253',	'\254',	'\255',	'\256',	'\257',
	'\260',	'\261',	'\262',	'\263',	'\264',	'\265',	'\266',	'\267',
	'\270',	'\271',	'\272',	'\273',	'\274',	'\275',	'\276',	'\277',
	'\300',	'\301',	'\302',	'\303',	'\304',	'\305',	'\306',	'\307',
	'\310',	'\311',	'\312',	'\313',	'\314',	'\315',	'\316',	'\317',
	'\320',	'\321',	'\322',	'\323',	'\324',	'\325',	'\326',	'\327',
	'\330',	'\331',	'\332',	'\333',	'\334',	'\335',	'\336',	'\337',
	'\340',	'\341',	'\342',	'\343',	'\344',	'\345',	'\346',	'\347',
	'\350',	'\351',	'\352',	'\353',	'\354',	'\355',	'\356',	'\357',
	'\360',	'\361',	'\362',	'\363',	'\364',	'\365',	'\366',	'\367',
	'\370',	'\371',	'\372',	'\373',	'\374',	'\375',	'\376',	'\377',
#    endif /* !MAC */
#   endif /* !CODEPAGE437 */
#  endif /* !ISO_8859_1 */
# endif /* NCHARS != 128*/
};

#endif /* !USE_CTYPE */
