//
// Created by Johny Georges on 2024-05-27.
//

#include "try-statement-type-checker-policy.h"
#include "../../type-checker.h"

namespace TryStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTTryStatementNode> tryStatementNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        TypeChecker::applyPolicyTo(tryStatementNode->getTryBlock()->getBlock(), typeCheckerResult, fileScope);
        TypeChecker::applyPolicyTo(tryStatementNode->getCatchBlock()->getBlock(), typeCheckerResult, fileScope);

        if (tryStatementNode->getFinallyBlock()) {
            TypeChecker::applyPolicyTo(tryStatementNode->getFinallyBlock().value()->getBlock(), typeCheckerResult, fileScope);
        }
    }
}