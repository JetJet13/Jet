//
// Created by Johny Georges on 2025-03-19.
//

#include "array-ir-dref-expression-injector-strategy.h"
#include "../../../../../ir-type/ir-array-pointer-type.h"
#include "../../../ir-injector-helpers/dref-ir-injector-helper/dref-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* ArrayIRDrefExpressionInjectorStrategy::inject(IRDrefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto loadedValue = DrefIRInjectorHelper::inject(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    auto irArrayPointerType = (IRArrayPointerType*)irExpression->getIRType();
    auto typeValue = irInjector->inject(irBlock, irArrayPointerType);
    auto loadedTypeValue = InstructionIRInjectorHelper::injectLoad(irArrayPointerType->getValue()->getAllocatedType(), typeValue, irBlock);
    irBlock->getBuilder()->get()->CreateCall(irModule->getCopyArrayFunction(), { irExpression->getIRValue()->getValue(), loadedValue, loadedTypeValue });
    return irExpression->getIRValue()->getValue();
}