//
// Created by Johny Georges on 2025-03-03.
//

#include "ref-ir-injector-helper.h"

llvm::Value* RefIRInjectorHelper::injectRefSource(IRBlockNode* irBlock, IRExpressionNode* irExpression, llvm::Value* irValue, IRModuleNode* irModule, IROperationType irOperationType) {
    if (irOperationType == IR_REF_ASSIGNMENT_OP) {
        auto allocation = irBlock->getBuilder()->get()->CreateAlloca(irExpression->getType());
        irBlock->getBuilder()->get()->CreateStore(irValue, allocation);
        return allocation;
    } else if (irOperationType == IR_REF_GLOBAL_ASSIGNMENT_OP) {
        auto globalVariable = new llvm::GlobalVariable(
                irExpression->getType(),
                false,
                llvm::GlobalValue::InternalLinkage
        );
        irModule->getModule()->insertGlobalVariable(globalVariable);

        irBlock->getBuilder()->get()->CreateStore(irValue, globalVariable);
        return globalVariable;
    }
}