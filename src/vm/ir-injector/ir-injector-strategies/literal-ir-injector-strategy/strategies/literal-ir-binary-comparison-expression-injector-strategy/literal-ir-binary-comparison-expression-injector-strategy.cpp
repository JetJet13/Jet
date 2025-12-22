//
// Created by Johny Georges on 2025-03-08.
//

#include "literal-ir-binary-comparison-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

llvm::Value* LiteralIRBinaryComparisonExpressionInjectorStrategy::inject(IRBinaryComparisonExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->isPredicateEqual() || irExpression->isPredicateNotEqual()) {
        auto leftIrTypeValue = irInjector->inject(irBlock, irExpression->getLeftIrType());
        auto loadedLeftIrTypeValue = InstructionIRInjectorHelper::injectLoad(irExpression->getLeftIrType()->getValue()->getAllocatedType(), leftIrTypeValue, irBlock);
        auto rightIrTypeValue = irInjector->inject(irBlock, irExpression->getRightIrType());
        auto loadedRightIrTypeValue = InstructionIRInjectorHelper::injectLoad(irExpression->getRightIrType()->getValue()->getAllocatedType(), rightIrTypeValue, irBlock);
        auto irLeftNodeValue = irInjector->inject(irBlock, irExpression->getLeftNode(), new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
        auto irRightNodeValue = irInjector->inject(irBlock, irExpression->getRightNode(), new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
        auto result = irBlock->getBuilder()->get()->CreateCall(irModule->getEqualValueFunction(), { irLeftNodeValue, irRightNodeValue, loadedLeftIrTypeValue, loadedRightIrTypeValue });
        return irExpression->isPredicateEqual()
        ? result
        : irBlock->getBuilder()->get()->CreateICmp(llvm::CmpInst::Predicate::ICMP_EQ, result, irBlock->getBuilder()->get()->getFalse());
    }

    auto irLeftNodeValue = irInjector->inject(irBlock, irExpression->getLeftNode(), (new IROperation(IR_OPERAND_VALUE_OP))->markAsUnderlying(), irModule, scope);
    auto irRightNodeValue = irInjector->inject(irBlock, irExpression->getRightNode(), (new IROperation(IR_OPERAND_VALUE_OP))->markAsUnderlying(), irModule, scope);
    return irBlock->getBuilder()->get()->CreateCmp(irExpression->getValue()->getPredicate(), irLeftNodeValue, irRightNodeValue);
}