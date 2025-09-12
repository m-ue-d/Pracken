#include "stdbool.h"
#include "stdlib.h"
#include "stdio.h"

#include "../utils/random.h"

#include "../components/cards.h"
#include "../entities/player.h"

extern AttackCard attackPile[ATTACK_DECK_SIZE];
extern int attackPileCount;

extern CardVariant discardPile[MAX_CARDS];
extern int discardPileCount;


extern int currentTurn;

void init_attack_deck();

void draw_card();

bool place_card(int idx, int x, int y);

void attack_opponent();

bool discard_card(int idx);

void free_discard_pile();