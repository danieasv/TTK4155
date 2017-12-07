/*! \file *********************************************************************
 *
 * \brief General PID implementation for AVR.
 *
 * Discrete PID controller implementation. Set up by giving P/I/D terms
 * to Init_PID(), and uses a struct PID_DATA to store internal values.
 *
 *
 *****************************************************************************/
#include "general_header_node2.h"
#include "pi.h"
#include "stdint.h"

/*! \brief Initialization of PID controller parameters.
 *
 *  Initialize the variables used by the PID algorithm.
 *
 *  \param Kp  Proportional term.
 *  \param Ki  Integral term.
 *  \param regulator_p  Struct with PI status.
 */
void pi_init(int16_t Kp_set, int16_t Ki_set, struct pi_t *regulator_p)
{
	// Start values for PID controller
	regulator_p->error_sum = 0;
	// Tuning constants for PID loop
	regulator_p->Kp = Kp_set;
	regulator_p->Ki = Ki_set;
}

/*! \brief PID control algorithm.
 *
 *  Calculates output from setpoint, process value and PID status.
 *
 *  \param set_point  Desired value.
 *  \param measurement  Measured value.
 *  \param pi_st  PI status struct.
 */
int16_t pi_controller(int16_t set_point, int16_t measurement, struct pi_t* regulator_p)
{
	int16_t error, p_term;
	int32_t i_term, ret;

	error = set_point - measurement;
	
	
	printf("SET POINT: %i,   MEASUREMENT: %i  ", set_point, measurement);

	// Calculate p-term
	p_term = regulator_p->Kp * error;


	// Calculate Iterm
	regulator_p->error_sum += error;
	i_term = (regulator_p->Ki * regulator_p->error_sum); // Not sure about this scaling number
	
	ret = (p_term + i_term) / SCALING_FACTOR;
	
	//printf("Kp term :  %i   , Ki term:  %i   ", p_term, i_term);
	
	return ((int16_t) ret);
}

/*! \brief Resets the integrator.
 *
 *  Calling this function will reset the integrator in the PID regulator.
 */
void pi_reset_integrator(struct pi_t *regulator_p)
{
	regulator_p->error_sum = 0;
}