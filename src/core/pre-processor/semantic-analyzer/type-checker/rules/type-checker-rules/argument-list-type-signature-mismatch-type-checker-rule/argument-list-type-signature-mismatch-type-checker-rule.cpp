//
// Created by Johny Georges on 2024-05-29.
//

#include "argument-list-type-signature-mismatch-type-checker-rule.h"
#include "../../../../../../../shared/utils/logger/logger.h"

void ArgumentListTypeSignatureMismatchTypeCheckerRule::enforce(std::vector<TypeSignature*>* parameterList, ASTFunctionArgumentListNode* argumentList,  std::string mismatchMessage, TypeCheckerResult* typeCheckerResult) {
    for (int i = 0; i < parameterList->size(); i++) {
        if (!parameterList->at(i)->isEquivalentTo(
                argumentList->getArguments()->at(i)->getArgument()->getTypeSignature())) {
            typeCheckerResult->addError(mismatchMessage);
        }
    }
}

TypeCheckerRuleType ArgumentListTypeSignatureMismatchTypeCheckerRule::getType() {
    return ARGUMENT_LIST_TYPE_SIGNATURE_MISMATCH_TCR;
}

std::string ArgumentListTypeSignatureMismatchTypeCheckerRule::toString() {
    return "ARGUMENT_LIST_TYPE_SIGNATURE_MISMATCH";
}

bool ArgumentListTypeSignatureMismatchTypeCheckerRule::isEqualTo(TypeCheckerRule* other) {
    return this->getType() != other->getType();
}

void ArgumentListTypeSignatureMismatchTypeCheckerRule::print() {
    Logger::log("------", this->toString(), "------");
}