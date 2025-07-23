/**
 * @file TimeProvider.h
 * @brief システムに現在時刻を取得し反映
 * @author 笹岡優希
 * @date 2025/07/16
*/
#ifndef TIME_PROVIDER_H_
#define TIME_PROVIDER_H_

#include <ctime>
#include <time.h>
#include <chrono>

//インターフェース
class TimeProvider {
public:
    virtual std::tm getCurrentTime() const = 0;
    virtual ~TimeProvider() = default;
};
//現在時刻を参照する
class SystemTimeProvider : public TimeProvider {
public:
    std::tm getCurrentTime() const override;
    
};
#endif
