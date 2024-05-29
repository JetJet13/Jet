//
// Created by Johny Georges on 2024-05-28.
//

#ifndef JETLANG_BINARY_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_BINARY_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-binary-expression-node.h"

namespace BinaryExpressionTypeCheckerPolicy {
    void apply(ASTBinaryExpressionNode* binaryExpression, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_BINARY_EXPRESSION_TYPE_CHECKER_POLICY_H
