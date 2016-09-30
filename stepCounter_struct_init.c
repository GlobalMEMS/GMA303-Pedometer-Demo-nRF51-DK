/*
 * stepCounter_struct_init.c
 *
 * Code generation for function 'stepCounter_struct_init'
 *
 */

/* Include files */
#include "stepCounter_struct_init.h"

/* Function Definitions */
void stepCounter_struct_init(stepCounter_t *pWalkStruct)
{
  int i0;

  /* %% init of stepCounter structure */
  /*  */
  /*  */
  /*  walkStruct */
  pWalkStruct->HIthrA = 2.0F;
  pWalkStruct->LIthrA = 0.7F;
  pWalkStruct->HIthrW = 1.7F;
  pWalkStruct->LIthrW = 1.05F;
  pWalkStruct->timeThr = 250.0F;

  /*  made a single for real time updates */
  pWalkStruct->HLI = 0U;
  pWalkStruct->HIt = 0U;
  pWalkStruct->LIt = 0U;
  pWalkStruct->HIcnt = 0U;
  pWalkStruct->LIcnt = 0U;
  for (i0 = 0; i0 < 3; i0++) {
    pWalkStruct->Acur[i0] = 0.0F;

    /* accel x y z time */
    pWalkStruct->AcurRMS[i0] = 0.0F;
    pWalkStruct->Aprev[i0] = 0.0F;
    pWalkStruct->AprevRMS[i0] = 0.0F;
  }

  pWalkStruct->Acurt = 0U;
  pWalkStruct->Aprevt = 0U;
  pWalkStruct->crossed = 0;
  pWalkStruct->addPoint = 0;

  /*  1 to add point, 0 for nothing, -1 to lose point */
  pWalkStruct->reset = 0;

  /*  end of interval reset flag */
  pWalkStruct->aTimeUnroll = 0U;
  pWalkStruct->prevTime = 0;
  pWalkStruct->nWrap = 0;
  pWalkStruct->timerOverflow = 0;
  pWalkStruct->counterOverflow = 0;

}

/* End of code generation (stepCounter_struct_init.c) */
