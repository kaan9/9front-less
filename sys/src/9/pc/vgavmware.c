#include "u.h"
#include "../port/lib.h"
#include "mem.h"
#include "dat.h"
#include "fns.h"
#include "io.h"
#include "../port/error.h"

#define	Image	IMAGE
#include <draw.h>
#include <memdraw.h>
#include <cursor.h>
#include "screen.h"

enum {
	PCIVMWARE	= 0x15AD,	/* PCI VID */

	VMWARE1		= 0x0710,	/* PCI DID */
	VMWARE2		= 0x0405,
};

enum {
	Rid = 0,
	Renable,
	Rwidth,
	Rheight,
	Rmaxwidth,

	Rmaxheight,
	Rdepth,
	Rbpp,
	Rpseudocolor,
	Rrmask,

	Rgmask,
	Rbmask,
	Rbpl,
	Rfbstart,	/* deprecated */
	Rfboffset,

	Rfbmaxsize,
	Rfbsize,
	Rcap,
	Rmemstart,	/* deprecated */
	Rmemsize,

	Rconfigdone,
	Rsync,
	Rbusy,
	Rguestid,
	Rcursorid,

	Rcursorx,
	Rcursory,
	Rcursoron,
	Nreg,

	FifoMin = 0,
	FifoMax = 1,
	FifoNextCmd = 2,
	FifoStop = 3,
	FifoUser = 4,

	Xupdate = 1,
	Xrectfill = 2,
	Xrectcopy = 3,
	Xdefinebitmap = 4,
	Xdefinebitmapscanline = 5,
	Xdefinepixmap = 6,
	Xdefinepixmapscanline = 7,
	Xrectbitmapfill = 8,
	Xrectpixmapfill = 9,
	Xrectbitmapcopy = 10,
	Xrectpixmapcopy = 11,
	Xfreeobject = 12,
	Xrectropfill = 13,
	Xrectropcopy = 14,
	Xrectropbitmapfill = 15,
	Xrectroppixmapfill = 16,
	Xrectropbitmapcopy = 17,
	Xrectroppixmapcopy = 18,
	Xdefinecursor = 19,
	Xdisplaycursor = 20,
	Xmovecursor = 21,
	Xdefinealphacursor = 22,
	Xcmdmax = 23,

	CursorOnHide = 0,
	CursorOnShow = 1,
	CursorOnRemoveFromFb = 2,
	CursorOnRestoreToFb = 3,

	Rpalette = 1024,
};

typedef struct Vmware	Vmware;
struct Vmware {
	uvlong	fb;

	ulong	ra;
	ulong	rd;

	ulong	r[Nreg];
	ulong	*mmio;
	ulong	mmiosize;

	char	chan[32];
	int	depth;
	int	ver;
};

Vmware xvm;
Vmware *vm=&xvm;

static ulong
vmrd(Vmware *vm, int i)
{
	outl(vm->ra, i);
	return inl(vm->rd);
}

static void
vmwr(Vmware *vm, int i, ulong v)
{
	outl(vm->ra, i);
	outl(vm->rd, v);
}

static void
vmwait(Vmware *vm)
{
	vmwr(vm, Rsync, 1);
	while(vmrd(vm, Rbusy))
		;
}

static void
vmwarelinear(VGAscr* scr, int, int)
{
	Pcidev *p;

	p = scr->pci;
	if(p == nil || p->vid != PCIVMWARE)
		return;
	if(p->mem[1].bar & 1)
		return;
	switch(p->did){
	default:
		return;
	case VMWARE1:
		vm->ver = 1;
		vm->ra = 0x4560;
		vm->rd = 0x4560 + 4;
		break;
	case VMWARE2:
		if((p->mem[0].bar & 1) == 0)
			return;
		vm->ver = 2;
		vm->ra = p->mem[0].bar & ~3;
		vm->rd = vm->ra + 1;
		break;
	}
	// vm->fb = vmrd(vm, Rfbstart);
	vm->fb = p->mem[1].bar & ~0xF;
	vm->fb += vmrd(vm, Rfboffset);
	vgalinearaddr(scr, vm->fb, vmrd(vm, Rfbmaxsize));
	if(scr->apsize)
		addvgaseg("vmwarescreen", scr->paddr, scr->apsize);

	if(scr->mmio==nil){
		uvlong mmiobase;
		ulong mmiosize;

		if(p->mem[2].bar & 1)
			return;
		// mmiobase = vmrd(vm, Rmemstart);
		mmiobase = p->mem[2].bar & ~0xF;
		if(mmiobase == 0)
			return;
		mmiosize = vmrd(vm, Rmemsize);
		scr->mmio = vmap(mmiobase, mmiosize);
		if(scr->mmio == nil)
			return;
		vm->mmio = scr->mmio;
		vm->mmiosize = mmiosize;
		addvgaseg("vmwaremmio", mmiobase, mmiosize);
	}
	scr->mmio[FifoMin] = 4*sizeof(ulong);
	scr->mmio[FifoMax] = vm->mmiosize;
	scr->mmio[FifoNextCmd] = 4*sizeof(ulong);
	scr->mmio[FifoStop] = 4*sizeof(ulong);
	vmwr(vm, Rconfigdone, 1);
}

