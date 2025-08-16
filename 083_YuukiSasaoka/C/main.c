#ifdef _WIN32
  #include <windows.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <io.h>
#include <fcntl.h>

#define MAX_POKEMON 100
#define NAME_LEN    32

typedef struct {
    wchar_t name[NAME_LEN];
    int hp, attack, defense, sp_attack, sp_defense, speed;
} Pokemon;

int load_pokemon_data(const wchar_t *filename, Pokemon A[], int max) {
    FILE *fp;
#ifdef _WIN32
    fp = _wfopen(filename, L"r, ccs=UTF-8");
#else
    fp = fopen("pokemon.txt", "r");
#endif
    if (!fp) {
        fwprintf(stderr, L"ファイルを開けませんでした: %ls\n", filename);
        return 0;
    }

    wchar_t line[256];
    int count = 0;
    while (count < max && fgetws(line, 256, fp)) {
        if (line[0]==L'\n' || line[0]==L'\r') continue;
        int n = swscanf(line,
                        L"%31ls %d %d %d %d %d %d",
                        A[count].name,
                        &A[count].hp,
                        &A[count].attack,
                        &A[count].defense,
                        &A[count].sp_attack,
                        &A[count].sp_defense,
                        &A[count].speed);
        if (n == 7) count++;
    }
    fclose(fp);
    return count;
}

int main() {
  // 1) コンソールをUTF-8＆ワイドモードに切り替え
  #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    
    SetConsoleCP(CP_UTF8);
    _setmode(_fileno(stdout), _O_U8TEXT);
    _setmode(_fileno(stdin),  _O_U8TEXT);
  #endif

  // 2) ロケールを UTF-8 に
  setlocale(LC_ALL, "ja_JP.UTF-8");

  // 3) データ読み込み
  Pokemon pokemons[MAX_POKEMON] = {0};
  int count = load_pokemon_data(L"pokemon.txt", pokemons, MAX_POKEMON);

  // 4) 表示
  wprintf(L"読み込まれたポケモン数: %d\n", count);
  for (int i = 0; i < count; i++) {
      wprintf(L"名前: %ls\n",   pokemons[i].name);
      wprintf(L"HP: %d\n",     pokemons[i].hp);
      wprintf(L"攻撃: %d\n",   pokemons[i].attack);
      wprintf(L"防御: %d\n",   pokemons[i].defense);
      wprintf(L"特攻: %d\n",   pokemons[i].sp_attack);
      wprintf(L"特防: %d\n",   pokemons[i].sp_defense);
      wprintf(L"素早さ: %d\n", pokemons[i].speed);
      wprintf(L"---------------\n");
  }

  wprintf(L"エンターキーを押してください...");
  getwchar();
  return 0;
}