//
// Created by Johny Georges on 2024-05-29.
//

#ifndef JETLANG_STRUCT_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_STRUCT_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-struct-expression-node.h"

namespace StructExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTStructExpressionNode> structExpression, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_STRUCT_EXPRESSION_TYPE_CHECKER_POLICY_H
