#ifndef POKEMON_H
#define POKEMON_H

typedef struct {
    char name[12];
    double height;
    double weight;
    int attack;
} pokemon ;

typedef struct typeofpokemon{
    int howmany;
    char name[9];
    pokemon *pokemonsofthistype;
    struct typeofpokemon *effectiveagainstme;
    struct typeofpokemon *effectiveagainstother;
} typeofpokemon ;

typedef struct  {
    int num_types;
    typeofpokemon *types;
} pokedex ;

// initializes pokedex
void init_pokedex(pokedex *ppokedex, int numoftypes, int numofpokemons, char *types);

// initializes type of pokemon
void init_type(typeofpokemon *typeofpokemon, int num, char *name);

// initializes pokemon
void init_pokemon(pokemon *curpokemon);

# endif
