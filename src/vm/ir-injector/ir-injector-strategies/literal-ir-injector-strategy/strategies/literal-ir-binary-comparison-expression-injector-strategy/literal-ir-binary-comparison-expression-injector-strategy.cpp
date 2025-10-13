//
// Created by Johny Georges on 2025-03-08.
//

#include "literal-ir-binary-comparison-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* LiteralIRBinaryComparisonExpressionInjectorStrategy::inject(IRBinaryComparisonExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->isPredicateEqual() || irExpression->isPredicateNotEqual()) {
        auto irTypeValue = irInjector->inject(irBlock, irExpression->getComparisonIrType());
        auto loadedIrTypeValue = InstructionIRInjectorHelper::injectLoad(irExpression->getComparisonIrType()->getValue()->getAllocatedType(), irTypeValue, irBlock);
        auto irLeftNodeValue = irInjector->inject(irBlock, irExpression->getLeftNode(), new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
        auto irRightNodeValue = irInjector->inject(irBlock, irExpression->getRightNode(), new IROperation(IR_OPERAND_POINTER_OP), irModule, scope);
        auto result = irBlock->getBuilder()->get()->CreateCall(irModule->getEqualValueFunction(), { irLeftNodeValue, irRightNodeValue, loadedIrTypeValue });
        return irExpression->isPredicateEqual()
        ? result
        : irBlock->getBuilder()->get()->CreateICmp(llvm::CmpInst::Predicate::ICMP_EQ, result, irBlock->getBuilder()->get()->getFalse());
    }

    auto irLeftNodeValue = irInjector->inject(irBlock, irExpression->getLeftNode(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
    auto irRightNodeValue = irInjector->inject(irBlock, irExpression->getRightNode(), new IROperation(IR_OPERAND_VALUE_OP), irModule, scope);
    return irBlock->getBuilder()->get()->CreateCmp(irExpression->getValue()->getPredicate(), irLeftNodeValue, irRightNodeValue);
}