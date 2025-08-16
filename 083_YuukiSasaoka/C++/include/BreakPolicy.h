#ifndef BREAK_POLICY_H_
#define BREAK_POLICY_H_

#include "AttendanceService.h"
#include <iostream>
#include <string>

class BreakPolicy {
public:
    BreakPolicy(const std::string& start, const std::string& end);
    int GetBreakMinutes(double work_hours) const;
 
private:
    std::string break_start_;
    std::string break_end_;
};

#endif
