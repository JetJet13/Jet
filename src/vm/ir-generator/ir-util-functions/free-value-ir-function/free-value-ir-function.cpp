//
// Created by Johny Georges on 2025-04-30.
//

#include "free-value-ir-function.h"
#include "../../../types/ir-type-id.h"

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
    auto intType = irGenerator->generateIntType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto typeValueIdIndex = irGenerator->generateIntConstant(typeValueType->getIdIndex());

    auto function = irModuleNode->getFreeValueFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto arrayIfBlock = irGenerator->generateIfBlock(irContext, "array.");
    auto arrayIfThenBlock = irGenerator->generateIfThenBlock(irContext, "array.");
    auto pointerIfBlock = irGenerator->generateIfBlock(irContext, "pointer.");
    auto pointerIfThenBlock = irGenerator->generateIfThenBlock(irContext, "pointer.");
    auto structIfBlock = irGenerator->generateIfBlock(irContext, "struct.");
    auto structIfThenBlock = irGenerator->generateIfThenBlock(irContext, "struct.");
    auto endBlock = irGenerator->generateIfEndBlock(irContext);

    auto pointerToElementTypeValueId = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), function->getArg(1), { zeroIndex, typeValueIdIndex });
    auto typeValueId = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToElementTypeValueId, "valueTypeId");

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
    pointerIfBlock->getBuilder()->get()->CreateCondBr(isValueTypePointer, pointerIfThenBlock->getBlock(), structIfBlock->getBlock());
    pointerIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getFreePointerFunction()->getFunctionType(),
            irContext->getIRModule()->getFreePointerFunction(),
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
    structIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeStruct, structIfThenBlock->getBlock(), arrayIfThenBlock->getBlock());
    structIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getFreeStructFunction()->getFunctionType(),
            irContext->getIRModule()->getFreeStructFunction(),
            {
                    function->getArg(0),
                    function->getArg(1)
            }
    );

    arrayIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    pointerIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    structIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());

    endBlock->addVoidReturn();
}