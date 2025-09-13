#include "board.h"


BoardSlot board[2][BOARD_HEIGHT][BOARD_WIDTH] = {0};

void init_board() {
    for (int player = 0; player < 2; player++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            board[player][0][x].type = ATTACK_SLOT;
            board[player][1][x].type = SUPPORT_SLOT;

            board[player][0][x].card = NULL;
            board[player][1][x].card = NULL;
        }
    }
}

bool base_rule_check(BoardSlot *slot, CardVariant *card) {
    switch (card->type) {
        case Attack:
            return slot->type == ATTACK_SLOT;
        case Support:
            return slot->type == SUPPORT_SLOT;
        case Joker:
            return slot->type == FLEX_SLOT || slot->type == SUPPORT_SLOT;
        default:
            return false;
    }
}