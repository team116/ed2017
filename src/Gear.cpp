/*
 * Gear.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */


#include <Gear.h>
#include "Ports.h"
#include <WPILib.h>

Gear* Gear::INSTANCE = nullptr;

Gear::Gear() {
	// TODO Auto-generated constructor stub
	left_piston = new frc::DoubleSolenoid(RobotPorts::LEFT_PISTON_OPEN , RobotPorts::LEFT_PISTON_CLOSE);
	right_piston = new frc::DoubleSolenoid(RobotPorts::RIGHT_PISTON_OPEN , RobotPorts::RIGHT_PISTON_CLOSE);
	compressor = new frc::Compressor();

	is_open = false;

	frc::LiveWindow::GetInstance()->AddActuator("Gear", "Compressor", compressor);
	compressor->StartLiveWindowMode();
}
void Gear::open() {
	left_piston->Set(frc::DoubleSolenoid::Value::kForward);	//kForward is an assumption, we need to test it
	right_piston->Set(frc::DoubleSolenoid::Value::kForward);
	is_open = true;
}
void Gear::close() {
	right_piston->Set(frc::DoubleSolenoid::Value::kReverse);	//also an assumption
	left_piston->Set(frc::DoubleSolenoid::Value::kReverse);
	is_open = false;
}
//numbers are subject to change
void Gear::process() {

}
bool Gear::isOpen() {
	return is_open;
}
void Gear::enableCompressor() {
	compressor->SetClosedLoopControl(true);
	compressor->Start();
}
void Gear::disableCompressor() {
	compressor->SetClosedLoopControl(false);
	compressor->Stop();
}

Gear* Gear::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Gear();
	}

	return INSTANCE;
}
