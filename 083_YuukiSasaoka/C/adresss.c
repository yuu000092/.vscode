//住所記録アプ理
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_RECORDS 100
#define MAX_LEN 100
#define CSV_FILE "address.csv"
//構造体
typedef struct {
    int id;
    char name[MAX_LEN];
    char address[MAX_LEN];
    char phone[MAX_LEN];
} AddressRecord;

//入力バッファクリア
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void load_csv(AddressRecord records[], int *count, int *next_id)
{
    FILE *fp = fopen(CSV_FILE, "r");
    if (!fp)
        return;
    // 初期化
    char line[512];
    // 1行ずつ読み込み
    while (fgets(line, sizeof(line), fp))
    {

        // 空行対策
        if (line[0] == '\n' || line[0] == '\r')
            continue;
        // トークン分割
        AddressRecord rec;
        char *token = strtok(line, ",");
        if (!token)
            continue;

        rec.id = atoi(token);
        if (rec.id <= 0)
            continue; // ID 0 やマイナスは無視

        token = strtok(NULL, ",");
        strcpy(rec.name, token ? token : "");

        token = strtok(NULL, ",");
        strcpy(rec.address, token ? token : "");

        token = strtok(NULL, ",");
        strcpy(rec.phone, token ? token : "");

        records[*count] = rec;
        (*count)++;

        if (rec.id >= *next_id)
        {
            *next_id = rec.id + 1;
        }
    }
    fclose(fp);
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

/* 追加 */
void add_record(AddressRecord records[], int *count, int *next_id) {
    if (*count >= MAX_RECORDS) {
        printf("これ以上登録できません。\n");
        return;
    }

    AddressRecord rec;
    rec.id = (*next_id)++;
    
    printf("名前: ");
    fgets(rec.name, MAX_LEN, stdin);
    rec.name[strcspn(rec.name, "\n")] = 0; // 改行削除

    printf("住所: ");
    fgets(rec.address, MAX_LEN, stdin);
    rec.address[strcspn(rec.address, "\n")] = 0; // 改行削除

    printf("電話番号: ");
    fgets(rec.phone, MAX_LEN, stdin);
    rec.phone[strcspn(rec.phone, "\n")] = 0; // 改行削除
    records[*count] = rec;
    (*count)++;
    printf("登録しました。ID: %d\n", rec.id);
}