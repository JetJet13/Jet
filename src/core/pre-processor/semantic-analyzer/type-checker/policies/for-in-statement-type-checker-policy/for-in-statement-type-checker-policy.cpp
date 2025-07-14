//
// Created by Johny Georges on 2024-05-27.
//

#include "for-in-statement-type-checker-policy.h"
#include "../../type-checker.h"
#include "../../rules/type-checker-rule-provider.h"
#include "../../types/type-checker-error-message-table.h"

namespace ForInStatementTypeCheckerPolicy {
    void apply(ASTForInStatementNode* forStatementNode, TypeCheckerResult* typeCheckerResult) {
        TypeChecker::applyPolicyTo(forStatementNode->getBlock(), typeCheckerResult);
        auto notIterableMessage = TypeCheckerErrorMessageTable::ForInStatementSourceNotIterable(forStatementNode->getSource());
        TypeCheckerRuleProvider::getIterableTypeSignatureTypeCheckerRule()
        ->enforce(
            forStatementNode->getSource()->getTypeSignature(),
            notIterableMessage,
            typeCheckerResult
        );

    }
}