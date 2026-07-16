//
// Created by Johny Georges on 2025-12-12.
//

#include "get-ref-count-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string GetRefCountIRFunction::getGetRefCountIRFunctionName() {
    return "jet.get.ref.count";
}

void GetRefCountIRFunction::generateGetRefCountFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generatePointerType();
    auto irSharedPtrType = irGenerator->generateIrSharedPtrType(irGenerator->generateVoidType());
    auto functionType = llvm::FunctionType::get(intType, { pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, GetRefCountIRFunction::getGetRefCountIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto pointerToRefCountPointer = functionBlock->getBuilder()->get()->CreateStructGEP(irSharedPtrType->getType(), function->getArg(0), irSharedPtrType->getRefCounterIndex());
    auto loadedRefCountPointer = InstructionIRInjectorHelper::injectLoad(pointerType, pointerToRefCountPointer, functionBlock);
    functionBlock->getBuilder()->get()->CreateRet(
        InstructionIRInjectorHelper::injectLoad(intType, loadedRefCountPointer, functionBlock)
    );

}