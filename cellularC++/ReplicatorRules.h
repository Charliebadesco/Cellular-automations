// ReplicatorRules.h
#ifndef REPLICATOR_RULES_H
#define REPLICATOR_RULES_H

#include "Rule.h"

class ReplicatorRules : public Rule {
public:
    int apply(int currentState, int neighbors) const override {
        // Replicator: The cell replicates itself when it has exactly two neighbors.
        // Otherwise, it behaves like a standard Game of Life cell.
        if (currentState == 1) {
            return (neighbors == 2) ? 1 : 0;
        } else {
            return (neighbors == 2) ? 1 : 0;
        }
    }
};

#endif // REPLICATOR_RULES_H
