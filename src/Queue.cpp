/*
 * Queue.cpp
 *
 *  Created on: Jan 28, 2017
 *      Author: Emina Ermin
 */

#include <Queue.h>
#include <DriverStation.h>

Queue::Queue() {
	// TODO Auto-generated constructor stub
	for (unsigned int i = 0; i < SIZE; i++) {
		values[i] = 0;
		frc::DriverStation::ReportError("Setting " + std::to_string(i) + " to " + std::to_string(values[i]));
	}
}

void Queue::Push(int accel) {
	frc::DriverStation::ReportError("Push check 1");
	for (int i = SIZE - 2; i >= 0; i--) {
		values[i+1] = values[i];
		//frc::DriverStation::ReportError("Index " + std::to_string(i));
	}
	frc::DriverStation::ReportError("Push check 2");
	values[0] = accel;
	frc::DriverStation::ReportError("Push check 3");
}

int Queue::Get(int index) {
	return values[index];
}

int Queue::Size() {
	return sizeof(values);
}
