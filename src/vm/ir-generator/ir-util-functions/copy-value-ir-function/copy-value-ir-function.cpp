//
// Created by Johny Georges on 2025-04-16.
//

#include "copy-value-ir-function.h"
#include "../../../types/ir-type-id.h"

std::string CopyValueIRFunction::getCopyValueIRFunctionName() {
    return "jet.copy.value";
}

void CopyValueIRFunction::declareCopyValueFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(), { pointerType->getType(), pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, CopyValueIRFunction::getCopyValueIRFunctionName(), irModuleNode->getModule());
}

void CopyValueIRFunction::generateCopyValueFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto typeValueType = irGenerator->generateIrTypeValueType();

    auto function = irModuleNode->getCopyValueFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto literalIfBlock = irGenerator->generateIfBlock(irContext, "literal.");
    auto literalIfThenBlock = irGenerator->generateIfThenBlock(irContext, "literal.");
    auto pointerIfBlock = irGenerator->generateIfBlock(irContext, "pointer.");
    auto pointerIfThenBlock = irGenerator->generateIfThenBlock(irContext, "pointer.");
    auto refIfBlock = irGenerator->generateIfBlock(irContext, "ref.");
    auto refIfThenBlock = irGenerator->generateIfThenBlock(irContext, "ref.");
    auto structIfBlock = irGenerator->generateIfBlock(irContext, "struct.");
    auto structIfThenBlock = irGenerator->generateIfThenBlock(irContext, "struct.");
    auto arrayIfThenBlock = irGenerator->generateIfThenBlock(irContext, "array.");
    auto endBlock = irGenerator->generateIfEndBlock(irContext);
    auto typeSizeInBytes = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getSizeInBytesIndex() }, "valueTypeSizeInBytes");
    auto typeValueId = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getIdIndex() }, "valueTypeId");

    functionBlock->getBuilder()->get()->CreateBr(literalIfBlock->getBlock());

    auto isValueTypeLiteral = literalIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            typeValueId,
            irGenerator->generateIntConstant(5)
    );
    literalIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeLiteral, literalIfThenBlock->getBlock(), pointerIfBlock->getBlock());
    literalIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getMemcpyFunction()->getFunctionType(),
            irContext->getIRModule()->getMemcpyFunction(),
            {
                function->getArg(0),
                function->getArg(1),
                typeSizeInBytes
            }
    );

    auto isValueTypePointer = pointerIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.POINTER)
    );
    pointerIfBlock->getBuilder()->get()->CreateCondBr(isValueTypePointer, pointerIfThenBlock->getBlock(), refIfBlock->getBlock());
    pointerIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getCopyPointerFunction()->getFunctionType(),
            irContext->getIRModule()->getCopyPointerFunction(),
            {
                function->getArg(0),
                function->getArg(1),
                function->getArg(2)
            }
    );

    auto isValueTypeRef = refIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.REF)
    );
    refIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeRef, refIfThenBlock->getBlock(), structIfBlock->getBlock());
    refIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getCopyRefFunction()->getFunctionType(),
            irContext->getIRModule()->getCopyRefFunction(),
            {
                function->getArg(0),
                function->getArg(1),
                function->getArg(2)
            }
    );

    auto isValueTypeStruct = structIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT)
    );
    structIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeStruct, structIfThenBlock->getBlock(), arrayIfThenBlock->getBlock());
    structIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getCopyStructFunction()->getFunctionType(),
            irContext->getIRModule()->getCopyStructFunction(),
            {
                function->getArg(0),
                function->getArg(1),
                function->getArg(2)
            }
    );

    arrayIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getCopyArrayFunction()->getFunctionType(),
            irContext->getIRModule()->getCopyArrayFunction(),
            {
                function->getArg(0),
                function->getArg(1),
                function->getArg(2)
            }
    );

    literalIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    pointerIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    refIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    structIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    arrayIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());

    endBlock->getBuilder()->get()->CreateRet(function->getArg(0));
}