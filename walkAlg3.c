/*
 * walkAlg3.c
 *
 * Code generation for function 'walkAlg3'
 *
 */

/* Include files */
#include <math.h>
#include <stdint.h>
#include "stepCounter_struct_init.h"

#define MAX_uint32_T	((uint32_t)(0xFFFFFFFFU))


/* Function Definitions */
static float eml_extremum(const float x[3])
{
  float extremum;
  int ix;

  extremum = x[0];

  for(ix = 1; ix < 3; ++ix){

    if(x[ix] > extremum) extremum = x[ix];

  } 

  return extremum;
}

void b_abs(const float x[3], float y[3])
{
  int k;
  for (k = 0; k < 3; k++) {
    y[k] = fabs(x[k]);
  }
}

void walkAlg3(stepCounter_t *pWalkStruct,
	      const float accDataIn[3],
	      const float aRMSin[3],
	      unsigned int tDataIn,
	      float whichThr)
{
  float LIth;
  float HIth;
  float b_accDataIn[3];
  int i1;
  float fv0[3];
  unsigned int q0;
  unsigned int qY;
  float b_walkStruct[3];
  float fv1[3];
  float fv2[3];
  float fv3[3];
  float fv4[3];
  float fv5[3];
  float fv6[3];
  float fv7[3];

  /* %% walking algorithm.  */
  /*  Performs step counting primarily targeted for the wrist mounting, uses */
  /*  maximum observed value for each. Could also be used for accel radii. */
  /*  Inputs:  */
  /*  walkStruct = holds all persistent varibles as well as thresholds, see */
  /*  stepCounter_struct_init for definitions. */
  /*  accDataIn = accel data inputs, x, y, z; can be lowpass filtered */
  /*  if desired. */
  /*  aRMSin = moving average or rms data, subtracted from data. Can input */
  /*  zeros, or input RMS data as desired, will require different thresholds. */
  /*  tDataIn = time data, in milliseconds, relative timing between points is */
  /*  all that matters, but must be unwrapped before input to this function. */
  /*  whichThr = allows user to store two sets of thresholds and switch with */
  /*  this value. Example, could use different thresholds for 0 aRMSin vs moving */
  /*  standard deviation for aRMSin and switch depending on if data available. */
  /*  */
  /*  */
  /*  choose a thershold setting  */
  /*  two threshold settings per to denote high acceleration or low */
  /*  acceleration amplitudes */
  if (whichThr == 2.0F) {
    LIth = pWalkStruct->LIthrA;
    HIth = pWalkStruct->HIthrA;
  } else {
    LIth = pWalkStruct->LIthrW;
    HIth = pWalkStruct->HIthrW;
  }

  pWalkStruct->addPoint = 0;
  for (i1 = 0; i1 < 3; i1++) {
    b_accDataIn[i1] = accDataIn[i1] - aRMSin[i1];
  }

  b_abs(b_accDataIn, fv0);
  if (eml_extremum(fv0) > LIth) {
    /*  check if data has crossed minimum threshold */
    if (!(pWalkStruct->crossed != 0)) {
      /*  when it crosses a threshold incremement steps */
      q0 = pWalkStruct->HLI;
      qY = q0 + 1U;
      if (qY < q0) {
        qY = MAX_uint32_T;
      }

      pWalkStruct->HLI = qY;

      /*  step count */
      pWalkStruct->crossed = 1;
    }

    /*  if newest point is highest current point for this crossing, save */
    /*  it as the current peak data point */
    for (i1 = 0; i1 < 3; i1++) {
      b_accDataIn[i1] = accDataIn[i1] - aRMSin[i1];
    }

    for (i1 = 0; i1 < 3; i1++) {
      b_walkStruct[i1] = pWalkStruct->Acur[i1] - pWalkStruct->AcurRMS[i1];
    }

    b_abs(b_accDataIn, fv1);
    b_abs(b_walkStruct, fv2);
    if (eml_extremum(fv1) > eml_extremum(fv2)) {
      for (i1 = 0; i1 < 3; i1++) {
        pWalkStruct->Acur[i1] = accDataIn[i1];
      }

      for (i1 = 0; i1 < 3; i1++) {
        pWalkStruct->AcurRMS[i1] = aRMSin[i1];
      }

      pWalkStruct->Acurt = tDataIn;

      /*  time and value */
    }
  } else {
    if (pWalkStruct->crossed != 0) {
      /*  once data crosses back under threshold, perform calculations and determine step type */
      pWalkStruct->addPoint = 1;
      for (i1 = 0; i1 < 3; i1++) {
        b_walkStruct[i1] = pWalkStruct->Acur[i1] - pWalkStruct->AcurRMS[i1];
      }

      b_abs(b_walkStruct, fv3);
      if (eml_extremum(fv3) > HIth) {
        /*  high impact point classification */
        q0 = pWalkStruct->HIcnt;
        qY = q0 + 1U;
        if (qY < q0) {
          qY = MAX_uint32_T;
        }

        pWalkStruct->HIcnt = qY;
        q0 = pWalkStruct->HIt;
        qY = q0 + 1U;
        if (qY < q0) {
          qY = MAX_uint32_T;
        }

        pWalkStruct->HIt = qY;
      } else {
        /*  low impact point classification */
        q0 = pWalkStruct->LIcnt;
        qY = q0 + 1U;
        if (qY < q0) {
          qY = MAX_uint32_T;
        }

        pWalkStruct->LIcnt = qY;
        q0 = pWalkStruct->LIt;
        qY = q0 + 1U;
        if (qY < q0) {
          qY = MAX_uint32_T;
        }

        pWalkStruct->LIt = qY;
      }

      if (pWalkStruct->HLI > 1U) {
        /*  remove data points that are too close together in time */
        q0 = pWalkStruct->Acurt;
        qY = q0 - pWalkStruct->Aprevt;
        if (qY > q0) {
          qY = 0U;
        }

        if ((double)(qY) < pWalkStruct->timeThr) {
          q0 = pWalkStruct->HLI;
          qY = q0 - 1U;
          if (qY > q0) {
            qY = 0U;
          }

          pWalkStruct->HLI = qY;
          pWalkStruct->addPoint = -1;
          for (i1 = 0; i1 < 3; i1++) {
            b_walkStruct[i1] = pWalkStruct->Aprev[i1] - pWalkStruct->AprevRMS[i1];
          }

          for (i1 = 0; i1 < 3; i1++) {
            b_accDataIn[i1] = pWalkStruct->Acur[i1] - pWalkStruct->AcurRMS[i1];
          }

          b_abs(b_walkStruct, fv4);
          b_abs(b_accDataIn, fv5);
          if (eml_extremum(fv4) > eml_extremum(fv5)) {
            for (i1 = 0; i1 < 3; i1++) {
              b_walkStruct[i1] = pWalkStruct->Acur[i1] - pWalkStruct->AcurRMS[i1];
            }

            b_abs(b_walkStruct, fv6);
            if (eml_extremum(fv6) > HIth) {
              q0 = pWalkStruct->HIcnt;
              qY = q0 - 1U;
              if (qY > q0) {
                qY = 0U;
              }

              pWalkStruct->HIcnt = qY;
              q0 = pWalkStruct->HIt;
              qY = q0 - 1U;
              if (qY > q0) {
                qY = 0U;
              }

              pWalkStruct->HIt = qY;
            } else {
              q0 = pWalkStruct->LIcnt;
              qY = q0 - 1U;
              if (qY > q0) {
                qY = 0U;
              }

              pWalkStruct->LIcnt = qY;
              q0 = pWalkStruct->LIt;
              qY = q0 - 1U;
              if (qY > q0) {
                qY = 0U;
              }

              pWalkStruct->LIt = qY;
            }

            for (i1 = 0; i1 < 3; i1++) {
              pWalkStruct->Acur[i1] = pWalkStruct->Aprev[i1];
            }

            for (i1 = 0; i1 < 3; i1++) {
              pWalkStruct->AcurRMS[i1] = pWalkStruct->AprevRMS[i1];
            }

            pWalkStruct->Acurt = pWalkStruct->Aprevt;
          } else {
            for (i1 = 0; i1 < 3; i1++) {
              b_walkStruct[i1] = pWalkStruct->Aprev[i1] - pWalkStruct->AprevRMS[i1];
            }

            b_abs(b_walkStruct, fv7);
            if (eml_extremum(fv7) > HIth) {
              q0 = pWalkStruct->HIcnt;
              qY = q0 - 1U;
              if (qY > q0) {
                qY = 0U;
              }

              pWalkStruct->HIcnt = qY;
              q0 = pWalkStruct->HIt;
              qY = q0 - 1U;
              if (qY > q0) {
                qY = 0U;
              }

              pWalkStruct->HIt = qY;
            } else {
              q0 = pWalkStruct->LIcnt;
              qY = q0 - 1U;
              if (qY > q0) {
                qY = 0U;
              }

              pWalkStruct->LIcnt = qY;
              q0 = pWalkStruct->LIt;
              qY = q0 - 1U;
              if (qY > q0) {
                qY = 0U;
              }

              pWalkStruct->LIt = qY;
            }
          }
        }
      }

      /*  set the current point as the previous point, and reset the */
      /*  current point for new steps. */
      for (i1 = 0; i1 < 3; i1++) {
        pWalkStruct->Aprev[i1] = pWalkStruct->Acur[i1];
      }

      for (i1 = 0; i1 < 3; i1++) {
        pWalkStruct->AprevRMS[i1] = pWalkStruct->AcurRMS[i1];
      }

      pWalkStruct->Aprevt = pWalkStruct->Acurt;
      for (i1 = 0; i1 < 3; i1++) {
        pWalkStruct->Acur[i1] = 0.0F;
      }

      for (i1 = 0; i1 < 3; i1++) {
        pWalkStruct->AcurRMS[i1] = 0.0F;
      }

      pWalkStruct->Acurt = 0U;
      pWalkStruct->crossed = 0;
    }
  }

  /*  end */
}

/* End of code generation (walkAlg3.c) */
