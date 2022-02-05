/****************************************************************************

  Copyright (c) 2022 Ronald Sieber

  Project:      Project independent
  Description:  Declaration of SimpleMovingAverage

  -------------------------------------------------------------------------

  28.01.2022 -rs:   Start of implementation

 ***************************************************************************/

#ifndef _SIMPLEMOVINGAVERAGE_H_
#define _SIMPLEMOVINGAVERAGE_H_



//---------------------------------------------------------------------------
//  Definitions
//---------------------------------------------------------------------------

#define SMA_DEFALUT_SAMPLE_WINDOW_SIZE  5


typedef struct
{

    int*    m_paiSampleWindow;                  // the size of this array represents how many numbers will be used to calculate the average
    long    m_lWindowSum;
    int     m_iAverageValue;
    int     m_iSampleWindowSize;
    int     m_iSampleWindowIndex;
    bool    m_fAverageSettled;

} tSmaWorkSpace;



//---------------------------------------------------------------------------
//  Prototypes of public functions
//---------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif


void  SmaInitialize (tSmaWorkSpace* pWrkSpc_p, int iSampleWindowSize_p);
void  SmaDelete (tSmaWorkSpace* pWrkSpc_p);
void  SmaClean (tSmaWorkSpace* pWrkSpc_p);
int   SmaGetSampleWindowSize (tSmaWorkSpace* pWrkSpc_p);
int   SmaCalcMovingAverage (tSmaWorkSpace* pWrkSpc_p, int iNewValue_p);
int   SmaGetAverageValue (tSmaWorkSpace* pWrkSpc_p);


#ifdef __cplusplus
}
#endif



#endif  // #ifndef _SIMPLEMOVINGAVERAGE_H_

