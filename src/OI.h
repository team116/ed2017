/*
 * OI.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#ifndef SRC_OI_H_
#define SRC_OI_H_

class OI {
public:
	static OI* getInstance();

private:
	OI();
	static OI* INSTANCE;
};

#endif /* SRC_OI_H_ */
