//
// Created by Johny Georges on 2024-11-09.
//

#ifndef JETLANG_FUNCTION_INVOCATION_IR_INJECTOR_HELPER_H
#define JETLANG_FUNCTION_INVOCATION_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../../ir-nodes/ir-load-instruction-node.h"
#include "../../../../ir-nodes/ir-instruction-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-object-access-expression-node.h"
#include "../../../ir-injector-map.h"

class FunctionInvocationIRInjectorHelper {
public:
    static llvm::Value* inject(IRFunctionInvocationExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode *irModule, IRLookupTable* scope);
    static llvm::Value* inject(IRClassMethodInvocationExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode *irModule, IRLookupTable* scope);
    static llvm::Value* inject(IRFunctionParameterInvocationExpressionNode* irExpression, std::unique_ptr<llvm::IRBuilder<>>*  builder, IRInjectorMap* irInjectorMap, IRModuleNode *irModule, IRLookupTable* scope);
};

#endif //JETLANG_FUNCTION_INVOCATION_IR_INJECTOR_HELPER_H
