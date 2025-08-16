#include "../include/AttendanceService.h"
#include "../include/TimeProvider.h"
#include "../include/ClockDisplay.h"
#include "../include/BreakPolicy.h" // 追加

#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <time.h>
#include <string>
#include <limits>

// コンストラクタ：ClockDisplayにSystemTimeProviderを渡す
AttendanceService::AttendanceService()
    : Idisplay(&provider), breakPolicy("12:00", "13:00") {} // 例: 休憩開始・終了

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

    // 勤務時間を取得（例: 8.0時間。実際は計算が必要）
    double work_hours = 8.0; // 仮の値。実際は出勤・退勤時刻から計算
    int break_minutes = breakPolicy.GetBreakMinutes(work_hours);

    std::cout << "本日の休憩時間: " << break_minutes << "分" << std::endl;
    return 0;
}

