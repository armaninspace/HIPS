/*
 * This software is copyrighted as noted below.  It may be freely copied,
 * modified, and redistributed, provided that the copyright notice is 
 * preserved on all copies.
 * 
 * There is no warranty or other guarantee of fitness for this software,
 * it is provided solely "as is".  Bug reports or fixes may be sent
 * to the author, who may or may not act on them as he desires.
 *
 * You may not include this software in a program or other software product
 * without supplying the source, or without informing the end-user that the 
 * source is available for no extra charge.
 *
 * If you modify this software, you should include a notice giving the
 * name of the person performing the modification, the date of modification,
 * and the reason for such modification.
 */
/* 
 * sVsetlinebuf.c - setlinebuf function for System V.
 * 
 * Author:	Russell D. Fish
 * 		Computer Science Dept.
 * 		University of Utah
 * Date:	Mon Aug 14 1989
 * Copyright (c) 1989, University of Utah
 */
#ifdef	NO_setlinebuf
#include <stdio.h>

void
setlinebuf( stream )
FILE *stream;
{
    setvbuf( stream, NULL, _IOLBF, 0 );
}
#endif
