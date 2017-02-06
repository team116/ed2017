/*
 * Converter.h
 *
 *  Created on: Feb 5, 2017
 *      Author: Will
 */

#ifndef CONVERTER_H_
#define CONVERTER_H_

#include <Servo.h>

class Converter {
public:
	static Converter* getInstance();

	void openServoConverter();
	void closeServoConverter();
	bool isOpen();

private:
	Converter();
	static Converter* INSTANCE;

	frc::Servo* servo_converter;

	bool is_open;
};

#endif /* CONVERTER_H_ */
