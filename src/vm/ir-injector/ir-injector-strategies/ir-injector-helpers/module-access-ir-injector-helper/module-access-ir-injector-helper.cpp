//
// Created by Johny Georges on 2026-03-27.
//

#include "module-access-ir-injector-helper.h"
#include "../instruction-ir-injector-helper/instruction-ir-injector-helper.h"


llvm::Value* ModuleAccessIRInjectorHelper::inject(IRModuleAccessExpressionNode* irExpression, IRBlockNode* irBlock, IRInjector* irInjector, std::shared_ptr<IRModuleNode> irModule, IRLookupTable* scope, IROperation* irOperation) {
    if (irOperation->isOperandPointer()) {
        return irExpression->getValue();
    }
    return InstructionIRInjectorHelper::injectLoad(irExpression->getIRType()->getSourceType()->getType(), irExpression->getValue(), irBlock, irExpression->getIRType()->getSourceType());
}