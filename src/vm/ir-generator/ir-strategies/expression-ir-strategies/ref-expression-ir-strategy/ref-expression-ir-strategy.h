//
// Created by Johny Georges on 2025-02-10.
//

#ifndef JETLANG_REF_EXPRESSION_IR_STRATEGY_H
#define JETLANG_REF_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-ref-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-ref-expression-node.h"

class RefExpressionIRStrategy {
private:
    std::shared_ptr<IRInstructionNode> generateAllocation(std::shared_ptr<ASTRefExpressionNode> node, std::shared_ptr<IRRefType> irType, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation);
public:
    std::shared_ptr<IRRefExpressionNode> generate(std::shared_ptr<ASTRefExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext, IROperation* irOperation);
};


#endif //JETLANG_REF_EXPRESSION_IR_STRATEGY_H
