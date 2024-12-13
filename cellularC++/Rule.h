#ifndef RULE_H
#define RULE_H
class Rule {
public:
    virtual int apply(int currentState, int neighbors) const = 0;
    virtual ~Rule() = default;
};


#endif // RULE_H
