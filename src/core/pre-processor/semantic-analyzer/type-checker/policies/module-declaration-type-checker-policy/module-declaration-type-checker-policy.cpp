//
// Created by Johny Georges on 2024-10-29.
//

#include "module-declaration-type-checker-policy.h"

namespace ModuleDeclarationTypeCheckerPolicy {
    void apply(ASTModuleDeclarationNode* moduleDeclarationNode, TypeCheckerResult* typeCheckerResult) {
        // nothing to type check for a module since it's just a collection of type-checked type-signatures
    }
}