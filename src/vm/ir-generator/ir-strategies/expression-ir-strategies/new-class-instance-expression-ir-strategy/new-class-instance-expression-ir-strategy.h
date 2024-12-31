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
public:
    IRNewClassInstanceExpressionNode* generate(ASTNewClassInstanceExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IROperationType irOperationType);
};


#endif //JETLANG_NEW_CLASS_INSTANCE_EXPRESSION_IR_STRATEGY_H
