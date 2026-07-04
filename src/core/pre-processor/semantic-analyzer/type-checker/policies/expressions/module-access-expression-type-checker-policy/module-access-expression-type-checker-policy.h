//
// Created by Johny Georges on 2026-03-27.
//

#ifndef JETLANG_MODULE_ACCESS_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_MODULE_ACCESS_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-module-access-expression-node.h"

namespace ModuleAccessExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTModuleAccessExpressionNode> moduleAccessExpression, TypeCheckerResult* typeCheckerResult);
}

#endif //JETLANG_MODULE_ACCESS_EXPRESSION_TYPE_CHECKER_POLICY_H
