#include "../include/AttendanceRepository.h" 

AttendanceRecord::AttendanceRecord(const std::string& user_id,
                                   const std::string& date,
                                   const std::string& clock_in,
                                   const std::string& clock_out,
                                   const std::string& break_start,
                                   const std::string& break_end)
  : user_id_(user_id),
    date_(date),
    clock_in_(clock_in),
    clock_out_(clock_out),
    break_start_(break_start),
    break_end_(break_end) {}

const std::string& AttendanceRecord::GetUserId() const {
  return user_id_;
}

const std::string& AttendanceRecord::GetDate() const {
  return date_;
}

const std::string& AttendanceRecord::GetClockIn() const {
  return clock_in_;
}

const std::string& AttendanceRecord::GetClockOut() const {
  return clock_out_;
}

const std::string& AttendanceRecord::GetBreakStart() const {
  return break_start_;
}

const std::string& AttendanceRecord::GetBreakEnd() const {
  return break_end_;
}
