#ifndef CARDSYSTEM_H
#define CARDSYSTEM_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include "../utils/random.h"

#include "../components/cards.h"
#include "../entities/player.h"
#include "../entities/board.h"

extern AttackCard attackPile[ATTACK_DECK_SIZE];
extern int attackPileCount;

extern CardVariant discardPile[MAX_CARDS];
extern int discardPileCount;


extern int currentTurn;

void init_decks();

void shuffle_deck(void *deck, size_t decksize, size_t elementSize);

void remove_from_hand(int player, int idx);

void draw_card();

bool place_card(int idx, int x, int y);

void attack_opponent();

bool discard_card(int idx);

void free_discard_pile();

#endif