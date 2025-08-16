#include "../include/BreakPolicy.h"
#include <iostream>

BreakPolicy::BreakPolicy(const std::string& start, const std::string& end)
    : break_start_(start), break_end_(end) {
    // コンストラクタの実装
    std::cout << "BreakPolicy created with start: " << break_start_
              << " and end: " << break_end_ << std::endl;
}

int BreakPolicy::GetBreakMinutes(double work_hours) const {
    if (work_hours >= 8.0) {
        return 60;
    } else if (work_hours >= 6.0) {
        return 15;
    } else {
        return 0;
    }
}

    class BreakPolicy {
    public:
        BreakPolicy(const std::string& start, const std::string& end);
        int GetBreakMinutes(double work_hours) const;
        // ...他のメンバー...
    private:
        std::string break_start_;
        std::string break_end_;
    };
    
    // ...existing code...

// ...existing code...