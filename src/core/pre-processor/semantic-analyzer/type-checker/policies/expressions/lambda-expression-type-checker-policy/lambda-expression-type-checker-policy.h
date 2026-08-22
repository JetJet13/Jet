//
// Created by Johny Georges on 2024-05-29.
//

#ifndef JETLANG_LAMBDA_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_LAMBDA_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-lambda-expression-node.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-lambda-with-fat-arrow-expression-node.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace LambdaExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTLambdaExpressionNode> lambdaExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
    void apply(std::shared_ptr<ASTLambdaWithFatArrowExpressionNode> lambdaExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_LAMBDA_EXPRESSION_TYPE_CHECKER_POLICY_H
