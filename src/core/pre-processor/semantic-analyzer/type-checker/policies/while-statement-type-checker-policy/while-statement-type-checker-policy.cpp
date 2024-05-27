//
// Created by Johny Georges on 2024-05-27.
//

#include "while-statement-type-checker-policy.h"
#include "../../type-checker.h"

namespace WhileStatementTypeCheckerPolicy {
    void apply(ASTWhileStatementNode* whileStatementNode, TypeCheckerResult* typeCheckerResult) {
        TypeChecker::applyPolicyTo(whileStatementNode->getCondition(), typeCheckerResult);
        TypeChecker::applyPolicyTo(whileStatementNode->getBlock(), typeCheckerResult);
    }
}