// MazeGenerationRules.h
#ifndef MAZERULES_H
#define MAZERULES_H

#include "Rule.h"

class MazeRules : public Rule {
public:
    int apply(int currentState, int neighbors) const override {
        if (currentState == 1) {
            return (neighbors == 3) ? 1 : 0; 
        } else {
            return (neighbors == 2) ? 1 : 0; 
        }
    }
};

#endif 
