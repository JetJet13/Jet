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
    IRInstructionNode* generateTupleAllocation(IRStructType* irType, IRGenerator* irGenerator, IRContext* irContext);
    IRInstructionNode* generateTuplePointerAllocation(std::shared_ptr<ASTTupleExpressionNode> node, IRStructRefType* irType, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation);
public:
    IRTupleExpressionNode* generate(std::shared_ptr<ASTTupleExpressionNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation);
};

#endif //JETLANG_TUPLE_EXPRESSION_IR_STRATEGY_H
