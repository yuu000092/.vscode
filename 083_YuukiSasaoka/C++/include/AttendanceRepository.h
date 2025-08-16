/**
 * @file AttendanceRepository.h
 * @brief 勤怠記録をCSVに保存・読み込み
 * @author 笹岡優希
 * @date 2025/07/17
 */
#ifndef ATTENDANCE_REPOSITORY_H_
#define ATTENDANCE_REPOSITORY_H_

#include "AttendanceRecord.h"
#include <vector>
#include <ctime>
#include <iomanip>
#include <string>
#include <iostream>

/// 1日分の勤怠情報を保持する構造体（またはクラス）
class AttendanceRecord {
public:
  AttendanceRecord(const std::string& user_id,
                   const std::string& date,
                   const std::string& clock_in,
                   const std::string& clock_out,
                   const std::string& break_start,
                   const std::string& break_end);

  // ゲッター
  const std::string& GetUserId() const;
  const std::string& GetDate() const;
  const std::string& GetClockIn() const;
  const std::string& GetClockOut() const;
  const std::string& GetBreakStart() const;
  const std::string& GetBreakEnd() const;

private:
  std::string user_id_;
  std::string date_;
  std::string clock_in_;
  std::string clock_out_;
  std::string break_start_;
  std::string break_end_;
  time_t startTime();
};

#endif  // ATTENDANCE_REPOSITORY_H
