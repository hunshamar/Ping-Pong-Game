/*This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief General pi implementation for AVR.
 *
 * Discrete pi controller implementation. Set up by giving P/I/D terms
 * to Init_pi(), and uses a struct pi_DATA to store internal values.
 *
 * - File:               pi.c
 * - Compiler:           IAR EWAAVR 4.11A
 * - Supported devices:  All AVR devices can be used.
 * - AppNote:            AVR221 - Discrete pi controller
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support email: avr@atmel.com
 *
 * $Name$
 * $Revision: 456 $
 * $RCSfile$
 * $Date: 2006-02-16 12:46:13 +0100 (to, 16 feb 2006) $
 *****************************************************************************/

#include "pi.h"
#include "stdint.h"







/*! \brief Initialisation of pi controller parameters.
 *
 *  Initialise the variables used by the pi algorithm.
 *
 *  \param p_factor  Proportional term.
 *  \param i_factor  Integral term.
 *  \param d_factor  Derivate term.
 *  \param pi  Struct with pi status.
 */
void PI_Init(int16_t p_factor, int16_t i_factor, struct pi_DATA *pi)
// Set up pi controller parameters
{
  // Start values for pi controller
  pi->sumError = 0;
  // Tuning constants for pi loop
  pi->P_Factor = p_factor;
  pi->I_Factor = i_factor;
  // Limits to avoid overflow
  pi->maxError = MAX_INT / (pi->P_Factor + 1);
  pi->maxSumError = MAX_I_TERM / (pi->I_Factor + 1);
}


/*! \brief PI control algorithm.
 *
 *  Calculates output from setpoint, process value and pi status.
 *
 *  \param setPoint  Desired value.
 *  \param processValue  Measured value.
 *  \param pi_st  pi status struct.
 */
int16_t PI_Controller(int16_t setPoint, int16_t processValue, struct pi_DATA *pi_st)
{
  int16_t error, p_term, d_term;
  int32_t i_term, ret, temp;

  error = setPoint - processValue;


  // Calculate Pterm and limit error overflow
  if (error > 100){
    p_term = 100;
  }
  else if (error < -100){
    p_term = -100;
  }
  else{
    p_term = pi_st->P_Factor * error;
  }

  // Calculate Iterm and limit integral runaway
  temp = pi_st->sumError + error;
  if(temp > pi_st->maxSumError){
    i_term = MAX_I_TERM;
    pi_st->sumError = pi_st->maxSumError;
  }
  else if(temp < -pi_st->maxSumError){
    i_term = -MAX_I_TERM;
    pi_st->sumError = -pi_st->maxSumError;
  }
  else{
    pi_st->sumError = temp;
    i_term = pi_st->I_Factor * pi_st->sumError;
  }


  ret = (p_term + i_term) / SCALING_FACTOR;
  if(ret > MAX_INT){
    ret = MAX_INT;
  }
  else if(ret < -MAX_INT){
    ret = -MAX_INT;
  }
  return((int16_t)ret);
}

/*! \brief Resets the integrator.
 *
 *  Calling this function will reset the integrator in the pi regulator.
 */
void pi_Reset_Integrator(PIData_t *pi_st)
{
  pi_st->sumError = 0;
}
