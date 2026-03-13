//
// Created by Johny Georges on 2024-11-08.
//

#ifndef JETLANG_FUNCTION_INVOCATION_EXPRESSION_IR_STRATEGY_H
#define JETLANG_FUNCTION_INVOCATION_EXPRESSION_IR_STRATEGY_H

#include <llvm/IR/Value.h>
#include "../../../ir-generator.h"
#include "../../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-function-invocation-expression-node.h"

class FunctionInvocationExpressionIRStrategy {
private:
    std::vector<llvm::Value*> prepArgumentList(ASTFunctionInvocationExpressionNode* node, std::vector<IRFunctionArgumentNode*>* irArguments, IRInvocableType* irInvocableType, IRGenerator* irGenerator, IRContext* irContext);
    std::vector<llvm::Value*> prepArgumentList(ASTFunctionInvocationExpressionNode* node, std::vector<IRFunctionArgumentNode*>* irArguments, IRFunctionType* irFunctionType, IRGenerator* irGenerator, IRContext* irContext);
public:
    IRExpressionNode* generate(ASTFunctionInvocationExpressionNode* node, IRGenerator* irGenerator, IRLookupTable* scope, IRContext* irContext, IROperation* irOperation);
};

#endif //JETLANG_FUNCTION_INVOCATION_EXPRESSION_IR_STRATEGY_H
