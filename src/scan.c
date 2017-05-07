// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   scandate.c
 * Author: bob
 *
 * Created on October 25, 2014
 */

/* Public Domain code written by Dave Edwards.
 */


/*
 This is free and unencumbered software released into the public domain.
 
 Anyone is free to copy, modify, publish, use, compile, sell, or
 distribute this software, either in source code form or as a compiled
 binary, for any purpose, commercial or non-commercial, and by any
 means.
 
 In jurisdictions that recognize copyright laws, the author or authors
 of this software dedicate any and all copyright interest in the
 software to the public domain. We make this dedication for the benefit
 of the public at large and to the detriment of our heirs and
 successors. We intend this dedication to be an overt act of
 relinquishment in perpetuity of all present and future rights to this
 software under copyright law.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 
 For more information, please refer to <http://unlicense.org/>
 */



#include    <stdarg.h>
#include    <stdbool.h>
#include    <stdint.h>
#include    "ascii.h"
#include    "hex.h"


//****************************************************************
//* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
//****************************************************************


 
/****************************************************************
* * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
****************************************************************/



/****************************************************************
* * * * * * * * * * *  External Subroutines   * * * * * * * * * *
****************************************************************/


//**********************************************************
//                      s s c a n
//**********************************************************


/* vvscanf - the guts of the input scanning */
/* several mods by Dave Edwards */
static
int             vvscanf(
    const
    char            *format,
    va_list         arg,
    const
    char            *s
)
{
    int             ch;
    int             fin = 0;
    int             cnt = 0;
    char            *cptr = 0;
    int             *iptr = 0;
    unsigned int    *uptr = 0;
    long            *lptr = 0;
    unsigned long   *luptr = 0;
    short           *hptr = 0;
    unsigned short  *huptr = 0;
#ifdef XYZZY
    double          *dptr;
    float           *fptr;
#endif
    //long startpos;
    const char      *startp;
    int             skipvar = 0;    /* nonzero if we are skipping this variable */
    int             modlong = 0;    /* nonzero if "l" modifier found */
    int             modshort = 0;   /* nonzero if "h" modifier found */
    int             informatitem;   /* nonzero if % format item started */
                                    /* informatitem is 1 if we have processed "%l" 
                                     * but not the type letter (s,d,e,f,g,...) yet. 
                                     */
    
    startp = s;
    ch = (unsigned char)*s++;
    informatitem = 0;   /* init */
    if (ch == 0) return -1;
    /* initially at EOF or end of string */
    while (!fin)
    {
        if (*format == '\0')
        {
            fin = 1;
        }
        else if (*format == '%' || informatitem)
        {
            if(*format=='%')   /* starting a format item */
            {
                format++;
                modlong=0;   /* init */
                modshort=0;
                skipvar = 0;
                if (*format == '*')
                {
                    skipvar = 1;
                    format++;
                }
            }
            if (*format == '%')   /* %% */
            {
                if (ch != '%') return (cnt);
                ch = (unsigned char)*s++;
                informatitem=0;
            }
            else if (*format == 'l')
            {
                /* Type modifier: l  (e.g. %ld or %lf) */
                modlong=1;
                informatitem=1;
            }
            else if (*format == 'h')
            {
                /* Type modifier: h (short int) */
                modshort=1;
                informatitem=1;
            }
            else    /* process a type character: */
            {
                informatitem=0;   /* end of format item */
                if (*format == 's')
                {
                    if (!skipvar)
                    {
                        cptr = va_arg(arg, char *);
                    }
                    /* Skip leading whitespace: */
                    while (ch>=0 && ascii_isWhiteSpaceA(ch))
                        ch = (unsigned char)*s++;
                    if (ch == 0)
                    /* at EOF or end of string */
                    {
                        fin = 1;
                        if (!skipvar) {
                            *cptr = 0;   /* give a null string */
                        }
                    }
                    else {
                        for(;;) {
                            if (ascii_isWhiteSpaceA(ch))
                                break;
                            if (ch == 0) {
                                fin = 1;
                                break;
                            }
                            if (!skipvar) {
                                *cptr++ = (char)ch;
                            }
                            ch = (unsigned char)*s++;
                        }
                        if (!skipvar) {
                            *cptr = '\0';
                        }
                        cnt++;
                    }
                }
                else if (*format == '[') {
                    int reverse = 0;
                    int found;
                    const char *first;
                    const char *last;
                    size_t size;
                    size_t mcnt = 0;
                    
                    if (!skipvar) {
                        cptr = va_arg(arg, char *);
                    }
                    format++;
                    if (*format == '^') {
                        reverse = 1;
                        format++;
                    }
                    if (*format == '\0') break;
                    first = format;
                    format++;
                    last = strchr(format, ']');
                    if (last == NULL) return (cnt);
                    size = (size_t)(last - first);
                    while (1) {
                        /* note that C90 doesn't require special
                         processing for '-' so it hasn't been
                         added */
                        found = (memchr(first, ch, size) != NULL);
                        if (found && reverse) break;
                        if (!found && !reverse) break;
                        if (!skipvar) {
                            *cptr++ = (char)ch;
                        }
                        mcnt++;
                        ch = (unsigned char)*s++;
                        /* if at EOF or end of string, bug out */
                        if (ch == 0) {
                            break;
                        }
                    }
                    if (mcnt > 0) {
                        if (!skipvar) {
                            *cptr++ = '\0';
                        }
                        cnt++;
                    }
                    else {
                        break;
                    }
                    format = last + 1;
                }
                else if (*format == 'c') {
                    if (!skipvar) {
                        cptr = va_arg(arg, char *);
                    }
                    if (ch == 0) fin = 1;
                    /* at EOF or end of string */
                    else
                    {
                        if (!skipvar)
                        {
                            *cptr = ch;
                        }
                        cnt++;
                        ch = (unsigned char)*s++;
                    }
                }
                else if (*format == 'n')
                {
                    uptr = va_arg(arg, unsigned int *);
                        *uptr = (unsigned int)(startp - s);
                }
                else if (*format == 'd' || *format == 'u'
                         || *format == 'x' || *format == 'o'
                         || *format == 'p'
                         || *format == 'i')
                {
                    int neg = 0;
                    unsigned long x = 0;
                    int undecided = 0;
                    int base = 10;
                    int mcnt = 0;
                    
                    if (*format == 'x') base = 16;
                    else if (*format == 'p') base = 16;
                    else if (*format == 'o') base = 8;
                    else if (*format == 'i') base = 0;
                    if (!skipvar)
                    {
                        if ((*format == 'd') || (*format == 'i'))
                        {
                            if (modlong) lptr = va_arg(arg, long *);
                            else if (modshort) hptr = va_arg(arg, short *);
                            else iptr = va_arg(arg, int *);
                        }
                        else
                        {
                            if (modlong) luptr = va_arg(arg, unsigned long *);
                            else if (modshort) huptr =
                                va_arg(arg, unsigned short *);
                            else uptr = va_arg(arg, unsigned int *);
                        }
                    }
                    /* Skip leading whitespace: */
                    while (ch>=0 && ascii_isWhiteSpaceA(ch))
                        ch = (unsigned char)*s++;
                    if (ch == '-')
                    {
                        neg = 1;
                        ch = (unsigned char)*s++;
                    }
                    else if(ch == '+') ch = (unsigned char)*s++;
                    
                    /* this logic is the same as strtoul so if you
                     change this, change that one too */
                    
                    if (base == 0)
                    {
                        undecided = 1;
                    }
                    while (!(ch == 0))
                    {
                        if (ascii_isNumericA((unsigned char)ch))
                        {
                            if (base == 0)
                            {
                                if (ch == '0')
                                {
                                    base = 8;
                                }
                                else
                                {
                                    base = 10;
                                    undecided = 0;
                                }
                            }
                            x = x * base + (ch - '0');
                            ch = (unsigned char)*s++;
                        }
                        /* DOS has a ':' in the pointer - skip that */
#if defined(__MSDOS__) && \
    !(defined(__PDOS__) && !defined(__MVS__)) && \
    !defined(__gnu_linux__)
                        else if ((*format == 'p') && (ch == ':'))
                        {
                            ch = (unsigned char)*s++;
                        }
#endif
                        else if (ascii_isAlphaA((unsigned char)ch))
                        {
                            if ((ch == 'X') || (ch == 'x'))
                            {
                                if ((base == 0) || ((base == 8) && undecided))
                                {
                                    base = 16;
                                    undecided = 0;
                                    ch = (unsigned char)*s++;
                                }
                                else if (base == 16)
                                {
                                    /* hex values are allowed to have an
                                     optional 0x */
                                    ch = (unsigned char)*s++;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            else if (base <= 10)
                            {
                                break;
                            }
                            else
                            {
                                x = x * base +
                                (ascii_toUpperA((unsigned char)ch) - 'A') + 10;
                                ch = (unsigned char)*s++;
                            }
                        }
                        else
                        {
                            break;
                        }
                        mcnt++;
                    }
                    
                    /* end of strtoul logic */
                    
                    /* If we didn't get any characters, don't go any
                     further */
                    if (mcnt == 0)
                    {
                        break;
                    }
                    
                    
                    if (!skipvar)
                    {
                        if ((*format == 'd') || (*format == 'i'))
                        {
                            long lval;
                            
                            if (neg)
                            {
                                lval = (long)-x;
                            }
                            else
                            {
                                lval = (long)x;
                            }
                            if (modlong) *lptr=lval;
                            /* l modifier: assign to long */
                            else if (modshort) *hptr = (short)lval;
                            /* h modifier */
                            else *iptr=(int)lval;
                        }
                        else
                        {
                            if (modlong) *luptr = (unsigned long)x;
                            else if (modshort) *huptr = (unsigned short)x;
                            else *uptr = (unsigned int)x;
                        }
                    }
                    cnt++;
                }
#ifdef XYZZY
                else if (*format=='e' || *format=='f' || *format=='g' ||
                         *format=='E' || *format=='G')
                {
                    /* Floating-point (double or float) input item */
                    int negsw1,negsw2,dotsw,expsw,ndigs1,ndigs2,nfdigs;
                    int ntrailzer,expnum,expsignsw;
                    double fpval,pow10;
                    
                    if (!skipvar)
                    {
                        if (modlong) dptr = va_arg(arg, double *);
                        else fptr = va_arg(arg, float *);
                    }
                    negsw1=0;   /* init */
                    negsw2=0;
                    dotsw=0;
                    expsw=0;
                    ndigs1=0;
                    ndigs2=0;
                    nfdigs=0;
                    ntrailzer=0;  /* # of trailing 0's unaccounted for */
                    expnum=0;
                    expsignsw=0;  /* nonzero means done +/- on exponent */
                    fpval=0.0;
                    /* Skip leading whitespace: */
                    while (ch>=0 && ascii_isWhiteSpaceA(ch))
                        ch = (unsigned char)*s++;
                    if (ch=='-')
                    {
                        negsw1=1;
                        ch = (unsigned char)*s++;
                    }
                    else if (ch=='+')
                        ch = (unsigned char)*s++;
                    while (ch>0)
                    {
                        if (ch=='.' && dotsw==0 && expsw==0) dotsw=1;
                        else if (ascii_isNumericA(ch))
                        {
                            if(expsw)
                            {
                                ndigs2++;
                                expnum=expnum*10+(ch-'0');
                            }
                            else
                            {
                                /* To avoid overflow or loss of precision,
                                 skip leading and trailing zeros unless
                                 really needed. (Automatic for leading
                                 0's, since 0.0*10.0 is 0.0) */
                                ndigs1++;
                                if (dotsw) nfdigs++;
                                if (ch=='0' && fpval!=0.)
                                {
                                    /* Possible trailing 0 */
                                    ntrailzer++;
                                }
                                else
                                {
                                    /* Account for any preceding zeros */
                                    while (ntrailzer>0)
                                    {
                                        fpval*=10.;
                                        ntrailzer--;
                                    }
                                    fpval=fpval*10.0+(ch-'0');
                                }
                            }
                        }
                        else if ((ch=='e' || ch=='E') && expsw==0) expsw=1;
                        else if ((ch=='+' || ch=='-') && expsw==1
                                 && ndigs2==0 && expsignsw==0)
                        {
                            expsignsw=1;
                            if (ch=='-') negsw2=1;
                        }
                        else break;   /* bad char: end of input item */
                        ch = (unsigned char)*s++;
                    }
                    if ((fp != NULL && ch == EOF)
                        || (fp == NULL && ch == 0)) fin=1;
                    /* Check for a valid fl-pt value: */
                    if (ndigs1==0 || (expsw && ndigs2==0)) return(cnt);
                    /* Complete the fl-pt value: */
                    if (negsw2) expnum=-expnum;
                    expnum+=ntrailzer-nfdigs;
                    if (expnum!=0 && fpval!=0.0)
                    {
                        negsw2=0;
                        if (expnum<0)
                        {
                            expnum=-expnum;
                            negsw2=1;
                        }
                        /* Multiply or divide by 10.0**expnum, using
                         bits of expnum (fast method) */
                        pow10=10.0;
                        for (;;)
                        {
                            if (expnum & 1)     /* low-order bit */
                            {
                                if (negsw2) fpval/=pow10;
                                else fpval*=pow10;
                            }
                            expnum>>=1;   /* shift right 1 bit */
                            if (expnum==0) break;
                            pow10*=pow10;   /* 10.**n where n is power of 2 */
                        }
                    }
                    if (negsw1) fpval=-fpval;
                    if (!skipvar)
                    {
                        /* l modifier: assign to double */
                        if (modlong) *dptr=fpval;
                        else *fptr=(float)fpval;
                    }
                    cnt++;
                }
#endif
            }
        }
        else if (ascii_isWhiteSpaceA((unsigned char)(*format)))
        {
            /* Whitespace char in format string: skip next whitespace
             chars in input data. This supports input of multiple
             data items. */
            while (ch>=0 && ascii_isWhiteSpaceA(ch))
            {
                ch = (unsigned char)*s++;
            }
        }
        else   /* some other character in the format string */
        {
            if (ch != *format) return (cnt);
            ch = (unsigned char)*s++;
        }
        format++;
        if (ch == 0) fin = 1;
        /* EOF */
    }
    return (cnt);
}





int             sscanf(
    const
    char            *s,
    const
    char            *format,
    ...
)
{
    va_list arg;
    int ret;
    
    va_start(arg, format);
    ret = vvscanf(format, arg, s);
    va_end(arg);
    return (ret);
}





