#include "augmentation.h"

/*
allows jokers to be placed in every slots
*/
bool clown_joker_anywhere(int player, int x, int y, CardVariant *card, BoardSlot *slot) {
    if (card->type == Joker) return true;
    return true;
}

Augmentation clownAug = {
    .name = "Clown",
    .placementModifiers = { clown_joker_anywhere },
    .placementModifierCount = 1,
    .damageModifiers = {0},
    .damageModifierCount = 0,
    .destructionHandlers = {0},
    .destructionHandlerCount = 0,
    .postAttackHooks = {0},
    .postAttackHookCount = 0,
    .discardModifiers = {0},
    .discardModifierCount = 0,
    .supportPileCount = SUPPORT_DECK_SIZE,
    .supportPile = {0}  //TODO: think of cool cards
};

/*
makes the attack cards support cards and allows support cards attack cards
*/
bool magician_swap_attack_support(int player, int x, int y, CardVariant *card, BoardSlot *slot) {
    if (card->type == Attack && board[player][x][1].card != NULL) {
        board[player][x][1].card = card;
        return false;
    }
    return true;
}

Augmentation magicianAug = {
    .name = "Magician",
    .placementModifiers = { magician_swap_attack_support },
    .placementModifierCount = 1,
    .damageModifiers = {0},
    .damageModifierCount = 0,
    .destructionHandlers = {0},
    .destructionHandlerCount = 0,
    .postAttackHooks = {0},
    .postAttackHookCount = 0,
    .discardModifiers = {0},
    .discardModifierCount = 0,
    .supportPileCount = SUPPORT_DECK_SIZE,
    .supportPile = {0}  //TODO: think of cool cards
};