//
// Created by Johny Georges on 2024-05-27.
//

#include "for-statement-type-checker-policy.h"
#include "../../type-checker.h"
#include "../../rules/type-checker-rule-provider.h"
#include "../../types/type-checker-error-message-table.h"

namespace ForStatementTypeCheckerPolicy {
    void apply(ASTForStatementNode* forStatementNode, TypeCheckerResult* typeCheckerResult) {
        TypeChecker::applyPolicyTo(forStatementNode->getBlock(), typeCheckerResult);

        TypeCheckerRuleProvider::getIterableTypeSignatureTypeCheckerRule()
        ->enforce(
            forStatementNode->getSource()->getTypeSignature(),
            TypeCheckerErrorMessageTable::ForStatementSourceNotIterable,
            typeCheckerResult
        );

    }
}