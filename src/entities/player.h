#ifndef PLAYER_H
#define PLAYER_H

#include "../components/cards.h"
#include "../components/augmentation.h"

extern CardVariant handCards[2][MAX_CARDS];
extern int handCardsCount[2];

extern float hp[2];

extern Augmentation *augmentations[2];

void init_support_deck(int augmentation_id);

//FIXME: DUPE CODE! REPLACE ASAP!!!
void add_placement_modifier(int player, PlacementModifier mod);
void add_attack_modifier(int player, AttackModifier mod);
void add_discard_modifier(int player, DiscardModifier mod);

#endif