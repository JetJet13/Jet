//
// Created by Johny Georges on 2025-03-08.
//

#include "tuple-ir-class-property-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* TupleIRClassPropertyAccessExpressionInjectorStrategy::inject(std::shared_ptr<IRClassPropertyAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, IRInjector* irInjector, IROperation* irOperation, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope) {
    auto allocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getTargetIRType()->getType());
    auto loadedStruct = ClassPropertyAccessIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope, new IROperation(IR_OPERAND_VALUE_OP));
    InstructionIRInjectorHelper::injectStore(loadedStruct, allocation, irBlock, irExpression->getTargetIRType());
    return allocation;
}