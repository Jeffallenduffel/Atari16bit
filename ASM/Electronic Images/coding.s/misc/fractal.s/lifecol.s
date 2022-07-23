;-----------------------------------------------------------------------;
;									;
;                            - L I F E -                                ;
;									;
; A concept by Professor John Conway of University Cambridge (C) 1970.  ;
;									;
; (This Version is Programmed By Martin Griffiths (alias Griff of I.C.) ; 
;-----------------------------------------------------------------------;

letsgo		clr.w -(sp)
		pea -1.w
		pea -1.w
		move.w #5,-(sp)
		trap #14			; lowres
		lea 12(sp),sp
		clr.l -(sp)
		move.w #$20,-(sp)
		trap #1				; supervisor
		addq.l #6,sp

		bsr initscreens
		bsr set_ints

vb_lp		bsr wait_vbl
		bsr Life_plot
		bsr Life_update
		cmp.b #$39+$80,$fffffc02.w
		bne.s vb_lp

.exit	 	bsr rest_ints
		move.l #$00000666,$ffff8240.w
		move.l #$06660666,$ffff8244.w
		clr -(sp)			; bye
		trap #1


wait_vbl	move.w vbl_timer(pc),d0
.waitvb		cmp.w vbl_timer(pc),d0
		beq.s .waitvb
		rts

; Initialisation and restore interrupt routs.

set_ints	move #$2700,sr
		lea old_stuff(pc),a0
		move.l $70.w,(a0)+
		lea my_vbl(pc),a1
		move.l a1,$70.w
		lea $fffffa00.w,a1
		movep.w 7(a1),d0
		move.w d0,(a0)+
		movep.w 13(a1),d0
		move.w d0,(a0)+
		moveq #0,d0
		movep.w d0,7(a1)
		movep.w d0,13(a1)
		move #$2300,sr
		rts

; Restore ints.

rest_ints	move #$2700,sr
		lea old_stuff(pc),a0
		move.l (a0)+,$70.w
		lea $fffffa00.w,a1
		move.w (a0)+,d0
		movep.w d0,7(a1)
		move.w (a0)+,d0
		movep.w d0,13(a1)
		move #$2300,sr
		rts

old_stuff	ds.l 10

initscreens	lea log_base(pc),a1
		move.l #screens+256,d0
		clr.b d0
		move.l d0,(a1)+
		add.l #32000,d0
		move.l d0,(a1)+
		move.l log_base(pc),a0
		bsr clear_screen
		move.l phy_base(pc),a0
		bsr clear_screen
		move.l log_base(pc),d0
		lsr #8,d0
		move.l d0,$ffff8200.w
		rts

; Clear screen ->A0

clear_screen	moveq #0,d0
		move #1999,d1
.cls		move.l d0,(a0)+
		move.l d0,(a0)+
		move.l d0,(a0)+
		move.l d0,(a0)+
		dbf d1,.cls
		rts
; Vbl

my_vbl		movem.l d0-d7/a0-a6,-(sp)
		movem.l life_pal(pc),d0-d7
		movem.l d0-d7,$ffff8240.w
		movem.l (sp)+,d0-d7/a0-a6
		addq #1,vbl_timer
		rte
life_pal	dc.w $000,$002,$003,$004,$005,$006,$007,$700
		dc.w $600,$500,$400,$300,$200,$000,$000,$000

; Life Stuff starts ere...

cells_wide	equ 40			; no. of cells  wide
cells_high	equ 25			; no. of cells high
array_width	equ cells_wide+2	; array width(width+1 either side)

; Update the life grid. (The Brut-force method!)

Life_update	move.l life_ptr(pc),a0
		lea life_array(pc),a2

		moveq #cells_high-1,d7
.vert_lp	lea 1(a0),a1
		lea 1(a2),a3
		moveq #cells_wide-1,d6
.horz_lp	moveq #0,d1
.l1		tst.b -array_width-1(a1)	; top left
		beq.s .l2
		addq #4,d1
.l2		tst.b -array_width(a1)  	; top middle
		beq.s .l3
		addq #4,d1
.l3		tst.b -array_width+1(a1)    	; top right 
		beq.s .l4
		addq #4,d1
.l4		tst.b -1(a1)     		; middle left
		beq.s .l5
		addq #4,d1
.l5		tst.b 1(a1)			; middle right
		beq.s .l6
		addq #4,d1
.l6		tst.b array_width-1(a1)		; bot left
		beq.s .l7
		addq #4,d1
.l7		tst.b array_width(a1)       	; bot middle
		beq.s .l8
		addq #4,d1
.l8		tst.b array_width+1(a1)    	; bot right 
		beq.s .l9
		addq #4,d1
.l9		move.b (a1)+,d0			; fetch cell
		bne.s .tis_a_liveun		; <>0=live cell

; The Cell is found to be Dead(empty), so if exactly 3 other cells are
; in the neighbouring cells then it is born...

.tis_a_deadun	cmp.b #3*4,d1
		beq.s .celllives		; new cell created!
.deadstaysdead	move.b #0,(a3)+			; stays dead!
		dbf d6,.horz_lp
		bra.s .rowdone

; The cell is found to be alive. There are three rules for live cells.
; 1. If there are none or 1 neighbour then it will die of loneliness
; 2. If there are two or three neighbouring cells it lives...
; 3. If there are four or more neighbours it dies of overcrowding!

.tis_a_liveun	jmp .lifeordeath(pc,d1.w)
.lifeordeath	bra.w .celldies  ;0
		bra.w .celldies  ;1
		bra.w .celllives ;2
		bra.w .celllives ;3
		bra.w .celldies  ;4
		bra.w .celldies  ;5
		bra.w .celldies  ;6
		bra.w .celldies  ;7
		bra.w .celldies  ;8

.celldies	move.b #0,(a3)+		; death!
		dbf d6,.horz_lp
		bra.s .rowdone
.celllives	move.b (a3)+,d1
		cmp.b #12*4,d1
		beq.s .celldone
		addq.b #4,d1
		move.b d1,-1(a3)
.celldone	dbf d6,.horz_lp
.rowdone	lea array_width(a0),a0
		lea array_width(a2),a2
		dbf d7,.vert_lp	

		lea life_array(pc),a0	
		move.l life_ptr(pc),a1
		moveq #cells_high-1,d7
.copyback	rept array_width/2
		move.w (a0)+,(a1)+
		endr
		dbf d7,.copyback
		rts

Life_plot	move.l life_ptr(pc),a0
		move.l log_base(pc),a2
		moveq #cells_high-1,d7
		moveq #6,d3
.vert_lp	lea 1(a0),a1
		move.l a2,a3
		moveq #1,d2
		moveq #(cells_wide/2)-1,d6
.horz_lp	clr.w d0
		move.b (a1)+,d0
		move.l movepcols(pc,d0),d0
		movep.l d0,(a3)
		movep.l d0,160(a3)
		movep.l d0,320(a3)
		movep.l d0,480(a3)
		movep.l d0,640(a3)
		movep.l d0,800(a3)
		movep.l d0,960(a3)
		movep.l d0,1120(a3)
		addq #1,a3
		clr.w d0
		move.b (a1)+,d0
		move.l movepcols(pc,d0),d0
		movep.l d0,(a3)
		movep.l d0,160(a3)
		movep.l d0,320(a3)
		movep.l d0,480(a3)
		movep.l d0,640(a3)
		movep.l d0,800(a3)
		movep.l d0,960(a3)
		movep.l d0,1120(a3)
		addq #7,a3
		dbf d6,.horz_lp
		lea array_width(a0),a0
		lea 8*160(a2),a2
		dbf d7,.vert_lp		
		rts

movepcols	dc.l $00000000
		dc.l $ff000000 ;1
		dc.l $00ff0000 ;2
		dc.l $ffff0000 ;3
		dc.l $0000ff00 ;4
		dc.l $ff00ff00 ;5
		dc.l $00ffff00 ;6
		dc.l $ffffff00 ;7
		dc.l $000000ff ;8
		dc.l $ff0000ff ;9
		dc.l $00ff00ff ;10
		dc.l $ffff00ff ;11
		dc.l $0000ffff ;12
		dc.l $ff00ffff ;13
		dc.l $00ffffff ;14
		dc.l $ffffffff ;15
		

life_array	rept cells_high
		ds.b array_width
		endr

life_ptr	dc.l Basic_Shuttle

; 'A glider'

 ds.b array_width 
glider		
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		
 dc.b 0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,4,0,0,0,0,0,0,0		
 dc.b 0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0		
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,4,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 ds.b array_width 

; 'Basic Shuttle'

 ds.b array_width 
Basic_Shuttle		
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		
 dc.b 0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		
 dc.b 0,0,0,0,0,4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0		
 dc.b 0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,4,0,0,0,0,0,4,0,0,0,0,0,0,0,4,4,0,0,0,4,4,4,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,4,4,0,0,4,4,0,4,0,0,0,4,0,0,0,0,0,0,0,4,4,0,0,0,0,4,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,4,0,0,0,4,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,4,4,0,4,0,0,0,0,0,0,4,4,0,0,0,4,4,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,4,0,0,4,0,0,0,0,0,4,4,0,4,0,0,0,0,0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,4,4,4,4,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,4,4,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,4,4,0,0,0,0,4,4,0,0,0,0,0,4,4,0,0,0,0,0,0,0,4,0,4,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,4,0,4,0,0,0,4,4,4,0,0,0,0,0,4,0,4,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,4,0,0,0,4,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,4,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 ds.b array_width 

; 'Methuselah'

 ds.b array_width 
Methuselah
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0		
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 dc.b 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
 ds.b array_width 


log_base	dc.l 0
phy_base	dc.l 0
switch		dc.w 0
vbl_timer	dc.w 0

		section bss
screens		ds.b 256
		ds.b 32000
		ds.b 32000