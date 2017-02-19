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
	const unsigned int LS_SHOOTER_AZIMUTH = 5;
	const unsigned int LS_CLIMBER = 4;


	//Encoders
	const unsigned int LEFT_DRIVE_ENCODER_1 = 9;
	const unsigned int LEFT_DRIVE_ENCODER_2 = 8;

	const unsigned int RIGHT_DRIVE_ENCODER_1 = 6;
	const unsigned int RIGHT_DRIVE_ENCODER_2 = 7;


	const unsigned int SHOOTER_ENCODER_1 = 1;
	const unsigned int SHOOTER_ENCODER_2 = 2;

	const unsigned int AZIMUTH_ENCODER = 0;

	const unsigned int AZIMUTH_MOTOR_PDP = 11;
}

namespace OIPorts
{
	//Joysticks
	const unsigned int JOYSTICK_LEFT = 0;
	const unsigned int JOYSTICK_RIGHT = 1;
	const unsigned int JOYSTICK_BUTTONS_1 = 2;
	const unsigned int JOYSTICK_BUTTONS_2 = 3;
	const unsigned int JOYSTICK_BUTTONS_3 = 4;


	/*
	 * KEY
	 * S2 - 2 Position switch
	 * S3 - 3 Position switch
	 * B - button
	 * P - Potentiometer
	 */


	//Drive Joystick controls
	const unsigned int B_DRIVE_STRAIGHT = 1;
	const unsigned int B_ROTATE = 2;


	//Button Box 1 controls
	const unsigned int B_SHOOT = 1;
	const unsigned int S2_SHOOTER_WHEELS_TOGGLE = 2;
	const unsigned int S2_SHOOTER_SPEED_AUTO_MANUAL_TOGGLE = 3;
	const unsigned int S2_CONVERTER = 4;
	const unsigned int S2_CAMERA_TOGGLE = 5;
	const unsigned int S2_CLIMBER_TOGGLE = 6;
	const unsigned int S2_AUTO_AZIMUTH_TOGGLE = 7;
	const unsigned int P_SHOOTER_AZIMUTH_ANGLE = 0;
	const unsigned int P_SHOOTER_SPEED = 1;


	//Button Box 2 controls
	const unsigned int B_GEAR_RELEASE = 1;
	const unsigned int B_GEAR_AUTO_ALIGN = 2;
	const unsigned int S3_BLENDER_FORWARD = 3;
	const unsigned int S3_BLENDER_REVERSE = 4;
	const unsigned int S3_LOADER_FORWARD = 5;
	const unsigned int S3_LOADER_REVERSE = 6;
	const unsigned int S3_INTAKE_FORWARD = 7;
	const unsigned int S3_INTAKE_REVERSE = 8;
	const unsigned int P_CLIMBER_SPEED = 0;


	//Button Box 3 controls
	const unsigned int AUTO_DIAGNOSTICS = 1;
	const unsigned int GYRO = 2;
	const unsigned int SHOOTER_AZ_PID = 3;
	const unsigned int SHOOTER_AZIMUTH = 4;
	const unsigned int SHOOTER_SPEED_PID = 5;
	const unsigned int SHOOTER_SPEED = 6;
	const unsigned int MOBILITY_ROTATION = 7;
	const unsigned int MOBILITY_DISTANCE = 8;
	const unsigned int MOBILITY_RIGHT = 9;
	const unsigned int MOBILITY_LEFT = 10;


	/*const unsigned int OPEN_GEAR_BUTTON = 8;

	//3 position switches
	const unsigned int INTAKE_ROLLER_IN = 6;    //These are commented out because there is only one three-way
	const unsigned int INTAKE_ROLLER_OUT = 7;  //toggle switch on the driver station and these require 3-way
	const unsigned int BLENDER_FORWARD_SWITCH = 1;  //toggle switches.
	const unsigned int BLENDER_REVERSE_SWITCH = 2;
	const unsigned int FEEDER_FORWARD_SWITCH = 3;
	const unsigned int FEEDER_REVERSE_SWITCH = 4;

	//2-way Toggle Switches
	const unsigned int CLIMBER_ON_SWITCH = 5;
	const unsigned int SHOOTER_ON_SWITCH = 9;*/
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
