/**
 * @file MenuController.h
 * @brief メニュー画面
 * @author 笹岡優希
 * @date 2025/07/15
*/
#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <iostream>
#include <string>
/// メニュー画面を起動し、ユーザー操作を受け付ける基本クラス
class IMenuController {
public:
    virtual int run() = 0;
    virtual ~IMenuController() = default;
};


// 前方宣言（必要な型が他のヘッダで定義されている場合）
class SystemTimeProvider;
class ClockDisplay;
class Service; // Service型も必要に応じて宣言

class MenuController :public IMenuController{
  public:
  /**
   * @brief メニュー画面を表示し、ユーザーの選択に応じて処理を分岐する
   * @note 派生クラスでオーバーライド可能（仮想関数）
   */


  /**
   * @brief メニュー画面の分岐処理
   * @note　while文とswitch文で終了までリピートする
   */
  int run(void) override;
  /**
   * @brief コンストラクタ
   * @note　システムの現在時刻を取得するプロバイダとClockDisplayのインスタンスを生成
   */
  MenuController();

  SystemTimeProvider* provider; // ポインタ型に変更
  ClockDisplay* display;        // ポインタ型に変更
  Service* service;             // Service型もポインタ型に

  int errorcount = 0;
};
#endif  // MENU_CONTROLLER_H
