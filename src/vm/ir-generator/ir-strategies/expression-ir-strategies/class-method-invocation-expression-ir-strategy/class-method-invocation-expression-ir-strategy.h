//
// Created by Johny Georges on 2024-12-27.
//

#ifndef JETLANG_CLASS_METHOD_INVOCATION_EXPRESSION_IR_STRATEGY_H
#define JETLANG_CLASS_METHOD_INVOCATION_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-method-invocation-expression-node.h"

class ClassMethodInvocationExpressionIRStrategy {
public:
    IRClassMethodInvocationExpressionNode* generate(ASTClassMethodInvocationExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope, IRModuleNode* irModule, IROperationType irOperationType);
};


#endif //JETLANG_CLASS_METHOD_INVOCATION_EXPRESSION_IR_STRATEGY_H
