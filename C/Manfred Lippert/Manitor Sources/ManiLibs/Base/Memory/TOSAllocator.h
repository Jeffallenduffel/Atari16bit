/*----------------------------------------------------------------------------------------	TOSAllocator.h, TOS allocator (Mxalloc ...)	20.7.2001 by Manfred Lippert, mani@mani.de	last change: 20.7.2001----------------------------------------------------------------------------------------*/#ifndef __ManiLibs_TOSAllocator_h__#define __ManiLibs_TOSAllocator_h__#include <Allocator.h>#if !TARGET_TOS	#error TOSAllocator.h used in Non-TOS Project#endif#if !MC68K	#error TOSAllocator.h used in Non-68K Project#endifclass TOSAllocator : public Allocator {	int16 mode;public:static const int16 ST				= 0x0;static const int16 TT				= 0x1;static const int16 FAVOR_ST		= 0x2;static const int16 FAVOR_TT		= 0x3;static const int16 PRIVATE			= 0x10;static const int16 GLOBAL			= 0x20;static const int16 SUPER			= 0x30;static const int16 READABLE		= 0x40;static const int16 XGLOBAL			= (GLOBAL|FAVOR_ST);static const int16 XREADABLE		= (READABLE|FAVOR_ST);	TOSAllocator(int16 mode);	int16 get_mode() const {return mode;};	int16 set_mode(int16 mode);	virtual void *allocate(size_t bytes);	virtual void deallocate(void *addr);	virtual void *reallocate(void *addr, size_t bytes);};#endif