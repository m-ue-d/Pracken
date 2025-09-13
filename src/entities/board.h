#ifndef BOARD_H
#define BOARD_H

#include <stddef.h>
#include <stdbool.h>

#include "../components/cards.h"

#define BOARD_WIDTH 4
#define BOARD_HEIGHT 2

typedef enum { ATTACK_SLOT, SUPPORT_SLOT, FLEX_SLOT } SlotType;

typedef struct {
    SlotType type;
    CardVariant *card;
} BoardSlot;

extern BoardSlot board[2][BOARD_HEIGHT][BOARD_WIDTH];

void init_board();

bool base_rule_check(BoardSlot *slot, CardVariant *card);

#endif