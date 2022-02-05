/****************************************************************************

  Copyright (c) 2022 Ronald Sieber

  Project:      Reference Project for SimpleMovingAverage
  Description:  Main module of SimpleMovingAverage Reference Project

  -------------------------------------------------------------------------

  Revision History:

  28.01.2022 -rs:   Start of implementation

****************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include "SimpleMovingAverage.hpp"                  // Template Class <SimpleMovingAverage>
#include "SimpleMovingAverage.h"                    // SimpleMovingAverage (Embedded C Version)





/***************************************************************************/
/*                                                                         */
/*                                                                         */
/*          G L O B A L   D E F I N I T I O N S                            */
/*                                                                         */
/*                                                                         */
/***************************************************************************/

//---------------------------------------------------------------------------
//  Application Configuration
//---------------------------------------------------------------------------

const int       APP_VERSION  = 1;                // 1.xx
const int       APP_REVISION = 0;                // x.00
const char      APP_BUILD_TIMESTAMP[] = __DATE__ " " __TIME__;



//---------------------------------------------------------------------------
//  Definitions
//---------------------------------------------------------------------------

#define ARRAY_SIZE(x) sizeof(x)/sizeof(x[0])



//---------------------------------------------------------------------------
//  Sample Series
//---------------------------------------------------------------------------

// a sample array of numbers. The represent "readings" from a sensor over time
int  aiDataSeries_g[] = { 50, 60, 70, 80, 100, 150, 160, 165, 155, 145, 130, 110, 100, 80, 60, 50, 40, 35, 30, 25, 20, 15, 10, 10, 10, 10 };
int  iDataSeriesLen_g = ARRAY_SIZE(aiDataSeries_g);





//=========================================================================//
//                                                                         //
//          P U B L I C   F U N C T I O N S                                //
//                                                                         //
//=========================================================================//

//---------------------------------------------------------------------------
//  Main function of this application
//---------------------------------------------------------------------------

int  main (int nArgCnt_p, char* pszArg_p[])
{

SimpleMovingAverage<int>    SmaSensor1;                         // SampleWindowSize = DEFAULT_SAMPLE_WINDOW_SIZE = 5
int                         iAverageValueSensor1;
SimpleMovingAverage<float>  SmaSensor2(10);                     // SampleWindowSize = 10
float                       flAverageValueSensor2;
tSmaWorkSpace               SmaSensor3;                         // SampleWindowSize is set via SmaInitialize()
int                         iAverageValue;
int                         iIdx;


    //-----------------------------------------------------------------------
    //  Applying of Template Class <SimpleMovingAverage>
    //-----------------------------------------------------------------------
    printf("\n\n---- SimpleMovingAverage<T> ----\n");
    printf("Data Series for Sensor1 (SampleWindowSize=%d):\n\n", SmaSensor1.GetSampleWindowSize());
    for (iIdx=0; iIdx<iDataSeriesLen_g; iIdx++)
    {
        iAverageValueSensor1 = SmaSensor1.CalcMovingAverage((int)aiDataSeries_g[iIdx]);
        printf("%d\t->\t%d\n", aiDataSeries_g[iIdx], iAverageValueSensor1);
    }

    printf("\n\n---- SimpleMovingAverage<T> ----\n");
    printf("Data Series for Sensor2 (SampleWindowSize=%d):\n\n", SmaSensor2.GetSampleWindowSize());
    for (iIdx=0; iIdx<iDataSeriesLen_g; iIdx++)
    {
        flAverageValueSensor2 = SmaSensor2.CalcMovingAverage((float)aiDataSeries_g[iIdx]);
        printf("%d\t->\t%f\n", aiDataSeries_g[iIdx], flAverageValueSensor2);
    }


    //-----------------------------------------------------------------------
    //  Applying of SimpleMovingAverage (Embedded C Version)
    //-----------------------------------------------------------------------
    printf("\n\n---- SmaCalcMovingAverage ----\n");
    SmaInitialize(&SmaSensor3, SMA_DEFALUT_SAMPLE_WINDOW_SIZE);
    printf("Data Series for Sensor3 (SampleWindowSize=%d):\n\n", SmaGetSampleWindowSize(&SmaSensor3));
    for (iIdx=0; iIdx<iDataSeriesLen_g; iIdx++)
    {
        iAverageValue = SmaCalcMovingAverage(&SmaSensor3, aiDataSeries_g[iIdx]);
        printf("%d\t->\t%d\n", aiDataSeries_g[iIdx], iAverageValue);
    }
    SmaDelete(&SmaSensor3);


    printf("\n\n");

    return (0);

}




// EOF

