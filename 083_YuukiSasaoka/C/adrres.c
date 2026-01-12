#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RECORDS 100
#define MAX_LEN 100

typedef struct
{
    int id;
    char name[MAX_LEN];
    char address[MAX_LEN];
    char phone[MAX_LEN];
} AddressRecord;

void clear_input_buffer();
void load_csv(AddressRecord records[], int *count, int *next_id, const char *filename);
void save_csv(AddressRecord records[], int count, const char *filename);

void add_record(AddressRecord records[], int *count, int *next_id);
void list_records(AddressRecord records[], int count);
void edit_record(AddressRecord records[], int index, int count);
void delete_record(AddressRecord records[], int *count, int index);
int confirm_action(const char *message);

/* バリデーション */
int utf8_strlen(const char *s);
int validate_name(const char *name);
int validate_address(const char *address);
int validate_phone(const char *phone);

int main(void)
{
    AddressRecord records[MAX_RECORDS];
    int count = 0; // 登録件数
    int next_id = 1; // 次のID
    int choice;// メニュー選択

    while (1)
    {
        printf("\n===== 住所登録アプリ =====\n");
        printf("1. 新規登録\n");
        printf("2. 一覧表示\n");
        printf("3.CSV保存\n");
        printf("0. 終了\n");
        printf("番号を選んでください: ");

        if (scanf("%d", &choice) != 1)
        {
            clear_input_buffer();
            printf("数字を入力してください。\n");
            continue;
        }
        clear_input_buffer();

        switch (choice)
        {
        case 1:
            add_record(records, &count, &next_id);
            break;
        case 2:
            list_records(records, count);
            break;
        case 3:
            // 保存か読み込みか選択
            int sub_choice;
            printf("1. CSV保存\n");
            printf("2. CSV読み込み\n");
            printf("番号を選んでください: ");
            if (scanf("%d", &sub_choice) != 1)
            {
                clear_input_buffer();
                printf("数字を入力してください。\n");
                break;
            }
            switch (sub_choice)
            {
            case 1:
                // CSV保存
                char filename_save[256];
                printf("保存するファイル名を入力してください（例: data.csv）: ");
                clear_input_buffer(); // ← これが無いと絶対に空判定になる
                fgets(filename_save, sizeof(filename_save), stdin);
                filename_save[strcspn(filename_save, "\n")] = '\0';

                if (strlen(filename_save) == 0)
                {
                    printf("ファイル名が空です。保存をキャンセルします。\n");
                    break;
                }

                save_csv(records, count, filename_save);
                break;
            case 2:
                printf("読み込むファイル名を入力してください（例: data.csv）: ");

                clear_input_buffer(); // ← これが無いと絶対に空判定になる

                char filename_read[256];
                fgets(filename_read, sizeof(filename_read), stdin);
                filename_read[strcspn(filename_read, "\n")] = '\0';

                if (strlen(filename_read) == 0)
                {
                    printf("ファイル名が空です。読み込みをキャンセルします。\n");
                    break;
                }

                load_csv(records, &count, &next_id, filename_read);
                break;
            }
            break;
        case 0:
        {
            char filename[256];
            printf("終了前に保存します。ファイル名を入力してください: ");
            fgets(filename, sizeof(filename), stdin);
            filename[strcspn(filename, "\n")] = '\0';

            if (strlen(filename) > 0)
            {
                save_csv(records, count, filename);
            }
            else
            {
                printf("ファイル名が空のため保存しませんでした。\n");
            }

            printf("終了します。\n");
            return 0;
        }
        default:
            printf("不正な番号です。\n");
        }
    }
}

/* 入力バッファクリア */
void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

/* 実行確認 */
int confirm_action(const char *message)
{
    char buf[10];
    while (1)
    {
        printf("%s (y/n): ", message);
        fgets(buf, sizeof(buf), stdin);

        if (buf[0] == 'y' || buf[0] == 'Y')
            return 1;
        if (buf[0] == 'n' || buf[0] == 'N')
            return 0;

        printf("y または n を入力してください。\n");
    }
}

/* UTF-8 の文字数カウント */
int utf8_strlen(const char *s)
{
    int count = 0;
    while (*s)
    {
        unsigned char c = (unsigned char)*s;
        if (c < 0x80)
            s += 1;
        else if ((c & 0xE0) == 0xC0)
            s += 2;
        else if ((c & 0xF0) == 0xE0)
            s += 3;
        else
            s += 1;
        count++;
    }
    return count;
}

