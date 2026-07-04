//
// Created by Johny Georges on 2024-06-25.
//

#ifndef JETLANG_VARIABLE_DECLARATION_IR_STRATEGY_H
#define JETLANG_VARIABLE_DECLARATION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../core/ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../../ir-generator.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-variable-declaration-node.h"

class VariableDeclarationIRStrategy {
private:
    IROperation* determineOperationType(std::shared_ptr<ASTVariableDeclarationNode> node);
    IRInstructionNode* generateVariableAllocation(std::shared_ptr<ASTVariableDeclarationNode> node, IRGenerator* irGenerator, IRType* irType, IRContext* irContext);
public:
    IRVariableDeclarationNode* generate(std::shared_ptr<ASTVariableDeclarationNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_VARIABLE_DECLARATION_IR_STRATEGY_H
