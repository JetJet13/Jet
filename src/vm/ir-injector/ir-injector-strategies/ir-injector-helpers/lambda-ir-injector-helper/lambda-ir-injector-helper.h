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
    static void incrementRefCountIfNecessary(llvm::Value* value, IRType* irType, IRBlockNode* irBlock, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule);
    static llvm::Value* injectDetails(IRLambdaExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope);
};

#endif //JETLANG_LAMBDA_IR_INJECTOR_HELPER_H
