//
// Created by Johny Georges on 2025-10-18.
//

#include "assert-ir-function.h"
#include "../print-ir-function/print-ir-function.h"

std::string AssertIRFunction::getAssertIRFunctionName() {
    return "jet.assert";
}

std::string AssertIRFunction::getAssertWithMessageIRFunctionName() {
    return "jet.assert.with.message";
}

std::string AssertIRFunction::getGlobalDefaultAssertMessageStringName() {
    return "jet.assert.default.message";
}

std::string AssertIRFunction::getGlobalAssertWithMessageStringName() {
    return "jet.assert.with.message.string";
}

void AssertIRFunction::generateAssertGlobals(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto defaultMessage = "\n\nAssertion Failed\n";
    auto defaultAssertMessageString = irGenerator->generateRawString(defaultMessage);
    new llvm::GlobalVariable(
            *irModuleNode->getModule(),
            defaultAssertMessageString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            defaultAssertMessageString,
            AssertIRFunction::getGlobalDefaultAssertMessageStringName()
    );

    std::string customMessageStartingPoint = "Message: ";
    auto assertWithCustomMessageString = irGenerator->generateRawString(defaultMessage + customMessageStartingPoint);
    new llvm::GlobalVariable(
            *irModuleNode->getModule(),
            assertWithCustomMessageString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            assertWithCustomMessageString,
            AssertIRFunction::getGlobalAssertWithMessageStringName()
    );

}

void AssertIRFunction::generateAssertFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto boolType = irGenerator->generateBooleanType();
    auto voidType = irGenerator->generateVoidType()->getType();
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(voidType, { boolType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0,
                                           AssertIRFunction::getAssertIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto abort = irModuleNode->getModule()->getOrInsertFunction("abort", llvm::FunctionType::get(voidType, { voidType }, false));
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isValueTrueIfBlock = irGenerator->generateIfBlock(irContext);
    auto isValueTrueIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto isValueTrueIfElseBlock = irGenerator->generateIfElseBlock(irContext);
    functionBlock->getBuilder()->get()->CreateBr(isValueTrueIfBlock->getBlock());
    auto isValueTrue = isValueTrueIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            function->getArg(0),
            functionBlock->getBuilder()->get()->getTrue()
    );
    isValueTrueIfBlock->getBuilder()->get()->CreateCondBr(isValueTrue, isValueTrueIfThenBlock->getBlock(), isValueTrueIfElseBlock->getBlock());
    isValueTrueIfThenBlock->addVoidReturn();
    isValueTrueIfElseBlock->getBuilder()->get()->CreateCall(printf, {
            irModuleNode->getModule()->getGlobalVariable(AssertIRFunction::getGlobalDefaultAssertMessageStringName())
    });
    isValueTrueIfElseBlock->getBuilder()->get()->CreateCall(abort);
    isValueTrueIfElseBlock->addVoidReturn();
}

void AssertIRFunction::generateAssertWithMessageFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto boolType = irGenerator->generateBooleanType();
    auto voidType = irGenerator->generateVoidType()->getType();
    auto pointerType = irGenerator->generatePointerType();
    auto stringArrayPointerType = irGenerator->generateIrStringArrayPointerType();
    auto functionType = llvm::FunctionType::get(voidType, { boolType, stringArrayPointerType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0,
                                           AssertIRFunction::getAssertWithMessageIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto abort = irModuleNode->getModule()->getOrInsertFunction("abort", llvm::FunctionType::get(voidType, { voidType }, false));
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto isValueTrueIfBlock = irGenerator->generateIfBlock(irContext);
    auto isValueTrueIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto isValueTrueIfElseBlock = irGenerator->generateIfElseBlock(irContext);
    functionBlock->getBuilder()->get()->CreateBr(isValueTrueIfBlock->getBlock());
    auto isValueTrue = isValueTrueIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            function->getArg(0),
            functionBlock->getBuilder()->get()->getTrue()
    );
    isValueTrueIfBlock->getBuilder()->get()->CreateCondBr(isValueTrue, isValueTrueIfThenBlock->getBlock(), isValueTrueIfElseBlock->getBlock());
    isValueTrueIfThenBlock->addVoidReturn();

    auto pointerToStringAllocation = isValueTrueIfElseBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), { stringArrayPointerType->getAllocIndex() });
    auto formatStringAllocation = irModuleNode->getModule()->getGlobalVariable(PrintIRFunction::getGlobalStringFormatStringName());
    isValueTrueIfElseBlock->getBuilder()->get()->CreateCall(printf, {
            irModuleNode->getModule()->getGlobalVariable(AssertIRFunction::getGlobalAssertWithMessageStringName())
    });
    isValueTrueIfElseBlock->getBuilder()->get()->CreateCall(printf, {
            formatStringAllocation,
            pointerToStringAllocation
    });
    isValueTrueIfElseBlock->getBuilder()->get()->CreateCall(irModuleNode->getPrintNewLineFunction());
    isValueTrueIfElseBlock->getBuilder()->get()->CreateCall(abort);
    isValueTrueIfElseBlock->addVoidReturn();
}