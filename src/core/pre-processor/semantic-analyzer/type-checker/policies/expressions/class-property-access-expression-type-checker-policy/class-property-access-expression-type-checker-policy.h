//
// Created by Johny Georges on 2024-05-29.
//

#ifndef JETLANG_CLASS_PROPERTY_ACCESS_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_CLASS_PROPERTY_ACCESS_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-class-property-access-expression-node.h"

namespace ClassPropertyAccessExpressionTypeCheckerPolicy {
    void apply(ASTClassPropertyAccessExpressionNode* classPropertyAccessExpression, TypeCheckerResult* typeCheckerResult);
};


#endif //JETLANG_CLASS_PROPERTY_ACCESS_EXPRESSION_TYPE_CHECKER_POLICY_H
