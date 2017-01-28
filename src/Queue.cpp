/*
 * Queue.cpp
 *
 *  Created on: Jan 28, 2017
 *      Author: Emina Ermin
 */

#include <Queue.h>

Queue::Queue() {
	// TODO Auto-generated constructor stub
	for (unsigned int i = 0; i < SIZE; i++) {
		values[i] = 0;
	}
}

void Queue::Push(int accel) {
	for (int i = SIZE - 2; i >= 0; i--) {
		values[i+1] = values[i];
	}
	values[0] = accel;
}

int Queue::Get(int index) {
	return values[index];
}

int Queue::Size() {
	return sizeof(values);
}
