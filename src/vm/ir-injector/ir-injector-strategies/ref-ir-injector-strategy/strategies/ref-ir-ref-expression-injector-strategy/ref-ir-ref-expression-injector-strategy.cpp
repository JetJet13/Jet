//
// Created by Johny Georges on 2025-05-10.
//

#include "ref-ir-ref-expression-injector-strategy.h"
#include "../../../ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

llvm::Value* RefIRRefExpressionInjectorStrategy::inject(IRRefExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, IROperation* irOperation, IRModuleNode *irModule, IRLookupTable* scope) {
    auto allocation = InstructionIRInjectorHelper::inject(irExpression->getIRValue(), irBlock);
    if (irExpression->getExpression()->isOneOf({ IR_OBJECT_ACCESS_EXPRESSION_NODE, IR_TUPLE_ACCESS_EXPRESSION_NODE })) {
        auto value = irInjector->inject(irBlock, irExpression->getExpression(), irOperation, irModule, scope);
        this->setupRef(allocation, value, irExpression->getArc().value()->getValue(), irExpression->getUnderlyingIRType(), irBlock, irModule);
        irBlock->getBuilder()->get()->CreateCall(irModule->getIncrementRefCountFunction(), { allocation });
    } else if (irExpression->getExpression()->is(IR_IDENTIFIER_EXPRESSION_NODE)) {
        this->setupRef(allocation, irExpression->getExpression()->getValue(), irExpression->getArc().value()->getValue(), irExpression->getUnderlyingIRType(), irBlock, irModule);
    } else {
        auto value = this->injectRawValue(irExpression, irBlock, irInjector, irOperation, irModule, scope);
        InstructionIRInjectorHelper::inject(irExpression->getArc().value(), irBlock);
        this->setupRef(allocation, value, irExpression->getArc().value()->getValue(), irExpression->getUnderlyingIRType(), irBlock, irModule);
    }

    if (irOperation->isOperandPointer()) {
        return allocation;
    }
    return irBlock->getBuilder()->get()->CreateLoad(irExpression->getIRType()->getType(), allocation);
}

void RefIRRefExpressionInjectorStrategy::setupRef(llvm::Value* allocation, llvm::Value* value, llvm::Value* valueArc, IRType* irType, IRBlockNode* irBlock, IRModuleNode *irModule) {
        irBlock->getBuilder()->get()->CreateCall(
                irModule->getSetupRefFunction(),
                { allocation, value, valueArc }
        );
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