// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   prt.c
 *	Generated 06/16/2015 07:51:09
 *
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




//*****************************************************************
//* * * * * * * * * * * *  Data Definitions   * * * * * * * * * * *
//*****************************************************************

/* Header File Inclusion */
#include    "prt_internal.h"
#include    <stdarg.h>
#include    <stdio.h>



#ifdef	__cplusplus
extern "C" {
#endif
    

    


 
    /****************************************************************
    * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
    ****************************************************************/

    static
    void            prt_num(
        PRT_DATA       *cbp,
        int             nm
    );
    
    static
    void            prt_tl(
        PRT_DATA       *cbp,
        char            *tl
    );
    
    
    static
    void            prt_foutc(
        PRT_DATA       *cbp,
        char            outchr
    )
    {
        
        if( putc( (outchr & 0x7F), cbp->pList ) == EOF ) {
            fprintf( stderr, "ERROR - Error writing to LIST.\n" );
            exit( 1 );
        }
        
    }
    
    
    
    static
    void            prt_fputc(
        PRT_DATA       *cbp,
        char            outchr
    )
    {
        
        switch( outchr ) {
            case '\f':                  /*** Form Feed ***/
                ++cbp->curpag;
                cbp->curlin = 0;
                break;
            case '\n':                  /*** New Line ***/
                ++cbp->curlin;
                cbp->curcol = 0;
                cbp->offlin = false;
                break;
            case '\r':                  /*** Carriage Return ***/
                cbp->curcol = 0;
                break;
            case '\t':                  /*** Horizontal Tab ***/
                do {
                    prt_foutc( cbp, ' ' );
                } while( ++cbp->curcol % cbp->dfttab );
                return;
            default:
                ++cbp->curcol;
        }
        prt_foutc( cbp, outchr );
        
    }
    
    
    
    static
    void            prt_header(
        PRT_DATA       *cbp
    )
    {
        int             i;
        
        prt_fputc( cbp, '\r' );
        if( cbp->curpag )
            prt_fputc( cbp, '\f' );
        else {
            ++cbp->curpag;
            cbp->curlin = 0;
        }
        if( cbp->prntyp == 1 )
            cbp->curlin = 3;
        else {
            for( i=0; i<cbp->offhdr; ++i )
                prt_fputc( cbp, '\n' );
        }
        prt_tl( cbp, (cbp->format ? cbp->curhdr[0] : NULL) );
        prt_tl( cbp, (cbp->format ? cbp->curhdr[1] : NULL) );
        prt_tl( cbp, (cbp->format ? cbp->curhdr[2] : NULL) );
        for( i=cbp->curlin; i<cbp->hdrsiz; ++i )
            prt_fputc( cbp, '\n' );
        cbp->curlin = cbp->hdrsiz;
    }
    
    
    
    static
    void            prt_linnum(
        PRT_DATA       *cbp
    )
    {
        
        prt_num( cbp, ++cbp->curdln );
        prt_fputc( cbp, ':' );
        prt_fputc( cbp, ' ' );
        prt_fputc( cbp, ' ' );
        
    }
    
    
    
    static
    void            prt_num(
        PRT_DATA       *cbp,
        int             nm
    )
    {
        int             i;
        int             j;
        char            num[5];
        
        j = nm;
        for( i=4; i>=0; --i ) {
            j = nm % 10;
            num[i] = (char)(j + '0');
            nm = nm / 10;
        }
        for( i=0; i<4; ++i ) {
            if( num[i] == '0' )
                num[i] = ' ';
            else
                break;
        }
        for( i=0; i<5; ++i )
            prt_fputc( cbp, num[i] );
        
    }
    
    
    
    static
    void            prt_Offset(
        PRT_DATA       *cbp,
        bool            wln
    )
    {
        int             i;
        
        /* Do initialization.
         */
        if( cbp->offlin )
            return;
        cbp->offlin = true;
        
        /* Print the line offset.
         */
        for( i=0; i<cbp->offset; i++ )
            prt_fputc( cbp, ' ' );
        
        /* Print the line number if applicable.
         */
        if( wln && cbp->prtdln )
            prt_linnum( cbp );
    }
    
    
    
    static
    void            prt_tl(
        PRT_DATA       *cbp,
        char            *tl
    )
    {
        
        if( tl == NULL )
            ;
        else {
            prt_Offset( cbp, false );
            for( ; *tl; ++tl ) {
                if( *tl == '#' )
                    prt_num( cbp, cbp->curpag );
                else
                    prt_fputc( cbp, *tl );
            }
        }
        prt_fputc( cbp, '\n' );
        
    }
    
    
    
    static
    void            prt_trailer(
        PRT_DATA       *cbp
    )
    {
        
        while( cbp->curlin < (cbp->pagsiz - cbp->tlrsiz) ) {
            prt_fputc( cbp, '\n' );
        }
        if( cbp->curlin == (cbp->pagsiz - cbp->tlrsiz) ) {
            //      for( i=0; i<cbp->offtlr; ++i )
            //          prt_fputc( cbp, '\n' );
            prt_tl( cbp, (cbp->format ? cbp->curtlr[0] : NULL) );
            prt_tl( cbp, (cbp->format ? cbp->curtlr[1] : NULL) );
            prt_tl( cbp, (cbp->format ? cbp->curtlr[2] : NULL) );
        }
        
    }
    
    
    
    



    /****************************************************************
    * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
    ****************************************************************/


    //===============================================================
    //                      *** Class Methods ***
    //===============================================================

    PRT_DATA *     prt_Alloc(
    )
    {
        PRT_DATA       *cbp;
        uint32_t        cbSize = sizeof(PRT_DATA);
        
        // Do initialization.
        
        cbp = obj_Alloc( cbSize );
        
        // Return to caller.
        return( cbp );
    }



    

    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    uint16_t        prt_getCol(
        PRT_DATA     *cbp
    )
    {

        // Validate the input parameters.
#ifdef NDEBUG
#else
        if( !prt_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif

        return cbp->curcol;
    }

    
    
    uint32_t        prt_getLineNumber(
        PRT_DATA       *cbp
    )
    {
#ifdef NDEBUG
#else
        if( !prt_Validate( cbp ) ) {
            DEBUG_BREAK();
        }
#endif
        return cbp->curlin;
    }




    

    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                        D e a l l o c
    //---------------------------------------------------------------

    void            prt_Dealloc(
        OBJ_ID          objId
    )
    {
        PRT_DATA        *this = objId;

        // Do initialization.
        if (NULL == this) {
            return;
        }        
#ifdef NDEBUG
#else
        if( !prt_Validate(this) ) {
            DEBUG_BREAK();
            return;
        }
#endif

        /* Print the final trailer.
         */
        prt_trailer(this);
        prt_fputc(this, '\r');
        prt_fputc(this, '\f');
        
        /* Reset HP Deskjet for output.
         */
        switch( this->prntyp ) {
            case    0:                          /*** Simple Printer ***/
                break;
            case    1:                          /*** LaserJet ***/
                fprintf(this->pList, "\033E");         /* Reset Printer */
                break;
            case    2:                          /*** DeskJet ***/
                fprintf(this->pList, "\033E");         /* Reset Printer */
        }
        
        fclose(this->pList);
        this->pList = NULL;
        
        obj_setVtbl(this, this->pSuperVtbl);
        obj_Dealloc(this);
        this = NULL;

        // Return to caller.
    }



    //---------------------------------------------------------------
    //                      H e x  C h r
    //---------------------------------------------------------------

    void            prt_HexChr(
        PRT_DATA		*cbp,
        uint8_t         chr_out
    )
    {
        char            wrkchr;
        
        /* Do Initialization.
         */
#ifdef NDEBUG
#else
        if( !prt_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        /* Display upper hex digit.
         */
        wrkchr = (char)((chr_out >> 4) & 0x0F);
        wrkchr = (char)(wrkchr<10 ? wrkchr+'0' : wrkchr+'A'-10);
        prt_Putc( cbp, wrkchr );
        
        /* Display lower hex digit.
         */
        wrkchr = (char)(chr_out & 0x0F);
        wrkchr = (char)(wrkchr<10 ? wrkchr+'0' : wrkchr+'A'-10);
        prt_Putc( cbp, wrkchr );
        
        /* Return to caller.
         */
    }
    
    
    
    
    //---------------------------------------------------------------
    //                         H e x  L i n e
    //---------------------------------------------------------------

    void            prt_HexLine(
        PRT_DATA		*cbp,
        uint8_t         *obj,
        uint16_t        len,
        uint32_t        off
    )
    {
        int             i;
        int             j;
        char            wrkchr;
        bool            SaveDln;
        
        /* Do Initialization.
         */
#ifdef NDEBUG
#else
        if( !prt_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        SaveDln = cbp->prtdln;
        cbp->prtdln = false;
        
        /*  Display the line.
         */
        for( i=0; i<4; i++ ) {
            prt_HexChr( cbp, (uint8_t)(off >> ((3-i)*8)) );
        }
        prt_Putc( cbp, ' ' );
        for( i=0; i<8; i++ ) {
            prt_Putc( cbp, ' ' );
            if( i == 4 )
                prt_Putc( cbp, ' ' );
            for(j=0; j<4; j++) {
                if( (4*i+j) < len )
                    prt_HexChr( cbp, obj[(4*i)+j] );
                else {
                    prt_Putc( cbp, ' ' );
                    prt_Putc( cbp, ' ' );
                }
            }
        }
        prt_Putc( cbp, ' ' );
        prt_Putc( cbp, ' ' );
        prt_Putc( cbp, '*' );
        for( i=0; i<32; i++ ) {
            if( i == 16 )
                prt_Putc( cbp, ' ' );
            wrkchr = (char)(obj[i] & 0x7F);
            if (wrkchr == 0x7F)
                wrkchr = '.';
            if (wrkchr < ' ')
                wrkchr = '.';
            if( i < len )
                prt_Putc( cbp, wrkchr );
            else {
                prt_Putc( cbp, ' ' );
            }
        }
        prt_Putc( cbp, '*' );
        prt_Putc( cbp, '\n' );
        
        /* Return to caller.
         */
        cbp->prtdln = SaveDln;
    }
    



    //---------------------------------------------------------------
    //                          I n i t
    //---------------------------------------------------------------

    PRT_DATA *      prt_Init(
        PRT_DATA        *this,
        int             prttyp,
        char            *lstfil
    )
    {
        int             i;
        
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        
        this = obj_Init( this, obj_getSize(this), OBJ_IDENT_PRT );
        if (OBJ_NIL == this) {
            return OBJ_NIL;
        }
        this->pSuperVtbl = obj_getVtbl(this);
        obj_setVtbl(this, &prt_Vtbl);
        
#ifdef  CPM
        strcpy( this->lstnam, "LST:" );/* Default List Name */
#endif
#if defined(MSDOS_ENV) || defined(OS2_ENV) || defined(OS2V2_ENV)
        strcpy( this->lstnam, "PRN" );/* Default List Name */
#endif
        this->pagsiz = 88;          /* Lines per Page */
        this->colmax = 141;         /* Number of Columns on a Page */
        this->hdrsiz = 6;           /* Number of Lines in Page Header */
        this->tlrsiz = 6;           /* Number of lines in Page Trailer */
        this->offhdr = 3;           /* Header Offset */
        this->offtlr = 2;           /* Trailer Offset */
        this->offset = 8;           /* Column Offset on Page */
        this->curpag = 0;           /* Current Page Number */
        this->curlin = 0;           /* Current Line Number */
        this->curcol = 0;           /* Current Column Number */
        this->curdln = 0;           /* Current Detail Line Number */
        this->dfttab = 4;           /* Default Tab Columns */
        this->offlin = false;       /* True = Offset done for this line */
        this->prtint = false;       /* True = Printing was interrupted */
        this->prtdln = false;       /* True = display line number */
        this->format = true;        /* True = display header/trailer */
        this->prthdr = true;        /* True = need to print a header */
        this->prntyp = 1;           /* Printer Type - Laserjet */
        
        /* Setup the input parameters.
         */
        if( prttyp )
            this->prntyp = prttyp - 1;
        if( lstfil == NULL )
            ;
        else
            strcpy(this->lstnam, lstfil);
        for( i=0; i<3; i++ ) {
            this->curhdr[i] = NULL;
            this->curtlr[i] = NULL;
        }
        
        /* Setup defaults by printer type.
         */
        switch( this->prntyp ) {
            case    0:              /*** Simple Printer ***/
                break;
            case    1:              /*** LaserJet ***/
                this->offset = 8;
                break;
            case    2:              /*** DeskJet ***/
                this->offset = 6;
        }
        
        if( (this->pList = fopen( this->lstnam, "w" )) == NULL ) {
            fprintf( stderr, "Fatal - could not open Output File %s.\n",
                    this->lstnam );
            exit( 1 );
        }
        
        /* Perform initialization. */
        if( !this->format ) {
            this->hdrsiz = 4;
            this->tlrsiz = 4;
        }
        
        /* Setup HP Deskjet for output.
         */
        switch(this->prntyp) {
            case    0:                          /*** Simple Printer ***/
                break;
            case    1:                          /*** LaserJet ***/
                if( this->offset == 0 )
                    this->offset = 8;
                fprintf(this->pList, "\033E" );           /* Reset Printer */
                fprintf(this->pList, "\033(s16.67H" );    /* Compressed Print */
                fprintf(this->pList, "\033&l4.8C" );      /* 10 lines per inch */
                fprintf(this->pList, "\033&l3E" );        /* Top Margin = 3 */
                fprintf(this->pList, "\033&l0L" );        /* Disable Perf Skip */
                this->pagsiz = 109;                       /* Lines per Page */
                break;
            case    2:                          /*** DeskJet ***/
                if( this->offset == 0 )
                    this->offset = 6;
                fprintf(this->pList, "\033E" );           /* Reset Printer */
                fprintf(this->pList, "\033(s0Q" );        /* Select Draft Quality. */
                fprintf(this->pList, "\033(s16.67H" );    /* Default to Compressed Print. */
                fprintf(this->pList, "\033&l4.8C" );      /* Set 10 lines per inch. */
                fprintf(this->pList, "\033&l0L" );        /* Disable Perf Skip */
                this->pagsiz = 109;                       /* Lines per Page */
        }
        
    #ifdef NDEBUG
    #else
        if( !prt_Validate(this) ) {
            DEBUG_BREAK();
            return OBJ_NIL;
        }
        //BREAK_NOT_BOUNDARY4(&this->thread);
    #endif

        return this;
    }

     

    //---------------------------------------------------------------
    //                       I s E n a b l e d
    //---------------------------------------------------------------
    
    void            prt_Printf(
        PRT_DATA        *cbp,
        const
        char			*fmt,
        ...
    )
    {
        va_list         arg_ptr;
        char            *str;
        char            *ptr;
        
        /* Do Initialization.
         */
#ifdef NDEBUG
#else
        if( !prt_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        str = (char *)mem_Malloc( 512 );
        if( str == NULL )
            return;
        va_start( arg_ptr, fmt );
        vsprintf( str, fmt, arg_ptr );
        va_end( arg_ptr );
        ptr = str;
        while( *ptr ) {
            prt_Putc( cbp, *ptr );
            ++ptr;
        }
        mem_Free( str );
        str = NULL;
        
    }
    
    
    
    void            prt_Putc(
        PRT_DATA        *cbp,
        char            outchr
    )
    {
        
        /* Do Initialization.
         */
#ifdef NDEBUG
#else
        if( !prt_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        
        if( cbp->prthdr ) {
            prt_header( cbp );
            cbp->prthdr = true;
        }
        
        if( (cbp->curcol == 0) && cbp->offset )
            prt_Offset( cbp, true );
        
        if( outchr == '\f' ) {
            prt_trailer( cbp );
            cbp->prthdr = true;
            return;
        }
        prt_fputc( cbp, outchr );
        if( outchr == '\n' ) {
            if( cbp->curlin >= (cbp->pagsiz - cbp->tlrsiz) ) {
                prt_trailer( cbp );
                cbp->prthdr = true;
            }
        }
        
    }
    
    
    
    void            prt_setHeader(
        PRT_DATA        *cbp,
        uint16_t		hdrnum,
        const
        char			*fmt,
        ...
    )
    {
        va_list     arg_ptr;
        char        *str;
        char        *ptr;
        
        /* Do Initialization.
         */
#ifdef NDEBUG
#else
        if( !prt_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        if( (hdrnum <= 0) || (hdrnum > 3) )
            return;
        if( fmt == NULL ) {
            cbp->curhdr[hdrnum-1] = NULL;
            return;
        }
        
        str = (char *)mem_Malloc( 512 );
        if( str == NULL )
            return;
        va_start( arg_ptr, fmt );
        vsprintf( str, fmt, arg_ptr );
        va_end( arg_ptr );
        ptr = NULL;
        switch( hdrnum ) {
            case    1:
                ptr = cbp->hdr1;
                break;
            case    2:
                ptr = cbp->hdr2;
                break;
            case    3:
                ptr = cbp->hdr3;
                break;
        }
        cbp->curhdr[hdrnum-1] = ptr;
        strcpy( cbp->curhdr[hdrnum-1], str);
        mem_Free( str );
        
    }
    
    

    void            prt_setTrailer(
        PRT_DATA        *cbp,
        uint16_t		hdrnum,
        const
        char			*fmt,
        ...
    )
    {
        va_list     arg_ptr;
        char        *str;
        char        *ptr;
        
        /* Do Initialization.
         */
#ifdef NDEBUG
#else
        if( !prt_Validate( cbp ) ) {
            DEBUG_BREAK();
            return;
        }
#endif
        if( (hdrnum <= 0) || (hdrnum > 3) )
            return;
        if( fmt == NULL ) {
            cbp->curhdr[hdrnum-1] = NULL;
            return;
        }
        
        str = (char *)mem_Malloc( 512 );
        if( str == NULL )
            return;
        va_start( arg_ptr, fmt );
        vsprintf( str, fmt, arg_ptr );
        va_end( arg_ptr );
        ptr = NULL;
        switch( hdrnum ) {
            case    1:
                ptr = cbp->tlr1;
                break;
            case    2:
                ptr = cbp->tlr2;
                break;
            case    3:
                ptr = cbp->tlr3;
                break;
        }
        cbp->curhdr[hdrnum-1] = ptr;
        strcpy( cbp->curhdr[hdrnum-1], str);
        mem_Free( str );
        
    }
    
    
    
    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            prt_Validate(
        PRT_DATA      *cbp
    )
    {
        if( cbp ) {
            if ( obj_IsKindOf(cbp,OBJ_IDENT_PRT) )
                ;
            else
                return false;
        }
        else
            return false;
        if( !(obj_getSize(cbp) >= sizeof(PRT_DATA)) )
            return false;

        // Return to caller.
        return true;
    }
    #endif


    
    
    
#ifdef	__cplusplus
}
#endif


