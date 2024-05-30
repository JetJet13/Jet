//
// Created by Johny Georges on 2024-05-28.
//

#include "unique-scoped-names-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void UniqueScopedNamesTypeCheckerRule::enforce(std::vector<ASTIdentifierNode*>* names, std::string nonUniqueMessage, TypeCheckerResult* typeCheckerResult) {
    auto sameNames = std::vector<ASTIdentifierNode*>();
    for (int i = 0; i < names->size(); ++i) {
        for (int j = i + 1; j < names->size(); ++j) {
            auto name = names->at(i);
            auto otherName = names->at(j);
            if (name == otherName) {
                sameNames.push_back(name);
            }
        }
    }

    if (!sameNames.empty()) {
        typeCheckerResult->addError(nonUniqueMessage);
    }

}

TypeCheckerRuleType UniqueScopedNamesTypeCheckerRule::getType() {
    return UNIQUE_SCOPED_NAMES_TCR;
}

std::string UniqueScopedNamesTypeCheckerRule::toString() {
    return "UNIQUE_SCOPED_NAMES";
}

bool UniqueScopedNamesTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void UniqueScopedNamesTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}