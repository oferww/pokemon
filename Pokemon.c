#include "Pokemon.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void init_pokedex(pokedex *ppokedex, int numoftypes, int numofpokemons, char typess[][9]){
    ppokedex->num_types = numoftypes;
    ppokedex->types = (typeofpokemon *) malloc(numoftypes * sizeof(typeofpokemon));
    int i;
    for ( i = 0 ; i < numoftypes ; i++) {
        init_type(&(ppokedex->types[i]), numofpokemons, &typess[i]);
    }
}

void init_type(typeofpokemon *ptypeofpokemon, int numofpokemons, char name[][9]){
    ptypeofpokemon->howmany = 0;
    strcpy(ptypeofpokemon->name, *name);
    ptypeofpokemon->pokemonsofthistype = (pokemon *) realloc(ptypeofpokemon->pokemonsofthistype , numofpokemons * sizeof(pokemon));
    ptypeofpokemon->effectiveagainstme = (typeofpokemon *) realloc(ptypeofpokemon->effectiveagainstme , numofpokemons * sizeof(typeofpokemon));
    ptypeofpokemon->effectiveagainstother = (typeofpokemon *) realloc(ptypeofpokemon->effectiveagainstother , numofpokemons * sizeof(typeofpokemon));

}
