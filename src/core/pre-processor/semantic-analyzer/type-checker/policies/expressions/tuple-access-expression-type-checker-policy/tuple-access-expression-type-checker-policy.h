//
// Created by Johny Georges on 2024-05-29.
//

#ifndef JETLANG_TUPLE_ACCESS_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_TUPLE_ACCESS_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-tuple-access-expression.h"

namespace TupleAccessExpressionTypeCheckerPolicy {
    void apply(ASTTupleAccessExpressionNode* tupleAccessExpression, TypeCheckerResult* typeCheckerResult);
};


#endif //JETLANG_TUPLE_ACCESS_EXPRESSION_TYPE_CHECKER_POLICY_H
