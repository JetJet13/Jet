//
// Created by Johny Georges on 2026-04-23.
//

#include "free-class-property-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"
#include "../../../types/ir-type-id.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string FreeClassPropertyIRFunction::getFreeClassPropertyIRFunctionName() {
    return "jet.free.class.property";
}

// this function exists because when class properties are initialized in the constructor,
// the class-property-assignment-injector-strategy calls 'freeValue' on the existing value
// of the class property, and since class properties aren't required to be initialized
// with an expression when declared, the existing value can be zero-initialized and so the
// free-value function will invoke 'free' on an uninitialized pointer. This function
// ensures we only attempt to free the value if the existing value isn't zero-initialized
void FreeClassPropertyIRFunction::generateFreeClassPropertyFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto sharedPtrType = irGenerator->generateIrSharedPtrType(pointerType);
    auto structRefType = irGenerator->generateIRStructRefType();
    auto invocableType = irGenerator->generateIRInvocableType();

    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType->getType(), typeValueType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0,
                           FreeClassPropertyIRFunction::getFreeClassPropertyIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    auto isClassPropertyArrayIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isClassPropertyArrayIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto isClassPropertyStringIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isClassPropertyStringIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto isClassPropertyRefIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isClassPropertyRefIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto isClassPropertyStructRefIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isClassPropertyStructRefIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto isClassPropertyInvocableIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isClassPropertyInvocableIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    functionBlock->createChild();
    auto freeBlock = functionBlock->getLastChildOrSelf();
    functionBlock->createChild();
    auto endBlock = functionBlock->getLastChildOrSelf();

    DebugIRInjectorHelper::injectLog(functionBlock, "FREEING CLASS PROPERTY!", irGenerator->getInjector(), irModuleNode);
    auto typeId = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), {typeValueType->getIdIndex() });

    auto isClassPropertyLiteral = functionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SGT,
            typeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.LITERAL)
    );
    functionBlock->getBuilder()->get()->CreateCondBr(isClassPropertyLiteral, endBlock->getBlock(), isClassPropertyArrayIfBlock->getBlock());

    auto isClassPropertyArray = isClassPropertyArrayIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.ARRAY)
    );
    isClassPropertyArrayIfBlock->getBuilder()->get()->CreateCondBr(isClassPropertyArray, isClassPropertyArrayIfThenBlock->getBlock(), isClassPropertyStringIfBlock->getBlock());
    auto pointerToArrayAlloc = isClassPropertyArrayIfThenBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getAllocIndex());
    auto loadedPointerToArrayAlloc = InstructionIRInjectorHelper::injectLoad(pointerType->getType(), pointerToArrayAlloc, isClassPropertyArrayIfThenBlock);
    auto isPointerToArrayAllocNull = isClassPropertyArrayIfThenBlock->getBuilder()->get()->CreateIsNull(loadedPointerToArrayAlloc);
    isClassPropertyArrayIfThenBlock->getBuilder()->get()->CreateCondBr(isPointerToArrayAllocNull, endBlock->getBlock(), freeBlock->getBlock());

    auto isClassPropertyString = isClassPropertyStringIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRING)
    );
    isClassPropertyStringIfBlock->getBuilder()->get()->CreateCondBr(isClassPropertyString, isClassPropertyStringIfThenBlock->getBlock(), isClassPropertyRefIfBlock->getBlock());
    auto pointerToStringAlloc = isClassPropertyStringIfThenBlock->getBuilder()->get()->CreateStructGEP(arrayPointerType->getType(), function->getArg(0), arrayPointerType->getAllocIndex());
    auto loadedPointerToStringAlloc = InstructionIRInjectorHelper::injectLoad(pointerType->getType(), pointerToStringAlloc, isClassPropertyStringIfThenBlock);
    auto isPointerToStringAllocNull = isClassPropertyStringIfThenBlock->getBuilder()->get()->CreateIsNull(loadedPointerToStringAlloc);
    isClassPropertyStringIfThenBlock->getBuilder()->get()->CreateCondBr(isPointerToStringAllocNull, endBlock->getBlock(), freeBlock->getBlock());


    auto isClassPropertyRef = isClassPropertyRefIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.REF)
    );
    isClassPropertyRefIfBlock->getBuilder()->get()->CreateCondBr(isClassPropertyRef, isClassPropertyRefIfThenBlock->getBlock(), isClassPropertyStructRefIfBlock->getBlock());
    auto pointerToRefCounter = isClassPropertyRefIfThenBlock->getBuilder()->get()->CreateStructGEP(sharedPtrType->getType(), function->getArg(0), sharedPtrType->getRefCounterIndex());
    auto loadedPointerToRefCounter = InstructionIRInjectorHelper::injectLoad(pointerType->getType(), pointerToRefCounter, isClassPropertyRefIfThenBlock);
    auto isPointerToRefCounterNull = isClassPropertyRefIfThenBlock->getBuilder()->get()->CreateIsNull(loadedPointerToRefCounter);
    isClassPropertyRefIfThenBlock->getBuilder()->get()->CreateCondBr(isPointerToRefCounterNull, endBlock->getBlock(), freeBlock->getBlock());


    auto isClassPropertyStructRef = isClassPropertyStructRefIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT_REF)
    );
    isClassPropertyStructRefIfBlock->getBuilder()->get()->CreateCondBr(isClassPropertyStructRef, isClassPropertyStructRefIfThenBlock->getBlock(), isClassPropertyStructRefIfBlock->getBlock());
    auto pointerToStruct = isClassPropertyStructRefIfThenBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(0), structRefType->getStructIndex());
    auto loadedPointerToStruct = InstructionIRInjectorHelper::injectLoad(pointerType->getType(), pointerToStruct, isClassPropertyStructRefIfThenBlock);
    auto isPointerToStructNull = isClassPropertyStructRefIfThenBlock->getBuilder()->get()->CreateIsNull(loadedPointerToStruct);
    isClassPropertyStructRefIfThenBlock->getBuilder()->get()->CreateCondBr(isPointerToStructNull, endBlock->getBlock(), freeBlock->getBlock());


    auto isClassPropertyInvocable = isClassPropertyInvocableIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.INVOCABLE)
    );
    isClassPropertyInvocableIfBlock->getBuilder()->get()->CreateCondBr(isClassPropertyInvocable, isClassPropertyInvocableIfThenBlock->getBlock(), endBlock->getBlock());
    auto pointerToInvocableFunction = isClassPropertyInvocableIfThenBlock->getBuilder()->get()->CreateStructGEP(invocableType->getType(), function->getArg(0), invocableType->getFunctionIndex());
    auto loadedPointerToFunction = InstructionIRInjectorHelper::injectLoad(pointerType->getType(), pointerToInvocableFunction, isClassPropertyInvocableIfThenBlock);
    auto isPointerToFunctionNull = isClassPropertyInvocableIfThenBlock->getBuilder()->get()->CreateIsNull(loadedPointerToFunction);
    isClassPropertyInvocableIfThenBlock->getBuilder()->get()->CreateCondBr(isPointerToFunctionNull, endBlock->getBlock(), freeBlock->getBlock());

    freeBlock->getBuilder()->get()->CreateCall(irModuleNode->getFreeValueFunction(), { function->getArg(0), function->getArg(1) });
    freeBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());

    DebugIRInjectorHelper::injectLog(endBlock, "FREEING CLASS PROPERTY DONE!", irGenerator->getInjector(), irModuleNode);
    endBlock->addVoidReturn();
}