//
// Created by Hady Sallam on 3/7/2023.
//

#ifndef ASSIGNMENT_1_LOGGER_H
#define ASSIGNMENT_1_LOGGER_H

#include <iostream>
#include <mutex>
#include <fstream>

/* enum for log levels in system */
typedef enum {
    OffLevel,
    ErrorLevel,
    WarnLevel,
    InfoLevel,
    DebugLevel
} LogLevel;

/* enum to choose output system */
typedef enum {
    mFile,
    mConsole,
} LogMode;


class cppLogger {
private:
    std::string appId;
    LogLevel log_Level;
    LogMode log_Mode;
    std::ofstream fout;

public:

    /* constructor taking 4 argument
     * appId => this class support multi threading so it may be more than id
     * log Level => log level can be change in run time
     * log Mode => to determine log output between console or cmd
     * File name => file name only active when mode is mFile
     * */
    cppLogger(std::string appId, LogLevel logLevel, LogMode logMode, std::string FileName);

    /*
     operator oveloading to print log message
     user pass only message to it in main function
     */
    friend std::ostream &operator<<(cppLogger &logObj, const char *msg);

    /*
     user can change log Level of each app in run time using this function
     */
    void SetLogLevel(std::string appId, LogLevel logLevel);

    /*
     user can change log Mode of each app in run time using this function
     */
    void SetLogMode(std::string appId, LogMode logMode);

    ~cppLogger(); /* Destructor */
};


#endif //ASSIGNMENT_1_LOGGER_H
