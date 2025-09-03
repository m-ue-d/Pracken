#include "stdbool.h"
#include "stdlib.h"

#include "../components/cards.h"
#include "../entities/player.h"

extern AttackCard attackPile[ATTACK_DECK_SIZE];
extern int attackPileCount;

extern CardVariant discardPile[MAX_CARDS];
extern int discardPileCount;


extern int currentTurn;

void init_attack_deck();

void draw_phase();

bool place_card();

void battle_phase();

bool discard_card(int idx);

void free_discard_pile();