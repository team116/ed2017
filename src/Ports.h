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
	//REAL ROBOT PORTS
	const unsigned int MOTOR_LEFT_FRONT = 0;
	const unsigned int MOTOR_RIGHT_FRONT = 1;
	const unsigned int MOTOR_LEFT_BACK = 2;
	const unsigned int MOTOR_RIGHT_BACK = 3;

	const unsigned int MOTOR_SHOOTER_FEEDER = 4;
	const unsigned int MOTOR_CLIMBER_LEFT = 5;
	const unsigned int MOTOR_CLIMBER_RIGHT = 6;
	const unsigned int MOTOR_SHOOTER_AZIMUTH = 7;
	const unsigned int MOTOR_INTAKE = 8;
	const unsigned int SERVO_CONVERTER = 9;
	const unsigned int MOTOR_BLENDER = 10;//N0*/

	//ANDERSON BOT PORTS
	/*const unsigned int MOTOR_LEFT_FRONT = 4;
	const unsigned int MOTOR_RIGHT_FRONT = 6;
	const unsigned int MOTOR_LEFT_BACK = 5;
	const unsigned int MOTOR_RIGHT_BACK = 7;

	const unsigned int MOTOR_SHOOTER_FEEDER = 0;
	const unsigned int MOTOR_CLIMBER_LEFT = 1;
	const unsigned int MOTOR_CLIMBER_RIGHT = 2;
	const unsigned int MOTOR_SHOOTER_AZIMUTH = 3;
	const unsigned int MOTOR_INTAKE = 8;
	const unsigned int SERVO_CONVERTER = 9;
	const unsigned int MOTOR_BLENDER = 10;//N0*/

	//Pnuematics
	const unsigned int PCM = 0;
	const unsigned int LEFT_PISTON_OPEN = 0;
	const unsigned int LEFT_PISTON_CLOSE = 1;
	const unsigned int RIGHT_PISTON_OPEN = 2;
	const unsigned int RIGHT_PISTON_CLOSE = 3;	//pretty sure we'll need to change these port #s


	//navX Motors

	//CAN Motors
	const unsigned int MOTOR_SHOOTER_WHEEL = 4;

	//Sensors
	const unsigned int LS_SHOOTER_AZIMUTH = 3;


	//Encoders
	const unsigned int LEFT_DRIVE_ENCODER_1 = 8;
	const unsigned int LEFT_DRIVE_ENCODER_2 = 9;

	const unsigned int RIGHT_DRIVE_ENCODER_1 = 6;
	const unsigned int RIGHT_DRIVE_ENCODER_2 = 7;


	const unsigned int SHOOTER_ENCODER_1 = 1;
	const unsigned int SHOOTER_ENCODER_2 = 2;

	const unsigned int AZIMUTH_ENCODER_1 = 4;
	const unsigned int AZIMUTH_ENCODER_2 = 5;

	const unsigned int AZIMUTH_MOTOR_PDP = 11;
}

namespace OIPorts
{
	//Joysticks
	const unsigned int JOYSTICK_LEFT = 0;
	const unsigned int JOYSTICK_RIGHT = 1;
	const unsigned int JOYSTICK_BUTTONS_1 = 2;
	const unsigned int JOYSTICK_BUTTONS_2 = 3;

	//Buttons
	const unsigned int BUTTON_DRIVE_STRAIGHT = 1;
	const unsigned int ROTATE_BUTTON = 2;
	const unsigned int OPEN_GEAR_BUTTON = 8;

	//3 position switches
	const unsigned int INTAKE_ROLLER_IN = 6;    //These are commented out because there is only one three-way
	const unsigned int INTAKE_ROLLER_OUT = 7;  //toggle switch on the driver station and these require 3-way
	const unsigned int BLENDER_FORWARD_SWITCH = 1;  //toggle switches.
	const unsigned int BLENDER_REVERSE_SWITCH = 2;
	const unsigned int FEEDER_FORWARD_SWITCH = 3;
	const unsigned int FEEDER_REVERSE_SWITCH = 4;

	//2-way Toggle Switches
	const unsigned int CLIMBER_ON_SWITCH = 5;
	const unsigned int SHOOTER_ON_SWITCH = 8;
	/*const unsigned int MOBILITY_ROTATION_PID_SWITCH = 9;
	const unsigned int MOBILITY_DISTANCE_PID_SWITCH = 10;
	const unsigned int SHOOTER_SPEED_PID_SWITCH = 11;
	const unsigned int SHOOTER_AZIMUTH_ANGLE_PID_SWITCH = 12;
	const unsigned int MOBILITY_LEFT_ENCODER_SWITCH = 13;
	const unsigned int MOBILITY_RIGHT_ENCODER_SWITCH = 14;
	const unsigned int SHOOTER_AZIMUTH_ENCODER_SWITCH = 15;
	const unsigned int SHOOTER_AZIMUTH_LIMIT_SWITCH = 16;
	const unsigned int SHOOTER_SPEED_ENCODER_SWITCH = 17;*/


	//Axes
	const unsigned int AXIS_Y = 1;
	const unsigned int AXIS_Z = 2;
}

namespace Utils
{
	enum MotorType {
		VictorSP,
		CANTalonSRX
	};

	const MotorType motor_type = MotorType::VictorSP;

	frc::SpeedController* constructMotor(unsigned int port);;
}

#endif /* SRC_PORTS_H_ */
