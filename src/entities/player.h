#include "../systems/cardsystem.h"

//arrays exist twice (player, opponent); similarly attributes are contained in arrays with the first value being the player and the second being the opponent =)

CardVariant handCardsPlayer[MAX_CARDS];
CardVariant handCardsOpponent[MAX_CARDS];

extern float hp[2];

//TODO: Augmentations