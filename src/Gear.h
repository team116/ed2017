/*
 * Gear.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#ifndef SRC_GEAR_H_
#define SRC_GEAR_H_

#include <SpeedController.h>
#include <DigitalInput.h>
#include <DoubleSolenoid.h>

class Gear {
public:
	static Gear* getInstance();
	void process();
	void open();
	void close();
	bool isOpen();
private:
	Gear();
	static Gear* INSTANCE;
	frc::SpeedController* gear_motor;
	frc::DigitalInput* LS_open;
	frc::DigitalInput* LS_close;
	frc::DoubleSolenoid* left_piston;
	frc::DoubleSolenoid* right_piston;

	bool is_open;
};

#endif /* SRC_GEAR_H_ */
