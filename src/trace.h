// vi:nu:et:sts=4 ts=4 sw=4

//****************************************************************
//          Trace support (trace) Header
//****************************************************************
/*
 * Program
 *				Trace support (trace)
 * Purpose
 *				This object provides a standardized way of handling
 *              a separate trace to run things without complications
 *              of interfering with the main trace. A trace may be 
 *              called a trace on other O/S's.
 *
 * Remarks
 *	1.      Using this object allows for testable code, because a
 *          function, TaskBody() must be supplied which is repeatedly
 *          called on the internal trace. A testing unit simply calls
 *          the TaskBody() function as many times as needed to test.
 *
 * History
 *	06/17/2015 Generated
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


#ifndef         TRACE_H
#define         TRACE_H



#ifdef	__cplusplus
extern "C" {
#endif
    

    //****************************************************************
    //* * * * * * * * * * * *  Data Definitions  * * * * * * * * * * *
    //****************************************************************


    typedef struct trace_data_s	TRACE_DATA;


#ifdef NDEBUG
#   define  TRC_FLAG(flag,desc,...)     /**/
#   define  TRC_FLAGS(flag,desc,...)    /**/
#   define  TRC_FLAGSF(flag,desc,...)   /**/
#   define  TRC_OBJ(cbp,desc,...)       /**/
#   define  TRC_OBJ_EXEC(cbp,exec)      /**/
#   define  TRC(desc,...)               /**/
#else
#   define  TRC_FLAG(flag,desc,...)\
    trace_FlagA(trace_Shared(),flag,desc,## __VA_ARGS__)
#   define  TRC_FLAGS(flag,desc,...)\
    do {\
        if (trace_FlagGet(trace_Shared(),flag)) {\
            trace_TraceA(trace_Shared(),desc,## __VA_ARGS__);\
        }\
    } while(0)
#   define  TRC_FLAGSF(flag,desc,...)\
    do {\
        if (trace_FlagGet(trace_Shared(),flag)) {\
            trace_TraceFuncA(trace_Shared(),__func__,desc,## __VA_ARGS__);\
        }\
    } while(0)
#   define  TRC_OBJ(cbp,desc,...)\
    do {\
        if (obj_Trace(cbp) || obj_Trace(((OBJ_DATA *)cbp)->pVtbl->pClassObject())) {\
            trace_TraceA(trace_Shared(),desc,## __VA_ARGS__);\
        }\
    } while(0)
#   define  TRC_OBJ_EXEC(cbp,exec)\
    do {\
        if (obj_Trace(cbp) || obj_Trace(((OBJ_DATA *)cbp)->pVtbl->pClassObject())) {\
            exec;\
        }\
    } while(0)
#   define  TRC(desc,...)\
    trace_TraceA(trace_Shared(),desc,## __VA_ARGS__)
#endif

    

    /****************************************************************
    * * * * * * * * * * *  Routine Definitions	* * * * * * * * * * *
    ****************************************************************/


    //---------------------------------------------------------------
    //                      *** Class Methods ***
    //---------------------------------------------------------------

    /* Alloc() allocates an area large enough for the trace including
     * the stack.  If 0 is passed for the stack size, then an ap-
     * propriate default is chosen. The stack size is passed to Init()
     * via obj_misc1.
     */
    TRACE_DATA *    trace_Alloc(
        void
    );
    
    
    TRACE_DATA *    trace_Shared(
        void
    );
    
    
    bool            trace_SharedReset(
        void
    );
    
    
    

    //---------------------------------------------------------------
    //                      *** Properties ***
    //---------------------------------------------------------------

    FILE *          trace_getStream(
        TRACE_DATA     *this
    );
    
    bool            trace_setStream(
        TRACE_DATA      *this,
        FILE            *pValue
    );
    
    
    bool            trace_getTrace(
        TRACE_DATA     *this
    );
    
    bool            trace_setTrace(
        TRACE_DATA      *this,
        bool            value
    );
    
    

    
    //---------------------------------------------------------------
    //                      *** Methods ***
    //---------------------------------------------------------------

    void            trace_FlagA(
        TRACE_DATA		*this,
        bool			flg,
        const
        char			*pszFormat,
        ...
    );
    
    
    ERESULT         trace_FlagSet(
        TRACE_DATA		*this,
        uint16_t        index,
        bool            fValue
    );
    
    
    TRACE_DATA *     trace_Init(
        TRACE_DATA      *this,
        const
        char            *pszFilePath
    );


    /*!
     Initialize the object with a supplied routine and its object pointer. 
     The function overrides the file/stream file output if it is present.
     @param     pLineOut is a pointer to a function that accepts the line of
                data and does something with it.
     @param     pLineOutObj is the object pointer to be passed to the pLineOut
                function when it is called.
     @return    If successful, a TRACE_DATA pointer otherwise OBJ_NIL
     */
    TRACE_DATA *    trace_InitLineOut(
        TRACE_DATA      *this,
        void            (*pLineOut)(
            OBJ_ID          this,
            const
            char            *pszData
        ),
        OBJ_ID          pLineOutObj
    );
    
    
    /*!
     Initialize the object with the given open file stream. The stream is
     used to output the trace data. It is not closed when this object is
     released.
     @param     pTraceFile stream file pointer. If NULL, then stderr will
                be used.
     @return    If successful, a TRACE_DATA pointer otherwise OBJ_NIL
     */
    TRACE_DATA *     trace_InitStream(
        TRACE_DATA      *this,
        FILE            *pTraceFile
    );
    
    
    void            trace_LineOut(
        TRACE_DATA      *this,
        const
        char            *pszData
    );
    
    
    void            trace_TraceA(
        TRACE_DATA		*this,
        const
        char			*pszFormat,
        ...
    );
    
    
    void            trace_TraceFuncA(
        TRACE_DATA		*this,
        const
        char			*pszFunc,           // __func__
        const
        char			*pszFormat,
        ...
    );
    
    
    
    
#ifdef	__cplusplus
}
#endif

#endif	/* TRACE_H */