/* バリデーション */
int validate_name(const char *name)
{
    return utf8_strlen(name) > 0 && utf8_strlen(name) <= 12;
}

int validate_address(const char *address)
{
    return utf8_strlen(address) > 0 && utf8_strlen(address) <= 64;
}

int validate_phone(const char *phone)
{
    int len = strlen(phone);
    if (len != 11)
        return 0;

    for (int i = 0; i < len; i++)
    {
        if (phone[i] < '0' || phone[i] > '9')
            return 0;
    }
    return 1;
}
/* CSV 読み込み */
void load_csv(AddressRecord records[], int *count, int *next_id, const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        printf("CSVファイル '%s' を開けませんでした。\n", filename);
        return;
    }

    // 既存データをクリア
    *count = 0;

    char line[512];
    int max_id = 0;

    while (fgets(line, sizeof(line), fp))
    {
        if (line[0] == '\n' || line[0] == '\r')
            continue;

        AddressRecord rec;
        char *token = strtok(line, ",");
        if (!token)
            continue;

        rec.id = atoi(token);
        if (rec.id <= 0)
            continue;

        token = strtok(NULL, ",");
        strcpy(rec.name, token ? token : "");

        token = strtok(NULL, ",");
        strcpy(rec.address, token ? token : "");

        token = strtok(NULL, ",");
        strcpy(rec.phone, token ? token : "");

        records[*count] = rec;
        (*count)++;

        if (rec.id > max_id)
            max_id = rec.id;
    }

    fclose(fp);

    // next_id を最大ID+1 に更新
    if (max_id >= *next_id)
        *next_id = max_id + 1;

    printf("CSV '%s' を読み込みました。（%d件）\n", filename, *count);
}

/* CSV 保存 */
void save_csv(AddressRecord records[], int count, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        printf("CSV保存に失敗しました。\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%d,%s,%s,%s\n",
                records[i].id,
                records[i].name,
                records[i].address,
                records[i].phone);
    }

    fclose(fp);
    printf("CSV保存しました。（%s）\n", filename);
}

