#ifndef AUGMENTATION_H
#define AUGMENTATION_H

#include <stdbool.h>
#include <stddef.h>

#include "cards.h"
#include "../entities/board.h"

#define MAX_AUGMENTATION_MODIFIERS 16

//modifies placement and returns if the default should be skipped or not
typedef bool (*PlacementModifier)(int player, int x, int y, CardVariant *card, BoardSlot *slot);

//returns damage based on currentDamage
typedef int (*DamageModifier)(int attackerPlayer, int defenderPlayer, CardVariant *attacker, CardVariant *target, int currentDamage);

//handles destruction and returns whether the default action is allowed or not
typedef bool (*DestructionHandler)(int ownerPlayer, CardVariant *card, int incomingDamage);

//run when an attack is done to apply final calculations
typedef void (*PostAttackHook)(int attackerPlayer, int defenderPlayer, CardVariant *attacker, CardVariant *target, int finalDamage);

//modifies discarding cards and returns if the default should be skipped or not
typedef bool (*DiscardModifier)(int player, CardVariant *card);

typedef struct {
    char name[32];

    //1: placement
    PlacementModifier placementModifiers[MAX_AUGMENTATION_MODIFIERS];
    int placementModifierCount;

    //2: combat
    DamageModifier damageModifiers[MAX_AUGMENTATION_MODIFIERS];
    int damageModifierCount;

    DestructionHandler destructionHandlers[MAX_AUGMENTATION_MODIFIERS];
    int destructionHandlerCount;

    PostAttackHook postAttackHooks[MAX_AUGMENTATION_MODIFIERS];
    int postAttackHookCount;

    //3: discard
    DiscardModifier discardModifiers[MAX_AUGMENTATION_MODIFIERS];
    int discardModifierCount;

    SupportCard supportPile[SUPPORT_DECK_SIZE];
    int supportPileCount;
} Augmentation;

extern Augmentation clownAug;
extern Augmentation magicianAug;

#endif