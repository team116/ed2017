/*
 * Converter.h
 *
 *  Created on: Feb 5, 2017
 *      Author: Will
 */

#ifndef CONVERTER_H_
#define CONVERTER_H_

class Converter {
public:
	static Converter* getInstance();

private:
	Converter();
	static Converter* INSTANCE;
};

#endif /* CONVERTER_H_ */