/* 新規登録 */
void add_record(AddressRecord records[], int *count, int *next_id)
{
    if (*count >= MAX_RECORDS)
    {
        printf("これ以上登録できません。\n");
        return;
    }

    AddressRecord rec;
    rec.id = (*next_id)++;

    /* 名前 */
    while (1)
    {
        printf("名前: ");
        fgets(rec.name, MAX_LEN, stdin);
        rec.name[strcspn(rec.name, "\n")] = '\0';

        if (validate_name(rec.name))
            break;
        printf("名前は1〜12文字で入力してください。\n");
    }

    /* 住所 */
    while (1)
    {
        printf("住所: ");
        fgets(rec.address, MAX_LEN, stdin);
        rec.address[strcspn(rec.address, "\n")] = '\0';

        if (validate_address(rec.address))
            break;
        printf("住所は1〜64文字で入力してください。\n");
    }

    /* 電話番号 */
    while (1)
    {
        printf("電話番号: ");
        fgets(rec.phone, MAX_LEN, stdin);
        rec.phone[strcspn(rec.phone, "\n")] = '\0';

        if (validate_phone(rec.phone))
            break;
        printf("電話番号は半角数字11桁で入力してください。\n");
    }

    /* 確認 */
    printf("\n入力内容:\n");
    printf("名前: %s\n", rec.name);
    printf("住所: %s\n", rec.address);
    printf("電話番号: %s\n", rec.phone);

    if (!confirm_action("この内容で登録しますか？"))
    {
        printf("登録をキャンセルしました。\n");
        return;
    }

    records[*count] = rec;
    (*count)++;

    printf("ID %d で登録しました。\n", rec.id);
}
/* 一覧表示（10件ごとページング） */
void list_records(AddressRecord records[], int count)
{
    if (count == 0)
    {
        printf("データがありません。\n");
        return;
    }

    int page = 0;                             // 現在のページ
    int per_page = 10;                        // 1ページあたり10件
    int total_pages = (count - 1) / per_page; // 0始まり

    while (1)
    {
        int start = page * per_page;
        int end = start + per_page;
        if (end > count)
            end = count;

        printf("\n--- 一覧 (ページ %d / %d) ---\n", page + 1, total_pages + 1);

        for (int i = start; i < end; i++)
        {
            printf("ID: %d / 名前: %s\n", records[i].id, records[i].name);
        }

        printf("\n操作: 数字=詳細  a=次ページ  b=前ページ  0=戻る\n");
        printf("入力: ");

        char buf[32];
        fgets(buf, sizeof(buf), stdin);

        /* 0 → 戻る */
        if (buf[0] == '0')
            return;

        /* a → 次ページ */
        if (buf[0] == 'a' || buf[0] == 'A')
        {
            if (page < total_pages)
                page++;
            else
                printf("これ以上次のページはありません。\n");
            continue;
        }

        /* b → 前ページ */
        if (buf[0] == 'b' || buf[0] == 'B')
        {
            if (page > 0)
                page--;
            else
                printf("これ以上前のページはありません。\n");
            continue;
        }
        /* 数字 → 詳細表示 */
        int id = atoi(buf);
        if (id > 0)
        {
            for (int i = 0; i < count; i++)
            {
                if (records[i].id == id)
                {
                    printf("\n--- 詳細表示 ---\n");
                    printf("ID: %d\n", records[i].id);
                    printf("名前: %s\n", records[i].name);
                    printf("住所: %s\n", records[i].address);
                    printf("電話番号: %s\n", records[i].phone);
                    printf("--------------------\n");

                    printf("操作: 1=修正 2=削除 その他=戻る\n");
                    printf("入力: ");
                    fgets(buf, sizeof(buf), stdin);
                    int sub_choice = atoi(buf);

                    if (sub_choice == 1)
                    {
                        edit_record(records, i, count); // ← ID ではなく index を渡す
                    }
                    else if (sub_choice == 2)
                    {
                        delete_record(records, count, i); // ← index を渡す
                    }
                    else
                    {
                        printf("一覧に戻ります。\n");
                        goto wait_enter;
                    }
                }
            }
            printf("ID %d は存在しません。\n", id);
        }
        else
        {
            printf("入力が正しくありません。\n");
        }

    wait_enter:
        printf("\nEnterキーで一覧に戻ります...");
        fgets(buf, sizeof(buf), stdin);
    }
}
void edit_record(AddressRecord records[], int index, int count)
{
    AddressRecord *rec = &records[index];
    AddressRecord old = *rec;
    char buf[MAX_LEN];

    while (1)
    {
        printf("\n--- 修正メニュー ---\n");
        printf("1. 名前を修正\n");
        printf("2. 住所を修正\n");
        printf("3. 電話番号を修正\n");
        printf("4. 全て修正\n");
        printf("0. 戻る\n");
        printf("番号を選んでください: ");

        int choice;
        if (scanf("%d", &choice) != 1)
        {
            clear_input_buffer();
            printf("数字を入力してください。\n");
            continue;
        }
        clear_input_buffer();

        if (choice == 0)
        {
            printf("修正をキャンセルしました。\n");
            return;
        }

        switch (choice)
        {
        case 1:
            /* 名前修正 */
            while (1)
            {
                printf("新しい名前: ");
                fgets(buf, MAX_LEN, stdin);
                buf[strcspn(buf, "\n")] = '\0';
                if (validate_name(buf))
                    break;
                printf("名前は1〜12文字で入力してください。\n");
            }
            printf("名前: %s → %s\n", old.name, buf);
            if (!confirm_action("この内容で修正しますか？"))
                return;
            strcpy(rec->name, buf);
            printf("修正しました。\n");
            return;

            /* 以下、住所・電話番号も同様に index を使って修正 */
        }
    }
}

void delete_record(AddressRecord records[], int *count, int index)
{
    printf("\n削除対象:\n");
    printf("ID: %d\n", records[index].id);
    printf("名前: %s\n", records[index].name);
    printf("住所: %s\n", records[index].address);
    printf("電話番号: %s\n", records[index].phone);

    if (!confirm_action("本当に削除しますか？"))
    {
        printf("削除をキャンセルしました。\n");
        return;
    }

    /* 削除処理 */
    for (int j = index; j < *count - 1; j++)
    {
        records[j] = records[j + 1];
    }
    (*count)--;

    /* ID 再採番 */
    for (int j = 0; j < *count; j++)
    {
        records[j].id = j + 1;
    }

    printf("削除しました。ID を再採番しました。\n");
}