#include <iostream>
#include <memory>
#include <string>
#include <Autonomous.h>
#include <Climber.h>
#include <Gear.h>
#include <Intake.h>
#include <Mobility.h>
#include <OI.h>
#include <Shooter.h>
#include <Feeder.h>
#include <Vision.h>
#include "Diagnostics.h"
#include "Log.h"
#include "AutoPlays/Routine.h"
#include "AutoPlays/Routines/DoNothing.h"
#include "AutoPLays/Routines/CrossBaseline.h"
#include "AutoPlays/Routines/DeliverGear.h"
#include "AutoPlays/Routines/Test.h"
#include "AutoPlays/Routines/PositionGear.h"
#include "AutoPlays/Routines/DeliverGearandShoot.h"
#include "AutoPlays/Routines/DeliverGearandTravel.h"
#include <IterativeRobot.h>
#include <Socket.h>

class Robot: public frc::IterativeRobot {
private:
	Autonomous* autonomous;
	Climber* climber;
	Gear* gear;
	Intake* intake;
	Mobility* mobility;
	OI* oi;
	Shooter* shooter;
	Feeder* feeder;
	Vision* vision;
	Diagnostics* diagnostics;
	Log* log;
	Socket* socket;
	Routine* auto_routine;

	float input;
	Timer* timer;

public:
	void RobotInit() {
		try {
			log = Log::getInstance();
		} catch(std::exception& e) {
			frc::DriverStation::ReportError("Error initializing Log");
			frc::DriverStation::ReportError(e.what());
		}

		log->write(Log::DEBUG_LEVEL, "Log Initialized");

		try {
			autonomous = Autonomous::getInstance();
		} catch(std::exception& e) {
			log->write(Log::ERROR_LEVEL, "Error initializing Autonomous\n%s", e.what());
		}

		log->write(Log::DEBUG_LEVEL, "Autonomous Initialized");
		try	{
		   //socket = new Socket();
		} catch(std::exception& e) {
					log->write(Log::ERROR_LEVEL, "Error initializing Socket\n%s", e.what());
		}
		try {
			climber = Climber::getInstance();
		} catch(std::exception& e) {
			log->write(Log::ERROR_LEVEL, "Error initializing Climber\n%s", e.what());
		}

		log->write(Log::DEBUG_LEVEL, "Climber Initialized");

		try {
			gear = Gear::getInstance();
		} catch(std::exception& e) {
			log->write(Log::ERROR_LEVEL, "Error initializing Gear\n%s", e.what());
		}

		log->write(Log::DEBUG_LEVEL, "Gear Initialized");

		try {
			intake = Intake::getInstance();
		} catch(std::exception& e) {
			log->write(Log::ERROR_LEVEL, "Error initializing Intake\n%s", e.what());
		}

		log->write(Log::DEBUG_LEVEL, "Intake Initialized");

		try {
			mobility = Mobility::getInstance();
		} catch(std::exception& e) {
			log->write(Log::ERROR_LEVEL, "Error initializing Mobility\n%s", e.what());
		}

		log->write(Log::DEBUG_LEVEL, "Mobility Initialized");

		try {
			oi = OI::getInstance();
		} catch(std::exception& e) {
			log->write(Log::ERROR_LEVEL, "Error initializing OI\n%s", e.what());
		}

		log->write(Log::DEBUG_LEVEL, "OI Initialized");

		try {
			shooter = Shooter::getInstance();
		} catch(std::exception& e) {
			log->write(Log::ERROR_LEVEL, "Error initializing Shooter\n%s", e.what());
		}

		log->write(Log::DEBUG_LEVEL, "Shooter Initialized");

		try {
			feeder = Feeder::getInstance();
		} catch(std::exception& e) {
			log->write(Log::ERROR_LEVEL, "Error initializing Feeder\n%s", e.what());
		}

		log->write(Log::DEBUG_LEVEL, "Feeder Initialized");

		try {
			vision = Vision::getInstance();
		} catch(std::exception& e) {
			log->write(Log::ERROR_LEVEL, "Error initializing Vision\n%s", e.what());
		}

		log->write(Log::DEBUG_LEVEL, "Vision Initialized");

		try {
			diagnostics = Diagnostics::getInstance();
		} catch(std::exception& e) {
			log->write(Log::ERROR_LEVEL, "Error initializing Diagnostics\n%s", e.what());
		}

		log->write(Log::DEBUG_LEVEL, "Diagnostics Initialized");

		mobility->disableRightEncoder();
		mobility->enableLeftEncoder();

		/*
		 * =====***!***=====
		 * SET AUTO PLAY HERE
		 * =====***!***=====
		 */
		Utils::Alliance auto_alliance = Utils::Alliance::Red;
		Utils::AutoLocation auto_location = Utils::AutoLocation::LoadingStation;
		auto_routine = new DeliverGear(auto_alliance, auto_location, true);



		if(typeid(*auto_routine) == typeid(DoNothing)) {
			NetworkTable::GetTable("SmartDashboard")->PutNumber("AutoPlay", 1);
		}
		else if(typeid(*auto_routine) == typeid(CrossBaseline)) {
			NetworkTable::GetTable("SmartDashboard")->PutNumber("AutoPlay", 6);
		}
		else if(typeid(*auto_routine) == typeid(PositionGear)) {
			NetworkTable::GetTable("SmartDashboard")->PutNumber("AutoPlay", 2);
		}
		else if(typeid(*auto_routine) == typeid(DeliverGear)) {
			NetworkTable::GetTable("SmartDashboard")->PutNumber("AutoPlay", 3);
		}
		else if(typeid(*auto_routine) == typeid(DeliverGearandShoot)) {
			NetworkTable::GetTable("SmartDashboard")->PutNumber("AutoPlay", 4);
		}
		else if(typeid(*auto_routine) == typeid(DeliverGearandTravel)) {
			NetworkTable::GetTable("SmartDashboard")->PutNumber("AutoPlay", 5);
		}
		else {
			NetworkTable::GetTable("SmartDashboard")->PutNumber("AutoPlay", -1);
		}

		switch(auto_alliance) {
		case Utils::Alliance::Blue:
			NetworkTable::GetTable("SmartDashboard")->PutNumber("AutoSide", 2);
			break;
		case Utils::Alliance::Red:
			NetworkTable::GetTable("SmartDashboard")->PutNumber("AutoSide", 1);
			break;
		default:
			NetworkTable::GetTable("SmartDashboard")->PutNumber("AutoSide", -1);
			break;
		}

		switch(auto_location) {
		case Utils::AutoLocation::Boiler:
			NetworkTable::GetTable("SmartDashboard")->PutNumber("AutoPosition", 1);
			break;
		case Utils::AutoLocation::Middle:
			NetworkTable::GetTable("SmartDashboard")->PutNumber("AutoPosition", 2);
			break;
		case Utils::AutoLocation::LoadingStation:
			NetworkTable::GetTable("SmartDashboard")->PutNumber("AutoPosition", 3);
			break;
		default:
			NetworkTable::GetTable("SmartDashboard")->PutNumber("AutoPosition", -1);
			break;
		}
	}

