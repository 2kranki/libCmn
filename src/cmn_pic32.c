//****************************************************************
//						Common Object Functions			
//****************************************************************
// vi: nu:noai:ts=4:sw=4

/*
 * Todo List
 *  ---         None yet
 * Remarks
 *  1.          None
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



/****************************************************************
* * * * * * * * * * * *  data definitions   * * * * * * * * * * *
****************************************************************/

/* Header File Inclusion */
#include        "cmn_pic32_internal.h"


static
volatile
uint32_t			accum = 0;
static
uint32_t			period = 0;


// CT – Core Timer Interrupt  0  0  IFS0<0>  IEC0<0>  IPC0<4:2>  IPC0<1:0>


// See ct_internal.h for definition.
static
const
CMN_ENTRY       cmn_table[1] = {
//TODO: Needs updating
    {   // ** Port 1 **
        // Interrupt Priorities
        6,
        0,
        (void *)0xBF881090,     /*IPC0*/
        (void *)0xBF881094,     /*IPC0CLR*/
        (void *)0xBF881098,     /*IPC0SET*/
        _IPC0_CTIP_POSITION,
        _IPC0_CTIP_MASK,
        _IPC0_CTIS_POSITION,
        _IPC0_CTIS_MASK,
        
        // Interrupt Flag
        (void *)0xBF881030,     /*IFS0*/
        (void *)0xBF881034,     /*IFS0CLR*/
        (void *)0xBF881038,     /*IFS0SET*/
        _IFS0_CTIF_MASK,
        
        (void *)0xBF881060,     /*IEC0*/
        (void *)0xBF881064,     /*IEC0CLR*/
        (void *)0xBF881068,     /*IEC0SET*/
        _IEC0_CTIE_MASK        
    }
};

static
CMN_DATA        *cmn_index[1] = {
    NULL
};




/* Internal Subroutine Definitions
 */
#ifdef NDEBUG
#else
static
bool			cmn_Validate(
    CMN_DATA        *cbp
);
#endif




/****************************************************************
* * * * * * * * * * *  Internal Subroutines * * * * * * * * * * *
****************************************************************/






/****************************************************************
* * * * * * * * * * *  External Subroutines   * * * * * * * * * *
****************************************************************/


//===============================================================
//                    P r o p e r t i e s
//===============================================================

//**********************************************************
//                          C f g
//**********************************************************

CFG_DATA *      cmn_getCfg(
    CMN_DATA        *cbp
)
{
    
	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif
    
	// Return to caller.
	return( cbp->pCfg );
}


bool            cmn_setCfg(
    CMN_DATA        *cbp,
    CFG_DATA        *pCfg
)
{
    INTERRUPT_STATUS;
    
	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
        return false;
    }
#endif
    
    DISABLE_INTERRUPTS();
    
    cbp->pCfg = pCfg;

    RESTORE_INTERRUPTS;
    
	// Return to caller.
	return true;
}



//**********************************************************
//                          C o n
//**********************************************************

CON_DATA *      cmn_getCon(
    CMN_DATA        *cbp
)
{

	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif

	// Return to caller.
	return( cbp->pCon );
}


bool            cmn_setCon(
    CMN_DATA        *cbp,
    CON_DATA        *pCon
)
{
    INTERRUPT_STATUS;

	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
        return false;
    }
#endif

    DISABLE_INTERRUPTS();

    cbp->pCon = pCon;

    RESTORE_INTERRUPTS;

	// Return to caller.
	return true;
}



//**********************************************************
//                          C t
//**********************************************************

CT_DATA *       cmn_getCt(
    CMN_DATA        *cbp
)
{
    
	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif
    
	// Return to caller.
	return( cbp->pCt );
}


bool            cmn_setCt(
    CMN_DATA        *cbp,
    CT_DATA         *pCt
)
{
    INTERRUPT_STATUS;
    
	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
        return false;
    }
#endif
    
    DISABLE_INTERRUPTS();
    
    cbp->pCt = pCt;
    
    RESTORE_INTERRUPTS;
    
	// Return to caller.
	return true;
}



//**********************************************************
//                          D m a
//**********************************************************

