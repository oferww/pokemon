#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pokemon.h"
#include "ctype.h"

// general structre to hold the lists of pokemons and types
typedef struct
{
    int num_types;
    int num_pokemons;
    typeofpokemon *types;
    pokemon *pokemons;
} pokedex;

// initializes pokedex
status init_pokedex(pokedex *ppokedex, int numoftypes, int numofpokemons, char *typess[])
{
    ppokedex->num_types = numoftypes;
    ppokedex->num_pokemons = numofpokemons;
    ppokedex->types = (typeofpokemon *)calloc(numoftypes , sizeof(typeofpokemon));
    if (ppokedex->types == NULL){
        printf("Memory Problem");
        return failure;
    }
    int i;
    for (i = 0; i < numoftypes; i++)
    {
        status init_t = init_type(&(ppokedex->types[i]), typess[i]);
        if (init_t == failure){
            printf("Type %s not initiated", typess[i]);
        }
    }
    ppokedex->pokemons = (pokemon *) calloc(numofpokemons, sizeof(pokemon));
    if (ppokedex->pokemons == NULL){
        printf("Memory Problem");
        return failure;
    }
    return  success;
}

void destroy_pokedex(typeofpokemon *t, pokemon *p){
    free(p);
    free(t);
}
// func to use in case 9, and most exit scenarios
void destroy_all(typeofpokemon * types, pokemon * pokemons,  int nt, int np, FILE *data){
    int i;
    for (i = 0; i < nt; i++) {
        destroy_type(&types[i]);
    }
    for (i = 0; i < np; i++) {
        destroy_pokemon(&pokemons[i]);
    }
    destroy_pokedex(types, pokemons);

    fclose(data);

    fprintf(stdout, "All the memory cleaned and the program is safely closed.\n");
}

