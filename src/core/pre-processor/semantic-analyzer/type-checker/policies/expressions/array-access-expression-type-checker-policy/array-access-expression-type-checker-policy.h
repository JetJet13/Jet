//
// Created by Johny Georges on 2024-05-28.
//

#ifndef JETLANG_ARRAY_ACCESS_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_ARRAY_ACCESS_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-array-access-expression-node.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace ArrayAccessExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTArrayAccessExpressionNode> arrayAccessExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_ARRAY_ACCESS_EXPRESSION_TYPE_CHECKER_POLICY_H
