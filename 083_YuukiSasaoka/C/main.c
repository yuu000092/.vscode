#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_POKEMON 100
#define NAME_LEN 32

typedef struct {
    char name[NAME_LEN];
    int hp;
    int attack;
    int defense;
    int sp_attack;
    int sp_defense;
    int speed;
} Pokemon;
int load_pokemon_data(const char *filename, Pokemon pokemons[], int max) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("ファイルを開けませんでした");
        return 0;
    }

    int count = 0;
    while (count < max && fscanf(fp, "%s %d %d %d %d %d %d",
        pokemons[count].name,
        &pokemons[count].hp,
        &pokemons[count].attack,
        &pokemons[count].defense,
        &pokemons[count].sp_attack,
        &pokemons[count].sp_defense,
        &pokemons[count].speed) == 7) {
        count++;
    }

    fclose(fp);
    return count;
}
void print_pokemon(const Pokemon *p) {
    printf("名前: %s\n", p->name);
    printf("HP: %d\n", p->hp);
    printf("攻撃: %d\n", p->attack);
    printf("防御: %d\n", p->defense);
    printf("特攻: %d\n", p->sp_attack);
    printf("特防: %d\n", p->sp_defense);
    printf("素早さ: %d\n", p->speed);
    printf("---------------\n");
}
int main() {
    Pokemon pokemons[MAX_POKEMON];
    int count = load_pokemon_data("pokemon.txt", pokemons, MAX_POKEMON);

    printf("読み込まれたポケモン数: %d\n", count);
    for (int i = 0; i < count; i++) {
        print_pokemon(&pokemons[i]);
    }

    return 0;
}