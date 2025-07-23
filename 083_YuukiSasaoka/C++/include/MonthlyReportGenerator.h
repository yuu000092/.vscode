#ifndef MONTHLY_REPORT_GENERATOR_HPP
#define MONTHLY_REPORT_GENERATOR_HPP

#include <string>
#include "AttendanceRepository.h"
#include "WorkTimeSummary.h"

/// 勤怠記録を月単位で集計し、WorkTimeSummary を生成する専用クラス
class MonthlyReportGenerator {
public:
  /// AttendanceRepository を参照して集計処理を行う
  explicit MonthlyReportGenerator(const AttendanceRepository& repository);

  /// 勤務情報を指定した年月・ユーザーIDで集計し、Summary を生成
  WorkTimeSummary Generate(const std::string& user_id, int year, int month);

private:
  const AttendanceRepository& repository_;  ///< 勤怠記録の取得元
};

#endif  // MONTHLY_REPORT_GENERATOR_HPP
