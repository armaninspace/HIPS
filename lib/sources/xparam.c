/*
 * Copyright (c) 1991 Michael Landy
 *
 * Disclaimer:  No guarantees of performance accompany this software,
 * nor is any responsibility assumed on the part of the authors.  All the
 * software has been tested extensively and every effort has been made to
 * insure its reliability.
 */

/*
 * xparam.c - HIPS extended parameter management
 *
 * Michael Landy 1/4/91
 */

#include <hipl_format.h>

#ifdef HUSESTDARG
#include <stdarg.h>
#else
#include <varargs.h>
#endif

char *strstr1();
h_boolean checkname();

/* setparam(hd,name,fmt,count,value) */

#ifdef HUSESTDARG
int setparam(struct header *hd, ...)

{

#else

int setparam(va_alist)

va_dcl

{
	struct header *hd;
#endif
	va_list ap;
	struct extpar *xp;
	char *name;
	int fmt,count;

#ifdef HUSESTDARG
	va_start(ap,hd);
#else
	va_start(ap);
	hd = va_arg(ap,struct header *);
#endif
	name = va_arg(ap,char *);
	if (checkname(name))
		return(perr(HE_PNAME,"setparam",name));
	fmt = va_arg(ap,int);
	count = va_arg(ap,int);
	if ((xp = findparam(hd,name)) == NULLPAR) {
		if ((xp = (struct extpar *) hmalloc(sizeof(struct extpar))) == 
			(struct extpar *) HIPS_ERROR) {
				va_end(ap);
				return(HIPS_ERROR);
		}
		xp->name = strsave(name);
		xp->nextp = hd->params;
		hd->params = xp;
		hd->numparam++;
	}
	else {
		if (hd->paramdealloc && xp->dealloc)
			free(xp->val.v_pb);
	}
	xp->format = fmt;
	xp->count = count;
	xp->dealloc = FALSE;
	if (count == 1) {
		switch (fmt) {
		case PFASCII:
		case PFBYTE:	xp->val.v_b = va_arg(ap,int); break;
		case PFSHORT:	xp->val.v_s = va_arg(ap,int); break;
		case PFINT:	xp->val.v_i = va_arg(ap,int); break;
		case PFFLOAT:	xp->val.v_f = va_arg(ap,double); break;
					/* Note that C converts float
					   arguments to double */
		default:	va_end(ap);
				return(perr(HE_HDPTYPE,"setparam",fmt));
		}
	}
	else {
		switch (xp->format) {
		case PFASCII:
		case PFBYTE:	xp->val.v_pb = va_arg(ap,byte *); break;
		case PFSHORT:	xp->val.v_ps = va_arg(ap,short *); break;
		case PFINT:	xp->val.v_pi = va_arg(ap,int *); break;
		case PFFLOAT:	xp->val.v_pf = va_arg(ap,float *); break;
		default:	va_end(ap);
				return(perr(HE_HDPTYPE,"setparam",fmt));
		}
	}
	va_end(ap);
	return(HIPS_OK);
}

/* setparamd(hd,name,fmt,count,value) */

#ifdef HUSESTDARG

int setparamd(struct header *hd, ...)
{

#else

int setparamd(va_alist)

va_dcl

{
	struct header *hd;
#endif
	va_list ap;
	struct extpar *xp;
	char *name;
	int fmt,count;

#ifdef HUSESTDARG
	va_start(ap,hd);
#else
	va_start(ap);
	hd = va_arg(ap,struct header *);
#endif
	name = va_arg(ap,char *);
	if (checkname(name))
		return(perr(HE_PNAME,"setparamd",name));
	fmt = va_arg(ap,int);
	count = va_arg(ap,int);
	if ((xp = findparam(hd,name)) == NULLPAR) {
		if ((xp = (struct extpar *) hmalloc(sizeof(struct extpar))) == 
			(struct extpar *) HIPS_ERROR) {
				va_end(ap);
				return(HIPS_ERROR);
		}
		xp->name = strsave(name);
		xp->nextp = hd->params;
		hd->params = xp;
		hd->numparam++;
	}
	else {
		if (hd->paramdealloc && xp->dealloc)
			free(xp->val.v_pb);
	}
	xp->format = fmt;
	xp->count = count;
	if (count == 1) {
		xp->dealloc = FALSE;
		switch (fmt) {
		case PFASCII:
		case PFBYTE:	xp->val.v_b = va_arg(ap,int); break;
		case PFSHORT:	xp->val.v_s = va_arg(ap,int); break;
		case PFINT:	xp->val.v_i = va_arg(ap,int); break;
		case PFFLOAT:	xp->val.v_f = va_arg(ap,double); break;
					/* Note that C converts float
					   arguments to double */
		default:	va_end(ap);
				return(perr(HE_HDPTYPE,"setparam",fmt));
		}
	}
	else {
		xp->dealloc = TRUE;
		switch (xp->format) {
		case PFASCII:
		case PFBYTE:	xp->val.v_pb = va_arg(ap,byte *); break;
		case PFSHORT:	xp->val.v_ps = va_arg(ap,short *); break;
		case PFINT:	xp->val.v_pi = va_arg(ap,int *); break;
		case PFFLOAT:	xp->val.v_pf = va_arg(ap,float *); break;
		default:	va_end(ap);
				return(perr(HE_HDPTYPE,"setparam",fmt));
		}
	}
	va_end(ap);
	return(HIPS_OK);
}

/* getparam(hd,name,fmt,count,valuepointer) */

#ifdef HUSESTDARG
int getparam(struct header *hd, ...)
{

#else

int getparam(va_alist)

va_dcl

{
	struct header *hd;
#endif
	va_list ap;
	struct extpar *xp;
	char *name;
	int fmt,*count;

#ifdef HUSESTDARG
	va_start(ap,hd);
#else
	va_start(ap);
	hd = va_arg(ap,struct header *);
#endif
	name = va_arg(ap,char *);
	if (checkname(name))
		return(perr(HE_PNAME,"getparam",name));
	fmt = va_arg(ap,int);
	count = va_arg(ap,int *);
	if ((xp = findparam(hd,name)) == NULLPAR) {
		va_end(ap);
		return(perr(HE_MISSPAR,"getparam",name));
	}
	if ((*count == 1 && xp->count != 1) || (*count != 1 && xp->count == 1))
		return(perr(HE_PCOUNT,"getparam",name));
	*count = xp->count;
	if (*count == 1) {
		switch (fmt) {
		case PFASCII:
		case PFBYTE:	*(va_arg(ap,byte *)) = xp->val.v_b; break;
		case PFSHORT:	*(va_arg(ap,short *)) = xp->val.v_s; break;
		case PFINT:	*(va_arg(ap,int *)) = xp->val.v_i; break;
		case PFFLOAT:	*(va_arg(ap,float *)) = xp->val.v_f; break;
		default:	va_end(ap);
				return(perr(HE_HDPTYPE,"getparam",fmt));
		}
	}
	else {
		switch (xp->format) {
		case PFASCII:
		case PFBYTE:	*(va_arg(ap,byte **)) = xp->val.v_pb; break;
		case PFSHORT:	*(va_arg(ap,short **)) = xp->val.v_ps; break;
		case PFINT:	*(va_arg(ap,int **)) = xp->val.v_pi; break;
		case PFFLOAT:	*(va_arg(ap,float **)) = xp->val.v_pf; break;
		default:	va_end(ap);
				return(perr(HE_HDPTYPE,"getparam",fmt));
		}
	}
	va_end(ap);
	return(HIPS_OK);
}

int clearparam(hd,name)

struct header *hd;
char *name;

{
	struct extpar *xp,*prev;

	if (checkname(name))
		return(perr(HE_PNAME,"clearparam",name));
	xp = hd->params;
	prev = NULLPAR;
	while (xp != NULLPAR) {
		if (strcmp(name,xp->name) == 0)
			break;
		prev = xp;
		xp = xp->nextp;
	}
	if (xp == NULLPAR)
		return(perr(HE_MISSPAR,"clearparam",name));
	if (prev == NULLPAR)
		hd->params = xp->nextp;
	else
		prev->nextp = xp->nextp;
	hd->numparam = hd->numparam - 1;

/*
 * Note that we free the binary parameter ONLY IF both the parameter itself
 * may be deallocated and this is the master header pointing to these
 * parameters.  Memory may be lost to deallocation if clearparam is called
 * with a non-master header (paramdealloc = 0) and a parameter other than the
 * first one, because having done that, the master header list of parameters
 * no longer points to this parameter binary area either.  BE CAREFUL.
 */

	if (hd->paramdealloc) {
		if (xp->dealloc)
			free(xp->val.v_pb);
		free(xp->name);
		free(xp);
	}
	return(HIPS_OK);
}

struct extpar *findparam(hd,name)

struct header *hd;
char *name;

{
	struct extpar *xp;

	xp = hd->params;
	while (xp != NULLPAR) {
		if (strcmp(name,xp->name) == 0)
			return(xp);
		xp = xp->nextp;
	}
	return(NULLPAR);
}

h_boolean checkname(name)

char *name;

{
	char *p;

	p = name;
	while (*p != '\0') {
		if (*p == ' ' || *p == '\t')
			return(TRUE);
		p++;
	}
	return(FALSE);
}

int mergeparam(hd1,hd2)

struct header *hd1,*hd2;

{
	struct extpar *xp;

	xp = hd2->params;
	while(xp != NULLPAR) {
		if (xp->count == 1) {
			switch (xp->format) {
			case PFASCII:
			case PFBYTE:	if (setparam(hd1,xp->name,xp->format,
						xp->count,xp->val.v_b)
						== HIPS_ERROR)
							return(HIPS_ERROR);
					break;
			case PFSHORT:	if (setparam(hd1,xp->name,xp->format,
						xp->count,xp->val.v_s)
						== HIPS_ERROR)
							return(HIPS_ERROR);
					break;
			case PFINT:	if (setparam(hd1,xp->name,xp->format,
						xp->count,xp->val.v_i)
						== HIPS_ERROR)
							return(HIPS_ERROR);
					break;
			case PFFLOAT:	if (setparam(hd1,xp->name,xp->format,
						xp->count,xp->val.v_f)
						== HIPS_ERROR)
							return(HIPS_ERROR);
					break;
			default:	return(perr(HE_HDPTYPE,"setparam",
						xp->format));
			}
		}
		else {
			switch (xp->format) {
			case PFASCII:
			case PFBYTE:	if (setparam(hd1,xp->name,xp->format,
						xp->count,xp->val.v_pb)
						== HIPS_ERROR)
							return(HIPS_ERROR);
					break;
			case PFSHORT:	if (setparam(hd1,xp->name,xp->format,
						xp->count,xp->val.v_ps)
						== HIPS_ERROR)
							return(HIPS_ERROR);
					break;
			case PFINT:	if (setparam(hd1,xp->name,xp->format,
						xp->count,xp->val.v_pi)
						== HIPS_ERROR)
							return(HIPS_ERROR);
					break;
			case PFFLOAT:	if (setparam(hd1,xp->name,xp->format,
						xp->count,xp->val.v_pf)
						== HIPS_ERROR)
							return(HIPS_ERROR);
					break;
			default:	return(perr(HE_HDPTYPE,"setparam",
						xp->format));
			}
		}
		xp = xp->nextp;
	}
	return(HIPS_OK);
}

/* grep for a parameter in a header */

struct extpar *grepparam(hd,name)

struct header *hd;
char *name;

{
	struct extpar *xp;

	xp = hd->params;
	while (xp != NULLPAR) {
		if (strstr1(xp->name,name) != NULL)
			return(xp);
		xp = xp->nextp;
	}
	return(NULLPAR);
}

char *strstr1(s1,s2)

char *s1,*s2;

{
	char *s;
	int len;

	len = strlen(s2);
	for (s=s1;*s;s++) {
		if (*s == *s2) {
			if (strncmp(s,s2,len) == 0)
				return(s);
		}
	}
	return(NULL);
}
