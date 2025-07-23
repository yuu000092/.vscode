/** 
 * @file AttendanceService.h
 * @brief 出退勤ビジネスロック
 * @author 笹岡優希
 * @date 2025/07/17
*/
#ifndef ATTENDANCE_SERVICE_H_
#define ATTENDANCE_SERVICE_H_

#include "TimeProvider.h"
#include "ClockDisplay.h"
#include <string>

class IAttendanceService {
public:
    virtual int clockIn() const = 0;
    virtual int clockOut() const = 0;
    // virtual std::string display() const = 0;
    virtual ~IAttendanceService() = default;
};

class AttendanceService : public IAttendanceService {
public:
    AttendanceService();  // コンストラクタ
    int clockIn() const override;
    int clockOut() const override;
    // std::string display() const override;

private:
    SystemTimeProvider provider;
    ClockDisplay Idisplay;
};

#endif  // ATTENDANCE_SERVICE_H_
