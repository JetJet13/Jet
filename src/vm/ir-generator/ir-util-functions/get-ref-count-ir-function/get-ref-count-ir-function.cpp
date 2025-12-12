//
// Created by Johny Georges on 2025-12-12.
//

#include "get-ref-count-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string GetRefCountIRFunction::getGetRefCountIRFunctionName() {
    return "jet.get.ref.count";
}

void GetRefCountIRFunction::generateGetRefCountFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generatePointerType();
    auto irRefType = irGenerator->generateIrRefType(irGenerator->generateVoidType());
    auto functionType = llvm::FunctionType::get(intType, { pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, GetRefCountIRFunction::getGetRefCountIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto pointerToRefCountPointer = functionBlock->getBuilder()->get()->CreateStructGEP(irRefType->getType(), function->getArg(0), irRefType->getRefCounterIndex());
    auto loadedRefCountPointer = InstructionIRInjectorHelper::injectLoad(pointerType, pointerToRefCountPointer, functionBlock);
    functionBlock->getBuilder()->get()->CreateRet(
        InstructionIRInjectorHelper::injectLoad(intType, loadedRefCountPointer, functionBlock)
    );

}