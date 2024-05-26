//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_TYPE_CHECKER_RULE_H
#define JETLANG_TYPE_CHECKER_RULE_H

#include <string>
#include "../types/type-checker-rule-type.h"

class TypeCheckerRule {
public:
    bool hasType(TypeCheckerRuleType type);
    virtual TypeCheckerRuleType getType() = 0;
    virtual std::string toString() = 0;
    virtual bool isEqualTo(TypeCheckerRule* other) = 0;
    virtual void print() = 0;
};

#endif //JETLANG_TYPE_CHECKER_RULE_H
