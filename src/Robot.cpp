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
		autonomous = Autonomous::getInstance();
		climber = Climber::getInstance();
		gear = Gear::getInstance();
		intake = Intake::getInstance();
		mobility = Mobility::getInstance();
		oi = OI::getInstance();
		shooter = Shooter::getInstance();
		vision = Vision::getInstance();
		diagnostics = Diagnostics::getInstance();
		log = Log::getInstance();
	}

	void AutonomousInit() override {

	}

	void AutonomousPeriodic() {
		autonomous->process();
		mobility->process();
		climber->process();
		gear->process();
		intake->process();
		shooter->process();
		diagnostics->process();
	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {
		oi->process();
		mobility->process();
		climber->process();
		gear->process();
		intake->process();
		shooter->process();
		diagnostics->process();

	}

	void TestInit() {
	}

	void TestPeriodic() {
		TeleopPeriodic();
	}
};

START_ROBOT_CLASS(Robot)
