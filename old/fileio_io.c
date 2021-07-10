// vi: nu:noai:ts=4:sw=4

//	I/O Interface 'fileio'
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




//#define			FILEIO_OBJECT_C	    1
#include        <fileio_internal.h>
#ifdef  FILEIO_SINGLETON
#include        <psxLock.h>
#endif



//===========================================================
//                  Object Definition
//===========================================================

static
const
OBJ_INFO        fileio_IO_Info;


static
IO_VTBL         fileio_IO_Vtbl;


static
ERESULT         fileio_IO_Close(OBJ_ID);


static
ERESULT         fileio_IO_Flush(OBJ_ID);


static
int32_t         fileio_IO_Read(OBJ_ID, uint8_t *, int32_t);


static
off_t           fileio_IO_Seek(OBJ_ID, off_t, uint8_t);


static
off_t           fileio_IO_Tell(OBJ_ID);


bool            fileio_IO_Validate(
    IO_INTERFACE    *this
);


static
int32_t         fileio_IO_Write(OBJ_ID, uint8_t *, int32_t);


static
uint16_t        fileio_IO_WhoAmI(
    void
);




    //-----------------------------------------------------------
    //                  Object Methods
    //-----------------------------------------------------------



    static
    IO_VTBL         fileio_IO_Vtbl;




    //===============================================================
    //                      P r o p e r t i e s
    //===============================================================

    //---------------------------------------------------------------
    //                          V t b l
    //---------------------------------------------------------------

    IO_VTBL * fileio_IO_getVtbl (
        void
    )
    {
        return &fileio_IO_Vtbl;
    }



    //===============================================================
    //                          M e t h o d s
    //===============================================================


    //---------------------------------------------------------------
    //                          C l o s e
    //---------------------------------------------------------------

    ERESULT         fileio_IO_Close (
        OBJ_ID          objId
    )
    {
        FILEIO_DATA     *this = IO_INTERFACE_DATA(FILEIO_DATA,objId,IO);
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!fileio_IO_Validate(objId)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        eRc = fileio_Close(this, false);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                          F l u s h
    //---------------------------------------------------------------

    ERESULT         fileio_IO_Flush (
        OBJ_ID          objId
    )
    {
        //FILEIO_DATA    *this = IO_INTERFACE_DATA(FILEIO_DATA,objId,IO);
        ERESULT         eRc = ERESULT_SUCCESS;
        
        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!fileio_IO_Validate(objId)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        //eRc = fileio_Flush(this);
        
        // Return to caller.
        return eRc;
    }



    //---------------------------------------------------------------
    //                     I s  K i n d  O f
    //---------------------------------------------------------------

    static
    bool            fileio_IO_IsKindOf(
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
    void *          fileio_IO_QueryInfo(
        OBJ_ID          objId,
        uint32_t        type,
        void            *pData
    )
    {
        FILEIO_DATA    *this = IO_INTERFACE_DATA(FILEIO_DATA,objId,IO);
        const
        char            *pStr = pData;
        
        if (OBJ_NIL == this) {
            return NULL;
        }
        
        switch (type) {
          
            case OBJ_QUERYINFO_TYPE_CLASS_OBJECT:
                return fileio_Class( );
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
                            return (void *)&fileio_IO_Info;
                        }
                        break;
                        
                    default:
                        break;
                }
                break;
                
            case OBJ_QUERYINFO_TYPE_INFO:
                return (void *)&fileio_IO_Info;
                break;
                
            case OBJ_QUERYINFO_TYPE_METHOD:
                switch (*pStr) {
                        
                    case 'C':
                        if (str_Compare("Close", (char *)pStr) == 0) {
                            return fileio_IO_Close;
                        }
                        break;
                        
                     case 'W':
                        if (str_Compare("WhoAmI", (char *)pStr) == 0) {
                            return fileio_IO_WhoAmI;
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

    int32_t         fileio_IO_Read (
        OBJ_ID          objId,
        uint8_t         *pBuffer,
        int32_t         size
    )
    {
        FILEIO_DATA     *this = IO_INTERFACE_DATA(FILEIO_DATA,objId,IO);
        ERESULT         eRc = ERESULT_SUCCESS;
        uint32_t        amt =0;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!fileio_IO_Validate(objId)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        eRc = fileio_Read(this, size, pBuffer, &amt);
        
        // Return to caller.
        return amt;
    }



    //---------------------------------------------------------------
    //                      R e l e a s e
    //---------------------------------------------------------------

        OBJ_ID          fileio_IO_Release(
            OBJ_ID          objId
        )
        {
            OBJ_DATA        *this = (OBJ_DATA *)IO_INTERFACE_DATA(FILEIO_DATA,objId,IO);

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

        OBJ_ID          fileio_IO_Retain(
            OBJ_ID          objId
        )
        {
            OBJ_DATA        *this = (OBJ_DATA *)IO_INTERFACE_DATA(FILEIO_DATA,objId,IO);

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
    //                          S e e k
    //---------------------------------------------------------------

    off_t           fileio_IO_Seek (
        OBJ_ID          objId,
        off_t           offset,
        uint8_t         type
    )
    {
        FILEIO_DATA     *this = IO_INTERFACE_DATA(FILEIO_DATA,objId,IO);
        //ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!fileio_IO_Validate(objId)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif

        switch (type) {
            case IO_SEEK_SET:
                return (int32_t)fileio_SeekBegin(this, offset);
                break;

            case IO_SEEK_CUR:
                return (int32_t)fileio_SeekCur(this, offset);
                break;

            case IO_SEEK_END:
                return (int32_t)fileio_SeekEnd(this, offset);
                break;

            default:
                break;
        }

        // Return to caller.
        return 0;
    }



    //---------------------------------------------------------------
    //                          T e l l
    //---------------------------------------------------------------

    off_t           fileio_IO_Tell (
        OBJ_ID          objId
    )
    {
        FILEIO_DATA     *this = IO_INTERFACE_DATA(FILEIO_DATA,objId,IO);
        //ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!fileio_IO_Validate(objId)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        return fileio_Tell(this);
    }



    //---------------------------------------------------------------
    //                      V a l i d a t e
    //---------------------------------------------------------------

    #ifdef NDEBUG
    #else
    bool            fileio_IO_Validate(
        IO_INTERFACE    *this
    )
    {

        if (this && (this->pVtbl ==  &fileio_IO_Vtbl))
            return true;
        
        // Return to caller.
        return false;
    }
    #endif



        //---------------------------------------------------------------
        //                      W h o  A m  I
        //---------------------------------------------------------------

    static
    uint16_t		fileio_IO_WhoAmI(
        void
    )
    {
        return OBJ_IDENT_IO;
    }



    //---------------------------------------------------------------
    //                          W r i t e
    //---------------------------------------------------------------

    int32_t         fileio_IO_Write (
        OBJ_ID          objId,
        uint8_t         *pBuffer,
        int32_t         size
    )
    {
        FILEIO_DATA     *this = IO_INTERFACE_DATA(FILEIO_DATA,objId,IO);
        ERESULT         eRc = ERESULT_SUCCESS;

        // Do initialization.
    #ifdef NDEBUG
    #else
        if (!fileio_IO_Validate(objId)) {
            DEBUG_BREAK();
            return ERESULT_INVALID_OBJECT;
        }
    #endif
        
        eRc = fileio_Write(this, size, pBuffer);
        
        // Return to caller.
        return eRc;
    }





//===========================================================
//                  Object Vtbl Definition
//===========================================================

static
IO_VTBL         fileio_IO_Vtbl = {
    {
        &fileio_IO_Info,
        fileio_IO_IsKindOf,
        fileio_IO_Retain,
        fileio_IO_Release,
        fileio_Dealloc,
        fileio_Class,
        fileio_IO_WhoAmI,
        (P_OBJ_QUERYINFO)fileio_IO_QueryInfo,
        NULL,           // (P_OBJ_TOSTRING)fileio_ToDebugString,
        NULL,			// fileio_Enable,
        NULL,			// fileio_Disable,
        NULL,			// (P_OBJ_ASSIGN)fileio_Assign,
        NULL,			// (P_OBJ_COMPARE)fileio_Compare,
        NULL, 			// (P_OBJ_PTR)fileio_Copy,
        NULL, 			// (P_OBJ_PTR)fileio_DeepCopy,
        NULL 			// (P_OBJ_HASH)fileio_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    fileio_IO_Close,
    fileio_IO_Flush,
    fileio_IO_Read,
    fileio_IO_Seek,
    fileio_IO_Tell,
    fileio_IO_Write

};



static
const
OBJ_INFO        fileio_IO_Info = {
    "fatFile",
    "I/O Interface",
    (OBJ_DATA *)&fileio_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&fileio_Vtbl,
    sizeof(FILEIO_DATA)

};





