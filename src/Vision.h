/*
 * Vision.h
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#ifndef SRC_VISION_H_
#define SRC_VISION_H_

#include "Mobility.h"
#include "Shooter.h"
#include "GripPipeline.h"

class Vision {
public:
	static Vision* getInstance();
	void process();

	bool canSeeGearHook();
	bool canSeeHighGoal();

	float gearHookDegreesHorizontal();
	float gearHookDistance();

	float highGoalDegreesHorizontal();
	float highGoalDistance();

	void turnToGearHook();
	void turnToHighGoal();

	enum CameraMode {
		Human,
		Computer
	};

	void setGearCamMode(CameraMode);
	void setShooterCamMode(CameraMode);

private:
	Vision();
	static Vision* INSTANCE;

	const int CAMERA_WIDTH = 640;
	const int CAMERA_HEIGHT = 480;

	Mobility* mobility;
	Shooter* shooter;

	grip::GripPipeline* processor;

	cs::UsbCamera gear_cam;
	cs::UsbCamera shooter_cam;

	cs::CvSink gear_sink;
	cs::CvSink shooter_sink;
};

#endif /* SRC_VISION_H_ */
