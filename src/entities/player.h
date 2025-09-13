#ifndef PLAYER_H
#define PLAYER_H

#include "../components/cards.h"
#include "../components/augmentation.h"

extern CardVariant handCards[2][MAX_CARDS];
extern int handCardsCount[2];

extern float hp[2];

Augmentation *augmentations[2];

void init_support_deck(int augmentation_id);

void add_modifier(int player, PlacementModifier mod);

#endif