int main(int argc, char **argv) {
    int numberOfTypes = atoi(argv[1]);
    int numberOfPokemons = atoi(argv[2]);
    FILE *data = fopen(argv[3], "r");

    char line[301];
    int line_number = 0;
    int types_line = 0;
    char psik[2] = ",";
    char bsr[2] = "\r";
    char bst[2] = "\t";
    char neku[2] = ":";
    char e[2] = "e";

    // finding "Types" row in the file, to read types under it
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
    char *listoftypes[numberOfTypes];
    int type_num = 0;
    int char_num = 0;

    // reading and saving all of the pokemons types in the file
    char buffer[9] = {0};
    for (i = 0; i < strlen(line); i++) {
        char letter[2];
        letter[0] = line[i];
        if (strstr(&letter[0], psik) == 0 && strstr(&letter[0], bsr) == 0) {
            buffer[char_num] = line[i];
            char_num++;
        } else {
            listoftypes[type_num] = malloc(strlen(buffer)+1);
            if (listoftypes[type_num] == NULL){
                printf("Memory Problem");
                fclose(data);
                fprintf(stdout, "All the memory cleaned and the program is safely closed.\n");
                return 0;
            }
            strcpy(listoftypes[type_num], buffer);
            type_num++;
            char_num = 0;
            memset(buffer, 0, strlen(buffer));
        }
    }

    // initializing pokedex struct
    pokedex pokedex_1;
    status init_p = init_pokedex(&pokedex_1, numberOfTypes, numberOfPokemons, listoftypes);
    if (init_p == failure){
        printf("Memory Problem");
        destroy_all(pokedex_1.types, pokedex_1.pokemons, pokedex_1.num_types, pokedex_1.num_pokemons, data);
    }
    // freeing all types from the temporary list, after saving it in the pokedex
    if (numberOfTypes == 0){
        free(listoftypes[0]);
    }
    else {
        for (i = 0; i < numberOfTypes; i++) {
            free(listoftypes[i]);
        }
    }

    // reading each line and adding to effective lists, if and where necessary
    char *cur_type = "";
    while (fgets(line, sizeof(line), data) && line[0] == '\t') {
        memset(buffer, 0, strlen(buffer));
        i = 1;
        int j = 0;
        while (!(isspace(line[i]))) {
            buffer[j] = line[i];
            i++;
            j++;
        }
        cur_type = malloc(strlen(buffer)+1);
        if (cur_type == NULL){
            printf("Memory Problem");
            destroy_all(pokedex_1.types, pokedex_1.pokemons, pokedex_1.num_types, pokedex_1.num_pokemons, data);
            return 0;
        }

        strcpy(cur_type, buffer);
        char letter[2];
        letter[0] = line[i];
        while (strstr(letter, neku) == 0) {
            letter[0] = line[i];
            i++;
        }

        int nekudotaim = i - 1;
        letter[0] = line[i - 2];

        // saving which kind of effective list is in row ,to use in if-else condition to check if its "me" or "other" effective list, used later in code
        char which[2] = "";
        strncpy(which,&letter[0],1);

            // counts how many to effective list
            int totaltoeffectivelist;
            totaltoeffectivelist = 0;
            for (i = i; line[i] != '\0'; i++) {
                letter[0] = line[i];
                if (strstr(&letter[0], psik) != 0) {
                    totaltoeffectivelist++;
                }
            }
            totaltoeffectivelist++;
            int source;

            // saves which index in the type list in the pokedex is the source to add to
            for (source = 0; source < numberOfTypes; source++) {
                if (strcmp(pokedex_1.types[source].name, cur_type) == 0) {
                    break;
                }
            }
            int curtoeffectivelist;
            j = nekudotaim;

            // adds each type in the row, to the relevant found list, of the source found
            for (curtoeffectivelist = 0; curtoeffectivelist < totaltoeffectivelist; curtoeffectivelist++) {
                j++;
                i = 0;
                letter[0] = line[j];
                memset(buffer, 0, strlen(buffer));
                // finding the next type in the row
                while ((strstr(&letter[0], psik) == 0) && line[j] != *bsr && line[j] != *bst) {
                    buffer[i] = line[j];
                    i++;
                    j++;
                    letter[0] = line[j];
                }
                cur_type = realloc(cur_type, strlen(buffer) + 1);
                if (cur_type == NULL){
                    printf("Memory Problem");
                    destroy_all(pokedex_1.types, pokedex_1.pokemons, pokedex_1.num_types, pokedex_1.num_pokemons, data);
                    return 0;
                }
                strcpy(cur_type, buffer);
                // finding the lst stop in the list, in which to put the new type
                int curtoeffectiveobject;
                for (curtoeffectiveobject = 0; curtoeffectiveobject < numberOfTypes; curtoeffectiveobject++) {
                    if (strcmp(pokedex_1.types[curtoeffectiveobject].name, cur_type) == 0) {
                        break;
                    }
                }

                // if-else condition that uses the char saved in line 161, to determine the relevant list (me/others)
                if (strstr(which, e) != 0) {
                    pokedex_1.types[source].howmanyme++;
                    pokedex_1.types[source].effectiveagainstme = (typeofpokemon **) realloc(
                            pokedex_1.types[source].effectiveagainstme,
                            pokedex_1.types[source].howmanyme * sizeof(typeofpokemon *));
                    if (pokedex_1.types[source].effectiveagainstme == NULL){
                        printf("Memory Problem");
                        destroy_all(pokedex_1.types, pokedex_1.pokemons, pokedex_1.num_types, pokedex_1.num_pokemons, data);
                        return 0;
                    }
                    pokedex_1.types[source].effectiveagainstme[pokedex_1.types[source].howmanyme - 1] = &(pokedex_1.types[curtoeffectiveobject]);
                    if (pokedex_1.types[source].howmanyme == totaltoeffectivelist) {
                        break;
                    }
                }
                else {
                    pokedex_1.types[source].howmanyother++;
                    pokedex_1.types[source].effectiveagainstother = (typeofpokemon **) realloc(
                            pokedex_1.types[source].effectiveagainstother,
                            pokedex_1.types[source].howmanyother * sizeof(typeofpokemon *));
                    if (pokedex_1.types[source].effectiveagainstother == NULL){
                        printf("Memory Problem");
                        destroy_all(pokedex_1.types, pokedex_1.pokemons, pokedex_1.num_types, pokedex_1.num_pokemons, data);
                        return 0;
                    }
                    pokedex_1.types[source].effectiveagainstother[pokedex_1.types[source].howmanyother - 1] = &(pokedex_1.types[curtoeffectiveobject]);
                    if (pokedex_1.types[source].howmanyother == totaltoeffectivelist) {
                        break;
            }
        }
            }
            free(cur_type);
        }

    // check when I am in the pokemons segment in file
    if (strstr(line, "Pokemons") == 0) {
        line_number = 0;
        int pokemons_line = 0;
        while (fgets(line, sizeof(line), data)) {
            if (pokemons_line != 0) {
                break;
            }
            line_number++;
            if (strstr(line, "Pokemons") != 0) {
                pokemons_line = line_number + 1;
            }
        }
    }

    // reads all pokemons and inserts to list by order of reading
    while (fgets(line, sizeof(line), data)) {
        char s[2] = ",";
        char *token;
        int counter = 0;
        char *type;
        char *name;
        char *species;
        double height;
        double weight;
        int attack;
        int chars = 0;

        token = strtok(line, s);
        size_t x;
        while (token != NULL) {
            switch (counter) {
                case 0:
                    name = malloc(strlen(token) + 1);
                    if (name == NULL){
                        printf("Memory Problem");
                        destroy_all(pokedex_1.types, pokedex_1.pokemons, pokedex_1.num_types, pokedex_1.num_pokemons, data);
                        return 0;
                    }
                    strcpy(name, token);
                    counter++;
                    break;

                case 1:
                    species = malloc(strlen(token) + 1);
                    if (species == NULL){
                        printf("Memory Problem");
                        destroy_all(pokedex_1.types, pokedex_1.pokemons, pokedex_1.num_types, pokedex_1.num_pokemons, data);
                        return 0;
                    }
                    strcpy(species, token);
                    counter++;
                    break;

                case 2:
                    height = atof(token);
                    counter++;
                    break;

                case 3:
                    weight = atof(token);
                    counter++;
                    break;

                case 4:
                    attack = atoi(token);
                    counter++;
                    break;

                case 5:
                    for (i = 0; i < strlen(token); i++) {
                        if (isalpha(token[i])) {
                            chars++;
                        }
                    }
                    type = calloc(1, chars + 1);
                    if (type == NULL){
                        printf("Memory Problem");
                        destroy_all(pokedex_1.types, pokedex_1.pokemons, pokedex_1.num_types, pokedex_1.num_pokemons, data);
                        return 0;
                    }
                    for (i = 0; i < chars; i++) {
                        if (isalpha(token[i])) {
                            type[i] = token[i];
                        }
                    }
                default:;
            }
            token = strtok(NULL, s);
        }

        // finding the next empty place to put the next pokemon
        int num = pokedex_1.num_pokemons;
        for(i = 0 ; i < num ; i++){
            if (pokedex_1.pokemons[i].name == NULL){
                break;
            }
        }

        // initializing pokemon, and placing it in its relevant spot in the list.
        status init_poke = init_pokemon(&pokedex_1.pokemons[i], name, species, type, height, weight, attack);
        if (init_poke == failure){
            printf("Pokemon %s not initiated", name);
        }
        int ii;
        for(ii = 0 ; ii < num ; ii++){
            if (strcmp(pokedex_1.types[ii].name, pokedex_1.pokemons[i].poketype) == 0){
                pokedex_1.types[ii].howmany++;
                break;
            }
        }
        free(type);
        free(species);
        free(name);
    }

    int choice;
    do {
        choice = 0;
        printf("Please choose one of the following numbers:\n");
        printf("1 : Print all Pokemons\n");
        printf("2 : Print all Pokemons types\n");
        printf("3 : Add type to effective against me list\n");
        printf("4 : Add type to effective against others list\n");
        printf("5 : Remove type from effective against me list\n");
        printf("6 : Remove type from effective against others list\n");
        printf("7 : Print Pokemon by name\n");
        printf("8 : Print Pokemons by type\n");
        printf("9 : Exit\n");

        scanf(" %d", &choice);
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        char requestpokemon[22];
        char requesttype[9];
        char sourcetype[9];
        char tolisttype[9];
        status x;
        switch (choice) {
            case 1:
                // Print all Pokemons
                for (i = 0; i < numberOfPokemons; i++) {
                    print_pokemon(&(pokedex_1.pokemons[i]));
                }
                choice = 10;
                break;

            case 2:
                // Print all Pokemons listoftypes
                for (i = 0; i < numberOfTypes; i++) {
                    print_type(&(pokedex_1.types[i]));
                }
                choice = 10;
                break;

            case 3: case 4:
                // Add type to effective against me list
                memset(sourcetype, 0, strlen(sourcetype));
                printf("Please enter type name:\n");
                scanf("%s", sourcetype);
                x = failure;
                for (i = 0; i < numberOfTypes; i++) {
                    if (strcmp(pokedex_1.types[i].name, sourcetype) == 0) {
                        x = success;
                        break;
                    }
                }
                    if (x == failure) {
                        choice = 10;
                        fprintf(stdout, "Type name doesn't exist.\n");
                        break;
                    }
                int k;
                if (choice == 3) {
                    memset(tolisttype, 0, strlen(tolisttype));
                    printf("Please enter type name to add to %s effective against me list:\n", sourcetype);
                    scanf("%s", tolisttype);
                    x = failure;
                    int j;
                    for (j = 0; j < numberOfTypes; j++) {
                        if (strcmp(pokedex_1.types[j].name, tolisttype) == 0) {
                            x = success;
                            break;
                        }
                    }
                    if (x == failure) {
                        choice = 10;
                        fprintf(stdout, "Type name doesn't exist.\n");
                        break;
                    }

                        for (k = 0; k < pokedex_1.types[i].howmanyme; k++) {
                            if (strcmp(pokedex_1.types[i].effectiveagainstme[k]->name, tolisttype) == 0) {
                                x = failure;
                                break;
                            }
                        }
                        if (x == failure) {
                            choice = 10;
                            fprintf(stdout, "This type already exist in the list.\n");
                            break;
                        }
                        pokedex_1.types[i].howmanyme++;
                        k++;
                        if (pokedex_1.types[i].howmanyme == 1){
                            pokedex_1.types[i].effectiveagainstme = (typeofpokemon **) malloc(sizeof(typeofpokemon *));
                            if (pokedex_1.types[i].effectiveagainstme == NULL){
                                printf("Memory Problem");
                                destroy_all(pokedex_1.types, pokedex_1.pokemons, pokedex_1.num_types, pokedex_1.num_pokemons, data);
                                return 0;
                            }
                        }
                        else {
                            pokedex_1.types[i].effectiveagainstme = (typeofpokemon **) realloc(
                                    pokedex_1.types[i].effectiveagainstme,
                                    pokedex_1.types[i].howmanyme * sizeof(typeofpokemon *));
                            if (pokedex_1.types[i].effectiveagainstme == NULL){
                                printf("Memory Problem");
                                destroy_all(pokedex_1.types, pokedex_1.pokemons, pokedex_1.num_types, pokedex_1.num_pokemons, data);
                                return 0;
                            }
                        }
                            pokedex_1.types[i].effectiveagainstme[k - 1] = &(pokedex_1.types[j]);
                        if (x == success) {
                            print_type(&pokedex_1.types[i]);
                        }
                    }
                else if (choice == 4) {
                    memset(tolisttype, 0, strlen(tolisttype));
                    printf("Please enter type name to add to %s effective against others list:\n", sourcetype);
                    scanf("%s", tolisttype);
                    x = failure;
                    int j;
                    for (j = 0; j < numberOfTypes; j++) {
                        if (strcmp(pokedex_1.types[j].name, tolisttype) == 0) {
                            x = success;
                            break;
                        }
                    }
                    if (x == failure) {
                        choice = 10;
                        fprintf(stdout, "Type name doesn't exist.\n");
                        break;
                    }
                        for (k = 0; k < pokedex_1.types[i].howmanyother; k++) {
                            if (strcmp(pokedex_1.types[i].effectiveagainstother[k]->name, tolisttype) == 0) {
                                x = failure;
                                break;
                            }
                        }
                        if (x == failure) {
                            choice = 10;
                            fprintf(stdout, "This type already exist in the list.\n");
                            break;
                        }
                        pokedex_1.types[i].howmanyother++;
                        k++;
                        if (pokedex_1.types[i].howmanyother == 1){
                            pokedex_1.types[i].effectiveagainstother = (typeofpokemon **) malloc(sizeof(typeofpokemon *));
                            if (pokedex_1.types[i].effectiveagainstother == NULL){
                                printf("Memory Problem");
                                destroy_all(pokedex_1.types, pokedex_1.pokemons, pokedex_1.num_types, pokedex_1.num_pokemons, data);
                                return 0;
                            }
                        }
                        else {
                            pokedex_1.types[i].effectiveagainstother = (typeofpokemon **) realloc(
                                    pokedex_1.types[i].effectiveagainstother,
                                    pokedex_1.types[i].howmanyme * sizeof(typeofpokemon *));
                            if (pokedex_1.types[i].effectiveagainstother == NULL){
                                printf("Memory Problem");
                                destroy_all(pokedex_1.types, pokedex_1.pokemons, pokedex_1.num_types, pokedex_1.num_pokemons, data);
                                return 0;
                            }
                        }
                        pokedex_1.types[i].effectiveagainstother[k - 1] = &(pokedex_1.types[j]);
                        if (x == success) {
                            print_type(&pokedex_1.types[i]);
                        }
                    }
                    choice = 10;
                    break;

            case 5: case 6:
                // Remove type from effective against me list
                memset(sourcetype, 0, strlen(sourcetype));
                printf("Please enter type name:\n");
                scanf("%s", sourcetype);
                x = failure;
                int j;
                for (i = 0; i < numberOfTypes; i++) {
                    if (strcmp(pokedex_1.types[i].name, sourcetype) == 0) {
                        x = success;
                        break;
                    }
                }
                if (x == failure) {
                    choice = 10;
                    fprintf(stdout, "Type name doesn't exist.\n");
                    break;
                }
                if (choice == 5) {
                memset(tolisttype, 0, strlen(tolisttype));
                printf("Please enter type name to remove from %s effective against me list:\n", sourcetype);
                scanf("%s", tolisttype);
                x = failure;
                for (j = 0; j < numberOfTypes; j++) {
                    if (strcmp(pokedex_1.types[j].name, tolisttype) == 0) {
                        x = success;
                        break;
                    }
                }
                if (x == failure) {
                    choice = 10;
                    fprintf(stdout, "Type name doesn't exist in the list.\n");
                    break;
                }
                for (k = 0; k < pokedex_1.types[i].howmanyme; k++) {
                    if (strcmp(pokedex_1.types[i].effectiveagainstme[k]->name, tolisttype) == 0) {
                        x = failure;
                        break;
                    }
                }
                if (x == success) {
                    choice = 10;
                    fprintf(stdout, "Type name doesn't exist in the list.\n");
                    break;
                }
                    pokedex_1.types[i].howmanyme--;
                typeofpokemon **curr = (typeofpokemon**)malloc(pokedex_1.types[i].howmanyme * sizeof(typeofpokemon));
                if (curr == NULL){
                    printf("Memory Problem");
                    destroy_all(pokedex_1.types, pokedex_1.pokemons, pokedex_1.num_types, pokedex_1.num_pokemons, data);
                    return 0;
                }
                int z;
                int z1;
                z1 = 0;
                for (z = 0 ; z < pokedex_1.types[i].howmanyme + 1; z++){
                    if (z==k){
                        continue;
                    }
                    else{
                        curr[z1] = pokedex_1.types[i].effectiveagainstme[z];
                        z1++;
                    }
                }
                free(pokedex_1.types[i].effectiveagainstme);
                pokedex_1.types[i].effectiveagainstme = curr;
                print_type(&pokedex_1.types[i]);
                }
                else if (choice == 6) {
                    memset(tolisttype, 0, strlen(tolisttype));
                    printf("Please enter type name to remove from %s effective against others list:\n", sourcetype);
                    scanf("%s", tolisttype);
                    x = failure;
                    for (j = 0; j < numberOfTypes; j++) {
                        if (strcmp(pokedex_1.types[j].name, tolisttype) == 0) {
                            x = success;
                            break;
                        }
                    }
                    if (x == failure) {
                        choice = 10;
                        fprintf(stdout, "Type name doesn't exist in the list.\n");
                        break;
                    }
                for (k = 0; k < pokedex_1.types[i].howmanyother; k++) {
                    if (strcmp(pokedex_1.types[i].effectiveagainstother[k]->name, tolisttype) == 0) {
                        x = failure;
                        break;
                    }
                }
                if (x == success) {
                    choice = 10;
                    fprintf(stdout, "Type name doesn't exist in the list.\n");
                    break;
                }
                pokedex_1.types[i].howmanyother--;
                typeofpokemon **curr = (typeofpokemon**)malloc(pokedex_1.types[i].howmanyother * sizeof(typeofpokemon));
                if (curr == NULL){
                    printf("Memory Problem");
                    destroy_all(pokedex_1.types, pokedex_1.pokemons, pokedex_1.num_types, pokedex_1.num_pokemons, data);
                    return 0;
                }
                int z;
                int z1;
                z1 = 0;
                for (z = 0 ; z < pokedex_1.types[i].howmanyother + 1; z++){
                    if (z==k){
                        continue;
                    }
                    else{
                        curr[z1] = pokedex_1.types[i].effectiveagainstother[z];
                        z1++;
                    }
                }
                free(pokedex_1.types[i].effectiveagainstother);
                pokedex_1.types[i].effectiveagainstother = curr;
                print_type(&pokedex_1.types[i]);
                }
                choice = 10;
                break;

            case 7:
                // Print Pokemon by name
                x = failure;
                printf("Please enter Pokemon name:\n");
                scanf("%s", requestpokemon);
                for (i = 0; i < numberOfPokemons; i++) {
                    if (strcmp(requestpokemon, pokedex_1.pokemons[i].name) == 0) {
                        print_pokemon(&(pokedex_1.pokemons[i]));
                        x = success;
                        break;
                    }
                }
                if (x != success) {
                    fprintf(stdout, "The Pokemon doesn't exist.\n");
                }
                choice = 10;
                break;

            case 8:
                // Print Pokemons by type
                x = failure;
                printf("Please enter type name:\n");
                scanf("%s", requesttype);
                for (i = 0; i < numberOfTypes; i++) {
                    if (strcmp(requesttype, pokedex_1.types[i].name) == 0) {
                        x = success;
                        if (pokedex_1.types[i].howmany > 0) {
                            printf("There are %d Pokemons with this type:\n", pokedex_1.types[i].howmany);
                            for (j = 0; j < numberOfPokemons; j++) {
                                if (strcmp(pokedex_1.pokemons[j].poketype, requesttype) == 0) {
                                    print_pokemon(&(pokedex_1.pokemons[j]));
                                }
                            }
                        } else {
                            printf("There are no Pokemons with this type:\n");
                        }
                        break;
                    }
                }
                if (x != success) {
                    fprintf(stdout, "Type name doesn't exist.\n");
                }
                choice = 10;
                break;

            case 9:
                // Exit
                destroy_all(pokedex_1.types, pokedex_1.pokemons, pokedex_1.num_types, pokedex_1.num_pokemons, data);
                break;

            default:
                fprintf(stdout, "Please choose a valid number.\n");
            choice = 10;
                }
        }
     while (choice < 0 || choice > 9);

        return 0;
}
