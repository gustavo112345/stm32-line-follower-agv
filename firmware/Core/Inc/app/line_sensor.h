/*
 * line_sensor.h
 *
 *  Created on: 21/10/2026
 *      Author: Gustavo
 */

#ifndef LINE_SENSOR_H_
#define LINE_SENSOR_H_

#include <stdint.h>

enum IR_sensor_array {
	IR_FAR_RIGHT,
	IR_RIGHT,
	IR_CENTER,
	IR_LEFT,
	IR_FAR_LEFT,
	N_SENSORS
};

float update_line_position(volatile uint16_t *bufferADC);

#endif /* LINE_SENSOR_H_ */
