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
			DriverStation::ReportError("Constructin talon on port " + std::to_string(port));
			return new frc::VictorSP(port);
			break;
		case CANTalonSRX:
			DriverStation::ReportError("Constructin talon on port " + std::to_string(port));
			return new CANTalon(port);
			break;
		default:
			DriverStation::ReportError("Error constructing motors");
			return nullptr;
		}
	}
}
