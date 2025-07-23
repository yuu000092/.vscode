#include "../include/AttendanceService.h"
#include "../include/TimeProvider.h"
#include "../include/ClockDisplay.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <time.h>
#include <string>
#include <limits>

// コンストラクタ：ClockDisplayにSystemTimeProviderを渡す
AttendanceService::AttendanceService() : Idisplay(&provider) {}

// 出勤処理
int AttendanceService::clockIn() const {
    std::string timeStr = Idisplay.display();
    std::cout << "出勤しました" << std::endl << timeStr << std::endl;
    return 0;
}

// 退勤処理（出勤と同様に Idisplay を使用）
int AttendanceService::clockOut() const {
    std::string timeStr = Idisplay.display();
    std::cout << "退勤しました" << std::endl << timeStr << std::endl;
    return 0;
}

