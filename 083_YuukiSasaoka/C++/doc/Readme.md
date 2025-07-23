
### 要件
- ログインできる
- メニュー画面で任意の数字を入力したら処理が行われる(例:出勤,1 退勤,2)
- 一定時間以上で休憩時間を自動設定(6時間で45分、8時間で合計1時間を自動カウント)
- 記録されている勤怠情報を編集できる
- 月ごとの勤怠記録一覧を表示させられる
- リアルタイムの時間を記録する
- リアルタイムで時間を表示させる
- 1日に何度も出勤できない
- 記録はCSVファイルに書き込まれる
- CSVファイルは個人によって異なる
- 隠しコマンドで現在時刻の更新を追加

### クラス設計

  | クラス名 | 主な責務 | 
|--------------------|----------------------------|
| AuthenticationService |出退勤のビジネスロジック。退勤時にAttendanceRecordを基に総労働時間を算出し、BreakPolicyを呼び出して休憩時間を確定| 
| UserSession | ログイン中ユーザーのセッション管理 | 
| TimeProvider | 現在時刻取得（モック差し替え可） | 
| ClockDisplay | リアルタイム時刻のコンソール／GUI 表示 | 
| BreakPolicy | 休憩時間算出ルール（6h→45分、8h→60分） | 
| finalizeDailyAttendance | 出退勤のビジネスロジック（1日1回チェック＋休憩付与） | 
| AttendanceRepository (or CsvRepo) | AttendanceRecordオブジェクトの永続化 | 
| MonthlyReportGenerator | 	AttendanceRepositoryからAttendanceRecordのリストを取得し、WorkTimeSummaryを生成して月次レポートを作成 | 
| MenuController | メニュー画面制御、各サービス呼び出し | 
| WorkTimeSummary| 総労働時間、休憩時間、実労働時間などを保持 MonthlyReportGeneratorなどが利用し、複雑な計算ロジックを単純化 | 
| AttendanceRecord | userId, startTime, endTime等を保持するデータクラスを導入 勤怠記録の受け渡しがオブジェクト単位となり、堅牢性が向上| 


### シーケンス図
==クラス図に準拠する==メソッド()の部分は英語

```mermaid
sequenceDiagram
    participant User
    participant MenuController
    participant UserSession
    participant TimeProvider
    participant AttendanceService
    participant AttendanceRepository
    participant BreakPolicy
    participant ClockDisplay

    User->>MenuController: 1を入力後出勤処理が開始
    MenuController->>UserSession: UserSession()　'--現在のユーザーを取得
    UserSession-->>MenuController: user{id, userId}を返却

    MenuController->>TimeProvider: getCurrentTime() '-- 時間を取得
    TimeProvider-->>MenuController: "YYYY-MM-DD HH:MM:SS"を返却

    MenuController->>AttendanceService: startTime(user, timestamp)'--出勤処理を実行
    AttendanceService->>AttendanceRepository:hasRecordForDate(userId, today) '--当日出勤済みか確認
    AttendanceRepository-->>AttendanceService: falseを返却

    AttendanceService->>AttendanceRepository: clockIn(userId, "YYYY-MM-DD HH:MM:SS") '--出勤時間を記録
    AttendanceRepository-->>AttendanceService: 保存成功を返却

    AttendanceService->>BreakPolicy: calculate(userId, date)休憩予定を登録
    BreakPolicy-->>AttendanceService: 6h→45分、8h→60分を登録

    AttendanceService-->>MenuController: 打刻完了を返却
    MenuController->>ClockDisplay: 画面状態を「出勤済み HH:MM」に更新
    ClockDisplay-->>MenuController: 表示を更新

    User->>MenuController: 2を入力後退勤処理が開始
    MenuController->>UserSession: UserSession()
    UserSession-->>MenuController: user{id, userId}を返却

    MenuController->>TimeProvider: getCurrentTime() '--時間を取得
    TimeProvider-->>MenuController: "YYYY-MM-DD HH:MM:SS"を返却

    MenuController->>AttendanceService: endTime(user, timestamp)退勤処理を実行
    AttendanceService->>AttendanceRepository: hasRecordForDate(userId, date)出勤記録が存在するか確認
    AttendanceRepository-->>AttendanceService: 出勤記録ありを返却

    AttendanceService->>AttendanceRepository: clockOut(userId, "YYYY-MM-DD HH:MM:SS")退勤時刻を保存
    AttendanceRepository-->>AttendanceService: 保存成功を返却

    AttendanceService-->>MenuController: 退勤完了を返却
    MenuController->>ClockDisplay: 画面状態を「退勤済み HH:MM」に更新
    ClockDisplay-->>MenuController: 表示を更新

```
