//
// Created by Johny Georges on 2026-02-24.
//

#include "free-ref-value-ir-function.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/debug-ir-injector-helper/debug-ir-injector-helper.h"
#include "../../../types/ir-type-id.h"

std::string FreeRefValueIRFunction::getFreeRefValueIRFunctionName() {
    return "jet.free.ref.value";
}

void FreeRefValueIRFunction::generateFreeRefValueFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto structRefType = irGenerator->generateIRStructRefType();
    auto functionType = llvm::FunctionType::get(irGenerator->getVoidType(), { pointerType->getType(), typeValueType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, FreeRefValueIRFunction::getFreeRefValueIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = std::make_shared<IRContext>(functionBlock, irModuleNode, context);

    auto structRefIfBlock = irGenerator->generateIfBlock(irContext, functionBlock->getScope(), "struct.ref.");
    auto structRefIfThenBlock = irGenerator->generateIfThenBlock(irContext, functionBlock->getScope(), "struct.ref.");
    auto structRefElseBlock = irGenerator->generateIfElseBlock(irContext, functionBlock->getScope());
    auto endBlock = irGenerator->generateIfEndBlock(irContext, functionBlock->getScope());

    DebugIRInjectorHelper::injectLog(functionBlock, "FREEING REF VALUE FUNCTION!", irGenerator->getInjector(), irModuleNode);
    auto typeValueId = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), { typeValueType->getIdIndex() });
    functionBlock->getBuilder()->get()->CreateBr(structRefIfBlock->getBlock());

    auto isValueTypeStructRef = structRefIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT_REF)
    );
    structRefIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeStructRef, structRefIfThenBlock->getBlock(), structRefElseBlock->getBlock());
    DebugIRInjectorHelper::injectLog(structRefIfThenBlock, "FREEING REF-VALUE STRUCT_REF!", irGenerator->getInjector(), irModuleNode);
    auto structTypePointer = structRefIfThenBlock->getBuilder()->get()->CreateExtractValue(function->getArg(1), {typeValueType->getAllocIndex() });
    auto loadedStructType = structRefIfThenBlock->getBuilder()->get()->CreateLoad(typeValueType->getType(), structTypePointer);
    auto pointerToStructPointer = structRefIfThenBlock->getBuilder()->get()->CreateStructGEP(structRefType->getType(), function->getArg(0), structRefType->getStructIndex());
    auto structPointer = structRefIfThenBlock->getBuilder()->get()->CreateLoad(pointerType->getType(), pointerToStructPointer);
    structRefIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getFreeStructFunction(),
            { structPointer, loadedStructType }
    );

    structRefElseBlock->getBuilder()->get()->CreateCall(
        irContext->getIRModule()->getFreeValueFunction(),
        {
            function->getArg(0),
            function->getArg(1)
        }
    );

    structRefIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    structRefElseBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    endBlock->addVoidReturn();
}