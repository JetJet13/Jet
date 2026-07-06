//
// Created by Johny Georges on 2025-03-08.
//

#include "literal-ir-array-access-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"

llvm::Value* LiteralIRArrayAccessExpressionInjectorStrategy::inject(std::shared_ptr<IRArrayAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto pointerAtIndex = ArrayIRInjectorHelper::getPointerToIndexedElement(irBlock, irExpression, irModule, irInjector, scope);
    if (irOperation->isOperandPointer()) {
        return pointerAtIndex;
    } else {
        return InstructionIRInjectorHelper::injectLoad(
                irExpression->getUnderlyingIRType()->getType(),
                pointerAtIndex,
                irBlock
        );
    }
}