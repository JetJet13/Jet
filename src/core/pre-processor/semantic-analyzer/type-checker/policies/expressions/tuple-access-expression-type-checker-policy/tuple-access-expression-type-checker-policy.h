//
// Created by Johny Georges on 2024-05-29.
//

#ifndef JETLANG_TUPLE_ACCESS_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_TUPLE_ACCESS_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-tuple-access-expression.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace TupleAccessExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTTupleAccessExpressionNode> tupleAccessExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};


#endif //JETLANG_TUPLE_ACCESS_EXPRESSION_TYPE_CHECKER_POLICY_H
