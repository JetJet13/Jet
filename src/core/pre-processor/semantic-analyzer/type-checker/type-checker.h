//
// Created by Johny Georges on 2024-05-20.
//

#ifndef JETLANG_TYPE_CHECKER_H
#define JETLANG_TYPE_CHECKER_H

#include <vector>
#include "../../../ast/ast-nodes/ast-node.h"
#include "../type-signature-lookup-table/type-signature-lookup-table.h"
#include "../ast-traverser/ast-traverser.h"
#include "types/type-checker-result.h"

class TypeChecker {
private:
    ASTTraverser traverser;
public:
    TypeChecker();
    TypeCheckerResult check(ASTNode* rootNode, TypeSignatureLookupTable* scope);

};

#endif //JETLANG_TYPE_CHECKER_H
