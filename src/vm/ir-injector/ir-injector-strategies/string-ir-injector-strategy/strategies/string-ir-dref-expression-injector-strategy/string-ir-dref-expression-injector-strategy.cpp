//
// Created by Johny Georges on 2025-03-24.
//

#include "string-ir-dref-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/dref-ir-injector-helper/dref-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StringIRDrefExpressionInjectorStrategy::inject(IRDrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto loadedValue = DrefIRInjectorHelper::inject(irExpression, irBlock, irInjector, irOperationType, irModule, scope);
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRType();
    auto typeValue = irInjector->inject(irBlock, irArrayPointerType);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue, irBlock);;
//    auto loadedTypeValue = irBlock->getBuilder()->get()->CreateLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue);
    irBlock->getBuilder()->get()->CreateCall(irModule->getCopyValueFunction(), { irExpression->getIRValue()->getValue(), loadedValue, loadedTypeValue });
    return irExpression->getIRValue()->getValue();
}