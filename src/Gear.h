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
#include <Compressor.h>

class Gear {
public:
	static Gear* getInstance();
	void process();
	void open();
	void close();
	bool isOpen();
	bool enabled();
	void enableCompressor();
	void disableCompressor();

private:
	Gear();
	static Gear* INSTANCE;

	frc::DoubleSolenoid* left_piston;
	frc::DoubleSolenoid* right_piston;
	frc::Compressor* compressor;

	bool is_open;
};

#endif /* SRC_GEAR_H_ */
