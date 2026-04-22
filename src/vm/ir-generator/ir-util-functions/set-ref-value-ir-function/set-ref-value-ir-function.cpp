//
// Created by Johny Georges on 2026-02-16.
//

#include "set-ref-value-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../types/ir-type-id.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

std::string SetRefValueIRFunction::getSetRefValueIRFunctionName() {
    return "jet.set.ref.value";
}

void SetRefValueIRFunction::generateSetRefValueFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto structRefType = irGenerator->generateIRStructRefType();
    auto refType = irGenerator->generateIrRefType(irGenerator->generateVoidType());
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType->getType(), pointerType->getType(), typeValueType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, SetRefValueIRFunction::getSetRefValueIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto structRefIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope(), "struct.ref.");
    auto structRefIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "struct.ref.");
    auto structRefElseBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope());
    auto endBlock = irGenerator->generateIfEndBlock(irContext, functionBlock->getScope());

    DebugIRInjectorHelper::injectLog(functionBlock, "SET REF VALUE FUNCTION!", irGenerator->getInjector(), irModuleNode);
    auto pointerToRefValue = functionBlock->getBuilder()->get()->CreateStructGEP(refType->getType(), function->getArg(0), refType->getRefValueIndex());
    auto loadedPointerToRefValue = InstructionIRInjectorHelper::injectLoad(refType->getRefValueType(), pointerToRefValue, functionBlock);
    auto typeValueId = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getIdIndex() });
    auto sizeInBytes = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), typeValueType->getSizeInBytesIndex());
    functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getFreeRefValueFunction(),
            { loadedPointerToRefValue, function->getArg(2) }
    );
    functionBlock->getBuilder()->get()->CreateBr(structRefIfBlock->getBlock());

    auto isValueTypeStructRef = structRefIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT_REF)
    );
    structRefIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeStructRef, structRefIfThenBlock->getBlock(), structRefElseBlock->getBlock());
    DebugIRInjectorHelper::injectLog(structRefIfThenBlock, "SETTING STRUCT_REF VALUE!", irGenerator->getInjector(), irModuleNode);
    auto pointerToOldStructPointer = structRefIfThenBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), loadedPointerToRefValue, structRefType->getStructIndex());
    auto oldStructPointer = InstructionIRInjectorHelper::injectLoad(pointerType->getType(), pointerToOldStructPointer, structRefIfThenBlock);
    auto pointerToNewStructPointer = structRefIfThenBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(1), structRefType->getStructIndex());
    auto newStructPointer = InstructionIRInjectorHelper::injectLoad(pointerType->getType(), pointerToNewStructPointer, structRefIfThenBlock);
    auto pointerToNewCounterPointer = structRefIfThenBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(1), structRefType->getCounterIndex());
    auto newCounterPointer = InstructionIRInjectorHelper::injectLoad(pointerType->getType(), pointerToNewCounterPointer, structRefIfThenBlock);
    // store the new struct pointer in the old struct-ref
    InstructionIRInjectorHelper::injectStore(newStructPointer, pointerToOldStructPointer, structRefIfThenBlock);
    // free the old struct-ref struct pointer
    structRefIfThenBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFreeFunction(),
            { oldStructPointer }
    );
    // free the new struct-ref counter because the old
    // struct-ref counter will continue to be used.
    structRefIfThenBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFreeFunction(),
            { newCounterPointer }
    );

    structRefElseBlock->getBuilder()->get()->CreateCall(
        irModuleNode->getMemcpyFunction(),
        { loadedPointerToRefValue, function->getArg(1), sizeInBytes }
    );


    structRefIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    structRefElseBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    // free the new value pointer after copying its contents
    // into the old value pointer
    endBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFreeFunction(),
            { function->getArg(1) }
    );
    endBlock->addVoidReturn();
}