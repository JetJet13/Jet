//
// Created by Johny Georges on 2025-12-22.
//

#include "equal-struct-ref-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

std::string EqualStructRefIRFunction::getEqualStructRefIRFunctionName() {
    return "jet.equal.struct.ref";
}

void EqualStructRefIRFunction::declareEqualStructRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateBooleanType(), { pointerType, pointerType, typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, EqualStructRefIRFunction::getEqualStructRefIRFunctionName(), irModuleNode->getModule()->get());
}


void EqualStructRefIRFunction::generateEqualStructRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto structRefType = irGenerator->generateIRStructRefType();
    auto function = irModuleNode->getEqualStructRefFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto structTypePointer = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getAllocIndex() });
    auto loadedStructType = functionBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), structTypePointer);
    auto firstStructPointer = functionBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(0), structRefType->getStructIndex());
    auto loadedFirstStructPointer = InstructionIRInjectorHelper::injectLoad(pointerType, firstStructPointer, functionBlock);

    auto secondStructPointer = functionBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(1), structRefType->getStructIndex());
    auto loadedSecondStructPointer = InstructionIRInjectorHelper::injectLoad(pointerType, secondStructPointer, functionBlock);

    auto result = functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getEqualStructFunction(),
            { loadedFirstStructPointer, loadedSecondStructPointer, loadedStructType }
    );
    functionBlock->getBuilder()->get()->CreateRet(result);
}