//
// Created by Johny Georges on 2024-07-15.
//

#ifndef JETLANG_ENUM_DECLARATION_IR_STRATEGY_H
#define JETLANG_ENUM_DECLARATION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../ir-generator.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-enum-declaration-node.h"
#include "../../../../core/ast/ast-nodes/ast-declaration-nodes/ast-enum-declaration-node.h"

class EnumDeclarationIRStrategy {
public:
    IREnumDeclarationNode* generate(ASTEnumDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule);
};

#endif //JETLANG_ENUM_DECLARATION_IR_STRATEGY_H
