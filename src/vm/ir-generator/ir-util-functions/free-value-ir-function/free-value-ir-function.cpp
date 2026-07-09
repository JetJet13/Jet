//
// Created by Johny Georges on 2025-04-30.
//

#include "free-value-ir-function.h"
#include "../../../types/ir-type-id.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

std::string FreeValueIRFunction::getFreeValueIRFunctionName() {
    return "jet.free.value";
}

void FreeValueIRFunction::declareFreeValueFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, FreeValueIRFunction::getFreeValueIRFunctionName(), irModuleNode->getModule()->get());
}

void FreeValueIRFunction::generateFreeValueFunction(std::shared_ptr<IRGenerator> irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto typeValueType = irGenerator->generateIrTypeValueType();

    auto function = irModuleNode->getFreeValueFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);

    auto arrayIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope(), "array.");
    auto arrayIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "array.");
    auto pointerIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope(), "pointer.");
    auto pointerIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "pointer.");
    auto refIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope(), "ref.");
    auto refIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "ref.");
    auto structRefIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope(), "struct.ref.");
    auto structRefIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "struct.ref.");
    auto structIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope(), "struct.");
    auto structIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "struct.");
    auto invocableIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope(), "invocable.");
    auto invocableIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "invocable.");
    auto stringIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope(), "string.");
    auto stringIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "string.");
    auto endBlock = irGenerator->generateIfEndBlock(irContext, functionBlock->getScope());

    DebugIRInjectorHelper::injectLog(functionBlock, "FREEING VALUE!", irGenerator->getInjector(), irModuleNode);
    auto typeValueId = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), { typeValueType->getIdIndex() });
    functionBlock->getBuilder()->get()->CreateBr(arrayIfBlock->getBlock());

    auto isValueTypeArray = arrayIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.ARRAY)
    );
    arrayIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeArray, arrayIfThenBlock->getBlock(), pointerIfBlock->getBlock());
    arrayIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getFreeArrayFunction()->getFunctionType(),
            irContext->getIRModule()->getFreeArrayFunction(),
            {
                function->getArg(0),
                function->getArg(1)
            }
    );

    auto isValueTypePointer = pointerIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.POINTER)
    );
    pointerIfBlock->getBuilder()->get()->CreateCondBr(isValueTypePointer, pointerIfThenBlock->getBlock(), refIfBlock->getBlock());
    pointerIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getFreePointerFunction()->getFunctionType(),
            irContext->getIRModule()->getFreePointerFunction(),
            {
                function->getArg(0),
                function->getArg(1)
            }
    );

    auto isValueTypeRef = refIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.REF)
    );
    refIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeRef, refIfThenBlock->getBlock(), structRefIfBlock->getBlock());
    refIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getFreeRefFunction()->getFunctionType(),
            irContext->getIRModule()->getFreeRefFunction(),
            {
                function->getArg(0),
                function->getArg(1)
            }
    );

    auto isValueTypeStructRef = structRefIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT_REF)
    );
    structRefIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeStructRef, structRefIfThenBlock->getBlock(), structIfBlock->getBlock());
    structRefIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getFreeStructRefFunction()->getFunctionType(),
            irContext->getIRModule()->getFreeStructRefFunction(),
            {
                function->getArg(0),
                function->getArg(1)
            }
    );

    auto isValueTypeStruct = structIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT)
    );
    structIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeStruct, structIfThenBlock->getBlock(), invocableIfBlock->getBlock());
    structIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getFreeStructFunction()->getFunctionType(),
            irContext->getIRModule()->getFreeStructFunction(),
            {
                function->getArg(0),
                function->getArg(1)
            }
    );

    auto isValueTypeInvocable = invocableIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.INVOCABLE)
    );
    invocableIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeInvocable, invocableIfThenBlock->getBlock(), stringIfBlock->getBlock());
    invocableIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getFreeInvocableFunction(),
            {
                function->getArg(0)
            }
    );

    auto isValueTypeString = stringIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRING)
    );
    stringIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeString, stringIfThenBlock->getBlock(), endBlock->getBlock());
    stringIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getFreeStringFunction()->getFunctionType(),
            irContext->getIRModule()->getFreeStringFunction(),
            {
                function->getArg(0)
            }
    );

    arrayIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    pointerIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    refIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    structRefIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    structIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    invocableIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    stringIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());

    DebugIRInjectorHelper::injectLog(endBlock, "DONE FREEING VALUE!", irGenerator->getInjector(), irModuleNode);
    endBlock->addVoidReturn();
}