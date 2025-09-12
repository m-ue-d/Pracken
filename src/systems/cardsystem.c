#include "cardsystem.h"

int currentTurn = 0;

AttackCard attackPile[ATTACK_DECK_SIZE] = {0};
int attackPileCount = 0;

CardVariant discardPile[MAX_CARDS] = {0};
int discardPileCount = 0;

void init_attack_deck() {
    for (int i = 0; i < ATTACK_DECK_SIZE; i++) {
        attackPile[i] = (AttackCard) {
            .color = i / 13,
            .value = (i % 13) + 1,
            .baseModifier = 1.0f
        };
    }
    attackPileCount = ATTACK_DECK_SIZE;

    shuffle_deck(attackPile, attackPileCount);
}

void shuffle_deck(CardVariant *deck, size_t decksize) {
    for(size_t a = 0; a < decksize - 1; a++) {
        size_t b = a + rand_lim(decksize - a);

        CardVariant temp = deck[a];
        deck[a] = deck[b];  
        deck[b] = temp;
    }
}

void draw_card() {
    int currentPlayer = currentTurn % 2;

    if(attackPileCount == 0) {
        printf("No cards left to draw");
        return;
    }

    AttackCard *card = malloc(sizeof(AttackCard));
    *card = attackPile[attackPileCount - 1];
    attackPileCount--;

    handCards[currentPlayer][handCardsCount[currentPlayer]] = (CardVariant) { 
        .ptr = card, 
        .type = Attack
    };
    handCardsCount[currentPlayer]++;
}

/*
place a card from the hand into slot x/y
*/
bool place_card(int idx, int x, int y) {
    return false;
}

void attack_opponent() {

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