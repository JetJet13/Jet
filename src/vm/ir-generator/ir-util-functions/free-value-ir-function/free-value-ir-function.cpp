//
// Created by Johny Georges on 2025-04-30.
//

#include "free-value-ir-function.h"
#include "../../../types/ir-type-id.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"

std::string FreeValueIRFunction::getFreeValueIRFunctionName() {
    return "jet.free.value";
}

void FreeValueIRFunction::declareFreeValueFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateVoidType()->getType(), { pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, FreeValueIRFunction::getFreeValueIRFunctionName(), irModuleNode->getModule());
}

void FreeValueIRFunction::generateFreeValueFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto typeValueType = irGenerator->generateIrTypeValueType();

    auto function = irModuleNode->getFreeValueFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto arrayIfBlock = irGenerator->generateIfBlock(irContext, "array.");
    auto arrayIfThenBlock = irGenerator->generateIfThenBlock(irContext, "array.");
    auto pointerIfBlock = irGenerator->generateIfBlock(irContext, "pointer.");
    auto pointerIfThenBlock = irGenerator->generateIfThenBlock(irContext, "pointer.");
    auto refIfBlock = irGenerator->generateIfBlock(irContext, "ref.");
    auto refIfThenBlock = irGenerator->generateIfThenBlock(irContext, "ref.");
    auto structIfBlock = irGenerator->generateIfBlock(irContext, "struct.");
    auto structIfThenBlock = irGenerator->generateIfThenBlock(irContext, "struct.");
    auto stringIfBlock = irGenerator->generateIfBlock(irContext, "string.");
    auto stringIfThenBlock = irGenerator->generateIfThenBlock(irContext, "string.");
    auto endBlock = irGenerator->generateIfEndBlock(irContext);

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
    refIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeRef, refIfThenBlock->getBlock(), structIfBlock->getBlock());
    refIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getFreeRefFunction()->getFunctionType(),
            irContext->getIRModule()->getFreeRefFunction(),
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
    structIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeStruct, structIfThenBlock->getBlock(), stringIfBlock->getBlock());
    structIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getFreeStructFunction()->getFunctionType(),
            irContext->getIRModule()->getFreeStructFunction(),
            {
                function->getArg(0),
                function->getArg(1)
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
    structIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    stringIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());

    endBlock->addVoidReturn();
}