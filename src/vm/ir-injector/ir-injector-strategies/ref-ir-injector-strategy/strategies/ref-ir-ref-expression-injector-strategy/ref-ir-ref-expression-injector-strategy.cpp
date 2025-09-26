//
// Created by Johny Georges on 2025-05-10.
//

#include "ref-ir-ref-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* RefIRRefExpressionInjectorStrategy::inject(IRRefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    if (irExpression->getExpression()->isOneOf({ IR_OBJECT_ACCESS_EXPRESSION_NODE, IR_TUPLE_ACCESS_EXPRESSION_NODE })) {
        auto value = irInjector->inject(irBlock, irExpression->getExpression(), irOperation, irModule, scope);
        auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
        irBlock->getBuilder()->get()->CreateCall(
            irModule->getSetupRefFunction()->getFunctionType(),
            irModule->getSetupRefFunction(),
            { allocation, value }
        );
        return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getType(), allocation);
    } else if (irExpression->getExpression()->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
        irBlock->getBuilder()->get()->CreateCall(
            irModule->getSetupRefFunction()->getFunctionType(),
            irModule->getSetupRefFunction(),
            { allocation, irExpression->getExpression()->getValue() }
        );
        return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getType(), allocation);
    }
    auto value = this->injectRawValue(irExpression, irBlock, irInjector, irOperation, irModule, scope);
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    irBlock->getBuilder()->get()->CreateCall(
        irModule->getSetupRefFunction()->getFunctionType(),
        irModule->getSetupRefFunction(),
        { allocation, value }
    );
    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getType(), allocation);
}

llvm::Value* RefIRRefExpressionInjectorStrategy::injectRawValue(IRRefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    auto rawValue = irInjector->inject(irBlock, irExpression->getExpression(), irOperation, irModule, scope);
    if (irOperation->isRefGlobalAssignment()) {
        auto globalVariable = new llvm::GlobalVariable(
                irExpression->getIRType()->getSourceType()->getType(),
                false,
                llvm::GlobalValue::InternalLinkage
        );
        irModule->getModule()->insertGlobalVariable(globalVariable);
        InstructionIRInjectorHelper::injectStore(rawValue, globalVariable, irBlock, irExpression->getIRType()->getRefValueIRType());
//        irBlock->getBuilder()->get()->CreateStore(rawValue, globalVariable);
        return globalVariable;
    }

    auto malloc = irBlock->getBuilder()->get()->CreateCall(
        irModule->getMallocFunction()->getFunctionType(),
        irModule->getMallocFunction(),
        { irBlock->getBuilder()->get()->getInt64(irExpression->getExpression()->getIRType()->getSizeInBytes()) }
    );
    irBlock->getBuilder()->get()->CreateStore(rawValue, malloc);
    return malloc;
}