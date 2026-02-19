//
// Created by Johny Georges on 2025-04-16.
//

#include "copy-value-ir-function.h"
#include "../../../types/ir-type-id.h"

std::string CopyValueIRFunction::getCopyValueIRFunctionName() {
    return "jet.copy.value";
}

void CopyValueIRFunction::declareCopyValueFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(pointerType->getType(), { pointerType->getType(), pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, CopyValueIRFunction::getCopyValueIRFunctionName(), irModuleNode->getModule()->get());
}

void CopyValueIRFunction::generateCopyValueFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto typeValueType = irGenerator->generateIrTypeValueType();

    auto function = irModuleNode->getCopyValueFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto literalIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope(), "literal.");
    auto literalIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "literal.");
    auto pointerIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope(), "pointer.");
    auto pointerIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "pointer.");
    auto refIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope(), "ref.");
    auto refIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "ref.");
    auto structRefIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope(), "struct.ref.");
    auto structRefIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "struct.ref.");
    auto structIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope(), "struct.");
    auto structIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "struct.");
    auto lambdaIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope(), "lambda.");
    auto lambdaIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "lambda.");
    auto arrayIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "array.");
    auto endBlock = irGenerator->generateIfEndBlock(irContext, functionBlock->getScope());
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
    refIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeRef, refIfThenBlock->getBlock(), structRefIfBlock->getBlock());
    refIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getCopyRefFunction()->getFunctionType(),
            irContext->getIRModule()->getCopyRefFunction(),
            {
                function->getArg(0),
                function->getArg(1),
                function->getArg(2)
            }
    );

    auto isValueTypeStructRef = structRefIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT_REF)
    );
    structRefIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeStructRef, structRefIfThenBlock->getBlock(), structIfBlock->getBlock());
    structRefIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getCopyStructRefFunction(),
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
    structIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeStruct, structIfThenBlock->getBlock(), lambdaIfBlock->getBlock());
    structIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getCopyStructFunction()->getFunctionType(),
            irContext->getIRModule()->getCopyStructFunction(),
            {
                function->getArg(0),
                function->getArg(1),
                function->getArg(2)
            }
    );

    auto isValueTypeLambda = lambdaIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.LAMBDA)
    );
    lambdaIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeLambda, lambdaIfThenBlock->getBlock(), arrayIfThenBlock->getBlock());
    lambdaIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getCopyLambdaFunction()->getFunctionType(),
            irContext->getIRModule()->getCopyLambdaFunction(),
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
    structRefIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    structIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    lambdaIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    arrayIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());

    endBlock->getBuilder()->get()->CreateRet(function->getArg(0));
}