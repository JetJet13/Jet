//
// Created by Johny Georges on 2026-09-29.
//

#include "get-vararg-ir-function.h"

std::string GetVarArgIRFunction::getGetVarArgIRFunctionName() {
    return "jet.get.vararg";
}

void GetVarArgIRFunction::generateGetVarArgFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto int32Type = irGenerator->generateInt32Type();
    auto pointerType = irGenerator->generateIrPointerType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto vaListType = llvm::StructType::get(**context, {
        pointerType->getType(),
        pointerType->getType(),
        pointerType->getType(),
        int32Type,
        int32Type
    });
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());

    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(),
                                                { pointerType->getType(), pointerType->getType() },
                                                false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                                           GetVarArgIRFunction::getGetVarArgIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    auto checkBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto inRegistryBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto onStackBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope());
    auto endBlock = irGenerator->generateIfEndBlock(irContext, functionBlock->getScope());

    functionBlock->getBuilder()->get()->CreateBr(checkBlock->getBlock());

    auto offsetPointer = checkBlock->getBuilder()->get()->CreateStructGEP(vaListType, function->getArg(1), 3);
    auto offsetValue = checkBlock->getBuilder()->get()->CreateLoad(int32Type, offsetPointer);
    auto zero = checkBlock->getBuilder()->get()->getInt32(0);
    auto offsetResult = checkBlock->getBuilder()->get()->CreateICmpSLT(offsetValue, zero);
    checkBlock->getBuilder()->get()->CreateCondBr(offsetResult, inRegistryBlock->getBlock(), onStackBlock->getBlock());

    // in-registry
    auto topPointer = inRegistryBlock->getBuilder()->get()->CreateStructGEP(vaListType, function->getArg(1), 1);
    auto topValue = inRegistryBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), topPointer);

    auto offset64Value = inRegistryBlock->getBuilder()->get()->CreateSExt(offsetValue, intType);
    auto registryPointerOffset = inRegistryBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, topValue, offset64Value);

    auto nextOffset = inRegistryBlock->getBuilder()->get()->CreateAdd(offsetValue, inRegistryBlock->getBuilder()->get()->getInt32(8));
    inRegistryBlock->getBuilder()->get()->CreateStore(nextOffset, offsetPointer);
    inRegistryBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());

    // on-stack
    auto stackPointer = onStackBlock->getBuilder()->get()->CreateStructGEP(vaListType, function->getArg(1), 0);
    auto stackValue = onStackBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), stackPointer);

    auto nextStack = onStackBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, stackValue, irGenerator->generateIntConstant(8));
    onStackBlock->getBuilder()->get()->CreateStore(nextStack, stackPointer);
    onStackBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());

    // end-block
    auto phi = endBlock->getBuilder()->get()->CreatePHI(pointerType->getType(), 2);
    phi->addIncoming(registryPointerOffset, inRegistryBlock->getBlock());
    phi->addIncoming(stackValue, onStackBlock->getBlock());

    auto varArgValue = endBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), phi);
    endBlock->getBuilder()->get()->CreateStore(varArgValue, function->getArg(0));
    endBlock->addVoidReturn();
}