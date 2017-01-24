/*
 * Ports.cpp
 *
 *  Created on: Jan 21, 2017
 *      Author: Will
 */

#include <Ports.h>
#include <DriverStation.h>
#include <VictorSP.h>
#include <CANTalon.h>

namespace Utils {
	frc::SpeedController* constructMotor(unsigned int port) {
		switch(motor_type) {
		case VictorSP:
			return new frc::VictorSP(port);
			break;
		case CANTalonSRX:
			return new CANTalon(port);
			break;
		default:
			return nullptr;
		}
	}
}
