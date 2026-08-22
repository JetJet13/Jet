//
// Created by Johny Georges on 2024-05-27.
//

#ifndef JETLANG_FUNCTION_RETURN_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_FUNCTION_RETURN_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-function-return-expression-node.h"
#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace FunctionReturnExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTFunctionReturnExpressionNode> functionReturnExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_FUNCTION_RETURN_EXPRESSION_TYPE_CHECKER_POLICY_H
