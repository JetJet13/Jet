//
// Created by Johny Georges on 2024-05-25.
//

#ifndef JETLANG_PARAMETER_TYPE_CHECKER_POLICY_H
#define JETLANG_PARAMETER_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-parameter-node.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace ParameterTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTFunctionParameterNode> functionParameter, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_PARAMETER_TYPE_CHECKER_POLICY_H
