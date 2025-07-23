#include "MenuController.h"
#include "../include/TimeProvider.h"
#include "../include/ClockDisplay.h"
#include "../include/AttendanceService.h"
#include <iostream>
#include <string>
#include <limits>

// メニュー画面のクラス

MenuController::MenuController() {}
int MenuController ::run() {
    //std::cout <<"runを実行"<<std::endl;
    int errorcount = 0;
    while (true) {
        // 時刻を表示
// displayがポインタの場合
provider = new SystemTimeProvider();
display = new ClockDisplay(provider);
std::string timeStr = display->display();
    std::cout << "現在時刻: " << timeStr << std::endl;

    // メニューの表示    
std::cout << "勤怠管理システム\n";
    std::cout << "------------------\n";
    std::cout
        << "1.出勤\n2.退勤\n3.編集\n4.未定\n5.終了\n選択:";  // メニュー画面
    int sel;
    std::cin >> sel;  // 入力処理
    if (std::cin.fail()) {
        std::cin.clear();
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        errorcount++;
        std::cout << "エラー: 数字を入力してください！ (" << errorcount<< "回目)\n";
        if (errorcount >= 3) {
            std::cout << "エラーが多すぎたため、システムを終了します。\n";
            return 1;
            }
          continue;
    }
switch (sel) {
  case 1: // 出勤
  {
    AttendanceService service;
      service.clockIn();
      break;
  }
  case 2: // 退勤
    {
        AttendanceService service;
        service.clockOut();
        break;
    }
    case 3: // 編集
      // 編集処理の実装
      // ここでは仮に編集処理を行うと表示する+      // 実際の編集処理は未実装
        printf("編集します(未実装)\n");
        break;
    case 4:
      // 未定の処理
      // ここでは仮に未定の処理を行うと表示する
      // 実際の処理は未実装
        printf("未定なので…\n");
    break;
    case 5: // 終了
    std::cout << "シャットダウンします\n";
    return 0;
    case 6:
      // 隠し要素の処理
      // ここでは仮に隠し要素の処理を行うと表示する
      // 実際の処理は未実装
        std::cout << "隠し要素(ロード機能とかいいかも？？？)\n";
        break;
    default:
      // 無効な選択
        errorcount++;
        std::cout << "無効な選択です！！\n";
        break;
    }  
    }
    return 0;
};
