//
// Created by Johny Georges on 2024-06-15.
//

#ifndef JETLANG_LOGICAL_EXPRESSION_IR_STRATEGY_H
#define JETLANG_LOGICAL_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-logical-expression-node.h"
#include "../../../ir-generator.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-logical-expression-node.h"

class LogicalExpressionIRStrategy {
private:
    llvm::Instruction::BinaryOps determineOperatorIR(ASTLogicalOperatorNode* node);
public:
    IRLogicalExpressionNode* generate(ASTLogicalExpressionNode* node, std::unique_ptr<llvm::LLVMContext>*, IRGenerator* irGenerator, IRLookupTable* scope);
};

#endif //JETLANG_LOGICAL_EXPRESSION_IR_STRATEGY_H
