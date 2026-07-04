//
// Created by Johny Georges on 2024-05-27.
//

#include "try-statement-type-checker-policy.h"
#include "../../type-checker.h"

namespace TryStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTTryStatementNode> tryStatementNode, TypeCheckerResult* typeCheckerResult) {
        TypeChecker::applyPolicyTo(tryStatementNode->getTryBlock()->getBlock(), typeCheckerResult);
        TypeChecker::applyPolicyTo(tryStatementNode->getCatchBlock()->getBlock(), typeCheckerResult);

        if (tryStatementNode->getFinallyBlock()) {
            TypeChecker::applyPolicyTo(tryStatementNode->getFinallyBlock().value()->getBlock(), typeCheckerResult);
        }
    }
}