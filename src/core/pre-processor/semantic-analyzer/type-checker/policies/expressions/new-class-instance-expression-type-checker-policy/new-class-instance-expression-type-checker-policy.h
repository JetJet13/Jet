//
// Created by Johny Georges on 2024-05-29.
//

#ifndef JETLANG_NEW_CLASS_INSTANCE_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_NEW_CLASS_INSTANCE_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-logical-expression-node.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-new-class-instance-expression.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace NewClassInstanceExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTNewClassInstanceExpressionNode> newClassInstanceExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_NEW_CLASS_INSTANCE_EXPRESSION_TYPE_CHECKER_POLICY_H
