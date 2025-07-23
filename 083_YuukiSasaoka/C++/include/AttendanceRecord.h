/**
 * @file AttendanceRecord.h
 * @brief 出退勤記録
 * @author 笹岡優希
 * @date 2025/07/17
*/
#ifndef ATTENDANCE_RECORD_H_
#define ATTENDANCE_RECORD_H_

#include <string>
#include <ctime>
#include <iomanip>
#include <chrono>


// 勤怠記録の受け渡しがオブジェクト単位となり、堅牢性が向上
class IAttendanceRecord {
    public:
    virtual std::string userId() const = 0;
    virtual std::time_t startTime() const = 0;
    virtual std::time_t endTime() const = 0;
    virtual int workingMinutes() const  =0;

    virtual ~IAttendanceRecord() = default;
};
class AttendanceRecord : public IAttendanceRecord{
public:
    std::string userId() const override;
    std::time_t startTime() const override;
    std::time_t endTime() const override;
    int workingMinutes() const override;
};

#endif  // ATTENDANCE_RECORD_H_
