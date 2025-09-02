#include "cardsystem.h"

int currentTurn = 0;
AttackCard attackDeck[ATTACKDECKSIZE];

void init_attack_deck() {
    for (int i = 0; i < ATTACKDECKSIZE; i++)
    {
        attackDeck[i] = (AttackCard) {
            .color = i / 13,
            .value = (i % 13) + 1,
            .baseModifier = 1.0f
        };
    }
    
}