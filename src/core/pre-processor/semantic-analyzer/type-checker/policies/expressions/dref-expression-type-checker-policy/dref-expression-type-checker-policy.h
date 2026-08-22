//
// Created by Johny Georges on 2025-02-01.
//

#ifndef JETLANG_DREF_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_DREF_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-dref-expression-node.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace DrefExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTDrefExpressionNode> drefExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_DREF_EXPRESSION_TYPE_CHECKER_POLICY_H
