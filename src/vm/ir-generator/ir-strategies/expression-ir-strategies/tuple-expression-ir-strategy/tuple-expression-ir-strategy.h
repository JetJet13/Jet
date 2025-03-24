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
    IRInstructionNode* generateTupleAllocation(ASTTupleExpressionNode* node, IRStructType* irType, IRGenerator* irGenerator, IRContext* irContext, IROperationType irOperationType);
public:
    IRTupleExpressionNode* generate(ASTTupleExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType);
};

#endif //JETLANG_TUPLE_EXPRESSION_IR_STRATEGY_H
