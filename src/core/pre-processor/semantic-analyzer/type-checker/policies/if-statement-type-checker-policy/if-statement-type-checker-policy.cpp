//
// Created by Johny Georges on 2024-05-27.
//

#include "if-statement-type-checker-policy.h"
#include "../../type-checker.h"

namespace IfStatementTypeCheckerPolicy {
    void apply(ASTIfStatementNode* ifStatementNode, TypeCheckerResult* typeCheckerResult) {
        TypeChecker::applyPolicyTo(ifStatementNode->getIfBlock()->getCondition(), typeCheckerResult);
        TypeChecker::applyPolicyTo(ifStatementNode->getIfBlock()->getBlock(), typeCheckerResult);

        for (auto elseIfBlock : *ifStatementNode->getElseIfBlocks()) {
            TypeChecker::applyPolicyTo(elseIfBlock->getCondition(), typeCheckerResult);
            TypeChecker::applyPolicyTo(elseIfBlock->getBlock(), typeCheckerResult);
        }

        if (ifStatementNode->getElseBlock()) {
            TypeChecker::applyPolicyTo(ifStatementNode->getElseBlock().value()->getBlock(), typeCheckerResult);
        }

    }
}