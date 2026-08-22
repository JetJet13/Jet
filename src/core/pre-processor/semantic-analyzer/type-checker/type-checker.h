//
// Created by Johny Georges on 2024-05-21.
//

#ifndef JETLANG_TYPE_CHECKER_H
#define JETLANG_TYPE_CHECKER_H

#include "../../../ast/ast-nodes/ast-node.h"
#include "types/type-checker-result/type-checker-result.h"
#include "../type-signature-lookup-table/type-signature-lookup-table.h"


namespace TypeChecker {
    void applyPolicyTo(std::shared_ptr<ASTNode> node, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_TYPE_CHECKER_H
