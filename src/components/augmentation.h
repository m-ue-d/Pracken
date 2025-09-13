#ifndef AUGMENTATION_H
#define AUGMENTATION_H

#include <stdbool.h>
#include <stddef.h>

#include "cards.h"
#include "../entities/board.h"

#define MAX_AUGMENTATION_MODIFIERS 16

typedef bool (*PlacementModifier)(int player, int x, int y, CardVariant *card, BoardSlot *slot);

typedef struct {
    char name[32];

    PlacementModifier modifiers[MAX_AUGMENTATION_MODIFIERS];
    int modifierCount;

    SupportCard supportPile[SUPPORT_DECK_SIZE];
    int supportPileCount;
} Augmentation;

extern Augmentation clownAug;
extern Augmentation magicianAug;

#endif