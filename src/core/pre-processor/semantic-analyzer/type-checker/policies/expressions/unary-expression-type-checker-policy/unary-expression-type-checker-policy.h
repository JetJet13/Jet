//
// Created by Johny Georges on 2024-05-29.
//

#ifndef JETLANG_UNARY_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_UNARY_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-unary-expression-node.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace UnaryExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTUnaryExpressionNode> unaryExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_UNARY_EXPRESSION_TYPE_CHECKER_POLICY_H