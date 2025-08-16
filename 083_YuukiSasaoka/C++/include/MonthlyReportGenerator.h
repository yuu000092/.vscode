#pragma once

#include <string>
#include "AttendanceRepository.h" // Ensure this header defines AttendanceRepository
#include "WorkTimeSummary.h"

/// @brief 勤怠記録を月単位で集計し、WorkTimeSummary を生成する専用クラス
class MonthlyReportGenerator {
public:
  /// @brief コンストラクタ。AttendanceRepository を参照して集計処理を行う
  /// @param repository 勤怠記録の取得元

  /// @brief 勤務情報を指定した年月・ユーザーIDで集計し、Summary を生成
  /// @param user_id ユーザーID
  /// @param year 年（例：2025）
  /// @param month 月（1〜12）
  /// @return 集計結果の WorkTimeSummary
  WorkTimeSummary Generate(const std::string& user_id, int year, int month);
};