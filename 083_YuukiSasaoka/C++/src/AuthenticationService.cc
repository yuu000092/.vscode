#include <iostream>
#include <string>



class AuthenticationService {
public:
    AuthenticationService() = default;

    bool authenticate(const std::string& username, const std::string& password) {
        // ここに認証ロジックを実装
        // 例: ユーザー名とパスワードが正しいかチェック
        if (username == "admin" && password == "password") {
            return true;
        }
        return false;
    }

    void logout() {
        // ログアウト処理を実装
        std::cout << "Logged out successfully." << std::endl;
    }
};