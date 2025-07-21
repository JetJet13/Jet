//
// Created by Johny Georges on 2025-07-21.
//

#include "print-statement-type-checker-policy.h"
#include "../../types/type-checker-error-message-table.h"

namespace PrintStatementTypeCheckerPolicy {
    void apply(ASTPrintStatementNode* printStatementNode, TypeCheckerResult* typeCheckerResult) {
        for (auto argument : *printStatementNode->getArguments()->getArguments()) {
            if (!argument->getArgument()->getTypeSignature()->getTargetTypeSignature()->isLiteral()) {
                typeCheckerResult->addError(TypeCheckerErrorMessageTable::PrintStatementArgumentNotLiteral(argument)());
            }
        }
    }
}