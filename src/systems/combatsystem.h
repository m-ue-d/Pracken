#ifndef COMBATSYSTEM_H
#define COMBATSYSTEM_H

#include <stdbool.h>
#include "cards.h"
#include "player.h"
#include "board.h"
#include "augmentation.h"

void attack_opponent(int currentTurn);

bool direct_attack_possible(int defender);
int get_base_damage(CardVariant *attacker);
int apply_damage_modifiers(int attackerPlayer, int defenderPlayer, CardVariant *attacker, CardVariant *target, int baseDamage);
bool apply_damage_to_card(int ownerPlayer, BoardSlot *targetSlot, CardVariant *targetCard, int damage);
void handle_card_destruction(int ownerPlayer, BoardSlot *slot);
void apply_post_attack_hooks(int attackerPlayer, int defenderPlayer, CardVariant *attacker, CardVariant *target, int finalDamage);

#endif