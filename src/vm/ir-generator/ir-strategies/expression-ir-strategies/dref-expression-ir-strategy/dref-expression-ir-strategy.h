//
// Created by Johny Georges on 2025-02-10.
//

#ifndef JETLANG_DREF_EXPRESSION_IR_STRATEGY_H
#define JETLANG_DREF_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-dref-expression-node.h"

class DrefExpressionIRStrategy {
private:
    std::shared_ptr<IRInstructionNode> generateAllocation(std::shared_ptr<ASTDrefExpressionNode> node, std::shared_ptr<IRType> irType, IRGenerator* irGenerator, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation);
public:
    std::shared_ptr<IRExpressionNode> generate(std::shared_ptr<ASTDrefExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IRContext> irContext, std::shared_ptr<IROperation> irOperation);
};

#endif //JETLANG_DREF_EXPRESSION_IR_STRATEGY_H
