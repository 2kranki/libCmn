// vi: nu:noai:ts=4:sw=4

//	Class Object Metods and Tables for 'xml'
//	Generated 10/02/2017 10:44:23


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



#define			XML_OBJECT_C	    1
#include        <xml_internal.h>



//-----------------------------------------------------------
//                  Class Object Definition
//-----------------------------------------------------------

struct xml_class_data_s	{
    // Warning - OBJ_DATA must be first in this object!
    OBJ_DATA        super;
    
    // Common Data
    //uint32_t        misc;
};
typedef struct xml_class_data_s XML_CLASS_DATA;




//-----------------------------------------------------------
//                  Class Methods
//-----------------------------------------------------------



static
const
OBJ_INFO        xml_Info;            // Forward Reference



OBJ_ID          xml_Class(
    void
);



static
bool            xml_ClassIsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_XML_CLASS == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ_CLASS == classID) {
       return true;
    }
    return false;
}


static
uint16_t		obj_ClassWhoAmI(
    void
)
{
    return OBJ_IDENT_XML_CLASS;
}


static
const
OBJ_IUNKNOWN    class_Vtbl = {
	&xml_Info,
    xml_ClassIsKindOf,
    obj_RetainNull,
    obj_ReleaseNull,
    NULL,
    xml_Class,
    obj_ClassWhoAmI
};



//-----------------------------------------------------------
//						Class Object
//-----------------------------------------------------------

static
const
XML_CLASS_DATA  xml_ClassObj = {
    {
        (const OBJ_IUNKNOWN *)&class_Vtbl,  // pVtbl
        sizeof(XML_CLASS_DATA),             // cbSize
        OBJ_IDENT_XML_CLASS,                // cbIdent
        0,                                  // cbFlags
        0,                                  // eRc
        1,                                  // cbRetainCount
        {0}                                 // cbMisc
    },
	//0
};



static
bool            xml_IsKindOf(
    uint16_t		classID
)
{
    if (OBJ_IDENT_XML == classID) {
       return true;
    }
    if (OBJ_IDENT_OBJ == classID) {
       return true;
    }
    return false;
}


// Dealloc() should be put into the Internal Header as well
// for classes that get inherited from.
void            xml_Dealloc(
    OBJ_ID          objId
);


OBJ_ID          xml_Class(
    void
)
{
    return (OBJ_ID)&xml_ClassObj;
}


static
uint16_t		xml_WhoAmI(
    void
)
{
    return OBJ_IDENT_XML;
}


const
XML_VTBL     xml_Vtbl = {
    {
        &xml_Info,
        xml_IsKindOf,
        obj_RetainStandard,
        obj_ReleaseStandard,
        xml_Dealloc,
        xml_Class,
        xml_WhoAmI,
        (P_OBJ_QUERYINFO)xml_QueryInfo,
        (P_OBJ_TOSTRING)xml_ToDebugString,
        NULL,			// xml_Enable,
        NULL,			// xml_Disable,
        NULL,			// (P_OBJ_ASSIGN)xml_Assign,
        NULL,			// (P_OBJ_COMPARE)xml_Compare,
        NULL, 			// (P_OBJ_PTR)xml_Copy,
        NULL,           // (P_OBJ_DEEPCOPY)
        NULL 			// (P_OBJ_HASH)xml_Hash,
    },
    // Put other object method names below this.
    // Properties:
    // Methods:
    //xml_IsEnabled,
 
};



static
const
OBJ_INFO        xml_Info = {
    "xml",
    "XML",
    (OBJ_DATA *)&xml_ClassObj,
    (OBJ_DATA *)&obj_ClassObj,
    (OBJ_IUNKNOWN *)&xml_Vtbl
};





