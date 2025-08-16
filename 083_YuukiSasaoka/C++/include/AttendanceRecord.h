/**
 * @file AttendanceRecord.h
 * @brief 出退勤記録
 * @author 笹岡優希
 * @date 2025/07/17
*/
#ifndef ATTENDANCE_RECORD_H_
#define ATTENDANCE_RECORD_H_
#include "AttendanceRepository.h"
#include "AttendanceService.h"

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
    virtual std::string date() const = 0;
    virtual std::string clockIn() const = 0;
    virtual std::string clockOut() const = 0;
    virtual int workingMinutes() const  =0;

    virtual ~IAttendanceRecord() = default;
};
class AttendanceRecord : public IAttendanceRecord {
public:
    AttendanceRecord(const std::string& user_id,
                     const std::string& date,
                     const std::string& clock_in,
                     const std::string& clock_out,
                     const std::string& break_start,
                     const std::string& break_end);

    std::string userId() const override;
    std::string date() const override;
    std::string clockIn() const override;
    std::string clockOut() const override;

    std::time_t startTime() const override;
    std::time_t endTime() const override;
    int workingMinutes() const override;

    std::string ToCSV() const;
    static AttendanceRecord FromCSV(const std::string& line);

private:
    std::string user_id_;
    std::string date_;
    std::string clock_in_;
    std::string clock_out_;
    std::string break_start_;
    std::string break_end_;
};

#endif  // ATTENDANCE_RECORD_H_
