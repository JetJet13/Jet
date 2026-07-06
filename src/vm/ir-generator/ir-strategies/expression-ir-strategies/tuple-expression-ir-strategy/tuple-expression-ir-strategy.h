//
// Created by Johny Georges on 2024-06-25.
//

#ifndef JETLANG_TUPLE_EXPRESSION_IR_STRATEGY_H
#define JETLANG_TUPLE_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../../core/ast/ast-nodes/ast-expression-nodes/ast-tuple-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-tuple-expression-node.h"

class TupleExpressionIRStrategy {
private:
    std::shared_ptr<IRInstructionNode> generateTupleAllocation(std::shared_ptr<IRStructType> irType, IRGenerator* irGenerator, IRContext* irContext);
    std::shared_ptr<IRInstructionNode> generateTuplePointerAllocation(std::shared_ptr<ASTTupleExpressionNode> node, std::shared_ptr<IRStructRefType> irType, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation);
public:
    std::shared_ptr<IRTupleExpressionNode> generate(std::shared_ptr<ASTTupleExpressionNode> node, IRGenerator* irGenerator, std::shared_ptr<IRLookupTable> scope, IRContext* irContext, IROperation* irOperation);
};

#endif //JETLANG_TUPLE_EXPRESSION_IR_STRATEGY_H
