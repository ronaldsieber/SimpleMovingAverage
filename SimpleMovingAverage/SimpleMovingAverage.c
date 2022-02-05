/****************************************************************************

  Copyright (c) 2022 Ronald Sieber

  Project:      Project independent
  Description:  Implementation of SimpleMovingAverage

  -------------------------------------------------------------------------

  28.01.2022 -rs:   Start of implementation

 ***************************************************************************/


#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>
#include "SimpleMovingAverage.h"                    // SimpleMovingAverage (Embedded C Version)





/***************************************************************************/
/*                                                                         */
/*                                                                         */
/*          G L O B A L   D E F I N I T I O N S                            */
/*                                                                         */
/*                                                                         */
/***************************************************************************/

//---------------------------------------------------------------------------
//  Configuration
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//  Constant definitions
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//  Local types
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//  Local variables
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//  Prototypes of internal functions
//---------------------------------------------------------------------------





//=========================================================================//
//                                                                         //
//          P U B L I C   F U N C T I O N S                                //
//                                                                         //
//=========================================================================//

//---------------------------------------------------------------------------
//  Initialization
//---------------------------------------------------------------------------

void  SmaInitialize (tSmaWorkSpace* pWrkSpc_p, int iSampleWindowSize_p)
{

    if (pWrkSpc_p == NULL)
    {
        return;
    }

    pWrkSpc_p->m_paiSampleWindow = malloc(sizeof(int) * iSampleWindowSize_p);
    pWrkSpc_p->m_iSampleWindowSize = iSampleWindowSize_p;

    SmaClean(pWrkSpc_p);

    return;

}



//---------------------------------------------------------------------------
//  Delete
//---------------------------------------------------------------------------

void  SmaDelete (tSmaWorkSpace* pWrkSpc_p)
{

    if (pWrkSpc_p == NULL)
    {
        return;
    }

    if (pWrkSpc_p->m_paiSampleWindow != NULL)
    {
        free(pWrkSpc_p->m_paiSampleWindow);
    }

    return;

}



//---------------------------------------------------------------------------
//  Clean
//---------------------------------------------------------------------------

void  SmaClean (tSmaWorkSpace* pWrkSpc_p)
{

int  iIdx;


    for (iIdx=0; iIdx<pWrkSpc_p->m_iSampleWindowSize; iIdx++)
    {
        pWrkSpc_p->m_paiSampleWindow[iIdx] = 0;
    }
    pWrkSpc_p->m_iSampleWindowIndex = 0;
    pWrkSpc_p->m_lWindowSum = 0;
    pWrkSpc_p->m_iAverageValue = 0;

    pWrkSpc_p->m_fAverageSettled = false;

    return;

}



//---------------------------------------------------------------------------
//  Get SampleWindow Size
//---------------------------------------------------------------------------

int   SmaGetSampleWindowSize (tSmaWorkSpace* pWrkSpc_p)
{

    return (pWrkSpc_p->m_iSampleWindowSize);

}



//---------------------------------------------------------------------------
//  Calculate Moving Average
//---------------------------------------------------------------------------

int  SmaCalcMovingAverage (tSmaWorkSpace* pWrkSpc_p, int iNewValue_p)
{

int  iAverageValue;


    // To avoid calculation errors, the moving average mode is only used after
    // the SampleWindow has been completely filled (m_fAverageSettled==true).
    // Until the first complete filling of the SampleWindow the classic
    // arithmetic average value is calculated.
    if ( pWrkSpc_p->m_fAverageSettled )
    {
        // subtract oldest value from previous sum, add the new value
        pWrkSpc_p->m_lWindowSum = pWrkSpc_p->m_lWindowSum - pWrkSpc_p->m_paiSampleWindow[pWrkSpc_p->m_iSampleWindowIndex] + iNewValue_p;

        // assign new value to the position in the sample window
        pWrkSpc_p->m_paiSampleWindow[pWrkSpc_p->m_iSampleWindowIndex] = iNewValue_p;

        // calculate new sliding average value
        iAverageValue = pWrkSpc_p->m_lWindowSum / pWrkSpc_p->m_iSampleWindowSize;
    }
    else
    {
        // add the new value
        pWrkSpc_p->m_lWindowSum = pWrkSpc_p->m_lWindowSum + iNewValue_p;

        // assign new value to the position in the sample window
        pWrkSpc_p->m_paiSampleWindow[pWrkSpc_p->m_iSampleWindowIndex] = iNewValue_p;

        // calculate new arithmetic average value
        iAverageValue = pWrkSpc_p->m_lWindowSum / (pWrkSpc_p->m_iSampleWindowIndex + 1);
    }


    // shift index pointer to next position
    pWrkSpc_p->m_iSampleWindowIndex++;
    if (pWrkSpc_p->m_iSampleWindowIndex >= pWrkSpc_p->m_iSampleWindowSize)
    {
        pWrkSpc_p->m_iSampleWindowIndex = 0;
        pWrkSpc_p->m_fAverageSettled = true;
    }

    pWrkSpc_p->m_iAverageValue = iAverageValue;

    return (iAverageValue);

}



//---------------------------------------------------------------------------
//  Get last calculated Average Value
//---------------------------------------------------------------------------

int  SmaGetAverageValue (tSmaWorkSpace* pWrkSpc_p)
{

    return (pWrkSpc_p->m_iAverageValue);

}




// EOF


