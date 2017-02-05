/*
 * Vision.cpp
 *
 *  Created on: Jan 15, 2017
 *      Author: Will
 */

#include <Vision.h>

Vision* Vision::INSTANCE;

Vision::Vision() {
	mobility = Mobility::getInstance();
	shooter = Shooter::getInstance();

	processor = new grip::GripPipeline();

	gear_cam = CameraServer::GetInstance()->StartAutomaticCapture("Gear Cam", 0);
	gear_cam.SetFPS(15);
	gear_cam.SetResolution(CAMERA_WIDTH, CAMERA_HEIGHT);

	shooter_cam = CameraServer::GetInstance()->StartAutomaticCapture("Shooter Cam", 1);
	shooter_cam.SetFPS(15);
	shooter_cam.SetResolution(CAMERA_WIDTH, CAMERA_HEIGHT);

	gear_sink = CameraServer::GetInstance()->GetVideo(gear_cam);
	shooter_sink = CameraServer::GetInstance()->GetVideo(shooter_cam);

	//Set camera settings
	std::vector<cs::VideoProperty> props = gear_cam.EnumerateProperties();
	if(props.size() >= 14) {
		props[1].Set(0);//brightness
		props[3].Set(100);//contrast
		props[5].Set(100);//saturation
		props[6].Set(0);//auto white balance
		props[8].Set(10000);//white balance
		props[12].Set(1);//auto exposure
		props[14].Set(10);//exposure
	}

	props = shooter_cam.EnumerateProperties();
	if(props.size() >= 14) {
		props[1].Set(0);//brightness
		props[3].Set(100);//contrast
		props[5].Set(100);//saturation
		props[6].Set(0);//auto white balance
		props[8].Set(10000);//white balance
		props[12].Set(1);//auto exposure
		props[14].Set(10);//exposure*/
	}
}

void Vision::process() {
	cv::Mat img;
	gear_sink.GrabFrame(img);
	processor->process(img);
}

bool Vision::canSeeGearHook() {
	return false;
}

bool Vision::canSeeHighGoal() {
	return false;
}

float Vision::gearHookDegreesHorizontal() {
	return 0.0;
}

float Vision::gearHookDistance() {
	return 0.0;
}

float Vision::highGoalDegreesHorizontal() {
	return 0.0;
}

float Vision::highGoalDistance() {
	return 0.0;
}

void Vision::turnToGearHook() {
	mobility->turnDegrees(-gearHookDegreesHorizontal());
}

void Vision::turnToHighGoal() {

}

void Vision::setGearCamMode(CameraMode mode) {
	std::vector<cs::VideoProperty> props = gear_cam.EnumerateProperties();
	switch(mode) {
	case Human:
		break;
	case Computer:
		props[1].Set(0);//brightness
		props[3].Set(100);//contrast
		props[5].Set(100);//saturation
		props[6].Set(0);//auto white balance
		props[8].Set(10000);//white balance
		props[12].Set(1);//auto exposure
		props[14].Set(10);//exposure
		break;
	}
}

void Vision::setShooterCamMode(CameraMode mode) {
	std::vector<cs::VideoProperty> props = shooter_cam.EnumerateProperties();
	switch(mode) {
	case Human:
		break;
	case Computer:
		props[1].Set(0);//brightness
		props[3].Set(100);//contrast
		props[5].Set(100);//saturation
		props[6].Set(0);//auto white balance
		props[8].Set(10000);//white balance
		props[12].Set(1);//auto exposure
		props[14].Set(10);//exposure
		break;
	}
}

Vision* Vision::getInstance()
{
	if(INSTANCE == nullptr) {
		INSTANCE = new Vision();
	}

	return INSTANCE;
}