DMA_DATA *      cmn_getDma(
    CMN_DATA        *cbp
)
{
    
	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif
    
	// Return to caller.
	return( cbp->pDma );
}


bool            cmn_setDma(
    CMN_DATA        *cbp,
    DMA_DATA        *pDma
)
{
    INTERRUPT_STATUS;
    
	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
        return false;
    }
#endif
    
    DISABLE_INTERRUPTS();
    
    cbp->pDma = pDma;
    
    RESTORE_INTERRUPTS;
    
	// Return to caller.
	return true;
}



//**********************************************************
//                          M o n
//**********************************************************

MON_DATA *      cmn_getMon(
    CMN_DATA        *cbp
)
{

	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif

	// Return to caller.
	return( cbp->pMon );
}


bool            cmn_setMon(
    CMN_DATA        *cbp,
    MON_DATA        *pMon
)
{
    INTERRUPT_STATUS;

	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
        return false;
    }
#endif

    DISABLE_INTERRUPTS();

    cbp->pMon = pMon;

    RESTORE_INTERRUPTS;

	// Return to caller.
	return true;
}



//**********************************************************
//                        O s c
//**********************************************************

OSC_DATA *      cmn_getOsc(
    CMN_DATA        *cbp
)
{
    
	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif
    
	// Return to caller.
	return( cbp->pOsc );
}


bool            cmn_setOsc(
    CMN_DATA        *cbp,
    OSC_DATA        *pOsc
)
{
    INTERRUPT_STATUS;
    
	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
        return false;
    }
#endif
    
    DISABLE_INTERRUPTS();
    
    cbp->pOsc = pOsc;

    RESTORE_INTERRUPTS;
    
	// Return to caller.
	return true;
}



//**********************************************************
//                      T i m e r 1
//**********************************************************

TIMER_DATA *	cmn_getTimer1(
    CMN_DATA        *cbp
)
{
    
	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif
    
	// Return to caller.
	return( cbp->pTimer1 );
}


bool            cmn_setTimer1(
    CMN_DATA        *cbp,
    TIMER_DATA      *pTimer
)
{
    INTERRUPT_STATUS;
    
	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
        return false;
    }
#endif
    
    DISABLE_INTERRUPTS();
    
    cbp->pTimer1 = pTimer;

    RESTORE_INTERRUPTS;
    
	// Return to caller.
	return true;
}



//**********************************************************
//                          U a r t 2
//**********************************************************

UART_DATA *     cmn_getUart2(
    CMN_DATA        *cbp
)
{

	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif

	// Return to caller.
	return( cbp->pUart2 );
}


bool            cmn_setUart2(
    CMN_DATA        *cbp,
    UART_DATA       *pUart
)
{
    INTERRUPT_STATUS;

	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
        return false;
    }
#endif

    DISABLE_INTERRUPTS();

    cbp->pUart2 = pUart;

    RESTORE_INTERRUPTS;

	// Return to caller.
	return true;
}



//**********************************************************
//                        U s e r 1
//**********************************************************

void *          cmn_getUser1(
    CMN_DATA        *cbp
)
{

	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif

	// Return to caller.
	return( cbp->pUser1 );
}

bool            cmn_setUser1(
    CMN_DATA        *cbp,
    void            *pData
)
{
    INTERRUPT_STATUS;

	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
        return false;
    }
#endif

    DISABLE_INTERRUPTS();

    cbp->pUser1 = pData;

    RESTORE_INTERRUPTS;

	// Return to caller.
	return true;
}



//**********************************************************
//                        U s e r 1
//**********************************************************

void *          cmn_getUser2(
    CMN_DATA        *cbp
)
{

	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
        return 0;
    }
#endif

	// Return to caller.
	return( cbp->pUser2 );
}

bool            cmn_setUser2(
    CMN_DATA        *cbp,
    void            *pData
)
{
    INTERRUPT_STATUS;

	// Validate the input parameters.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
        return false;
    }
#endif

    DISABLE_INTERRUPTS();

    cbp->pUser2 = pData;

    RESTORE_INTERRUPTS;

	// Return to caller.
	return true;
}



//===============================================================
//                    M e t h o d s
//===============================================================


/**********************************************************
                        C l o s e
 **********************************************************/

