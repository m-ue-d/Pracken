typedef enum {
    SPADE,
    CLUB,
    HEART,
    DIAMOND
} Color;

#define CARDWIDTH = 31
#define CARDHEIGHT = 46

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