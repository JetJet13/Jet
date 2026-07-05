//
// Created by Johny Georges on 2024-06-17.
//

#ifndef JETLANG_ARRAY_EXPRESSION_IR_STRATEGY_H
#define JETLANG_ARRAY_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-array-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-array-expression-node.h"
#include "../../../../ir-type/ir-array-type.h"

class ArrayExpressionIRStrategy {
private:
    IRInstructionNode* generateArrayAllocation(std::shared_ptr<ASTArrayExpressionNode> node, std::shared_ptr<IRArrayPointerType> irArrayPointerType, std::shared_ptr<IRArrayType> irArrayType, std::shared_ptr<IRType> arrayElementIrType, std::vector<IRInstructionNode*> childAllocations, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation);
    IRInstructionNode* generateArrayPointerAllocation(std::shared_ptr<ASTArrayExpressionNode> node, std::shared_ptr<IRArrayPointerType> irArrayPointerType, std::shared_ptr<IRArrayType> irArrayType, IRInstructionNode* arrayAllocation, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation);
public:
    IRArrayExpressionNode* generate(std::shared_ptr<ASTArrayExpressionNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation);
};

#endif //JETLANG_ARRAY_EXPRESSION_IR_STRATEGY_H
