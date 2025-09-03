#include "../components/cards.h"

//TODO: This isn't really an entity. FIXME!

extern SupportCard supportPile[2][SUPPORT_DECK_SIZE];
extern int supportPileCount[2];

extern CardVariant handCards[2][MAX_CARDS];
extern int handCardsCount[2];

extern CardVariant openAttackCards[2][4];  //may include Joker/Support, depending on the augmentations
extern int openAttackCardsCount[2];

extern CardVariant openSupportCards[2][4]; //includes Joker
extern int openSupportCardsCount[2];

extern float hp[2];

void init_support_deck(int augmentation_id);

//TODO: Implement Augmentations