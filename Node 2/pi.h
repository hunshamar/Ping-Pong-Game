/*This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief Header file for PI.c.
 *
 * - File:               PI.h
 * - Compiler:           IAR EWAAVR 4.11A
 * - Supported devices:  All AVR devices can be used.
 * - AppNote:            AVR221 - Discrete PI controller
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support email: avr@atmel.com
 *
 * $Name$
 * $Revision: 456 $
 * $RCSfile$
 * $Date: 2006-02-16 12:46:13 +0100 (to, 16 feb 2006) $
 *****************************************************************************/

#ifndef PI_H
#define PI_H

#include "stdint.h"

#define SCALING_FACTOR  128

/*! \brief PI Status
 *
 * Setpoints and data used by the PI control algorithm
 */
typedef struct pi_DATA{
  //! Summation of errors, used for integrate calculations
  int32_t sumError;
  //! The Proportional tuning constant, multiplied with SCALING_FACTOR
  int16_t P_Factor;
  //! The Integral tuning constant, multiplied with SCALING_FACTOR
  int16_t I_Factor;
  //! Maximum allowed error, avoid overflow
  int16_t maxError;
  //! Maximum allowed sumerror, avoid overflow
  int32_t maxSumError;
} PIData_t;

/*! \brief Maximum values
 *
 * Needed to avoid sign/overflow problems
 */
// Maximum value of variables
#define MAX_INT         INT16_MAX
#define MAX_LONG        INT32_MAX
#define MAX_I_TERM      (MAX_LONG / 2)

// Boolean values
#define FALSE           0
#define TRUE            1

void PI_Init(int16_t p_factor, int16_t i_factor, struct pi_DATA *pi);
int16_t PI_Controller(int16_t setPoint, int16_t processValue, struct pi_DATA *pi_st);
void PI_Reset_Integrator(PIData_t *PI_st);

#endif
