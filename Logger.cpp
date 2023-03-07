//
// Created by Hady Sallam on 3/7/2023.
//

#include "Logger.h"

std::mutex log_mutex;

/* Mutex ensures that only one thread has access to an operator overloading
   by using operations like a lock and unlock
 * here , mutex is released at the end of func automatically
*/


cppLogger::cppLogger(std::string appId, LogLevel logLevel, LogMode logMode, std::string FileName) {

    if (appId != "") { /* to check that ,fileId (Name) is not empty  */
        this->appId = appId;
        this->log_Level = logLevel;
        this->log_Mode = logMode;

        if (logMode == mFile) { /* in case , log mode is text file, so we must enter file name */
            fout.open(FileName + ".txt", std::ios::app);
        }

    } else {
        // Do Nothing
    }
}


void cppLogger::SetLogLevel(std::string appId, LogLevel logLevel) {

    if (appId != "") { /* to check that ,fileId (Name) is not empty  */
        this->appId = appId;
        this->log_Level = logLevel;

    } else {
        // Do Nothing
    }
}

void cppLogger::SetLogMode(std::string appId, LogMode logMode) {

    if (appId != "") { /* to check that ,fileId (Name) is not empty  */
        this->appId = appId;
        this->log_Mode = logMode;

    } else {
        // Do Nothing
    }
}

std::ostream &operator<<(cppLogger &logObj, const char *msg) {

    std::lock_guard<std::mutex> guard(log_mutex);
    /* mutex Lock to ensures that only one thread has access to an operator overloading */


    time_t tmNow = time(NULL);
    struct tm my_time = *localtime(&tmNow);
    /* to return time stamp (current time) */

    static int16_t counterA = 0;  /* count when App1 enter this function */
    static int16_t counterB = 0;  /* count when App2 enter this function */
    static int16_t counter = 0;   /* generic counter get value of current APP counter to print it for user*/
    /* counterA*/


    if (logObj.appId == "AppId1") { /* Here app1 (Thread 1) enter func */
        counterA++;
        counter = counterA;

    } else if (logObj.appId == "AppId2") { /* Here app2 (Thread 2) enter func */
        counterB++;
        counter = counterB;
    } else {
        // Do Nothing
    }

    /*
     *  Log format
     *  | TS(hh:mm:ss) |AppId | LogNum | LogLevel | LogMsg |
     *   std::cout << "| " << my_time.tm_hour << ":" << my_time.tm_min << ":" << my_time.tm_sec << " |" <<
     *   previous line pasrsing timestamp to HH:MM:SS
         logObj.appId << " | " << counter << " | " << "lOff" << " | " << msg << std::endl;
         previous line |AppId | LogNum | LogLevel | LogMsg |
    */
    if (logObj.log_Mode == mConsole) { /* user request output in console */
        switch (logObj.log_Level) { /* switch between multiple log level for each app */
            case OffLevel:

                std::cout << "| " << my_time.tm_hour << ":" << my_time.tm_min << ":" << my_time.tm_sec << " |" <<
                          logObj.appId << " | " << counter << " | " << "lOff" << " | " << msg << std::endl;
                break;
            case ErrorLevel:

                std::cout << "| " << my_time.tm_hour << ":" << my_time.tm_min << ":" << my_time.tm_sec << " |" <<
                          logObj.appId << " | " << counter << " | " << "lError" << " | " << msg << std::endl;
                break;

            case WarnLevel:

                std::cout << "| " << my_time.tm_hour << ":" << my_time.tm_min << ":" << my_time.tm_sec << " |" <<
                          logObj.appId << " | " << counter << " | " << "lWarn" << " | " << msg << std::endl;
                break;

            case InfoLevel:

                std::cout << "| " << my_time.tm_hour << ":" << my_time.tm_min << ":" << my_time.tm_sec << " |" <<
                          logObj.appId << " | " << counter << " | " << "lInfo" << " | " << msg << std::endl;
                break;

            case DebugLevel:

                std::cout << "| " << my_time.tm_hour << ":" << my_time.tm_min << ":" << my_time.tm_sec << " |" <<
                          logObj.appId << " | " << counter << " | " << "lDebug" << " | " << msg << std::endl;
                break;

        }
    } else if (logObj.log_Mode == mFile) { /* user request output in text file */
        switch (logObj.log_Level) { /* switch between multiple log level for each app */
            case OffLevel:

                logObj.fout << "| " << my_time.tm_hour << ":" << my_time.tm_min << ":" << my_time.tm_sec << " |" <<
                            logObj.appId << " | " << counter << " | " << "lOff" << " | " << msg << std::endl;
                break;
            case ErrorLevel:

                logObj.fout << "| " << my_time.tm_hour << ":" << my_time.tm_min << ":" << my_time.tm_sec << " |" <<
                            logObj.appId << " | " << counter << " | " << "lError" << " | " << msg << std::endl;
                break;

            case WarnLevel:

                logObj.fout << "| " << my_time.tm_hour << ":" << my_time.tm_min << ":" << my_time.tm_sec << " |" <<
                            logObj.appId << " | " << counter << " | " << "lWarn" << " | " << msg << std::endl;
                break;

            case InfoLevel:

                logObj.fout << "| " << my_time.tm_hour << ":" << my_time.tm_min << ":" << my_time.tm_sec << " |" <<
                            logObj.appId << " | " << counter << " | " << "lInfo" << " | " << msg << std::endl;
                break;

            case DebugLevel:

                logObj.fout << "| " << my_time.tm_hour << ":" << my_time.tm_min << ":" << my_time.tm_sec << " |" <<
                            logObj.appId << " | " << counter << " | " << "lDebug" << " | " << msg << std::endl;
                break;

        }
    } else {
        // Do Nothing
    } // Switch Closed

    return std::cout;
}

cppLogger::~cppLogger() {
    if (fout.is_open()) { /* if file is opened when user select text file for ouput log messages */
        fout.close(); /* close text file */
    }
}