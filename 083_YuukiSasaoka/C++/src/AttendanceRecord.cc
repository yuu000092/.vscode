#include "../include/AttendanceRecord.h"
//#include "../include/AttendanceRepository.h"
#include <iostream>
#include <time.h>
#include <chrono>


time_t AttendanceRecord::startTime() const {
    // Implement your logic here, for example:
    return std::time(nullptr);
}

time_t AttendanceRecord::endTime() const{

    return std::time(nullptr);
}
