/*
 * stepCounter_struct_init.h
 *
 * Code generation for function 'stepCounter_struct_init'
 *
 */

#ifndef __STEPCOUNTER_STRUCT_INIT_H__
#define __STEPCOUNTER_STRUCT_INIT_H__

/* Include files */

typedef struct
{
    float HIthrA;
    float LIthrA;
    float HIthrW;
    float LIthrW;
    float timeThr;
    unsigned int HLI;
    unsigned int HIt;
    unsigned int LIt;
    unsigned int HIcnt;
    unsigned int LIcnt;
    float Acur[3];
    float AcurRMS[3];
    float Aprev[3];
    float AprevRMS[3];
    unsigned int Acurt;
    unsigned int Aprevt;
    unsigned char crossed;
    signed char addPoint;
    unsigned char reset;
    unsigned int aTimeUnroll;
    unsigned short prevTime;
    unsigned short nWrap;
    unsigned char timerOverflow;
    unsigned char counterOverflow;
} stepCounter_t;

/* Function Declarations */
extern void stepCounter_struct_init(stepCounter_t *pWalkStruct);

#endif

/* End of code generation (stepCounter_struct_init.h) */
