//
// Created by Johny Georges on 2024-11-09.
//

#ifndef JETLANG_FUNCTION_INVOCATION_IR_INJECTOR_HELPER_H
#define JETLANG_FUNCTION_INVOCATION_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../../ir-nodes/ir-instruction-node.h"
#include "../../../ir-injector.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-function-invocation-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-method-invocation-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-array-prototype-invocation-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-tuple-access-invocation-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-object-access-invocation-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-shared-ptr-prototype-invocation-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-array-access-invocation-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-class-static-method-invocation-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-string-prototype-invocation-expression-node.h"

class FunctionInvocationIRInjectorHelper {
public:
    static llvm::Value* inject(std::shared_ptr<IRFunctionInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation);
    static llvm::Value* inject(std::shared_ptr<IRClassMethodInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation);
    static llvm::Value* inject(std::shared_ptr<IRArrayPrototypeInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation);
    static llvm::Value* inject(std::shared_ptr<IRStringPrototypeInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation);
    static llvm::Value* inject(std::shared_ptr<IRSharedPtrPrototypeInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation);
    static llvm::Value* inject(std::shared_ptr<IRTupleAccessInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation);
    static llvm::Value* inject(std::shared_ptr<IRObjectAccessInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation);
    static llvm::Value* inject(std::shared_ptr<IRArrayAccessInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation);
    static llvm::Value* inject(std::shared_ptr<IRClassStaticMethodInvocationExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope, std::shared_ptr<IROperation> irOperation);
};

#endif //JETLANG_FUNCTION_INVOCATION_IR_INJECTOR_HELPER_H
