//
// Created by Johny Georges on 2025-03-08.
//

#include "tuple-ir-class-property-access-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/class-property-access-ir-injector-helper/class-property-access-ir-injector-helper.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* TupleIRClassPropertyAccessExpressionInjectorStrategy::inject(std::shared_ptr<IRClassPropertyAccessExpressionNode> irExpression, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IROperation> irOperation, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope) {
    auto allocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getTargetIRType()->getType());
    auto loadedStruct = ClassPropertyAccessIRInjectorHelper::inject(irExpression, irBlock, irInjector, irModule, scope, std::make_shared<IROperation>(IR_OPERAND_VALUE_OP));
    InstructionIRInjectorHelper::injectStore(loadedStruct, allocation, irBlock, irExpression->getTargetIRType());
    return allocation;
}