CMN_DATA *      cmn_Close(
    CMN_DATA        *cbp
)
{
    bool            fRc;
    INTERRUPT_STATUS;
    
	// Do initialization.
#ifdef NDEBUG
#else
    if( !cmn_Validate( cbp ) ) {
        DEBUG_BREAK();
    }
    if( NULL == cmn_index[0] ) {
		return NULL;
	}
#endif
    
    
    DISABLE_INTERRUPTS();
    
	if (cbp->pCt) {
		cbp->pCt = ct_Close( cbp->pCt );
	}
	if (cbp->pDma) {
        obj_Release(cbp->pDma);
		cbp->pDma = OBJ_NIL;
	}
	if (cbp->pMon) {
		cbp->pMon = mon_Close( cbp->pMon );
	}
	if (cbp->pCon) {
        obj_Release(cbp->pCon);
		cbp->pCon = OBJ_NIL;
	}
	if (cbp->pUart2) {
		cbp->pUart2 = uart_Close( cbp->pUart2 );
	}
	if (cbp->pTimer1) {
		cbp->pTimer1 = timer_Close( cbp->pTimer1 );
	}
	if (cbp->pOsc) {
        obj_Release(cbp->pOsc);
		cbp->pOsc = OBJ_NIL;
	}
	if (cbp->pCfg) {
        obj_Release(cbp->pCfg);
		cbp->pCfg = OBJ_NIL;
	}
    
	// Free the main control block.
    mem_Free( cbp );
    cmn_index[0] = cbp = NULL;
    
    RESTORE_INTERRUPTS;
    
	// Return to caller.
	return( cbp );
}



//---------------------------------------------------------------
//                          O p e n
//---------------------------------------------------------------

// This function assumes that interrupts have been disabled.

CMN_DATA *      cmn_Open(
    CFG_DATA        *pCfg,			// CFG Object or NULL
    CT_DATA         *pCt,			// CT Object or NULL
    DMA_DATA        *pDma,			// DMA Object or NULL
    OSC_DATA        *pOsc,			// OSC Object or NULL
    TIMER_DATA      *pTimer1        // TIMER Object or NULL
)
{
    CMN_DATA        *cbp;
    uint32_t        cbSize;
    INTERRUPT_STATUS;

    DISABLE_INTERRUPTS();

	// Allocate the control block.
	cbSize = ROUNDUP4(sizeof(CMN_DATA));
    cbp = (CMN_DATA *)mem_Malloc( cbSize );
    if( NULL == cbp ) {
        return NULL;
    }
    memset( cbp, 0, cbSize );
	cbp->cbSize = cbSize;
    cbp->identifier = CMN_IDENTIFIER;
    cmn_index[0] = cbp;
    
    cbp->utp = &cmn_table[0];
    
    cbp->pCfg = pCfg;
    if (NULL == cbp->pCfg) {
        cbp->pCfg = cfg_Alloc();
        cbp->pCfg = cfg_Init( cbp->pCfg );
    }
    
    cbp->pOsc = pOsc;
    if (NULL == cbp->pOsc) {
        cbp->pOsc = osc_Alloc( );
        cbp->pOsc = osc_Init( cbp->pOsc, NULL, NULL, 0 );
    }

    // Note: This must follow OSC object creation because it uses it.
    cbp->pCt = pCt;
    if (NULL == cbp->pCt) {
        cbp->pCt = ct_Open( 1000 /*1ms*/, true );
    }

    cbp->pDma = pDma;
    if (NULL == cbp->pDma) {
        //TODO: cbp->pDma = dma_Open( );
    }

    cbp->pTimer1 = pTimer1;
    
    RESTORE_INTERRUPTS;

    return cbp;
}





/**********************************************************
                    V a l i d a t e
 **********************************************************/

#ifdef NDEBUG
#else
static
bool			cmn_Validate(
    CMN_DATA        *cbp
)
{
    
	// Do initialization.
    
	if( cbp && (cbp->identifier == CMN_IDENTIFIER) )
		;
	else
		return false;
	if( !(cbp->cbSize >= sizeof(CMN_DATA)) )
		return false;
    
	// Return to caller.
	return true;
}
#endif









