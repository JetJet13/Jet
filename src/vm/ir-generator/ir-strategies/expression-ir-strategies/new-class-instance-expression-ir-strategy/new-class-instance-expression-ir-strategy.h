//
// Created by Johny Georges on 2024-12-30.
//

#ifndef JETLANG_NEW_CLASS_INSTANCE_EXPRESSION_IR_STRATEGY_H
#define JETLANG_NEW_CLASS_INSTANCE_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-new-class-instance-expression-node.h"

class NewClassInstanceExpressionIRStrategy {
private:
    IRInstructionNode* generateClassInstanceAllocation(ASTNewClassInstanceExpressionNode* node, IRClassType* irClassType, IRGenerator* irGenerator, IRContext* irContext, IROperationType irOperationType);
public:
    IRNewClassInstanceExpressionNode* generate(ASTNewClassInstanceExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperationType irOperationType);
};


#endif //JETLANG_NEW_CLASS_INSTANCE_EXPRESSION_IR_STRATEGY_H
