// vi:nu:et:sts=4 ts=4 sw=4
/*
 * File:   hexDataToJSON.c
 *
 * Created on August 27, 2017
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
#include    <hex_internal.h>
#include    <crc.h>




#ifdef	__cplusplus
extern "C" {
#endif
    
    
    
    
    
    
    /****************************************************************
     * * * * * * * * * * *  Internal Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    
    /****************************************************************
     * * * * * * * * * * *  External Subroutines   * * * * * * * * * *
     ****************************************************************/
    
    
    //===============================================================
    //                      *** Class Methods ***
    //===============================================================
    

    ASTR_DATA *     hex_DataToJSON(
        uint32_t        length,
        void            *pData
    )
    {
        char            str[256];
        uint32_t        i;
        int             j;
        ASTR_DATA       *pStr;
        const
        OBJ_INFO        *pInfo;
        //ASTR_DATA       *pWrk;
        char            *pChr;
        char            chrs[12];
        CRC_DATA        *pCrc = OBJ_NIL;
        uint32_t        crc;
        
        pInfo = hex_Vtbl.iVtbl.pInfo;
        
        pStr = AStr_New();
        str[0] = '\0';
        j = snprintf(
                     str,
                     sizeof(str),
                     "{\"objectType\":\"%s\"",
                     pInfo->pClassName
                     );
        AStr_AppendA(pStr, str);
        
        AStr_AppendPrint(pStr, ", \"len\":%d", length);
        
        pCrc = crc_New(CRC_TYPE_IEEE_32);
        crc = crc_AccumBlock(pCrc, length, pData);
        obj_Release(pCrc);
        pCrc = OBJ_NIL;
        AStr_AppendPrint(pStr, ", \"crc\":%d", crc);
        
        AStr_AppendA(pStr, ", \"data\":\"");
        pChr = pData;
        for (i=0; i<length; ++i) {
            chrs[0] = hex_DigitToChrA((*pChr >> 4) & 0x0F);
            chrs[1] = hex_DigitToChrA(*pChr & 0x0F);
            chrs[2] = '\0';
            ++pChr;
            AStr_AppendA(pStr, chrs);
        }
        AStr_AppendA(pStr, "\"");
        
        AStr_AppendA(pStr, "}\n");
        
        return pStr;
    }
    
    
    
    
    
    

    
    
    
    
    
#ifdef	__cplusplus
}
#endif

