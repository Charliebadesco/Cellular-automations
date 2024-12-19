// HighLifeRules.h
#ifndef HIGH_LIFE_RULES_H
#define HIGH_LIFE_RULES_H

#include "Rule.h"

class HighLifeRules : public Rule {
public:
    int apply(int currentState, int neighbors) const override {
        
        if (currentState == 1) {
            return (neighbors == 2 || neighbors == 3) ? 1 : 0;
        } else {
            return (neighbors == 3 || neighbors == 6) ? 1 : 0;
        }
    }
};

#endif // HIGH_LIFE_RULES_H
