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
    llvm::Instruction::BinaryOps determineOperatorIR(std::shared_ptr<ASTLogicalOperatorNode> node);
public:
    std::shared_ptr<IRLogicalExpressionNode> generate(std::shared_ptr<ASTLogicalExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation);
};

#endif //JETLANG_LOGICAL_EXPRESSION_IR_STRATEGY_H
