#include "cardsystem.h"

int currentTurn = 0;

AttackCard attackPile[ATTACK_DECK_SIZE] = {0};
int attackPileCount = 0;

CardVariant discardPile[MAX_CARDS] = {0};
int discardPileCount = 0;

void init_decks() {
    for (int i = 0; i < ATTACK_DECK_SIZE; i++) {
        attackPile[i] = (AttackCard) {
            .color = i / 13,
            .value = (i % 13) + 1,
            .baseModifier = 1.0f
        };
    }
    attackPileCount = ATTACK_DECK_SIZE;
    shuffle_deck(attackPile, attackPileCount, sizeof(AttackCard));

    for (int i = 0; i < sizeof(hp) / sizeof(hp[0]); i++){
        if(!augmentations[i]) continue;
        shuffle_deck(augmentations[i]->supportPile, augmentations[i]->supportPileCount, sizeof(SupportCard));
    }
}

void shuffle_deck(void *deck, size_t decksize, size_t elementSize) {
    if (deck == NULL || decksize <= 1) return;

    char *arr = deck;
    char *temp = malloc(elementSize);
    if (!temp) return;

    for (size_t i = decksize - 1; i > 0; i--) {
        size_t j = rand_lim(i + 1);

        memcpy(temp, arr + i * elementSize, elementSize);
        memcpy(arr + i * elementSize, arr + j * elementSize, elementSize);
        memcpy(arr + j * elementSize, temp, elementSize);
    }

    free(temp);
}

/*
shifts cards left to remove the card at idx
*/
void remove_from_hand(int player, int idx) {
    for (int i = idx; i < handCardsCount[player] - 1; i++) {
        handCards[player][i] = handCards[player][i + 1];
    }
    handCardsCount[player]--;
}

/*
Draws a card from the selected pile
*/
void draw_card() {
    int currentPlayer = currentTurn % 2;

    if(attackPileCount == 0) {
        printf("No cards left to draw");
        return;
    }

    AttackCard *card = malloc(sizeof(AttackCard));
    *card = attackPile[--attackPileCount];

    handCards[currentPlayer][handCardsCount[currentPlayer]++] = (CardVariant) { 
        .ptr = card, 
        .type = Attack
    };
}

/*
place a card from the hand into slot x/y
*/
bool place_card(int idx, int x, int y) {
    int currentPlayer = currentTurn % 2;
    CardVariant *card = &handCards[currentPlayer][idx];
    BoardSlot *slot = &board[currentPlayer][y][x];

    Augmentation *aug = augmentations[currentPlayer];

    for (int i = 0; i < aug->placementModifierCount; i++) {
        if(!aug->placementModifiers[i](currentPlayer, x, y, card, slot)) return false;
    }
    
    if (!base_rule_check(slot, card)) return false; //FIXME: Flawed if used here =)

    slot->card = card;
    remove_from_hand(currentPlayer, idx);
    return true;
}

void attack_opponent() {
    int currentPlayer = currentTurn % 2;
    //TODO: Implement
}

/*
discard the hand card at idx
*/
bool discard_card(int idx) {
    int currentPlayer = currentTurn % 2;
    CardVariant *card = &handCards[currentPlayer][idx];

    Augmentation *aug = augmentations[currentPlayer];

    for (int i = 0; i < aug->discardModifierCount; i++) {
        aug->discardModifiers[i](currentPlayer, card);  //TODO: Think of a way to interpret the true/false output!
    }

    discardPile[discardPileCount++] = *card;

    remove_from_hand(currentPlayer, idx);
    currentTurn++;
    return true;
}