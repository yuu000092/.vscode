#ifndef WORKTIME_SUMMARY_H_
#define WORKTIME_SUMMARY_H_

#include <AttendanceRepository.h> // Ensure this header defines AttendanceRepository
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <string>

class WorkTimeSummary{

public:
    virtual WorkTimeSummary Generate(const std::string& user_id, int year, int month) const = 0;
    virtual void SaveToCSV(const std::string& filename, const WorkTimeSummary& summary) const = 0;
    virtual void LoadFromCSV(const std::string& filename, WorkTimeSummary& summary) const = 0;
    virtual void PrintSummary(const WorkTimeSummary& summary) const = 0;
    virtual ~WorkTimeSummary() = default;

        // 必要に応じて他のメンバーを追加
    };

#endif
