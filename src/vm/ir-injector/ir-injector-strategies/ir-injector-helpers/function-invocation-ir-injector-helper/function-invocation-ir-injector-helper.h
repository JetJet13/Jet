//
// Created by Johny Georges on 2024-11-09.
//

#ifndef JETLANG_FUNCTION_INVOCATION_IR_INJECTOR_HELPER_H
#define JETLANG_FUNCTION_INVOCATION_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../../ir-nodes/ir-load-instruction-node.h"
#include "../../../../ir-nodes/ir-instruction-node.h"
#include "../../../ir-injector.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-function-invocation-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-method-invocation-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-function-parameter-invocation-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-array-prototype-invocation-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-tuple-access-invocation-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-object-access-invocation-expression-node.h"

class FunctionInvocationIRInjectorHelper {
public:
    static llvm::Value* inject(IRFunctionInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope);
    static llvm::Value* inject(IRClassMethodInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope);
    static llvm::Value* inject(IRFunctionParameterInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope);
    static llvm::Value* inject(IRArrayPrototypeInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope, IROperation* irOperation);
    static llvm::Value* inject(IRTupleAccessInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope);
    static llvm::Value* inject(IRObjectAccessInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IRModuleNode *irModule, IRLookupTable* scope);
};

#endif //JETLANG_FUNCTION_INVOCATION_IR_INJECTOR_HELPER_H
