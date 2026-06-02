//
// Created by Johny Georges on 2026-06-01.
//

#include "lambda-class-static-method-invocation-expression-injector-strategy.h"

llvm::Value* LambdaIRClassStaticMethodInvocationExpressionInjectorStrategy::inject(IRClassStaticMethodInvocationExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto numArgs = irExpression->getIRArguments()->size();
    for (unsigned long i = 0; i < numArgs; ++i) {
        auto argument = irExpression->getIRArguments()->at(i);
        auto argumentValue = irInjector->inject(irBlock, argument->getArgument(), argument->getOperation(), irModule, scope);
        irExpression->getValue()->setArgOperand(i, argumentValue);
    }

    return irBlock->getBuilder()->get()->Insert(irExpression->getValue());
}