/*
 * Queue.h
 *
 *  Created on: Jan 28, 2017
 *      Author: Emina Ermin
 */

#ifndef SRC_QUEUE_H_
#define SRC_QUEUE_H_

class Queue {
public:
	Queue();
	void Push(int accel);
	int Get(int index);
	int Size();

private:
	static const int SIZE = 10;
	int values [SIZE];
};

#endif /* SRC_QUEUE_H_ */