static void
vmfifowr(Vmware *vm, ulong v)
{
	ulong *mm;

	mm = vm->mmio;
	if(mm[FifoNextCmd]+sizeof(ulong) == mm[FifoStop]
	|| (mm[FifoNextCmd]+sizeof(ulong) == mm[FifoMax]
	    && mm[FifoStop] == mm[FifoMin]))
		vmwait(vm);

	mm[mm[FifoNextCmd]/sizeof(ulong)] = v;

	/* must do this way so mm[FifoNextCmd] is never mm[FifoMax] */
	v = mm[FifoNextCmd] + sizeof(ulong);
	if(v == mm[FifoMax])
		v = mm[FifoMin];
	mm[FifoNextCmd] = v;
}

static void
vmwareflush(VGAscr*, Rectangle r)
{
	if(vm->mmio == nil)
		return;

	vmfifowr(vm, Xupdate);
	vmfifowr(vm, r.min.x);
	vmfifowr(vm, r.min.y);
	vmfifowr(vm, r.max.x-r.min.x);
	vmfifowr(vm, r.max.y-r.min.y);
	vmwait(vm);
}

static void
vmwareload(VGAscr*, Cursor *c)
{
	int i;
	ulong clr, set;
	ulong and[16];
	ulong xor[16];

	if(vm->mmio == nil)
		return;

	vmfifowr(vm, Xdefinecursor);
	vmfifowr(vm, 1);	/* cursor id */
	vmfifowr(vm, -c->offset.x);
	vmfifowr(vm, -c->offset.y);

	vmfifowr(vm, 16);	/* width */
	vmfifowr(vm, 16);	/* height */
	vmfifowr(vm, 1);	/* depth for and mask */
	vmfifowr(vm, 1);	/* depth for xor mask */

	for(i=0; i<16; i++){
		clr = (c->clr[i*2+1]<<8) | c->clr[i*2];
		set = (c->set[i*2+1]<<8) | c->set[i*2];
		and[i] = ~(clr|set);	/* clr and set pixels => black */
		xor[i] = clr&~set;		/* clr pixels => white */
	}
	for(i=0; i<16; i++)
		vmfifowr(vm, and[i]);
	for(i=0; i<16; i++)
		vmfifowr(vm, xor[i]);

	vmwait(vm);
}

static int
vmwaremove(VGAscr*, Point p)
{
	if(vm->mmio == nil)
		return 1;
	vmwr(vm, Rcursorid, 1);
	vmwr(vm, Rcursorx, p.x);
	vmwr(vm, Rcursory, p.y);
	vmwr(vm, Rcursoron, CursorOnShow);
	return 0;
}

static void
vmwaredisable(VGAscr*)
{
	if(vm->mmio == nil)
		return;
	vmwr(vm, Rcursorid, 1);
	vmwr(vm, Rcursoron, CursorOnHide);
}

static void
vmwareenable(VGAscr*)
{
	if(vm->mmio == nil)
		return;
	vmwr(vm, Rcursorid, 1);
	vmwr(vm, Rcursoron, CursorOnShow);
}

static int
vmwarescroll(VGAscr*, Rectangle r, Rectangle sr)
{
	if(vm->mmio == nil)
		return 0;
	vmfifowr(vm, Xrectcopy);
	vmfifowr(vm, sr.min.x);
	vmfifowr(vm, sr.min.y);
	vmfifowr(vm, r.min.x);
	vmfifowr(vm, r.min.y);
	vmfifowr(vm, Dx(r));
	vmfifowr(vm, Dy(r));
	vmwait(vm);
	return 1;
}

static int
vmwarefill(VGAscr*, Rectangle r, ulong sval)
{
	if(vm->mmio == nil)
		return 0;
	vmfifowr(vm, Xrectfill);
	vmfifowr(vm, sval);
	vmfifowr(vm, r.min.x);
	vmfifowr(vm, r.min.y);
	vmfifowr(vm, r.max.x-r.min.x);
	vmfifowr(vm, r.max.y-r.min.y);
	vmwait(vm);
	return 1;
}

static void
vmwaredrawinit(VGAscr *scr)
{
	scr->scroll = vmwarescroll;
	if(vm->ver == 1)
		scr->fill = vmwarefill;
}

VGAdev vgavmwaredev = {
	"vmware",
	0,
	0,
	0,
	vmwarelinear,
	vmwaredrawinit,
	0,
	0,
	0,
	vmwareflush,
};

VGAcur vgavmwarecur = {
	"vmwarehwgc",

	vmwareenable,
	vmwaredisable,
	vmwareload,
	vmwaremove,
};
