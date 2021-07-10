// vi: nu:noai:ts=4:sw=4

//	I/O Interface 'RRDS'
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




//#define			RRDS_OBJECT_C	    1
#include        <RRDS_internal.h>
#ifdef          RRDS_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Object Definition
//===========================================================

static
const
OBJ_INFO        RRDS_IO_Info;


static
IORRDS_VTBL     RRDS_IO_Vtbl;


static
ERESULT         RRDS_IO_Close(OBJ_ID,bool);


static
ERESULT         RRDS_IO_Flush(OBJ_ID);


static
ERESULT         RRDS_IO_Read(OBJ_ID, uint32_t, uint8_t *);


bool            RRDS_IO_Validate(
    IORRDS_INTERFACE *this
);


static
ERESULT         RRDS_IO_Write(OBJ_ID, uint32_t, uint8_t *);


static
uint16_t        RRDS_IO_WhoAmI(
    void
);




//-----------------------------------------------------------
//                  Object Methods
//-----------------------------------------------------------



    static
    IORRDS_VTBL     RRDS_IO_Vtbl;




    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          V t b l
    //---------------------------------------------------------------

    IORRDS_VTBL * RRDS_IO_getVtbl (
        void
    )
    {
        return &RRDS_IO_Vtbl;
    }



    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          C l o s e
    //---------------------------------------------------------------

    ERESULT         RRDS_IO_Close (
        OBJ_ID          objId,
        bool            fDelete
    )
    {
        RRDS_DATA       *this = IO_INTERFACE_DATA(RRDS_DATA,objId,IO);
        ERESULT         eRc;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!RRDS_IO_Validate(objId)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        eRc = RRDS_Close(this, fDelete);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          F l u s h
    //---------------------------------------------------------------

    ERESULT         RRDS_IO_Flush (
        OBJ_ID          objId
    )
    {
        //RRDS_DATA       *this = IO_INTERFACE_DATA(RRDS_DATA,objId,IO);
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!RRDS_IO_Validate(objId)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        //eRc = RRDS_Flush(this);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                     I s  K i n d  O f
    //---------------------------------------------------------------

    static
    bool            RRDS_IO_IsKindOf(
        uint16_t        classID
    )
    {
        if (OBJ_IDENT_IORRDS == classID) {
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
    void *          RRDS_IO_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        RRDS_DATA       *this = IO_INTERFACE_DATA(RRDS_DATA,objId,IO);
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
        
        switch (type) {
          
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return RRDS_Class( );
                break;
                
            // Query for an address to specific data within the object.
            // This should be used very sparingly since it breaks the
            // object's encapsulation.
            case OBJ_QUERYINFO_TYPE_DATA_PTR:
                switch (*pStr) {
     
                    case 'I':
                        if (str_Compare("Info", (char *)pStr) == 0) {
                            return (void *)&RRDS_IO_Info;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)&RRDS_IO_Info;
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'C':
                        if (str_Compare("Close", (char *)pStr) == 0) {
                            return RRDS_IO_Close;
                        }
                        break;
                        
                     case 'W':
                        if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                            return RRDS_IO_WhoAmI;
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

    ERESULT         RRDS_IO_Read (
        OBJ_ID          objId,
        uint32_t        rcdNo,
        uint8_t         *pBuffer
    )
    {
        RRDS_DATA       *this = IO_INTERFACE_DATA(RRDS_DATA,objId,IO);
        ERESULT         eRc;
        
        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!RRDS_IO_Validate(objId)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        eRc = RRDS_RecordRead(this, rcdNo, pBuffer);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                      R e l e a s e
    //---------------------------------------------------------------

        OBJ_ID          RRDS_IO_Release(
            OBJ_ID          objId
        )
        {
            RRDS_DATA       *this = IO_INTERFACE_DATA(RRDS_DATA,objId,IO);

            if (OBJ_NIL == this) {
                return OBJ_NIL;
            }
            if (NULL == obj_getVtbl(this)) {
                return OBJ_NIL;
            }
            if (obj_getVtbl(this)->pRelease) {
                obj_getVtbl(this)->pRelease(this);
            }
            return objId;
        }



        //---------------------------------------------------------------
        //                      R e t a i n
        //---------------------------------------------------------------

        OBJ_ID          RRDS_IO_Retain(
            OBJ_ID          objId
        )
        {
            RRDS_DATA       *this = IO_INTERFACE_DATA(RRDS_DATA,objId,IO);

            if (OBJ_NIL == this) {
                return OBJ_NIL;
            }
            if (NULL == obj_getVtbl(this)) {
                return OBJ_NIL;
            }
            if (obj_getVtbl(this)->pRetain) {
                obj_getVtbl(this)->pRetain(this);
            }
            return objId;
        }



    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            RRDS_IO_Validate(
        IORRDS_INTERFACE *this
    )
    {

        if (this && (this->pVtbl ==  &RRDS_IO_Vtbl))
            return true;
        
        // Return to caller.
        return false;
    }
    #endif



        //---------------------------------------------------------------
        //                      W h o  A m  I
        //---------------------------------------------------------------

    static
    uint16_t		RRDS_IO_WhoAmI(
        void
    )
    {
        return OBJ_IDENT_IORRDS;
    }



    //---------------------------------------------------------------
    //                          W r i t e
    //---------------------------------------------------------------

    ERESULT         RRDS_IO_Write (
        OBJ_ID          objId,
        uint32_t        rcdNo,
        uint8_t         *pBuffer
    )
    {
        RRDS_DATA       *this = IO_INTERFACE_DATA(RRDS_DATA,objId,IO);
        ERESULT         eRc;
        
        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!RRDS_IO_Validate(objId)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        eRc = RRDS_RecordWrite(this, rcdNo, pBuffer);
        
        // Return to caller.
        return eRc;
    }





//===========================================================
//                  Object Vtbl Definition
//===========================================================

static
IORRDS_VTBL     RRDS_IO_Vtbl = {
    {
        &RRDS_IO_Info,
        RRDS_IO_IsKindOf,
        RRDS_IO_Retain,
        RRDS_IO_Release,
        RRDS_Dealloc,
        RRDS_Class,
        RRDS_IO_WhoAmI,
        (P_OBJ_QUERYINFO)RRDS_IO_QueryInfo,
        NULL,           // (P_OBJ_TOSTRING)RRDS_ToDebugString,
        NULL,			// RRDS_Enable,
        NULL,			// RRDS_Disable,
        NULL,			// (P_OBJ_ASSIGN)RRDS_Assign,
        NULL,			// (P_OBJ_COMPARE)RRDS_Compare,
        NULL, 			// (P_OBJ_PTR)RRDS_Copy,
        NULL, 			// (P_OBJ_PTR)RRDS_DeepCopy,
        NULL 			// (P_OBJ_HASH)RRDS_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    RRDS_IO_Close,
    RRDS_IO_Flush,
    RRDS_IO_Read,
    RRDS_IO_Write

};



static
const
OBJ_INFO        RRDS_IO_Info = {
    "RRDS",
    "I/O Interface",
    (OBJ_DATA *)&RRDS_ClassObj,
    (OBJ_DATA *)&lru_ClassObj,
    (OBJ_IUNKNOWN *)&RRDS_Vtbl,
    sizeof(RRDS_DATA)

};





