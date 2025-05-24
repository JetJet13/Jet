//
// Created by Johny Georges on 2024-09-23.
//

#include "array-access-ir-function.h"
#include "../../../utils/ir-instruction-node-factory/ir-instruction-node-factory.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"

std::string ArrayAccessIRFunction::getArrayAccessIRFunctionName() {
    return "jet.array.access.within.bounds";
}

// this function should return void and only check if the index is within bounds.
// The IR Strategies will be responsible for creating pointer instances for the corresponding index.
void ArrayAccessIRFunction::generateArrayAccessFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    // todo: complete this function.
    auto arrayIndexAccessType = irGenerator->generateIntType();
    auto pointerType = irGenerator->generatePointerType();
    auto arrayPointerType = llvm::StructType::get(**context, { arrayIndexAccessType, pointerType });
    auto functionType = llvm::FunctionType::get(pointerType, { arrayIndexAccessType, arrayPointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, ArrayAccessIRFunction::getArrayAccessIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto pointerToValueAtIndex = functionBlock->getBuilder()->get()->CreateAlloca(irGenerator->generateIntType());
    functionBlock->getBuilder()->get()->CreateRet(pointerToValueAtIndex);
}