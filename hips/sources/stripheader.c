/*
 * Copyright (c) 1991 Michael Landy
 *
 * Disclaimer:  No guarantees of performance accompany this software,
 * nor is any responsibility assumed on the part of the authors.  All the
 * software has been tested extensively and every effort has been made to
 * insure its reliability.
 */

/*
 * stripheader.c - strip an image sequence of its header
 *
 * use:	stripheader <input_seq >output_seq
 *
 * to load: cc -o stripheader stripheader.c -lhips
 *
 * Michael Landy - 4/19/82
 * HIPS 2 - msl - 1/8/91
 */

#include <stdio.h>
#include <hipl_format.h>

static Flag_Format flagfmt[] = {LASTFLAG};

int main(argc,argv)

int argc;
char **argv;

{
	struct header hd;
	int c,i,*fmts,fmtssize;
	hsize_t currsize;
	Filename filename;
	FILE *fp;

	Progname = strsave(*argv);
	parseargs(argc,argv,flagfmt,FFONE,&filename);
	fp = hfopenr(filename);
	fread_hdr_a(fp,&hd,filename);
	if (hd.sizeimage) {
		for (i=0;i<hd.num_frame;i++) {
			fread_image(fp,&hd,i,filename);
			write_image(&hd,i);
		}
	}
	else if (hd.pixel_format == PFMIXED) {
		fmtssize = hd.num_frame;
		getparam(&hd,"formats",PFINT,&fmtssize,&fmts);
		if (fmtssize != hd.num_frame)
			perr(HE_FMTSLEN,filename);
		setformat(&hd,fmts[0]);
		alloc_image(&hd);
		currsize = hd.sizeimage;
		for (i=0;i<hd.num_frame;i++) {
			setformat(&hd,fmts[i]);
			if (hd.sizeimage > currsize) {
				free(hd.image);
				alloc_image(&hd);
				currsize = hd.sizeimage;
			}
			fread_image(fp,&hd,i,filename);
			write_image(&hd,i);
		}
	}
	else {
		while ((c=getc(fp)) != EOF) putchar(c);
	}
	return(0);
}
