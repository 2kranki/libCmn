// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Message Log Interface (logInterface) Header
//****************************************************************
/*
 * Program
 *			Message Log Interface (msgInterface)
 * Purpose
 *          The Message Log Interface provides a common interface for
 *          objects that need to issue various informational,
 *          warning and fatal messages.
 *
 *
 * Remarks
 *	1.      N/A
 *
 * History
 *	11/24/2021 Created
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



#ifndef         LOGINTERFACE_H
#define         LOGINTERFACE_H

    
typedef struct log_interface_vtbl_s    {
        OBJ_IUNKNOWN    iVtbl;              // Inherited Vtbl.
        // Properties:
        // Methods:
        void        (*pLogDebug)(OBJ_ID, const char *, ...);
        void        (*pLogFatal)(OBJ_ID, const char *, ...);
        void        (*pLogInfo)(OBJ_ID, const char *, ...);
        void        (*pLogWarn)(OBJ_ID, const char *, ...);
        ERESULT     (*pClose)(OBJ_ID);
    } LOG_INTERFACE_VTBL;
    
    typedef struct log_interface_s    {
        LOG_INTERFACE_VTBL  *pVtbl;
    } LOG_INTERFACE;
    
#define LOG_INTERFACE_DATA(data,obj_id,interface)\
            (data *)(((uint8_t *)objId)-offsetof(data,interface))

#define iLog_Debug(pLog,pFormatA,...)\
        if (pLog)\
            ((LOG_INTERFACE *)(pLog))->pVtbl->pLogDebug(pLog,pFormatA,__VA_ARGS__)
#define iLog_Fatal(pLog,pFormatA,...)\
        if (pLog)\
            ((LOG_INTERFACE *)(pLog))->pVtbl->pLogFatal(pLog,pFormatA,__VA_ARGS__)
#define iLog_Info(pLog,pFormatA,...)\
        if (pLog)\
            ((LOG_INTERFACE *)(pLog))->pVtbl->pLogInfo(pLog,pFormatA,__VA_ARGS__)
#define iLog_Warn(pLog,pFormatA,...)\
        if (pLog)\
            ((LOG_INTERFACE *)(pLog))->pVtbl->pLogWarn(pLog,pFormatA,__VA_ARGS__)

#endif  // LOGINTERFACE_H







