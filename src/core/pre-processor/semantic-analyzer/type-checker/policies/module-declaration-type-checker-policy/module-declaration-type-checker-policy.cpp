//
// Created by Johny Georges on 2024-10-29.
//

#include "module-declaration-type-checker-policy.h"

namespace ModuleDeclarationTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTModuleDeclarationNode> moduleDeclarationNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope) {
        // nothing to type check for a module since it's just a collection of type-checked type-signatures
    }
}