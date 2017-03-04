/*
 * Log.cpp
 *
 *  Created on: Jan 26, 2017
 *      Author: Will
 */

#include <Log.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <DriverStation.h>
#include <WPILib.h>

Log* Log::INSTANCE = nullptr;

const bool Log::PRINT_TO_DS = true;

Log::Log()
{
	char* filepath = generateLogFilename();
	log_file = fopen(filepath, "w");
	time_t current_time;
	time(&current_time);
	fprintf(log_file,"Began logging at %s\n",ctime(&current_time));
	fflush(log_file);
}

Log::~Log()
{
	if(log_file){
		time_t end_time;
		time(&end_time);
		fprintf(log_file,"Stopped logging at %s\n", ctime(&end_time));
		fprintf(log_file,"--------------------------------------------------\n");
		fclose(log_file);
	}
}

const Log::debugLevelType MAXIMUM_DEBUG_LEVEL = Log::TRACE_LEVEL;
//this can be set to the least urgent type of message that we want to log
//for the moment it's at trace so we'll log EVERYTHING

void Log::write(Log::debugLevelType debug_level, const char* str, ...)
{
	if(log_file && (debug_level<=MAXIMUM_DEBUG_LEVEL)){
		char buffer[256];
		va_list args;

		va_start(args,str);
		vsprintf(buffer,str,args);
		va_end(args);

		char system_info[255];
		bool is_error = false;

		if(PRINT_TO_DS) {
			frc::DriverStation& ds = frc::DriverStation::GetInstance();
			switch(debug_level) {
			case Log::ERROR_LEVEL:
				//Allow it to fall through to warning because they both do the same thing anyways
				is_error = true;
				snprintf(system_info, 255, "Battery: %2.2f BrownOut: %d IsDSAttached: %d IsFMSAttached: %d IsSysActive: %d Enabled: %d IsAutonomous: %d IsTeleop: %d IsTest: %d",
										ds.GetBatteryVoltage(),
										ds.IsBrownedOut(),
										ds.IsDSAttached(),
										ds.IsFMSAttached(),
										ds.IsSysActive(),
										ds.IsEnabled(),
										ds.IsAutonomous(),
										ds.IsOperatorControl(),
										ds.IsTest());
			case Log::WARNING_LEVEL:
				frc::DriverStation::ReportError(buffer);
				break;
			}
		}

		char timestamp[29];
		generateTimestamp(timestamp, 29);

		fputs(timestamp, log_file);
		fputs("\t", log_file);
		fputs(buffer, log_file);
		if(is_error) {
			fputs("\n SYSTEM DUMP: ", log_file);
			fputs(system_info, log_file);
		}
		fputs("\n", log_file);
		fflush(log_file);
	}
}

void Log::generateTimestamp(char* str, size_t len)
{
	struct tm* local_time;
	time_t t;
	time(&t);
	local_time = localtime(&t);

	snprintf(str, len, "[%02i:%02i:%02i Match Time: %3.0f]", local_time->tm_hour, local_time->tm_min, local_time->tm_sec, frc::DriverStation::GetInstance().GetMatchTime());
}

char* Log::generateLogFilename()
{
	const char base[] = "log ";
	const char ext[] = ".txt";
	FILE* previous_log_file;

	int file_num = 0;

	while(true){
		sprintf(filename,"/home/lvuser/%s%d%s",base,file_num,ext);

		previous_log_file = fopen(filename,"r");
		if(!previous_log_file){
			break;
		}
		else{
			fclose(previous_log_file);
			file_num++;
		}
	}

	printf("Log File Name = %s\n", filename);
	return filename;
}

Log* Log::getInstance()
{
	if (INSTANCE == nullptr)
	{
		INSTANCE = new Log();
	}
	return INSTANCE;
}
