#include "../include/MenuController.h"
#include "../include/TimeProvider.h"
#include "../include/ClockDisplay.h"
#include <iostream>
#include <memory>
#include <thread>

int main() {

    // メニューコントローラのインスタンスを生成
  // スマートポインタを利用してクラスのインスタンスを動的に生成
  std::unique_ptr<MenuController> menu_ = std::make_unique<MenuController>();
    int result = menu_->run();
  // メニューコントローラのrunメソッドを呼び出す
  //runを実行
  MenuController* controller = new MenuController();
  int runResult = controller->run();

    // 結果を表示
    if (result == 0) {
        std::cout << "メニューが正常に終了しました。\n";
    } else {
        std::cout << "メニューが異常終了しました。\n";
    }
  delete controller;//メモリ解放
 return 0; // 結果を返す
}
