#include "cardsystem.h"

int currentTurn = 0;
AttackCard attackDeck[ATTACK_DECK_SIZE];
CardVariant discardPile[MAX_CARDS];

void init_attack_deck() {
    for (int i = 0; i < ATTACK_DECK_SIZE; i++)
    {
        attackDeck[i] = (AttackCard) {
            .color = i / 13,
            .value = (i % 13) + 1,
            .baseModifier = 1.0f
        };
    }
    
}

void draw_phase() {

}

bool place_card() {
    return false;
}

void battle_phase() {

}

bool discard_card(int idx) {
    return false;
}

void free_discard_pile() {
    for (int i = 0; i < MAX_CARDS; i++)
    {
        free(discardPile[i].ptr);
    }
}