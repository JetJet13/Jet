//
// Created by Johny Georges on 2025-10-25.
//

#ifndef JETLANG_ARGUMENT_LIST_TYPE_CHECKER_POLICY_H
#define JETLANG_ARGUMENT_LIST_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-argument-list-node.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace ArgumentListTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTFunctionArgumentListNode> functionArgumentList, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_ARGUMENT_LIST_TYPE_CHECKER_POLICY_H
