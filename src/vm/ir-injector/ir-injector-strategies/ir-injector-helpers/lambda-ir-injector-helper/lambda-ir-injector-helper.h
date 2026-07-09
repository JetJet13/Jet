//
// Created by Johny Georges on 2026-06-01.
//

#ifndef JETLANG_LAMBDA_IR_INJECTOR_HELPER_H
#define JETLANG_LAMBDA_IR_INJECTOR_HELPER_H

#include <llvm/IR/IRBuilder.h>
#include "../../../ir-injector.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-module-access-expression-node.h"
#include "../../../../ir-nodes/ir-expression-nodes/ir-lambda-expression-nodes/ir-lambda-expression-node.h"

class LambdaIRInjectorHelper {
public:
    static void incrementRefCountForInvocationExpression(llvm::Value* value, std::shared_ptr<IRType> irType, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule);
    static llvm::Value* injectDetails(std::shared_ptr<IRLambdaExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_LAMBDA_IR_INJECTOR_HELPER_H
