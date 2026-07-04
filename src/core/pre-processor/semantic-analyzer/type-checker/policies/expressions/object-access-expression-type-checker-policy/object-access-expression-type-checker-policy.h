//
// Created by Johny Georges on 2024-05-29.
//

#ifndef JETLANG_OBJECT_ACCESS_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_OBJECT_ACCESS_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-object-access-expression-node.h"

namespace ObjectAccessExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTObjectAccessExpressionNode> objectAccessExpression, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_OBJECT_ACCESS_EXPRESSION_TYPE_CHECKER_POLICY_H
