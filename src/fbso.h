// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//                  Blocked File Output (fbso) Header
//****************************************************************
/*
 * Program
 *			Blocked File Output (fbso)
 * Purpose
 *			This object provides a standard way of writing
 *          file routines to disk. Its advantage over just
 *          using stream I/O is that you have the additional
 *          properties associated with the file such as its
 *          path within this object.
 *
 * Remarks
 *	1.      Writing Little/Big Endian numbers to a file in various
 *          sizes is supported. The default is little endian,
 *          but that can be changed via a property.
 *
 * History
 *	07/01/2015 Generated
 *  09/20/2016 Added PutU8, PutU16, PutU24, PutU32.
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





#include        <cmn_defs.h>
#include        <Path.h>


#ifndef         FBSO_H
#define         FBSO_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct fbso_data_s	FBSO_DATA;

    typedef struct fbso_vtbl_s	{
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Put other methods below this as pointers and add their
        // method names to the vtbl definition in fileio_object.c.
        // Properties:
        // Methods:
        //bool        (*pIsEnabled)(FILEIO_DATA *);
    } FBSO_VTBL;
    
    



    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    FBSO_DATA *     fbso_Alloc(
        void
    );
    
    
    FBSO_DATA *     fbso_New(
        PATH_DATA       *pPath
    );
    
    
    FBSO_DATA *     fbso_NewStd(
        FILE            *pFileOut
    );
    

    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    bool            fbso_setBigEndian(
        FBSO_DATA       *this,
        bool            value
    );
    
    
    PATH_DATA *     fbso_getPath(
        FBSO_DATA		*this
    );
    
    bool            fbso_setPath(
        FBSO_DATA		*this,
        PATH_DATA       *pValue
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    ERESULT         fbso_ChangeBufferSize(
        FBSO_DATA		*this,
        uint16_t        newBufferSize
    );
    

    ERESULT         fbso_Close(
        FBSO_DATA		*this
    );
    
    
    ERESULT         fbso_Flush(
        FBSO_DATA		*this
    );
    
    
    // Init() creates the FBSO object and opens the file path given
    // overwriting a previous file if present.
    FBSO_DATA *     fbso_Init(
        FBSO_DATA       *this,
        PATH_DATA       *pPath
    );


    // InitConCat() creates the FBSO object and opens the file path
    // given. If the file existed already, then the file is opened
    // to the end of it and ready for further concatenation.
    FBSO_DATA *     fbso_InitConCat(
        FBSO_DATA       *this,
        PATH_DATA       *pPath
    );
    
    
    ERESULT         fbso_Print(
        FBSO_DATA		*this,
        const
        char            *pFormat,
        ...
    );
    
    
    /*!
     Put the given data into the file.
     @param     this    object pointer
     @param     value   data to be written to the file
     @return    If successful, ERESULT_SUCCESS. Otherwise, an
                 ERESULT_* error code.
     */
    ERESULT         fbso_PutU8(
        FBSO_DATA		*this,
        const
        uint8_t         value
    );
    
    
    /*!
     Put the given data into the file in multiple bytes using the
     object's endian type to determine the order.
     @param     this    object pointer
     @param     value   data to be written to the file
     @return    If successful, ERESULT_SUCCESS. Otherwise, an
                ERESULT_* error code.
     */
    ERESULT         fbso_PutU16(
        FBSO_DATA		*this,
        const
        uint16_t        value
    );
    
    
    /*!
     Put the given data into the file in multiple bytes using the
     object's endian type to determine the order.
     @param     this    object pointer
     @param     value   data to be written to the file
     @return    If successful, ERESULT_SUCCESS. Otherwise, an
     ERESULT_* error code.
     */
    ERESULT         fbso_PutU24(
        FBSO_DATA		*this,
        const
        uint32_t        value
    );
    
    
    /*!
     Put the given data into the file in multiple bytes using the
     object's endian type to determine the order.
     @param     this    object pointer
     @param     value   data to be written to the file
     @return    If successful, ERESULT_SUCCESS. Otherwise, an
     ERESULT_* error code.
     */
    ERESULT         fbso_PutU32(
        FBSO_DATA		*this,
        const
        uint32_t        value
    );
    
    
    ERESULT         fbso_Putc(
        FBSO_DATA		*this,
        char            chr
    );
    
    
    ERESULT         fbso_Puts(
        FBSO_DATA		*this,
        const
        char            *pStr
    );
    

    ERESULT         fbso_Putwc(
        FBSO_DATA		*this,
        W32CHR_T        chr
    );
    
    
    /*!
     Write the given string to the file without any
     trailing NUL.
     @param     this    object pointer
     @param     pValue  data to be written to the file
     @return    If successful, ERESULT_SUCCESS. Otherwise, an
                ERESULT_* error code.
     */
    ERESULT         fbso_PutAStr(
        FBSO_DATA		*this,
        ASTR_DATA       *pValue
    );
    
    
    ERESULT         fbso_Tell(
        FBSO_DATA		*this,
        long            *pFileOffset
    );



#ifdef	__cplusplus
}
#endif

#endif	/* FBSO_H */

