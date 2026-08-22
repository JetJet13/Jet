//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_FUNCTION_BLOCK_TYPE_CHECKER_POLICY_H
#define JETLANG_FUNCTION_BLOCK_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-block-node.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace FunctionBlockTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTFunctionBlockNode> functionBlock, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_FUNCTION_BLOCK_TYPE_CHECKER_POLICY_H
