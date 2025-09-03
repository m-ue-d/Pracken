#include "stdbool.h"
#include "stdlib.h"

#include "../components/cards.h"

#define ATTACK_DECK_SIZE 52
#define SUPPORT_DECK_SIZE 8
#define MAX_CARDS 128

extern AttackCard attackPile[ATTACK_DECK_SIZE];
extern SupportCard supportPile[SUPPORT_DECK_SIZE];
extern CardVariant discardPile[MAX_CARDS];

extern int currentTurn;

void init_attack_deck();

void draw_phase();

bool place_card();

void battle_phase();

bool discard_card(int idx);

void free_discard_pile();