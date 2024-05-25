//
// Created by Johny Georges on 2024-05-25.
//

#include "type-checker-rule.h"


bool TypeCheckerRule::hasType(TypeCheckerRuleType type) {
    return this->getType() == type;
}