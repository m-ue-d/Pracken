#include "combatsystem.h"
#include <stdio.h>
#include <string.h>

bool direct_attack_possible(int defender) {
    for (size_t i = 0; i < BOARD_WIDTH; i++) {
        if (board[defender][1][i].card) return false;
    }
    return true;
}

int get_base_damage(CardVariant *attacker) {
    if(!attacker) return;

    switch (attacker->type) {
        case Attack:
            AttackCard *a = (AttackCard *) attacker->ptr;
            return a ? a->value * a->baseModifier : 0;
        case Joker:
            JokerCard *j = (JokerCard *) attacker->ptr;
            return j ? j->value * j->baseModifier : 0;
        default:
            return 0;
    }
}

//apply modifiers in order 1.attacker and 2.defender to the damage value
int apply_damage_modifiers(int attackerPlayer, int defenderPlayer, CardVariant *attacker, CardVariant *target, int baseDamage) {
    int damage = baseDamage;

    Augmentation *attackerAug = augmentations[attackerPlayer];
    Augmentation *defenderAug = augmentations[defenderPlayer];

    if (attackerAug) {
        for (int i = 0; i < attackerAug->attackModifierCount; ++i) {
            AttackModifier m = attackerAug->attackModifiers[i];
            if (m) damage = m(attackerPlayer, defenderPlayer, attacker, target, damage);
        }
    }

    if (defenderAug) {
        for (int i = 0; i < defenderAug->defenseModifierCount; ++i) {
            DefenseModifier m = defenderAug->defenseModifiers[i];
            if (m) damage = m(attackerPlayer, defenderPlayer, attacker, target, damage);
        }
    }

    return damage;
}

//destroys the card if damage is high enough, when there is no card
bool apply_damage_to_card(int ownerPlayer, BoardSlot *targetSlot, CardVariant *targetCard, int damage) {

}

void handle_card_destruction(int ownerPlayer, BoardSlot *slot) {

}

void apply_post_attack_hooks(int attackerPlayer, int defenderPlayer, CardVariant *attacker, CardVariant *target, int finalDamage) {

}

void attack_opponent(int currentTurn) {
    int currentPlayer = currentTurn % 2;
    int enemyPlayer = 1 - currentPlayer;

    extern int chosenAttackX, chosenAttackY; //attacker coordinates
    extern int chosenTargetX, chosenTargetY; //target coordinates
    extern bool chosenDirectAttack; // if true, attack HP directly


}