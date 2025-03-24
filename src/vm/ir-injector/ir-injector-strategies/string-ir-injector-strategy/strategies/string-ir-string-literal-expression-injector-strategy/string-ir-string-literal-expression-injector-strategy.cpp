//
// Created by Johny Georges on 2025-03-08.
//

#include "string-ir-string-literal-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/array-ir-injector-helper/array-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* StringIRStringLiteralExpressionInjectorStrategy::inject(IRStringLiteralExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperationType irOperationType, IRModuleNode *irModule, IRLookupTable* scope) {
    auto arrayAllocation = irExpression->getSourceAggregateAllocation()->getValue();
    InstructionIRInjectorHelper::inject(irExpression->getSourceAggregateAllocation(), irBlock);
    irBlock->getBuilder()->get()->CreateStore(irExpression->getValue(), arrayAllocation);
    return ArrayIRInjectorHelper::injectArrayPointer(irBlock, irExpression->getIRType(), irExpression->getValue()->getType()->getArrayNumElements(),
                                                     irExpression->getSourceAggregateAllocation(),
                                                     irExpression->getAggregatePointerAllocation())->getValue();
}