#include <stddef.h>
#include <aes.h>
#include <moddef.h>

void	cdecl mod_init(void);	/* Initialisierung des Moduls */
void	cdecl mod_quit(void);	/* Deinitialisierung */
int		cdecl do_function1(GRECT *area, LAYER *l, MASK *mm);
int		cdecl do_function2(uchar *c, uchar *m, uchar *y, int w, int h, GRECT *area, int prv);
int		invert(uchar *pp, int ww, GRECT *area);


int				global[80];

static MODULE_FN mod_fn=
{
	mod_init,
	mod_quit,
	do_function1,
	do_function2
};

static MODULEBLK mblock=
{
	"GRAPEMODULE",
	'0101',
	/* name */
	"1234567890123456789012345678901",

	/* CICONBLK */
	NULL,NULL,NULL,0,0,0,0,0,0,0,0,0,0,0,NULL,
	/* mask_data */
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,
	/* data_data */
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,
	/* name */
	0,0,
	/* CICON */
	0,NULL,NULL,NULL,NULL,NULL,
	/* col_data */
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,
	/* bw_data */
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,
	
	0,&mod_fn,
	
	/* Objekt-Tree+Service */
	NULL,
	((void cdecl(*)(int ob))0),
	
	/* global */
	NULL,
	/* Grape-Functions */
	NULL,
	/* id */
	0
};

void main(void)
{
	appl_init();
	if(mblock.magic[0])
		form_alert(1,"[3][Ich bin ein Grape-Modul!][Abbruch]");
	appl_exit();
}

void cdecl mod_init(void)
{
	int a;
	
	for(a=0; a < 80; ++a)
		_GemParBlk.global[a]=mblock.global[a];
		
}

void cdecl mod_quit(void)
{
}

int		cdecl do_function1(GRECT *area, LAYER *l, MASK *mm)
{
	int w, h;
	uchar *c, *m, *y;
	
	w=l->word_width;
	h=l->height;
	
	if(mm)
	{
		c=mm->mask;
		m=y=NULL;
	}
	else
	{
		c=l->blue;
		m=l->red;
		y=l->yellow;
	}
	
	if(c||m||y)
	{
		if(!(_G_ undo_buf(area, l, mm, 1)))
				return(0);/* Undo schlug fehl */
		return(do_function2(c,m,y,w,h,area,-1));
	}
	else
		return(0);
}

int		cdecl do_function2(uchar *c, uchar *m, uchar *y, int w, int h, GRECT *area, int prv)
{
	register uchar *cc=c, *mm=m, *yy=y;
	register int	ww=area->g_w;
	register long ldif=(long)w-(long)area->g_w;
	register unsigned int mr, mg, mb, mc;
	long start=(long)w*(long)area->g_y+(long)area->g_x;
	register int xc,yc;
	
	if((mm==NULL) && (yy==NULL))
	{/* 8Bit Grau */
		cc+=start;
		for(yc=area->g_h; yc > 0; --yc)
		{
			for(xc=ww; xc > 0; --xc)
			{
				mc=255-*cc;
				mr=mc*(int)(*cc);	mr/=255;*cc++=(uchar)mr;
			}
			cc+=ldif;
		}
		return(1);
	}
	
	cc+=start;
	mm+=start;
	yy+=start;
	
	for(yc=area->g_h; yc > 0; --yc)
	{
		for(xc=ww; xc > 0; --xc)
		{
			mr=255-*cc;
			mg=255-*mm;
			mb=255-*yy;
			/* RGB->Grey Hibyte(77*R+151*G+28*B) */
			mc=77*mr+151*mg+28*mb;
			mc=mc >> 8;
			mr=mc*(int)(*cc);	mr/=255;*cc++=(uchar)mr;
			mr=mc*(int)(*mm);	mr/=255;*mm++=(uchar)mr;
			mr=mc*(int)(*yy);	mr/=255;*yy++=(uchar)mr;
		}
		cc+=ldif;
		mm+=ldif;
		yy+=ldif;
	}
	
	return(1);
}
