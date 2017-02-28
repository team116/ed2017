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
#include <Socket.h>

#include <AutoPlays/Routine.h>
#include <AutoPlays/Routines/CrossBaseline.h>
#include <AutoPlays/Routines/DeliverGear.h>
#include <AutoPlays/Routines/DeliverGearandShoot.h>
#include <AutoPlays/Routines/DeliverGearandShootandEmptyHopper.h>
#include <AutoPlays/Routines/DoNothing.h>
#include <AutoPlays/Routines/EmptyAllHoppers.h>
#include <AutoPlays/Routines/EmptyHopper.h>
#include <AutoPlays/Routines/EmptyHopperandShoot.h>
#include <AutoPlays/Routines/Shoot.h>
#include <AutoPlays/Routines/ShootandCrossBaseline.h>
#include <AutoPlays/Routines/ShootandDeliverGear.h>

class Robot: public frc::IterativeRobot {
private:
	Climber* climber;
	Gear* gear;
	Intake* intake;
	Mobility* mobility;
	OI* oi;
	Shooter* shooter;
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
		} catch(std::exception* e) {
			frc::DriverStation::ReportError("Error initializing Log");
			frc::DriverStation::ReportError(e->what());
		}

		log->write(Log::DEBUG_LEVEL, "Log Initialized");

		try {
			socket = new Socket();
		} catch(std::exception* e) {
			log->write(Log::ERROR_LEVEL, "Error initializing Socket\n%s", e->what());
		}

		log->write(Log::DEBUG_LEVEL, "Autonomous Initialized");
		try	{
		   //socket = new Socket();
		} catch(std::exception* e) {
					log->write(Log::ERROR_LEVEL, "Error initializing Socket\n%s", e->what());
		}
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

		mobility->disableRightEncoder();
		mobility->enableLeftEncoder();
	}

	void DisabledInit() {
		mobility->stopDriveStraight();
		mobility->stopDriveDistance();
		mobility->disableDistancePID();
		mobility->disableRotationPID();
		shooter->disableAzimuthPID();
		shooter->disableShooterPID();
		shooter->stopAzimuthVisionTrack();

		gear->disableCompressor();

		if(auto_routine != nullptr) {
			auto_routine->end();
		}
	}
	void DisabledPeriodic(){
		Socket::Packet packet = socket->process();
		if (packet.play == Socket::NO_UPDATE.play &&
		    packet.location == Socket::NO_UPDATE.location &&
			packet.alliance == Socket::NO_UPDATE.alliance){
			return;
		}

		delete auto_routine;
		auto_routine = nullptr;
		Socket::PlaySelection selection = Socket::packetToSelection(packet);
		switch (selection.play) {
		case Utils::AutoPlay::CrossBaseline:
			auto_routine = new CrossBaseline(selection.location);
			break;
		case Utils::AutoPlay::DeliverGear:
			auto_routine = new DeliverGear(selection.location);
			break;
		case Utils::AutoPlay::DeliverGearAndShoot:
			auto_routine = new DeliverGearandShoot(selection.alliance, selection.location);
			break;
		case Utils::AutoPlay::DeliverGearAndShootAndEmptyHopper:
			auto_routine = new DeliverGearandShootandEmptyHopper();
			break;
		case Utils::AutoPlay::DoNothing:
			auto_routine = new DoNothing();
			break;
		case Utils::AutoPlay::EmptyAllHoppers:
			auto_routine = new EmptyAllHoppers();
			break;
		case Utils::AutoPlay::EmptyHopper:
			auto_routine = new EmptyHopper();
			break;
		case Utils::AutoPlay::EmptyHopperAndShoot:
			auto_routine = new EmptyHopperandShoot();
			break;
		case Utils::AutoPlay::Shoot:
			auto_routine = new Shoot(selection.alliance, selection.location);
			break;
		case Utils::AutoPlay::ShootAndCrossBaseline:
			auto_routine = new ShootandCrossBaseline(selection.alliance, selection.location);
			break;
		case Utils::AutoPlay::ShootAndDeliverGear:
			auto_routine = new ShootandDeliverGear();
			break;
		default:
			log->write(Log::WARNING_LEVEL, "Socket::PlaySelection contained unknown play value %d", (int)selection.play);
		}
	}
	void AutonomousInit() override {
		try {

			mobility->turnDegrees(15);

			/*if(vision->canSeeGearHook()) {
				mobility->turnDegrees(vision->gearHookDegreesHorizontal());
			}*/


			//Set the play here
			//auto_routine = new DeliverGear(Utils::AutoLocation::MiddleForward);

			//auto_routine->start();

			//timer = new Timer();

			//input = std::stof(SmartDashboard::GetString("DB/String 0", "0.0"));
			/*timer->Reset();
			timer->Start();
			mobility->startDriveStraight();
			mobility->setStraightSpeed(1.0);*/
			//mobility->disableLeftEncoder();
			//mobility->disableRightEncoder();
			//mobility->StartDriveDistance(24);

			//Sensor turn degrees
			//mobility->turnDegrees(15);

			//No sensor turn degrees tuning
			/*timer->Reset();
			timer->Start();
			mobility->resetGyro();
			mobility->setLeft(1.0);
			mobility->setRight(-1.0);*/

		} catch(std::exception* e) {
			log->write(Log::ERROR_LEVEL, "Error in AutonomousInit\n%s", e->what());
		}
	}

	void AutonomousPeriodic() {
		try {
			mobility->process();
			climber->process();
			gear->process();
			intake->process();
			shooter->process();
			diagnostics->process();

			//auto_routine->process();

			/*if(timer->HasPeriodPassed(input)) {
				mobility->setStraightSpeed(0.0);
				mobility->setLeft(0.0);
				mobility->setRight(0.0);
				frc::DriverStation::ReportError("Angle: " + std::to_string(mobility->getGyroAngle()));
			}*/
		} catch(std::exception* e) {
			log->write(Log::ERROR_LEVEL, "Error in AutonomousPeriodic\n%s", e->what());
		}
	}

	void TeleopInit() {
		try {
			DisabledInit();
			mobility->resetGyro();
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
			//diagnostics->process();
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
			gear->enableCompressor();
		} catch(std::exception* e) {
			log->write(Log::ERROR_LEVEL, "Error in TestPeriodic\n%s", e->what());
		}
	}
	~Robot(){
		delete socket;
		socket = nullptr;
	}
};

START_ROBOT_CLASS(Robot)
