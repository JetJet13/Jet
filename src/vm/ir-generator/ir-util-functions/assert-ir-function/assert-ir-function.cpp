//
// Created by Johny Georges on 2025-10-18.
//

#include "assert-ir-function.h"
#include "../print-ir-function/print-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string AssertIRFunction::getAssertIRFunctionName() {
    return "jet.assert";
}

std::string AssertIRFunction::getAssertWithMessageIRFunctionName() {
    return "jet.assert.with.message";
}

std::string AssertIRFunction::getAssertDebugRefCountIRFunctionName() {
    return "jet.assert.debug.ref.count";
}

std::string AssertIRFunction::getAssertDebugStructRefCountIRFunctionName() {
    return "jet.assert.debug.struct.ref.count";
}

std::string AssertIRFunction::getAssertDebugLambdaRefCountIRFunctionName() {
    return "jet.assert.debug.lambda.ref.count";
}

std::string AssertIRFunction::getGlobalDefaultAssertMessageStringName() {
    return "jet.assert.default.message";
}

std::string AssertIRFunction::getGlobalAssertDebugRefCountMessageStringName() {
    return "jet.assert.debug.ref.count.message";
}

std::string AssertIRFunction::getGlobalAssertDebugStructRefCountMessageStringName() {
    return "jet.assert.debug.struct.ref.count.message";
}

std::string AssertIRFunction::getGlobalAssertDebugLambdaRefCountMessageStringName() {
    return "jet.assert.debug.lambda.ref.count.message";
}

void AssertIRFunction::generateAssertGlobals(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto defaultMessage = "\n\nAssertion Failed\n";
    auto defaultAssertMessageString = irGenerator->generateRawString(defaultMessage);
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            defaultAssertMessageString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            defaultAssertMessageString,
            AssertIRFunction::getGlobalDefaultAssertMessageStringName()
    );
}

void AssertIRFunction::generateAssertDebugGlobals(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto debugRefCountMessage = "\n\nRef Count Assertion Failed\n";
    auto debugRefCountMessageString = irGenerator->generateRawString(debugRefCountMessage);
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            debugRefCountMessageString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            debugRefCountMessageString,
            AssertIRFunction::getGlobalAssertDebugRefCountMessageStringName()
    );

    auto debugStructRefCountMessage = "\n\nStruct Ref Count Assertion Failed\n";
    auto debugStructRefCountMessageString = irGenerator->generateRawString(debugStructRefCountMessage);
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            debugStructRefCountMessageString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            debugStructRefCountMessageString,
            AssertIRFunction::getGlobalAssertDebugStructRefCountMessageStringName()
    );

    auto debugLambdaRefCountMessage = "\n\nLambda Ref Count Assertion Failed\n";
    auto debugLambdaRefCountMessageString = irGenerator->generateRawString(debugLambdaRefCountMessage);
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            debugLambdaRefCountMessageString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            debugLambdaRefCountMessageString,
            AssertIRFunction::getGlobalAssertDebugLambdaRefCountMessageStringName()
    );
}

void AssertIRFunction::generateAssertFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto boolType = irGenerator->generateBooleanType();
    auto voidType = irGenerator->getVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(voidType, { boolType, pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0,
                                           AssertIRFunction::getAssertIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto abort = irModuleNode->getModule()->get()->getOrInsertFunction("abort", llvm::FunctionType::get(voidType, { }, false));
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    auto isValueTrueIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isValueTrueIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto isValueTrueIfElseBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope());
    functionBlock->getBuilder()->get()->CreateBr(isValueTrueIfBlock->getBlock());
    auto isValueTrue = isValueTrueIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            function->getArg(0),
            functionBlock->getBuilder()->get()->getTrue()
    );
    isValueTrueIfBlock->getBuilder()->get()->CreateCondBr(isValueTrue, isValueTrueIfThenBlock->getBlock(), isValueTrueIfElseBlock->getBlock());
    isValueTrueIfThenBlock->addVoidReturn();
    isValueTrueIfElseBlock->getBuilder()->get()->CreateCall(printf, {
            irModuleNode->getModule()->get()->getGlobalVariable(AssertIRFunction::getGlobalDefaultAssertMessageStringName())
    });
    isValueTrueIfElseBlock->getBuilder()->get()->CreateCall(printf, {
            function->getArg(1)
    });
    isValueTrueIfElseBlock->getBuilder()->get()->CreateCall(abort);
    isValueTrueIfElseBlock->addVoidReturn();
}

