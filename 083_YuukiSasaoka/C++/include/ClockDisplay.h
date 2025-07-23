/**
 * @file ClockDisplay.h
 * @brief リアルタイム時刻のコンソール/GUI表示
 * @author 笹岡優希
 * @date 2025/07/16
*/
#ifndef CLOCK_DISPLAY_H_
#define CLOCK_DISPLAY_H_

#include "TimeProvider.h"
#include <chrono>
#include <iostream>
#include <iomanip>
#include <string>

using std::string;
using std::tm;

// インターフェースは純粋仮想関数で
class IClockDisplay {
public:
    virtual std::string display() const = 0; // 時刻を表示するメソッド
    virtual ~IClockDisplay() = default;// 仮想デストラクタ
};

// ClockDisplayクラス
class ClockDisplay: public IClockDisplay {
public:
    // コンストラクタ
    // TimeProviderを受け取るコンストラクタ
    // これにより、ClockDisplayはTimeProviderから現在の時刻を取得できる     

    explicit ClockDisplay(TimeProvider* provider);// コンストラクタ
    std::string display() const override;// 時刻を表示するメソッド
    std::chrono::system_clock::time_point tmToTimePoint(const std::tm& t) const;
private:
    // メンバ変数
    // 時刻を取得するためのプロバイダ
    TimeProvider* timeProvider_;
};
#endif