	void DisabledInit() {
		NetworkTable::GetTable("SmartDashboard")->PutBoolean("Auton Enabled", false);
		NetworkTable::GetTable("SmartDashboard")->PutBoolean("Tele Enabled", false);

		mobility->stopDriveStraight();
		mobility->stopDriveDistance();
		mobility->stopTurnDegrees();
		mobility->disableDistancePID();
		mobility->disableRotationPID();
		shooter->disableAzimuthPID();
		shooter->disableShooterPID();
		shooter->stopAzimuthVisionTrack();

		gear->disableCompressor();

		if(auto_routine != nullptr) {
			log->write(Log::TRACE_LEVEL, "Disabled Init ending routine");
			auto_routine->end();
		}
	}
	void DisabledPeriodic(){
		//Makes sure the sensor toggles get read
		oi->process();

		/*int AP = socket->process();
		if(AP == -1){
			return;
		}*/
	}

	void AutonomousInit() override {
		try {
			//Makes sure the sensor toggles get read
			oi->process();

			//Set the play here
			auto_routine = new PositionGear(Utils::Alliance::Blue, Utils::AutoLocation::Boiler, true);


			auto_routine->start();

			NetworkTable::GetTable("SmartDashboard")->PutBoolean("Auton Enabled", true);

		} catch(std::exception& e) {
			log->write(Log::ERROR_LEVEL, "Error in AutonomousInit\n%s", e.what());
		}
	}

	void AutonomousPeriodic() {
		try {
			mobility->process();
			climber->process();
			gear->process();
			intake->process();
			shooter->process();
			feeder->process();
			diagnostics->process();

			if(auto_routine != nullptr) {
				if(auto_routine->isFinished()) {
					auto_routine->end();
					auto_routine = nullptr;
					log->write(Log::TRACE_LEVEL, "Ending routine in auto periodic");
				} else {
					auto_routine->process();
				}
			}

		} catch(std::exception& e) {
			log->write(Log::ERROR_LEVEL, "Error in AutonomousPeriodic\n%s", e.what());
		}
	}

	void TeleopInit() {
		try {
			DisabledInit();
			mobility->resetGyro();
			NetworkTable::GetTable("SmartDashboard")->PutBoolean("Tele Enabled", true);
		} catch(std::exception& e) {
			log->write(Log::ERROR_LEVEL, "Error in TeleopInit\n%s", e.what());
		}
	}

	void TeleopPeriodic() {
		try {
			oi->process();
			mobility->process();
			climber->process();
			gear->process();
			intake->process();
			shooter->process();
			feeder->process();
			//diagnostics->process();
		} catch(std::exception& e) {
			log->write(Log::ERROR_LEVEL, "Error in TeleopPeriodic\n%s", e.what());
		}
	}

	void TestInit() {
		try {
		} catch(std::exception& e) {
			log->write(Log::ERROR_LEVEL, "Error in TestInit\n%s", e.what());
		}
	}

	void TestPeriodic() {
		try {
			//TeleopPeriodic();
			gear->enableCompressor();
		} catch(std::exception& e) {
			log->write(Log::ERROR_LEVEL, "Error in TestPeriodic\n%s", e.what());
		}
	}
	~Robot(){
		//delete socket;
	}
};

START_ROBOT_CLASS(Robot)
