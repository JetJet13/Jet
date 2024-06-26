//
// Created by Johny Georges on 2024-06-25.
//

#ifndef JETLANG_VARIABLE_DECLARATION_IR_STRATEGY_H
#define JETLANG_VARIABLE_DECLARATION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../core/ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../../ir-generator.h"
#include "../../ir-lookup-table/ir-lookup-table.h"


class VariableDeclarationIRStrategy {
public:
    llvm::Value* generate(ASTVariableDeclarationNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope);
};

#endif //JETLANG_VARIABLE_DECLARATION_IR_STRATEGY_H
