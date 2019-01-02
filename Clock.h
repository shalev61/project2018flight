#ifndef CLOCK_H
#define CLOCK_H

#include <chrono>
using namespace std::chrono;

//retrun milliseconds as object
inline milliseconds convertIntToMilliseconds(int time) {
    return duration_cast<milliseconds>(milliseconds(time));
}

//get the time now in milliseconds
inline milliseconds theTimeNowInMillis() {
    return duration_cast<milliseconds>(system_clock::now().time_since_epoch());
}

#endif