void AssertIRFunction::generateAssertWithMessageFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto boolType = irGenerator->generateBooleanType();
    auto voidType = irGenerator->getVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto stringArrayPointerType = irGenerator->generateIrStringArrayPointerType();
    auto functionType = llvm::FunctionType::get(voidType, { boolType, stringArrayPointerType->getType(), pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0,
                                           AssertIRFunction::getAssertWithMessageIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto abort = irModuleNode->getModule()->get()->getOrInsertFunction("abort", llvm::FunctionType::get(voidType, { }, false));
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    auto isValueTrueIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isValueTrueIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto isValueTrueIfElseBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope());
    functionBlock->getBuilder()->get()->CreateBr(isValueTrueIfBlock->getBlock());
    auto isValueTrue = isValueTrueIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            function->getArg(0),
            functionBlock->getBuilder()->get()->getTrue()
    );
    isValueTrueIfBlock->getBuilder()->get()->CreateCondBr(isValueTrue, isValueTrueIfThenBlock->getBlock(), isValueTrueIfElseBlock->getBlock());
    isValueTrueIfThenBlock->addVoidReturn();

    auto pointerToStringAllocation = isValueTrueIfElseBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), { stringArrayPointerType->getAllocIndex() });
    auto formatStringAllocation = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalStringFormatStringName());
    isValueTrueIfElseBlock->getBuilder()->get()->CreateCall(printf, {
            irModuleNode->getModule()->get()->getGlobalVariable(AssertIRFunction::getGlobalDefaultAssertMessageStringName())
    });
    isValueTrueIfElseBlock->getBuilder()->get()->CreateCall(printf, {
            function->getArg(2)
    });
    isValueTrueIfElseBlock->getBuilder()->get()->CreateCall(printf, {
            formatStringAllocation,
            pointerToStringAllocation
    });
    isValueTrueIfElseBlock->getBuilder()->get()->CreateCall(irModuleNode->getPrintNewLineFunction());
    isValueTrueIfElseBlock->getBuilder()->get()->CreateCall(abort);
    isValueTrueIfElseBlock->addVoidReturn();
}

void AssertIRFunction::generateAssertDebugRefCountFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto voidType = irGenerator->getVoidType();
    auto sharedPtrType = irGenerator->generateIrSharedPtrType(irGenerator->generateVoidType());
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(voidType, { pointerType, intType, pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0,
                                           AssertIRFunction::getAssertDebugRefCountIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto abort = irModuleNode->getModule()->get()->getOrInsertFunction("abort", llvm::FunctionType::get(voidType, { }, false));
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    auto isRefCountMatchTrueIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isRefCountMatchIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto isRefCountMatchIfElseBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope());
    functionBlock->getBuilder()->get()->CreateBr(isRefCountMatchTrueIfBlock->getBlock());
    auto pointerToRefCountPointer = isRefCountMatchTrueIfBlock->getBuilder()->get()->CreateStructGEP(sharedPtrType->getType(), function->getArg(0), sharedPtrType->getRefCounterIndex());
    auto refCountPointer = InstructionIRInjectorHelper::injectLoad(pointerType, pointerToRefCountPointer, isRefCountMatchTrueIfBlock);
    auto refCount = InstructionIRInjectorHelper::injectLoad(intType, refCountPointer, isRefCountMatchTrueIfBlock);
    auto isValueTrue = isRefCountMatchTrueIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            function->getArg(1),
            refCount
    );
    isRefCountMatchTrueIfBlock->getBuilder()->get()->CreateCondBr(isValueTrue, isRefCountMatchIfThenBlock->getBlock(), isRefCountMatchIfElseBlock->getBlock());
    isRefCountMatchIfThenBlock->addVoidReturn();
    isRefCountMatchIfElseBlock->getBuilder()->get()->CreateCall(printf, {
            irModuleNode->getModule()->get()->getGlobalVariable(AssertIRFunction::getGlobalAssertDebugRefCountMessageStringName())
    });
    isRefCountMatchIfElseBlock->getBuilder()->get()->CreateCall(printf, {
            function->getArg(2)
    });
    isRefCountMatchIfElseBlock->getBuilder()->get()->CreateCall(abort);
    isRefCountMatchIfElseBlock->addVoidReturn();
}

