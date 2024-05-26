//
// Created by Johny Georges on 2024-05-25.
//

#include "function-block-type-checker-policy.h"
#include "../../type-checker.h"

namespace FunctionBlockTypeCheckerPolicy {
    void apply(ASTFunctionBlockNode* functionBlockNode, TypeCheckerResult* typeCheckerResult) {
        for (auto statement : *functionBlockNode->getContents()) {
            TypeChecker::applyPolicyTo(statement, typeCheckerResult);
        }
    }

}