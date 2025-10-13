//
// Created by Johny Georges on 2025-10-13.
//

#include "equal-value-ir-function.h"
#include "../../../types/ir-type-id.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string EqualValueIRFunction::getEqualValueIRFunctionName() {
    return "jet.equal.value";
}

void EqualValueIRFunction::declareEqualValueFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateBooleanType(), { pointerType->getType(), pointerType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, EqualValueIRFunction::getEqualValueIRFunctionName(), irModuleNode->getModule());
}

void EqualValueIRFunction::generateEqualValueFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto floatType = irGenerator->generateFloatType();
    auto charType = irGenerator->generateCharType();
    auto boolType = irGenerator->generateBooleanType();
    auto typeValueType = irGenerator->generateIrTypeValueType();

    auto function = irModuleNode->getEqualValueFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);

    auto intIfBlock = irGenerator->generateIfBlock(irContext, "int.");
    auto intIfThenBlock = irGenerator->generateIfThenBlock(irContext, "int.");
    auto floatIfBlock = irGenerator->generateIfBlock(irContext, "float.");
    auto floatIfThenBlock = irGenerator->generateIfThenBlock(irContext, "float.");
    auto charIfBlock = irGenerator->generateIfBlock(irContext, "char.");
    auto charIfThenBlock = irGenerator->generateIfThenBlock(irContext, "char.");
    auto boolIfBlock = irGenerator->generateIfBlock(irContext, "bool.");
    auto boolIfThenBlock = irGenerator->generateIfThenBlock(irContext, "bool.");
    auto stringIfBlock = irGenerator->generateIfBlock(irContext, "string.");
    auto stringIfThenBlock = irGenerator->generateIfThenBlock(irContext, "string.");
    auto refIfBlock = irGenerator->generateIfBlock(irContext, "ref.");
    auto refIfThenBlock = irGenerator->generateIfThenBlock(irContext, "ref.");
    auto structIfBlock = irGenerator->generateIfBlock(irContext, "struct.");
    auto structIfThenBlock = irGenerator->generateIfThenBlock(irContext, "struct.");
    auto arrayIfBlock = irGenerator->generateIfBlock(irContext, "array.");
    auto arrayIfThenBlock = irGenerator->generateIfThenBlock(irContext, "array.");
    auto endBlock = irGenerator->generateIfEndBlock(irContext);
    auto typeValueId = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getIdIndex() }, "valueTypeId");

    functionBlock->getBuilder()->get()->CreateBr(intIfBlock->getBlock());

    auto isValueTypeInt = intIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.INT)
    );
    intIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeInt, intIfThenBlock->getBlock(), floatIfBlock->getBlock());
    auto firstIntValue = InstructionIRInjectorHelper::injectLoad(intType, function->getArg(0), intIfThenBlock);
    auto secondIntValue = InstructionIRInjectorHelper::injectLoad(intType, function->getArg(1), intIfThenBlock);
    intIfThenBlock->getBuilder()->get()->CreateRet(
        intIfThenBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            firstIntValue,
            secondIntValue
        )
    );

    auto isValueTypeFloat = floatIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.FLOAT)
    );
    floatIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeFloat, floatIfThenBlock->getBlock(), charIfBlock->getBlock());
    auto firstFloatValue = InstructionIRInjectorHelper::injectLoad(floatType, function->getArg(0), floatIfThenBlock);
    auto secondFloatValue = InstructionIRInjectorHelper::injectLoad(floatType, function->getArg(1), floatIfThenBlock);
    floatIfThenBlock->getBuilder()->get()->CreateRet(
            floatIfThenBlock->getBuilder()->get()->CreateICmp(
                    llvm::CmpInst::Predicate::ICMP_EQ,
                    firstFloatValue,
                    secondFloatValue
            )
    );

    auto isValueTypeChar = charIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.CHAR)
    );
    charIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeChar, charIfThenBlock->getBlock(), boolIfBlock->getBlock());
    auto firstCharValue = InstructionIRInjectorHelper::injectLoad(charType, function->getArg(0), charIfThenBlock);
    auto secondCharValue = InstructionIRInjectorHelper::injectLoad(charType, function->getArg(1), charIfThenBlock);
    charIfThenBlock->getBuilder()->get()->CreateRet(
            charIfThenBlock->getBuilder()->get()->CreateICmp(
                    llvm::CmpInst::Predicate::ICMP_EQ,
                    firstCharValue,
                    secondCharValue
            )
    );

    auto isValueTypeBool = boolIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.BOOL)
    );
    boolIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeBool, boolIfThenBlock->getBlock(), stringIfBlock->getBlock());
    auto firstBoolValue = InstructionIRInjectorHelper::injectLoad(boolType, function->getArg(0), boolIfThenBlock);
    auto secondBoolValue = InstructionIRInjectorHelper::injectLoad(boolType, function->getArg(1), boolIfThenBlock);
    boolIfThenBlock->getBuilder()->get()->CreateRet(
            boolIfThenBlock->getBuilder()->get()->CreateICmp(
                llvm::CmpInst::Predicate::ICMP_EQ,
                firstBoolValue,
                secondBoolValue
            )
    );

    auto isValueTypeString = stringIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRING)
    );
    stringIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeString, stringIfThenBlock->getBlock(), refIfBlock->getBlock());
    stringIfThenBlock->getBuilder()->get()->CreateRet(
        stringIfThenBlock->getBuilder()->get()->CreateCall(
           irModuleNode->getEqualStringFunction(),
           { function->getArg(0), function->getArg(1) }
        )
    );

    auto isValueTypeRef = refIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.REF)
    );
    refIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeRef, refIfThenBlock->getBlock(), structIfBlock->getBlock());
    refIfThenBlock->getBuilder()->get()->CreateRet(
        refIfThenBlock->getBuilder()->get()->CreateCall(
                irContext->getIRModule()->getEqualRefFunction()->getFunctionType(),
                irContext->getIRModule()->getEqualRefFunction(),
                {
                    function->getArg(0),
                    function->getArg(1),
                    function->getArg(2)
                }
        )
    );

    auto isValueTypeStruct = structIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT)
    );
    structIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeStruct, structIfThenBlock->getBlock(), arrayIfBlock->getBlock());
    structIfThenBlock->getBuilder()->get()->CreateRet(
        structIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getEqualStructFunction()->getFunctionType(),
            irContext->getIRModule()->getEqualStructFunction(),
            {
                function->getArg(0),
                function->getArg(1),
                function->getArg(2)
            }
        )
    );


    auto isValueTypeArray = arrayIfBlock->getBuilder()->get()->CreateICmp(
        llvm::CmpInst::Predicate::ICMP_EQ,
        typeValueId,
        irGenerator->generateIntConstant(IR_TYPE_ID.ARRAY)
    );
    arrayIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeArray, arrayIfThenBlock->getBlock(), endBlock->getBlock());
    arrayIfThenBlock->getBuilder()->get()->CreateRet(
        arrayIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getEqualArrayFunction()->getFunctionType(),
            irContext->getIRModule()->getEqualArrayFunction(),
            {
                function->getArg(0),
                function->getArg(1),
                function->getArg(2)
            }
        )
    );

    endBlock->getBuilder()->get()->CreateRet(irGenerator->generateBoolean(false));
}