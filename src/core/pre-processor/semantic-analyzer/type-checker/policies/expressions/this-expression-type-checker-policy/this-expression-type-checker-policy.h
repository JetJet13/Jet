//
// Created by Johny Georges on 2024-05-29.
//

#ifndef JETLANG_THIS_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_THIS_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-this-expression-node.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace ThisExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTThisExpressionNode> thisExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_THIS_EXPRESSION_TYPE_CHECKER_POLICY_H
