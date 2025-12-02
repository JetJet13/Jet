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
    IROperation* determineOperationType(ASTVariableDeclarationNode* node);
    IRInstructionNode* generateVariableAllocation(ASTVariableDeclarationNode* node, IRGenerator* irGenerator, IRType* irType, IRExpressionNode* irExpression, IRContext* irContext);
    IRInstructionNode* generateVariableCaptureCounter(ASTVariableDeclarationNode* node, IRGenerator* irGenerator, IRContext* irContext);
public:
    IRVariableDeclarationNode* generate(ASTVariableDeclarationNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext);
};

#endif //JETLANG_VARIABLE_DECLARATION_IR_STRATEGY_H