void AssertIRFunction::generateAssertDebugStructRefCountFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto voidType = irGenerator->getVoidType();
    auto structRefType = irGenerator->generateIRStructRefType();
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(voidType, { pointerType, intType, pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0,
                                           AssertIRFunction::getAssertDebugStructRefCountIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto abort = irModuleNode->getModule()->get()->getOrInsertFunction("abort", llvm::FunctionType::get(voidType, { }, false));
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    auto isRefCountMatchTrueIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isRefCountMatchIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto isRefCountMatchIfElseBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope());
    functionBlock->getBuilder()->get()->CreateBr(isRefCountMatchTrueIfBlock->getBlock());
    auto pointerToRefCountPointer = isRefCountMatchTrueIfBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(0), structRefType->getCounterIndex());
    auto refCountPointer = InstructionIRInjectorHelper::injectLoad(pointerType, pointerToRefCountPointer, isRefCountMatchTrueIfBlock);
    auto refCount = InstructionIRInjectorHelper::injectLoad(intType, refCountPointer, isRefCountMatchTrueIfBlock);
    auto isValueTrue = isRefCountMatchTrueIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            function->getArg(1),
            refCount
    );
    isRefCountMatchTrueIfBlock->getBuilder()->get()->CreateCondBr(isValueTrue, isRefCountMatchIfThenBlock->getBlock(), isRefCountMatchIfElseBlock->getBlock());
    isRefCountMatchIfThenBlock->addVoidReturn();
    isRefCountMatchIfElseBlock->getBuilder()->get()->CreateCall(printf, {
            irModuleNode->getModule()->get()->getGlobalVariable(AssertIRFunction::getGlobalAssertDebugStructRefCountMessageStringName())
    });
    isRefCountMatchIfElseBlock->getBuilder()->get()->CreateCall(printf, {
            function->getArg(2)
    });
    isRefCountMatchIfElseBlock->getBuilder()->get()->CreateCall(abort);
    isRefCountMatchIfElseBlock->addVoidReturn();
}

void AssertIRFunction::generateAssertDebugLambdaRefCountFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto voidType = irGenerator->getVoidType();
    auto invocableType = irGenerator->generateIRInvocableType();
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(voidType, { pointerType, intType, pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0,
                                           AssertIRFunction::getAssertDebugLambdaRefCountIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto abort = irModuleNode->getModule()->get()->getOrInsertFunction("abort", llvm::FunctionType::get(voidType, { }, false));
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);
    auto isRefCountMatchTrueIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope());
    auto isRefCountMatchIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope());
    auto isRefCountMatchIfElseBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope());
    functionBlock->getBuilder()->get()->CreateBr(isRefCountMatchTrueIfBlock->getBlock());
    auto pointerToRefCountPointer = isRefCountMatchTrueIfBlock->getBuilder()->get()->CreateStructGEP(invocableType->getType(), function->getArg(0), invocableType->getFunctionRefCounterIndex());
    auto refCountPointer = InstructionIRInjectorHelper::injectLoad(pointerType, pointerToRefCountPointer, isRefCountMatchTrueIfBlock);
    auto refCount = InstructionIRInjectorHelper::injectLoad(intType, refCountPointer, isRefCountMatchTrueIfBlock);
    auto isValueTrue = isRefCountMatchTrueIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            function->getArg(1),
            refCount
    );
    isRefCountMatchTrueIfBlock->getBuilder()->get()->CreateCondBr(isValueTrue, isRefCountMatchIfThenBlock->getBlock(), isRefCountMatchIfElseBlock->getBlock());
    isRefCountMatchIfThenBlock->addVoidReturn();
    isRefCountMatchIfElseBlock->getBuilder()->get()->CreateCall(printf, {
            irModuleNode->getModule()->get()->getGlobalVariable(AssertIRFunction::getGlobalAssertDebugLambdaRefCountMessageStringName())
    });
    isRefCountMatchIfElseBlock->getBuilder()->get()->CreateCall(printf, {
            function->getArg(2)
    });
    isRefCountMatchIfElseBlock->getBuilder()->get()->CreateCall(abort);
    isRefCountMatchIfElseBlock->addVoidReturn();
}