#include "Pokemon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

status init_type(typeofpokemon *ptypeofpokemon, char *name)
{
    if (ptypeofpokemon == NULL || name == NULL){
        return failure;
    }
    ptypeofpokemon->name = (char*)malloc(strlen(name)+1);
    if (ptypeofpokemon->name == NULL){
        printf("Memory Problem");
        return failure;
    }
    strcpy(ptypeofpokemon->name, name);
    ptypeofpokemon->effectiveagainstme = (typeofpokemon **) NULL;
    ptypeofpokemon->effectiveagainstother = (typeofpokemon **) NULL;
    return success;
}

void destroy_type(typeofpokemon * type) {
    if (type->effectiveagainstme != NULL) {
        free(type->effectiveagainstme);
    }
    if (type->effectiveagainstme != NULL) {
        free(type->effectiveagainstother);
    }
    if (type->name != NULL) {
        free(type->name);
    }
}

status init_pokemon(pokemon *newpoke, char *name, char *species, char *poketype,
                  double height, double weight, int attack) {
    if (newpoke == NULL || name == NULL || poketype == NULL){
        return failure;
    }
    newpoke->name = (char*)malloc(strlen(name)+1);
    if (newpoke->name == NULL){
        printf("Memory Problem");
        return failure;
    }
    strcpy(newpoke->name, name);
    newpoke->species = (char*)malloc(strlen(species)+1);
    if (newpoke->species == NULL){
        printf("Memory Problem");
        return failure;
    }
    strcpy(newpoke->species, species);
    newpoke->poketype = (char*)malloc(strlen(poketype)+1);
    if (newpoke->poketype == NULL){
        printf("Memory Problem");
        return failure;
    }
    strcpy(newpoke->poketype, poketype);
    newpoke->bioinfo =
            (bio *) malloc( sizeof(bio));
    if (newpoke->bioinfo == NULL){
        printf("Memory Problem");
        return failure;
    }
    status init_b = init_bio(newpoke->bioinfo, height, weight, attack);
    if (init_b == failure){
        printf("Type %s not initiated", name);
    }
    return success;
}

void destroy_pokemon(pokemon * poke){
    if (poke->name != NULL) {
        free(poke->name);
    }
    if (poke->species != NULL) {
        free(poke->species);
    }
    if (poke->poketype != NULL) {
        free(poke->poketype);
    }
    if (poke->bioinfo != NULL) {
        destroy_bio(poke->bioinfo);
    }
}

status init_bio(bio *pbio,double height, double weight, int attack){
    if (pbio == NULL){
        return failure;
    }
    pbio->height = height;
    pbio->weight = weight;
    pbio->attack = attack;
    return success;
}

void destroy_bio(bio * bio1){
    free(bio1);
}

void print_pokemon(pokemon *pokemon1){
    printf("%s :\n", pokemon1->name);
    printf("%s, %s Type.\n", pokemon1->species, pokemon1->poketype);
    printf("Height: %.2f m    Weight: %.2f kg    Attack: %d\n\n", pokemon1->bioinfo->height, pokemon1->bioinfo->weight, pokemon1->bioinfo->attack);
}

void print_type(typeofpokemon *typeofpokemon1){
    printf("Type %s -- %d pokemons\n", typeofpokemon1->name, typeofpokemon1->howmany);

    if(typeofpokemon1->howmanyme > 0) {
        printf("\tThese types are super-effective against %s:", typeofpokemon1->name);
        int i;
        for ( i = 0 ; i < typeofpokemon1->howmanyme - 1; i++){
            printf("%s ,", typeofpokemon1->effectiveagainstme[i]->name);
        }
        printf("%s\n", typeofpokemon1->effectiveagainstme[i]->name);
    }

    if(typeofpokemon1->howmanyother > 0) {
        printf("\t%s moves are super-effective against:", typeofpokemon1->name);
        int i;
        for ( i = 0 ; i < typeofpokemon1->howmanyother - 1; i++){
            printf("%s ,", typeofpokemon1->effectiveagainstother[i]->name);
        }
        printf("%s\n", typeofpokemon1->effectiveagainstother[i]->name);
    }
    printf("\n");
}



