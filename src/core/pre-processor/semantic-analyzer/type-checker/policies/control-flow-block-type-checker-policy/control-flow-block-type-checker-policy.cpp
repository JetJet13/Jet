//
// Created by Johny Georges on 2024-05-27.
//

#include "control-flow-block-type-checker-policy.h"
#include "../../type-checker.h"

namespace ControlFlowBlockTypeCheckerPolicy {
    void apply(ASTControlFlowBlockNode* controlFlowBlockNode, TypeCheckerResult* typeCheckerResult) {
        for (auto statement : *controlFlowBlockNode->getContents()) {
            TypeChecker::applyPolicyTo(statement, typeCheckerResult);
        }
    }
}