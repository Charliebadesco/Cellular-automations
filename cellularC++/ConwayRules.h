// ConwayRules.h
#ifndef CONWAY_RULES_H
#define CONWAY_RULES_H

#include "Rule.h"

class ConwayRules : public Rule {
public:
    int apply(int currentState, int neighbors) const override {
        // Conway's Game of Life: Any live cell with fewer than two live neighbors dies (underpopulation).
        // Any live cell with two or three live neighbors lives on to the next generation (survival).
        // Any live cell with more than three live neighbors dies (overpopulation).
        // Any dead cell with exactly three live neighbors becomes a live cell (reproduction).
        
        if (currentState == 1) {
            return (neighbors == 2 || neighbors == 3) ? 1 : 0;
        } else {
            return (neighbors == 3) ? 1 : 0;
        }
    }
};

#endif // CONWAY_RULES_H
