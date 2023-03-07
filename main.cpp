
#include <thread>
#include "Logger.h"

/* Creating two object */
cppLogger App1("AppId1", WarnLevel, mFile, "LoggerFile");
cppLogger App2("AppId2", WarnLevel, mFile, "LoggerFile");

void log_func(int th) {

    if (th == 0) { /* thread one is processing now */

        App1 << "hello From Text File ";

        App1.SetLogLevel("AppId1", DebugLevel); /* try to test log level */
        App1 << "hello From new Log Level";

        App1.SetLogMode("AppId1", mConsole); /* try to test log Mode */
        App1 << "hello From Command Line ";


    } else if (th == 1) { /* thread two is processing now */

        App2 << "hello From Text File ";

        App2.SetLogLevel("AppId2", ErrorLevel); /* try to test log level */
        App2 << "hello From new Log Level";

        App2.SetLogMode("AppId2", mConsole);  /* try to test log Mode */
        App2 << "hello From Command Line ";

    }

}

int main() {


    std::thread th1(log_func, 0); /* create thread 1 */
    std::thread th2(log_func, 1); /* create thread 2 */

    /* join method :
    * the calling thread goes into a waiting state. It remains in a waiting state until the referenced thread terminates.
     */
    
    th1.join();
    th2.join();

    return 0;
}
