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
	}

	void AutonomousInit() override {

	}

	void AutonomousPeriodic() {
		vision->process();
		autonomous->process();
		mobility->process();
		climber->process();
		gear->process();
		intake->process();
		shooter->process();
	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {
		oi->process();
		vision->process();
		mobility->process();
		climber->process();
		gear->process();
		intake->process();
		shooter->process();
	}

	void TestPeriodic() {

	}
};

START_ROBOT_CLASS(Robot)
