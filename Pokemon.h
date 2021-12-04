#ifndef POKEMON_H
#define POKEMON_H
#include "Defs.h"

// structs to hold the 3 objects of the project
typedef struct
{
    double height;
    double weight;
    int attack;
} bio;

typedef struct
{
    char *name;
    char *species;
    char *poketype;
    bio *bioinfo;
} pokemon;

typedef struct typeofpokemon{
    int howmany;
    char *name;
    int howmanyme;
    struct typeofpokemon **effectiveagainstme;
    int howmanyother;
    struct typeofpokemon **effectiveagainstother;
} typeofpokemon;

// initializes type of pokemon
status init_type(typeofpokemon *ptypeofpokemon, char *name);

// destroys type of pokemon
void destroy_type(typeofpokemon * type);

// initializes pokemon
status init_pokemon(pokemon *newpoke, char *name, char *species, char *poketype,
                  double height, double weight, int attack);
// destroys pokemon
void destroy_pokemon(pokemon * poke);

// initializes bio
status init_bio(bio *pbio,double height, double weight, int attack);

// destroys bio
void destroy_bio(bio * bio1);

void print_pokemon(pokemon *pokemon1);

void print_type(typeofpokemon *typeofpokemon1);

#endif
