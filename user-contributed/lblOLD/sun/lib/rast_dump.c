/* rast_dump.c - write a Sun rasterfile
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

This software is copyright (C) by the Lawrence Berkeley Laboratory.
Permission is granted to reproduce this software for non-commercial
purposes provided that this notice is left intact.

It is acknowledged that the U.S. Government has rights to this software
under Contract DE-AC03-765F00098 between the U.S.  Department of Energy
and the University of California.

This software is provided as a professional and academic contribution
for joint exchange. Thus, it is experimental, and is provided ``as is'',
with no warranties of any kind whatsoever, no support, no promise of
updates, or printed documentation. By using this software, you
acknowledge that the Lawrence Berkeley Laboratory and Regents of the
University of California shall have no liability with respect to the
infringement of other copyrights by any part of this software.

For further information about this notice, contact William Johnston,
Bld. 50B, Rm. 2239, Lawrence Berkeley Laboratory, Berkeley, CA, 94720.
(wejohnston@lbl.gov)

For further information about this software, contact:
	Jin Guojun
	Bld. 50B, Rm. 2275, Lawrence Berkeley Laboratory, Berkeley, CA, 94720.
	g_jin@lbl.gov

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% AUTHOR:	Jin Guojun - LBL	10/1/91
*/

#include "imagedef.h"

#ifndef	TOP_BITMAP_VALUE
#define	TOP_BITMAP_VALUE	255
#endif

/*	colormap_t	pr_colormap;	*/
/*	{ int type, lenght; char* map[3] }	SUN raster color map */

extern struct rasterfile	srhd;
extern RastSWidth(/*struct rasterfile*	srhd*/);


#ifndef	RAS_RLE_ECODE
#define	RAS_RLE_ECODE	128
#endif

rast_dump_header(struct	rasterfile *srhd, colormap_t *cmap, FILE *fp)
{
if (fwrite(srhd, sizeof(*srhd), 1, fp) < 1)
	return	prgmerr(0, "write RAS header");
if (srhd->ras_maplength && fwrite(cmap->map[0], srhd->ras_maplength, 1, fp) < 1)
	return	prgmerr(0, "write RAS cmap");
return	0;
}

pr_dump(struct pixrect *prt, FILE *fp, colormap_t *cmap, int type, int flag)
{
double	junk;
byte	*buf = prt->pr_data->md_image;
register int	d, i, pad;

srhd.ras_magic = RAS_MAGIC;
srhd.ras_type = type;
if (cmap)	{
	srhd.ras_maptype = cmap->type;
	srhd.ras_maplength = cmap->length * 3;
} else	srhd.ras_maptype = srhd.ras_maplength = 0;
srhd.ras_width = prt->pr_size.x;
srhd.ras_height= prt->pr_size.y;
srhd.ras_depth = prt->pr_depth;
i = srhd.ras_width*srhd.ras_height;
d = srhd.ras_depth>>3;
if (! d)	d++;
srhd.ras_length = i * d;

if (type != RT_BYTE_ENCODED && (pad=rast_dump_header(&srhd, cmap, fp)) < 0)
	return	pad;

pad = RAST_ODD_PAD(srhd.ras_width);

if (type==RT_BYTE_ENCODED) {
int	pad_len = srhd.ras_width * d, pad_w;
byte*	encode = NZALLOC(i, d, "ras_enc"), *dp = buf;
register int	c, w;

#define	padw(o)	*buf++ = w,	w = pad_len o
#define	add_RRE	*buf++ = d; if (d==RAS_RLE_ECODE) *buf++ = 0;	c--;	pad_w++

buf = encode;
    for (w=pad_len, i *= d; i-- > 0;)	{
	d = *dp;
	for (c=pad_w=0; d == *++dp; c++);
	if (c)	{
	    i -= c;
	    if (pad && w <= c)	while (w <= c)	{
		switch (w)	{	/* wired design. silly?	*/
		case 2:	add_RRE;	add_RRE;
		case 1:	/* pad at last pixel, not padding pos.? */
			padw(;)
			w -= (dp - prt->pr_data->md_image) % pad_len;
			break;
		default:
			if (!pad && c > pad_len)	/* no padding ? */
				w = pad_len - c % pad_len,
				c += c / pad_len;
			else	{
				pad_w = w > 256 ? 256 : w;
				*buf++ = RAS_RLE_ECODE;
				*buf++ = pad_w-1;	c -= pad_w;
				*buf++ = d;
				w -= pad_w;
			}
		}
		if (c > pad_len || !w)	break;
	    }	else	pad_w += c;
	    if (c > 1 || d==RAS_RLE_ECODE)	{
split:		*buf++ = RAS_RLE_ECODE;
		if (pad_w + c > pad_len)	{
			*buf++ = pad_len - pad_w - 1;
			*buf++ = d;
			c -= pad_len - pad_w;
			*buf++ = pad_w = 0;	w = pad_len;
			*buf++ = RAS_RLE_ECODE;
		}
		if (c > 255)	{
			*buf++ = 255;	*buf++ = d;
			c -= 256;	pad_w += 256;	w -= 256;
			goto	split;
		}
		if (c || d==RAS_RLE_ECODE)	*buf++ = c;
		else	buf--;	/* only one left	*/
	    } else	{
		register int	j = c;	w -= c;
		while (j--)	*buf++ = d;
	    }
	}
	*buf++ = d;
	if (d==RAS_RLE_ECODE && !c)
		*buf++ = c;
	if (pad && --w <= 0)
		padw(;)
    }
    srhd.ras_length = buf - encode;
    d = rast_dump_header(&srhd, cmap, fp) < 0 ||
	fwrite(encode, srhd.ras_length, 1, fp) < 1;
    CFREE(encode);
    i = d ? -1 : srhd.ras_length;
}
else if (srhd.ras_width & d & 1)	{
	for (d *= RastSWidth(&srhd), i=srhd.ras_height; i--; buf+=d) {
		if (fwrite(buf, 1, d, fp) != d)
			return	prgmerr(0, "write rastline %d", i);
		if (pad)
			fwrite(&junk, 1, pad, fp);
	}
	i = srhd.ras_width*srhd.ras_height;
} else	{	d = fwrite(buf, d, i, fp);
		if (d != i)
			return	prgmerr(0, "read rastfile %d", d);
}
return	i;
}
