//
// Created by Johny Georges on 2025-12-10.
//

#include "free-lambda-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

std::string FreeLambdaIRFunction::getFreeLambdaIRFunctionName() {
    return "jet.free.lambda";
}

void FreeLambdaIRFunction::declareFreeLambdaFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, FreeLambdaIRFunction::getFreeLambdaIRFunctionName(), irModuleNode->getModule()->get());
}

void FreeLambdaIRFunction::generateFreeLambdaFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto intType = irGenerator->generateIntType();
    auto irInvocableType = irGenerator->generateIRInvocableType();

    auto function = irModuleNode->getFreeLambdaFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto freeLambdaIfBlock = irGenerator->generateIfBlock(irContext);
    auto freeLambdaIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto freeLambdaEndBlock = irGenerator->generateIfEndBlock(irContext);

    auto pointerToRefCounterPointer = functionBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), function->getArg(0), irInvocableType->getFunctionRefCounterIndex());
    auto refCounterPointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToRefCounterPointer);
    auto currentRefCount = functionBlock->getBuilder()->get()->CreateLoad(intType, refCounterPointer, "currentRefCount");
    DebugIRInjectorHelper::injectLog(functionBlock, currentRefCount, irGenerator->getInjector(), irModuleNode);
    functionBlock->getBuilder()->get()->CreateBr(freeLambdaIfBlock->getBlock());

    auto isLastRef = freeLambdaIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLE,
            currentRefCount,
            irGenerator->generateIntConstant(1)
    );
    freeLambdaIfBlock->getBuilder()->get()->CreateCondBr(isLastRef, freeLambdaIfThenBlock->getBlock(), freeLambdaEndBlock->getBlock());

    auto pointerToLambdaScope = freeLambdaIfThenBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), function->getArg(0), irInvocableType->getFunctionScopeArgumentIndex());
    auto loadedLambdaScope = InstructionIRInjectorHelper::injectLoad(irInvocableType->getFunctionScopeArgumentType(), pointerToLambdaScope, freeLambdaIfThenBlock);
    auto pointerToCleanupFunction = freeLambdaIfThenBlock->getBuilder()->get()->CreateStructGEP(irInvocableType->getType(), function->getArg(0), irInvocableType->getFunctionCleanupIndex());
    auto loadedCleanupFunction = InstructionIRInjectorHelper::injectLoad(irInvocableType->getFunctionCleanupType(), pointerToCleanupFunction, freeLambdaIfThenBlock);
//    freeLambdaIfThenBlock->getBuilder()->get()->CreateCall(
//            irInvocableType->getCleanupFunctionType(),
//            loadedCleanupFunction,
//            {
//                loadedLambdaScope
//            }
//    );
//    freeLambdaIfThenBlock->getBuilder()->get()->CreateCall(
//            irModuleNode->getMallocFreeFunction(),
//            {
//                loadedLambdaScope
//            }
//    );
    freeLambdaIfThenBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFreeFunction(),
            {
                refCounterPointer
            }
    );
    DebugIRInjectorHelper::injectLog(freeLambdaIfThenBlock, "DONE FREEING LAMBDA!", irGenerator->getInjector(), irModuleNode);
    freeLambdaIfThenBlock->getBuilder()->get()->CreateBr(freeLambdaEndBlock->getBlock());

    freeLambdaEndBlock->addVoidReturn();
}