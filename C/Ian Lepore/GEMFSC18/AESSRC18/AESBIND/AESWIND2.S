
;*========================================================================
;*
;* AESFAST GEM bindings.
;*
;*========================================================================

          .include  "aesfast.sh"
          
;*************************************************************************
;*
;* Window manager routines 2 of 2.
;*
;*************************************************************************

;-------------------------------------------------------------------------
; wind_get
;-------------------------------------------------------------------------

_wind_get::
          .cargs    #8,.handle,.field,.p1.l,.p2.l,.p3.l,.p4.l
          link      a6,#-10
          AControl  104,2,5,0

          moveq.l    #-10,d2   
          lea       .handle(a6),a1
          ACall     RET2HERE

          moveq.l   #-10,d1
          lea       .p1(a6),a1
          jmp       (a0)
  
;-------------------------------------------------------------------------
; wind_calc
;-------------------------------------------------------------------------

_wind_calc::
          .cargs    #8,.i1,.i2,.i3,.i4,.i5,.i6,.p1.l,.p2.l,.p3.l,.p4.l
          link      a6,#-10

          AControl  108,6,5,0
          
          moveq.l   #-10,d2    
          lea       .i1(a6),a1
          ACall     RET2HERE

          moveq.l   #-10,d1
          lea       .p1(a6),a1
          jmp       (a0)
          
;         end of code

