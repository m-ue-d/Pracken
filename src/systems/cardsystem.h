#include "stdbool.h"

#include "../components/cards.h"

#define ATTACKDECKSIZE 52

extern AttackCard attackDeck[ATTACKDECKSIZE];
extern int currentTurn;

void draw_phase();

bool place_card();

void battle_phase();

bool discard_card();

void init_attack_deck();