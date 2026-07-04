//
// Created by Johny Georges on 2025-06-28.
//

#ifndef JETLANG_INTERFACE_TYPE_CHECKER_POLICY_H
#define JETLANG_INTERFACE_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-type-declaration-nodes/ast-interface-type-declaration-node.h"

namespace InterfaceTypeDeclarationTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTInterfaceTypeDeclarationNode> interfaceTypeDeclarationNode, TypeCheckerResult* typeCheckerResult);
};

#endif //JETLANG_INTERFACE_TYPE_CHECKER_POLICY_H
