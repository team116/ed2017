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
#include <Vision.h>
#include "Diagnostics.h"
#include "Log.h"

#include <IterativeRobot.h>

class Robot: public frc::IterativeRobot {
private:
	Autonomous* autonomous;
	Climber* climber;
	Gear* gear;
	Intake* intake;
	Mobility* mobility;
	OI* oi;
	Shooter* shooter;
	Vision* vision;
	Diagnostics* diagnostics;
	Log* log;

public:
	void RobotInit() {
		try {
			log = Log::getInstance();
		} catch(std::exception* e) {
			frc::DriverStation::ReportError("Error initializing Log");
			frc::DriverStation::ReportError(e->what());
		}

		log->write(Log::DEBUG_LEVEL, "Log Initialized");

		try {
			autonomous = Autonomous::getInstance();
		} catch(std::exception* e) {
			log->write(Log::ERROR_LEVEL, "Error initializing Autonomous\n%s", e->what());
		}

		log->write(Log::DEBUG_LEVEL, "Autonomous Initialized");

		try {
			climber = Climber::getInstance();
		} catch(std::exception* e) {
			log->write(Log::ERROR_LEVEL, "Error initializing Climber\n%s", e->what());
		}

		log->write(Log::DEBUG_LEVEL, "Climber Initialized");

		try {
			gear = Gear::getInstance();
		} catch(std::exception* e) {
			log->write(Log::ERROR_LEVEL, "Error initializing Gear\n%s", e->what());
		}

		log->write(Log::DEBUG_LEVEL, "Gear Initialized");

		try {
			intake = Intake::getInstance();
		} catch(std::exception* e) {
			log->write(Log::ERROR_LEVEL, "Error initializing Intake\n%s", e->what());
		}

		log->write(Log::DEBUG_LEVEL, "Intake Initialized");

		try {
			mobility = Mobility::getInstance();
		} catch(std::exception* e) {
			log->write(Log::ERROR_LEVEL, "Error initializing Mobility\n%s", e->what());
		}

		log->write(Log::DEBUG_LEVEL, "Mobility Initialized");

		try {
			oi = OI::getInstance();
		} catch(std::exception* e) {
			log->write(Log::ERROR_LEVEL, "Error initializing OI\n%s", e->what());
		}

		log->write(Log::DEBUG_LEVEL, "OI Initialized");

		try {
			shooter = Shooter::getInstance();
		} catch(std::exception* e) {
			log->write(Log::ERROR_LEVEL, "Error initializing Shooter\n%s", e->what());
		}

		log->write(Log::DEBUG_LEVEL, "Shooter Initialized");

		try {
			vision = Vision::getInstance();
		} catch(std::exception* e) {
			log->write(Log::ERROR_LEVEL, "Error initializing Vision\n%s", e->what());
		}

		log->write(Log::DEBUG_LEVEL, "Vision Initialized");

		try {
			diagnostics = Diagnostics::getInstance();
		} catch(std::exception* e) {
			log->write(Log::ERROR_LEVEL, "Error initializing Diagnostics\n%s", e->what());
		}

		log->write(Log::DEBUG_LEVEL, "Diagnostics Initialized");
	}

	void DisabledInit() {
		mobility->stopDriveStraight();
		mobility->disableDistancePID();
		mobility->disableRotationPID();
		shooter->disableAzimuthPID();
		shooter->disableShooterPID();
	}

	void AutonomousInit() override {
		try {
			gear->enableCompressor();
		} catch(std::exception* e) {
			log->write(Log::ERROR_LEVEL, "Error in AutonomousInit\n%s", e->what());
		}
	}

	void AutonomousPeriodic() {
		try {
			autonomous->process();
			mobility->process();
			climber->process();
			gear->process();
			intake->process();
			shooter->process();
			diagnostics->process();
		} catch(std::exception* e) {
			log->write(Log::ERROR_LEVEL, "Error in AutonomousPeriodic\n%s", e->what());
		}
	}

	void TeleopInit() {
		try {

		} catch(std::exception* e) {
			log->write(Log::ERROR_LEVEL, "Error in TeleopInit\n%s", e->what());
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
			diagnostics->process();
		} catch(std::exception* e) {
			log->write(Log::ERROR_LEVEL, "Error in TeleopPeriodic\n%s", e->what());
		}
	}

	void TestInit() {
		try {

		} catch(std::exception* e) {
			log->write(Log::ERROR_LEVEL, "Error in TestInit\n%s", e->what());
		}
	}

	void TestPeriodic() {
		try {
			TeleopPeriodic();
		} catch(std::exception* e) {
			log->write(Log::ERROR_LEVEL, "Error in TestPeriodic\n%s", e->what());
		}
	}
};

START_ROBOT_CLASS(Robot)
