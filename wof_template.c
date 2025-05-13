#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXTS 20

#define CHAR_RANGE ('Z' - 'A' + 1)

int check(char* text)
{
    char *p = text;
    while (*p != '\0')
    {
        if(*p == '_')
        {
            return 0;
        }
        p++;
    }
    return 1;
}

int guess_a_letter(char* text, const char* original_text)
{
    char letter = 'A' + (rand() % CHAR_RANGE);
    char *po = (char*)original_text;
    char *pt = (char*)text;
    int r = 0;
    while(*po != '\0')
    {
        if(*po == letter)
        {
            *pt = letter;
            r=1;
        }
        pt++;
        po++;
    }
    return r; 
}

char* play(const char* original_text, const int number_of_players, const int turns, int* p_player)
{
    char* text = (char*) malloc( (strlen(original_text)+1)*sizeof(char) );
    char *p = (char*)original_text;
    char *pt = text;
    while (*p != '\0')
    {
        if (*p == ' ')
        {   
            *pt = ' ';
        }
        else
        {
            *pt = '_';
        }
        p++;
        pt++;
    }
    *pt = '\0';
    *p_player = 0;
    int change = 0;
    int turn = turns;
    while(!check(text) && turn != 0) 
    {
        if (change)
        {
            *p_player = (*p_player+1) % number_of_players;
            change = 0;
        }
        if (!guess_a_letter(text, original_text))
        {
            change = 1;
            turn--;
        }
    }
    return text;
}


int main() {

    const char* texts[MAX_TEXTS] = {
        "PAN TADEUSZ",
        "HENRYK SIENKIEWICZ",
        "MORZE KASPIJSKIE",
        "POGODA DLA BOGACZY",
        "CZERWONE GITARY",
        "KAZANIE PIOTRA SKARGI",
        "QUO VADIS",
        "ADAM MICKIEWICZ",
        "ALBERT EINSTEIN",
        "DENNIS RITCHIE",
        "FIZYKA KWANTOWA",
        "PROGRAMOWANIE IMPERATYWNE",
        "ALGORYTMY I STRUKTURY DANYCH",
        "BRIAN KERNIGHAN",
        "CZERWONY KAPTUREK",
        "MARIA KONOPNICKA",
        "WILLIAM SHAKESPEARE",
        "ZBIGNIEW ZAPASIEWICZ",
        "MAGDALENA SAMOZWANIEC",
        "JEZIORO ONTARIO"
    };

    int number_of_players, turns, player;
    unsigned seed;

    scanf("%d %u %d", &number_of_players, &seed, &turns);
    srand(seed);
    const int number = rand() % MAX_TEXTS;
    char* text = play(texts[number], number_of_players, turns, &player);
    printf("%s\n", text);
    printf("%d\n", player);
    free(text);

    return 0;

}

