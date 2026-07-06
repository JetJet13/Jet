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
    std::shared_ptr<IRInstructionNode> generateVariableAllocation(std::shared_ptr<ASTVariableDeclarationNode> node, IRGenerator* irGenerator, std::shared_ptr<IRType> irType, IRContext* irContext);
public:
    std::shared_ptr<IRVariableDeclarationNode> generate(std::shared_ptr<ASTVariableDeclarationNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext);
};

#endif //JETLANG_VARIABLE_DECLARATION_IR_STRATEGY_H
