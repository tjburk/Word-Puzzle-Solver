// This timer typically has 1/1000000 second (1 micro-second) accuracy
// under most Linux distributions

/**********************************************
 * Title: Timer
 * Author: Aaron Bloomfield
 * Date: 10/16/22 Date Written: 2014
 * Availability: https://github.com/aaronbloomfield/pdr repository
 **********************************************/

#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

class timer {
public:
    timer();
    timer(timer& myTimer);
    void start();
    void stop();

    // Returns the time elapsed, in seconds
    double getTime();
private:
    steady_clock::time_point start_time, stop_time;
    bool running;

};

ostream& operator<<(ostream& theStream, timer& theTimer);

#endif