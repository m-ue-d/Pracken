#include "player.h"

SupportCard supportPile[2][SUPPORT_DECK_SIZE] = {0};
int supportPileCount[2] = {0, 0};

CardVariant handCards[2][MAX_CARDS] = {0};
int handCardsCount[2] = {0, 0};

float hp[2] = { 8888, 8888 };

Augmentation *augmentations[2] = {0};

void init_support_deck(int augmentation_id) {
    //TODO: Implement
}

void add_modifier(int player, PlacementModifier mod) {
    if (augmentations[player]->modifierCount < MAX_AUGMENTATION_MODIFIERS) {
        augmentations[player]->modifiers[augmentations[player]->modifierCount++] = mod;
    }
}