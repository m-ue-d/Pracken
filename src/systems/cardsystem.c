#include "cardsystem.h"

int currentTurn = 0;

AttackCard attackPile[ATTACK_DECK_SIZE] = {0};
attackPileCount = 0;

CardVariant discardPile[MAX_CARDS] = {0};
discardPileCount = 0;

void init_attack_deck() {
    for (int i = 0; i < ATTACK_DECK_SIZE; i++) {
        attackPile[i] = (AttackCard) {
            .color = i / 13,
            .value = (i % 13) + 1,
            .baseModifier = 1.0f
        };
    }
}

void draw_phase() {
    int currentPlayer = currentTurn % 2;

    //TODO: draw random card

    CardVariant card = attackPile;

    handCards[currentPlayer][next] = card;
}

bool place_card() {
    return false;
}

void battle_phase() {

}

bool discard_card(int idx) {

    currentTurn++;
    return false;
}

void free_discard_pile() {
    for (int i = 0; i < MAX_CARDS; i++) {
        free(discardPile[i].ptr);
    }
}