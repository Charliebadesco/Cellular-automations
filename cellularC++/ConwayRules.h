#ifndef ConwayRules_H
#define ConwayRules_H

#include "Rule.h"

class ConwayRules : public Rule {
public:
    int apply(int currentState, int neighbors) const override {
        if (currentState== 1) {
            return (neighbors== 2 || neighbors== 3) ? 1 : 0;
        } else {
            return (neighbors== 3) ? 1 : 0;
        }
    }
};

#endif
