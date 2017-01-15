/*
 * Vision.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#ifndef SRC_VISION_H_
#define SRC_VISION_H_

class Vision {
public:
	static Vision* getInstance();

private:
	Vision();
	static Vision* INSTANCE;
};

#endif /* SRC_VISION_H_ */
