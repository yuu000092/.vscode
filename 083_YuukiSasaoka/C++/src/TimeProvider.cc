#include "../include/TimeProvider.h"

#include <iostream>
#include <ctime>
#include <time.h>
#include <chrono>

std::tm SystemTimeProvider::getCurrentTime() const {
    std::time_t t = std::time(nullptr);
    return *std::localtime(&t); // std::tm を返すようにする
}
