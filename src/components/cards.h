#ifndef CARDS_H
#define CARDS_H

typedef enum {
    SPADE,
    CLUB,
    HEART,
    DIAMOND
} Color;

#define CARDWIDTH = 31
#define CARDHEIGHT = 46

#define ATTACK_DECK_SIZE 52
#define SUPPORT_DECK_SIZE 8
#define MAX_CARDS 128

typedef struct {
    Color color;
    int value;
    float baseModifier;
} AttackCard;

typedef struct {
    char name[128];
    int value;
    float baseModifier;
} JokerCard;

typedef struct {
    char name[128];
    float modifier;
} SupportCard;

typedef enum { Attack, Joker, Support } CardTypeTag;
typedef struct {
    CardTypeTag type;
    void *ptr;
} CardVariant;

#endif