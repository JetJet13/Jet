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
    IRInstructionNode* generateClassInstanceAllocation(std::shared_ptr<IRNewClassInstanceType> irNewClassInstanceType, IRGenerator* irGenerator, IRContext* irContext);
    IRInstructionNode* generateClassInstancePointerAllocation(std::shared_ptr<ASTNewClassInstanceExpressionNode> node, std::shared_ptr<IRNewClassInstanceType> irClassInstanceType, IRGenerator* irGenerator, IRContext* irContext, IROperation* irOperation);
public:
    IRNewClassInstanceExpressionNode* generate(std::shared_ptr<ASTNewClassInstanceExpressionNode> node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation);
};


#endif //JETLANG_NEW_CLASS_INSTANCE_EXPRESSION_IR_STRATEGY_H
