//
// Created by Johny Georges on 2024-05-27.
//

#include "if-statement-type-checker-policy.h"
#include "../../type-checker.h"

namespace IfStatementTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTIfStatementNode> ifStatementNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        TypeChecker::applyPolicyTo(ifStatementNode->getIfBlock()->getCondition(), typeCheckerResult, fileScope);
        TypeChecker::applyPolicyTo(ifStatementNode->getIfBlock()->getBlock(), typeCheckerResult, fileScope);

        for (auto elseIfBlock : *ifStatementNode->getElseIfBlocks()) {
            TypeChecker::applyPolicyTo(elseIfBlock->getCondition(), typeCheckerResult, fileScope);
            TypeChecker::applyPolicyTo(elseIfBlock->getBlock(), typeCheckerResult, fileScope);
        }

        if (ifStatementNode->getElseBlock()) {
            TypeChecker::applyPolicyTo(ifStatementNode->getElseBlock().value()->getBlock(), typeCheckerResult, fileScope);
        }

    }
}