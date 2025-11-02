#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H

#include <stdbool.h>
#include "cards.h"
#include "../components/augmentation.h"
#include "board.h"

void attack_opponent(void);

int get_base_damage(CardVariant *attacker);
int apply_damage_modifiers(int attackerPlayer, int defenderPlayer, CardVariant *attacker, CardVariant *target, int baseDamage);
bool apply_damage_to_card(int ownerPlayer, BoardSlot *targetSlot, CardVariant *targetCard, int damage);
void handle_card_destruction(int ownerPlayer, BoardSlot *slot);
void apply_post_attack_hooks(int attackerPlayer, int defenderPlayer, CardVariant *attacker, CardVariant *target, int finalDamage);


#endif