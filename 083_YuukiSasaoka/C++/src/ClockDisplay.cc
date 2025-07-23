#include "ClockDisplay.h"
#include "TimeProvider.h"

#include <chrono>
#include <time.h>
#include <iostream>

std::chrono::system_clock::time_point ClockDisplay::tmToTimePoint(const std::tm& t)const{
    std::tm temp = t;
    return std::chrono::system_clock::from_time_t(std::mktime(&temp));
}
// コンストラクタ
// ここで初期化しないとTimeProviderから時間を持ってこれない
ClockDisplay::ClockDisplay(TimeProvider* provider) {
    // メンバ変数を初期化
    timeProvider_ = provider;
    // ここに代入がないと空っぽになる
}

std::string ClockDisplay::display() const {
    std::tm now = timeProvider_->getCurrentTime();
    const char* weekdaysJP[] = {"日曜日", "月曜日", "火曜日", "水曜日", "木曜日", "金曜日", "土曜日"};
    auto tp = tmToTimePoint(now);  // std::tmをstd::chrono::system_clock::time_pointに変換
    // 現在の時刻を表示
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::cout << "現在の時刻: " << now.tm_year + 1900 << "年 " << now.tm_mon + 1
            << "月 " << now.tm_mday << "日（" << weekdaysJP[now.tm_wday]
            << "） " << now.tm_hour << "時 " << now.tm_min << "分 "
            << now.tm_sec << "秒" << std::endl;
    return std::string();  // ctimeは改行を含むのでそのまま返す
};
