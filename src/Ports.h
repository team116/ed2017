/*
 * Ports.h
 *
 *  Created on: Jan 19, 2017
 *      Author: Will
 */

#ifndef SRC_PORTS_H_
#define SRC_PORTS_H_

#include <SpeedController.h>

namespace RobotPorts
{
	//PWM Motors
/*  VICTORSP PORTS
	const unsigned int MOTOR_LEFT_FRONT = 0;
	const unsigned int MOTOR_RIGHT_FRONT = 1;
	const unsigned int MOTOR_LEFT_BACK = 2;
	const unsigned int MOTOR_RIGHT_BACK = 3; */
/*  CANTALON PORTS */
	const unsigned int MOTOR_LEFT_FRONT = 4;
	const unsigned int MOTOR_RIGHT_FRONT = 6;
	const unsigned int MOTOR_LEFT_BACK = 5;
	const unsigned int MOTOR_RIGHT_BACK = 7;

	const unsigned int MOTOR_SHOOTER_AZIMUTH = 4;
	const unsigned int MOTOR_SHOOTER_FEEDER = 5;
	const unsigned int MOTOR_INTAKE = 6;
	//const unsigned int SERVO_GEAR_RIGHT = 8;
	//const unsigned int SERVO_GEAR_LEFT = 7;
	const unsigned int SERVO_CONVERTER = 9;

	//navX Motors
	//Possible gear motor?
	const unsigned int MOTOR_GEAR = 10;//N0
	const unsigned int MOTOR_BLENDER = 11;//N1
	const unsigned int MOTOR_CLIMBER = 12;//N2

	//CAN Motors
	const unsigned int MOTOR_SHOOTER_WHEEL = 1;

	//Sensors
	const unsigned int LS_GEAR_OPEN = 1;
	const unsigned int LS_GEAR_CLOSED = 2;
	const unsigned int SHOOTER_ENCODER_1 = 3;
	const unsigned int SHOOTER_ENCODER_2 = 4;
}

namespace OIPorts
{
	//Joysticks
	const unsigned int JOYSTICK_LEFT = 0;
	const unsigned int JOYSTICK_RIGHT = 1;
	const unsigned int JOYSTICK_BUTTONS_1 = 2;
	const unsigned int JOYSTICK_BUTTONS_2 = 3;

	//Buttons

}

namespace Utils
{
	enum MotorType {
		VictorSP,
		CANTalonSRX
	};

	const MotorType motor_type = MotorType::CANTalonSRX;

	frc::SpeedController* constructMotor(unsigned int port);;
}

#endif /* SRC_PORTS_H_ */
