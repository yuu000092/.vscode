#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
    

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
} Contact;
//名前と番号を格納する構造体

int main() {
    Contact phonebook[MAX_CONTACTS];
    int count = 0;
    int choice;

    while (1) {
        printf("\n--- 電話帳メニュー ---\n");
        printf("1. 連絡先を追加\n");
        printf("2. 連絡先を表示\n");
        printf("3. 終了\n");
        printf("選択してください: ");
        scanf("%d", &choice);
        getchar(); // 改行文字の除去

        if (choice == 1) {
            if (count >= MAX_CONTACTS) {
                printf("電話帳がいっぱいです。\n");
                continue;
            }
            printf("名前を入力: ");
            fgets(phonebook[count].name, sizeof(phonebook[count].name), stdin);
            phonebook[count].name[strcspn(phonebook[count].name, "\n")] = '\0'; // 改行削除

            printf("電話番号を入力: ");
            fgets(phonebook[count].phone, sizeof(phonebook[count].phone), stdin);
            phonebook[count].phone[strcspn(phonebook[count].phone, "\n")] = '\0';

            count++;
            printf("連絡先を追加しました。\n");

        } else if (choice == 2) {
            printf("\n--- 登録された連絡先 ---\n");
            for (int i = 0; i < count; i++) {
                printf("%d. 名前: %s, 電話番号: %s\n", i + 1, phonebook[i].name, phonebook[i].phone);
            }

        } else if (choice == 3) {
            printf("終了します。\n");
            break;

        } else {
            printf("無効な選択です。\n");
        }
    }

    return 0;
}
