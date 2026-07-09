//
// Created by Johny Georges on 2026-06-01.
//

#include "lambda-ir-identifier-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* LambdaIRIdentifierExpressionInjectorStrategy::inject(std::shared_ptr<IRIdentifierExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    if (irOperation->incrementRefCount()) {
        irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementLambdaRefCountFunction(), { irExpression->getValue() });
    }

    if (irOperation->isOperandPointer()) {
        return irExpression->getValue();
    }

    return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getSourceType()->getType(), irExpression->getValue(), irBlock, irExpression->getIRType()->getSourceType());
}