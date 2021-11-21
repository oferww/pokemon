#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pokemon.h"
#include "ctype.h"


int main(__attribute__((unused)) int argc, char **argv) {
    int numberOfTypes = atoi(argv[1]);
    int numberOfPokemons = atoi(argv[2]);
    FILE *data = fopen(argv[3], "r");

    char line[300];
    int line_number = 0;
    int types_line = 0;
    while (fgets(line, sizeof(line), data)) {
        if (types_line != 0) {
            break;
        }
        line_number++;
        if (strstr(line, "Types") != 0) {
            types_line = line_number + 1;
        }
    }

    int i;
    char listoftypes[numberOfTypes][9];
    for (i = 0; i < numberOfTypes; i++) {
        int j;
        for (j = 0; j < 9; j++) {
            listoftypes[i][j] = 0;
        }
    }
    int type_num = 0;
    int char_num = 0;

    for (i = 0; i < strlen(line); i++) {
        char letter[2];
        letter[0] = line[i];
        if (strstr(&letter[0], ",") == 0 && strstr(&letter[0], "\r") == 0) {
            listoftypes[type_num][char_num] = line[i];
            char_num++;
        } else {
            type_num++;
            char_num = 0;
        }
    }


    pokedex pokedex_1;
    init_pokedex(&pokedex_1, numberOfTypes, numberOfPokemons, &listoftypes);


    while (fgets(line, sizeof(line), data)) {

        char cur_type[9];
        for (i = 0; i < numberOfTypes; i++) {
            cur_type[i] = 0;
        }
        i = 1;
        int j = 0;
        while ( ! (isspace(line[i]))) {
            cur_type[j] = line[i];
            i++;
            j++;
        }

        char letter[2];
        letter[0] = line[i];
        while (strstr(&letter[0], ":") == 0) {
            letter[0] = line[i];
            i++;
        }

        int nekudotaim = i-1 ;
        letter[0] = line[i-2];
        if (strstr(&letter[0], "e") != 0) {
            int number = 0;
            for (i ; line[i] != '\0'; i++) {
                letter[0] = line[i];
                if (strstr(&letter[0], ",") != 0) {
                    number++;
                }
            }
            number++;
            int p;
            for (p = 0; p < numberOfTypes; p++) {
                if (strcmp(pokedex_1.types[p].name, cur_type) == 0) {
                    pokedex_1.types[p].effectiveagainstme = (typeofpokemon **) realloc(
                            pokedex_1.types[p].effectiveagainstme, number * sizeof(int));
                    int c;
                    for (c = 0; c < number; c++) {
                        for (i = 0; i < numberOfTypes; i++) {
                            cur_type[i] = 0;
                        }
                        i = 0;
                        j = nekudotaim + 1;
                        letter[0] = line[j];
                        while (strstr(&letter[0], ",") == 0) {
                            cur_type[i] = line[j];
                            i++;
                            j++;
                            letter[0] = line[j];
                        }
                        int pp;
                        for (pp = 0; pp < numberOfTypes; pp++) {
                            if (strcmp(listoftypes[pp], cur_type) == 0) {
                                (pokedex_1.types[p].effectiveagainstme[c]) = (pokedex_1.types[pp]);
                                break;
                            }
                        }
                    }
                }
            }
        }
//            else{
//                int number = 0;
//                int c;
//                for ( c = 0 ; line[c] != '\0' ; number ++){
//                    if (strcmp(",", &line[c]) == 0){
//                        number++ ;
//                    }
//                }
//                number++;
//                int p;
//                for ( p = 0 ; p < numberOfTypes ; p++ ){
//                    if (strcmp(pokedex_1.listoftypes[p]->name, cur_type) == 0){
//                        pokedex_1.listoftypes[p]->effectiveagainstother = (typeofpokemon **) realloc(pokedex_1.listoftypes[p]->effectiveagainstother, number * sizeof(int));
//                        for ( c = 0 ; c < number ; c++ ){
//                            strcpy(cur_type , "");
//                            while ( strcmp(&line[i], ",") != 0 ){
//                                cur_type[i] = line[i];
//                                i++;
//                            }
//                            int pp;
//                            for ( pp = 0 ; pp < numberOfTypes ; pp++ ){
//                                if (strcmp(pokedex_1.listoftypes[pp]->name, cur_type) == 0){
//                                    *(pokedex_1.listoftypes[p]->effectiveagainstother[c]) = *((pokedex_1.listoftypes[pp]));
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }


//    char pokemons[numberOfPokemons][12];
//    int pokemonnum = 0;
//    char_num = 0;
//    for (i = 0 ; i < strlen(line) ; i++ ){
//        if (line[i] != ","){
//            listoftypes[type_num][char_num] = line[i];
//            char_num++;
//        }
//        if (strcmp(&line[i],",") == 0){
//            type_num++ ;
//            char_num = 0 ;
//        }
//    }


        int choice;
        do {
            choice = 0;
            printf("Please choose one of the following numbers:\n");
            printf("1 : Print all Pokemons\n");
            printf("2 : Print all Pokemons listoftypes\n");
            printf("3 : Add type to effective against me list\n");
            printf("4 : Add type to effective against others \n");
            printf("5 : Remove type from effective against me list\n");
            printf("6 : Remove type from effective against others list\n");
            printf("7 : Print Pokemon by name\n");
            printf("8 : Print Pokemons by type\n");
            printf("9 : Exit\n");

//        char cho[3];
//        fgets(cho,2, stdin);
//        choice = (int) *cho;

            scanf(" %d", &choice);
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}

            switch (choice) {
                case 1:
                    // Print all Pokemons
                    choice = 10;
                    break;

                case 2:
                    // Print all Pokemons listoftypes
                    for (i = 0; i < numberOfTypes; i++) {
//                    printf("%s", pokedex_1.listoftypes[i]->name);
                    }
                    choice = 10;
                    break;
                case 3:
                    // Add type to effective against me list
                    choice = 10;
                    break;

                case 4:
                    // Add type to effective against others list
                    choice = 10;
                    break;

                case 5:
                    // Remove type from effective against me list
                    choice = 10;
                    break;

                case 6:
                    // Remove type from effective against others list
                    choice = 10;
                    break;

                case 7:
                    // Print Pokemon by name
                    choice = 10;
                    break;

                case 8:
                    // Print Pokemons by type
                    choice = 10;
                    break;

                case 9:
                    // Exit
                    break;

                default:
                    fprintf(stderr, "Please choose a valid number.\n");
                    choice = 10;
            }

        } while (choice < 0 || choice > 9);

        return 0;
    }
}
