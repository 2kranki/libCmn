// vi: nu:noai:ts=4:sw=4

//	I/O Interface 'memrrds'
//	Generated 11/02/2018 09:11:58


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




//#define			MEMRRDS_OBJECT_C	    1
#include        <memrrds_internal.h>
#ifdef  MEMRRDS_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Object Definition
//===========================================================

static
const
OBJ_INFO        memrrds_IO_Info;


static
IORRDS_VTBL     memrrds_IO_Vtbl;


static
ERESULT         memrrds_IO_Close(OBJ_ID,bool);


static
ERESULT         memrrds_IO_Flush(OBJ_ID);


static
ERESULT         memrrds_IO_Read(OBJ_ID, uint32_t, uint8_t *);


bool            memrrds_IO_Validate(
    IORRDS_INTERFACE    *this
);


static
ERESULT         memrrds_IO_Write(OBJ_ID, uint32_t, uint8_t *);


static
uint16_t        memrrds_IO_WhoAmI(
    void
);




//-----------------------------------------------------------
//                  Object Methods
//-----------------------------------------------------------



    static
    IORRDS_VTBL     memrrds_IO_Vtbl;




    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          V t b l
    //---------------------------------------------------------------

    IORRDS_VTBL * memrrds_IO_getVtbl (
        void
    )
    {
        return &memrrds_IO_Vtbl;
    }



    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          C l o s e
    //---------------------------------------------------------------

    ERESULT         memrrds_IO_Close (
        OBJ_ID          objId,
        bool            fDelete
    )
    {
        //MEMRRDS_DATA    *this = IO_INTERFACE_DATA(MEMRRDS_DATA,objId,IO);
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!memrrds_IO_Validate(objId)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        //eRc = memrrds_Close(this, fDelete);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          F l u s h
    //---------------------------------------------------------------

    ERESULT         memrrds_IO_Flush (
        OBJ_ID          objId
    )
    {
        //MEMRRDS_DATA    *this = IO_INTERFACE_DATA(MEMRRDS_DATA,objId,IO);
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!memrrds_IO_Validate(objId)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        //eRc = memrrds_Flush(this);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                     I s  K i n d  O f
    //---------------------------------------------------------------

    static
    bool            memrrds_IO_IsKindOf(
        uint16_t        classID
    )
    {
        if (OBJ_IDENT_IO == classID) {
            return true;
        }
        if (OBJ_IDENT_OBJ == classID) {
            return true;
        }
        return false;
    }



    //---------------------------------------------------------------
    //                     Q u e r y  I n f o
    //---------------------------------------------------------------

    static
    void *          memrrds_IO_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        MEMRRDS_DATA    *this = IO_INTERFACE_DATA(MEMRRDS_DATA,objId,IO);
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
        
        switch (type) {
          
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return memrrds_Class( );
                break;
                
            // Query for an address to specific data within the object.
            // This should be used very sparingly since it breaks the
            // object's encapsulation.
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'D':
                        if (str_Compare("DirR", (char *)pStr) == 0) {
                            return this;
                        }
                        break;
                        
                    case 'I':
                        if (str_Compare("Info", (char *)pStr) == 0) {
                            return (void *)&memrrds_IO_Info;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)&memrrds_IO_Info;
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'C':
                        if (str_Compare("Close", (char *)pStr) == 0) {
                            return memrrds_IO_Close;
                        }
                        break;
                        
                     case 'W':
                        if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                            return memrrds_IO_WhoAmI;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            default:
                break;
        }
        
        return NULL;
    }




    //---------------------------------------------------------------
    //                          R e a d
    //---------------------------------------------------------------

    ERESULT         memrrds_IO_Read (
        OBJ_ID          objId,
        uint32_t        rcdNo,
        uint8_t         *pBuffer
    )
    {
        MEMRRDS_DATA    *this = IO_INTERFACE_DATA(MEMRRDS_DATA,objId,IO);
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!memrrds_IO_Validate(objId)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        eRc = memrrds_Read(this, rcdNo, pBuffer);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                      R e l e a s e
    //---------------------------------------------------------------

        OBJ_ID          memrrds_IO_Release(
            OBJ_ID          objId
        )
        {
            OBJ_DATA        *this = (OBJ_DATA *)IO_INTERFACE_DATA(MEMRRDS_DATA,objId,IO);

            if (OBJ_NIL == this) {
                return OBJ_NIL;
            }
            if (NULL == this->pVtbl) {
                return OBJ_NIL;
            }
            if (this->pVtbl->pRelease) {
                this->pVtbl->pRelease(this);
            }
            return objId;
        }



        //---------------------------------------------------------------
        //                      R e t a i n
        //---------------------------------------------------------------

        OBJ_ID          memrrds_IO_Retain(
            OBJ_ID          objId
        )
        {
            OBJ_DATA        *this = (OBJ_DATA *)IO_INTERFACE_DATA(MEMRRDS_DATA,objId,IO);

            if (OBJ_NIL == this) {
                return OBJ_NIL;
            }
            if (NULL == this->pVtbl) {
                return OBJ_NIL;
            }
            if (this->pVtbl->pRetain) {
                this->pVtbl->pRetain(this);
            }
            return objId;
        }



    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            memrrds_IO_Validate(
        IORRDS_INTERFACE *this
    )
    {

        if (this && (this->pVtbl ==  &memrrds_IO_Vtbl))
            return true;
        
        // Return to caller.
        return false;
    }
    #endif



        //---------------------------------------------------------------
        //                      W h o  A m  I
        //---------------------------------------------------------------

    static
    uint16_t		memrrds_IO_WhoAmI(
        void
    )
    {
        return OBJ_IDENT_IORRDS;
    }



    //---------------------------------------------------------------
    //                          W r i t e
    //---------------------------------------------------------------

    ERESULT         memrrds_IO_Write (
        OBJ_ID          objId,
        uint32_t        rcdNo,
        uint8_t         *pBuffer
    )
    {
        MEMRRDS_DATA    *this = IO_INTERFACE_DATA(MEMRRDS_DATA,objId,IO);
        ERESULT         eRc;
        
        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!memrrds_IO_Validate(objId)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        eRc = memrrds_Write(this, rcdNo, pBuffer);
        
        // Return to caller.
        return eRc;
    }





//===========================================================
//                  Object Vtbl Definition
//===========================================================

static
IORRDS_VTBL     memrrds_IO_Vtbl = {
    {
        &memrrds_IO_Info,
        memrrds_IO_IsKindOf,
        memrrds_IO_Retain,
        memrrds_IO_Release,
        memrrds_Dealloc,
        memrrds_Class,
        memrrds_IO_WhoAmI,
        (P_OBJ_QUERYINFO)memrrds_IO_QueryInfo,
        NULL,           // (P_OBJ_TOSTRING)memrrds_ToDebugString,
        NULL,			// memrrds_Enable,
        NULL,			// memrrds_Disable,
        NULL,			// (P_OBJ_ASSIGN)memrrds_Assign,
        NULL,			// (P_OBJ_COMPARE)memrrds_Compare,
        NULL, 			// (P_OBJ_PTR)memrrds_Copy,
        NULL, 			// (P_OBJ_PTR)memrrds_DeepCopy,
        NULL 			// (P_OBJ_HASH)memrrds_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    memrrds_IO_Close,
    memrrds_IO_Flush,
    memrrds_IO_Read,
    memrrds_IO_Write

};



static
const
OBJ_INFO        memrrds_IO_Info = {
    "memrrds",
    "I/O Interface",
    (OBJ_DATA *)&memrrds_ClassObj,
    (OBJ_DATA *)&blks_ClassObj,
    (OBJ_IUNKNOWN *)&memrrds_Vtbl,
    sizeof(MEMRRDS_DATA)

};





