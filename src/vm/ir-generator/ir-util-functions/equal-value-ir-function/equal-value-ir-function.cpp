//
// Created by Johny Georges on 2025-10-13.
//

#include "equal-value-ir-function.h"
#include "../../../types/ir-type-id.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string EqualValueIRFunction::getEqualValueIRFunctionName() {
    return "jet.equal.value";
}

void EqualValueIRFunction::declareEqualValueFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generateIrPointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto functionType = llvm::FunctionType::get(irGenerator->generateBooleanType(), { pointerType->getType(), pointerType->getType(), typeValueType->getType(), typeValueType->getType() }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, EqualValueIRFunction::getEqualValueIRFunctionName(), irModuleNode->getModule()->get());
}

void EqualValueIRFunction::generateEqualValueFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
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
    auto structRefIfBlock = irGenerator->generateIfBlock(irContext, "struct.ref");
    auto structRefIfThenBlock = irGenerator->generateIfThenBlock(irContext, "struct.ref.");
    auto structIfBlock = irGenerator->generateIfBlock(irContext, "struct.");
    auto structIfThenBlock = irGenerator->generateIfThenBlock(irContext, "struct.");
    auto arrayIfBlock = irGenerator->generateIfBlock(irContext, "array.");
    auto arrayIfThenBlock = irGenerator->generateIfThenBlock(irContext, "array.");
    auto lambdaIfBlock = irGenerator->generateIfBlock(irContext, "lambda.");
    auto lambdaIfThenBlock = irGenerator->generateIfThenBlock(irContext, "lambda.");
    auto refIfBlock = irGenerator->generateIfBlock(irContext, "ref.");
    auto refIfThenBlock = irGenerator->generateIfThenBlock(irContext, "ref.");
    auto refLeftOnlyIfBlock = irGenerator->generateIfBlock(irContext, "ref.left.only");
    auto refLeftOnlyIfThenBlock = irGenerator->generateIfThenBlock(irContext, "ref.left.only");
    auto refRightOnlyIfBlock = irGenerator->generateIfBlock(irContext, "ref.right.only");
    auto refRightOnlyIfThenBlock = irGenerator->generateIfThenBlock(irContext, "ref.right.only");
    auto endBlock = irGenerator->generateIfEndBlock(irContext);
    auto leftTypeValueId = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(2), { typeValueType->getIdIndex() }, "leftValueTypeId");
    auto rightTypeValueId = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(3), { typeValueType->getIdIndex() }, "rightValueTypeId");



    functionBlock->getBuilder()->get()->CreateBr(intIfBlock->getBlock());

    auto isLeftValueTypeInt = intIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            leftTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.INT)
    );
    auto isRightValueTypeInt = intIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            rightTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.INT)
    );
    auto areBothValueTypesInt = intIfBlock->getBuilder()->get()->CreateBinOp(
            llvm::BinaryOperator::And,
            isLeftValueTypeInt,
            isRightValueTypeInt
    );
    intIfBlock->getBuilder()->get()->CreateCondBr(areBothValueTypesInt, intIfThenBlock->getBlock(), floatIfBlock->getBlock());
    auto firstIntValue = InstructionIRInjectorHelper::injectLoad(intType, function->getArg(0), intIfThenBlock);
    auto secondIntValue = InstructionIRInjectorHelper::injectLoad(intType, function->getArg(1), intIfThenBlock);
    intIfThenBlock->getBuilder()->get()->CreateRet(
        intIfThenBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            firstIntValue,
            secondIntValue
        )
    );

    auto isLeftValueTypeFloat = floatIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            leftTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.FLOAT)
    );
    auto isRightValueTypeFloat = floatIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            rightTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.FLOAT)
    );
    auto areBothValueTypesFloat = floatIfBlock->getBuilder()->get()->CreateBinOp(
            llvm::BinaryOperator::And,
            isLeftValueTypeFloat,
            isRightValueTypeFloat
    );
    floatIfBlock->getBuilder()->get()->CreateCondBr(areBothValueTypesFloat, floatIfThenBlock->getBlock(), charIfBlock->getBlock());
    auto firstFloatValue = InstructionIRInjectorHelper::injectLoad(floatType, function->getArg(0), floatIfThenBlock);
    auto secondFloatValue = InstructionIRInjectorHelper::injectLoad(floatType, function->getArg(1), floatIfThenBlock);
    floatIfThenBlock->getBuilder()->get()->CreateRet(
            floatIfThenBlock->getBuilder()->get()->CreateICmp(
                    llvm::CmpInst::Predicate::ICMP_EQ,
                    firstFloatValue,
                    secondFloatValue
            )
    );

    auto isLeftValueTypeChar = charIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            leftTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.CHAR)
    );
    auto isRightValueTypeChar = charIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            rightTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.CHAR)
    );
    auto areBothValueTypesChar = charIfBlock->getBuilder()->get()->CreateBinOp(
            llvm::BinaryOperator::And,
            isLeftValueTypeChar,
            isRightValueTypeChar
    );
    charIfBlock->getBuilder()->get()->CreateCondBr(areBothValueTypesChar, charIfThenBlock->getBlock(), boolIfBlock->getBlock());
    auto firstCharValue = InstructionIRInjectorHelper::injectLoad(charType, function->getArg(0), charIfThenBlock);
    auto secondCharValue = InstructionIRInjectorHelper::injectLoad(charType, function->getArg(1), charIfThenBlock);
    charIfThenBlock->getBuilder()->get()->CreateRet(
            charIfThenBlock->getBuilder()->get()->CreateICmp(
                    llvm::CmpInst::Predicate::ICMP_EQ,
                    firstCharValue,
                    secondCharValue
            )
    );


    auto isLeftValueTypeBool = boolIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            leftTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.BOOL)
    );
    auto isRightValueTypeBool = boolIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            rightTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.BOOL)
    );
    auto areBothValueTypesBool = boolIfBlock->getBuilder()->get()->CreateBinOp(
            llvm::BinaryOperator::And,
            isLeftValueTypeBool,
            isRightValueTypeBool
    );
    boolIfBlock->getBuilder()->get()->CreateCondBr(areBothValueTypesBool, boolIfThenBlock->getBlock(), stringIfBlock->getBlock());
    auto firstBoolValue = InstructionIRInjectorHelper::injectLoad(boolType, function->getArg(0), boolIfThenBlock);
    auto secondBoolValue = InstructionIRInjectorHelper::injectLoad(boolType, function->getArg(1), boolIfThenBlock);
    boolIfThenBlock->getBuilder()->get()->CreateRet(
            boolIfThenBlock->getBuilder()->get()->CreateICmp(
                llvm::CmpInst::Predicate::ICMP_EQ,
                firstBoolValue,
                secondBoolValue
            )
    );


    auto isLeftValueTypeString = stringIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            leftTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRING)
    );
    auto isRightValueTypeString = stringIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            rightTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRING)
    );
    auto areBothValueTypesString = stringIfBlock->getBuilder()->get()->CreateBinOp(
            llvm::BinaryOperator::And,
            isLeftValueTypeString,
            isRightValueTypeString
    );
    stringIfBlock->getBuilder()->get()->CreateCondBr(areBothValueTypesString, stringIfThenBlock->getBlock(), structRefIfBlock->getBlock());
    stringIfThenBlock->getBuilder()->get()->CreateRet(
        stringIfThenBlock->getBuilder()->get()->CreateCall(
           irModuleNode->getEqualStringFunction(),
           { function->getArg(0), function->getArg(1) }
        )
    );

    auto isLeftValueTypeStructRef = structRefIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            leftTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT_REF)
    );
    auto isRightValueTypeStructRef = structRefIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            rightTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT_REF)
    );
    auto areBothValueTypesStructRef = structRefIfBlock->getBuilder()->get()->CreateBinOp(
            llvm::BinaryOperator::And,
            isLeftValueTypeStructRef,
            isRightValueTypeStructRef
    );
    structRefIfBlock->getBuilder()->get()->CreateCondBr(areBothValueTypesStructRef, structRefIfThenBlock->getBlock(), structIfBlock->getBlock());
    structRefIfThenBlock->getBuilder()->get()->CreateRet(
            structRefIfThenBlock->getBuilder()->get()->CreateCall(
                    irContext->getIRModule()->getEqualStructRefFunction(),
                    {
                            function->getArg(0),
                            function->getArg(1),
                            function->getArg(2)
                    }
            )
    );

    auto isLeftValueTypeStruct = structIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            leftTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT)
    );
    auto isRightValueTypeStruct = structIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            rightTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT)
    );
    auto areBothValueTypesStruct = structIfBlock->getBuilder()->get()->CreateBinOp(
            llvm::BinaryOperator::And,
            isLeftValueTypeStruct,
            isRightValueTypeStruct
    );
    structIfBlock->getBuilder()->get()->CreateCondBr(areBothValueTypesStruct, structIfThenBlock->getBlock(), arrayIfBlock->getBlock());
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


    auto isLeftValueTypeArray = arrayIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            leftTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.ARRAY)
    );
    auto isRightValueTypeArray = arrayIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            rightTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.ARRAY)
    );
    auto areBothValueTypesArray = arrayIfBlock->getBuilder()->get()->CreateBinOp(
            llvm::BinaryOperator::And,
            isLeftValueTypeArray,
            isRightValueTypeArray
    );
    arrayIfBlock->getBuilder()->get()->CreateCondBr(areBothValueTypesArray, arrayIfThenBlock->getBlock(), lambdaIfBlock->getBlock());
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

    auto isLeftValueTypeLambda = lambdaIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            leftTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.LAMBDA)
    );
    auto isRightValueTypeLambda = lambdaIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            rightTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.LAMBDA)
    );
    auto areBothValueTypesLambda = lambdaIfBlock->getBuilder()->get()->CreateBinOp(
            llvm::BinaryOperator::And,
            isLeftValueTypeLambda,
            isRightValueTypeLambda
    );
    lambdaIfBlock->getBuilder()->get()->CreateCondBr(areBothValueTypesLambda, lambdaIfThenBlock->getBlock(), refIfBlock->getBlock());
    lambdaIfThenBlock->getBuilder()->get()->CreateRet(
            lambdaIfThenBlock->getBuilder()->get()->CreateCall(
                    irContext->getIRModule()->getEqualLambdaFunction()->getFunctionType(),
                    irContext->getIRModule()->getEqualLambdaFunction(),
                    {
                        function->getArg(0),
                        function->getArg(1)
                    }
            )
    );


    auto isLeftValueTypeRef = refIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            leftTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.REF)
    );
    auto isRightValueTypeRef = refIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            rightTypeValueId,
            irGenerator->generateIntConstant(IR_TYPE_ID.REF)
    );

    auto areBothValueTypesRef = refIfBlock->getBuilder()->get()->CreateBinOp(
            llvm::BinaryOperator::And,
            isLeftValueTypeRef,
            isRightValueTypeRef
    );
    refIfBlock->getBuilder()->get()->CreateCondBr(areBothValueTypesRef, refIfThenBlock->getBlock(), refLeftOnlyIfBlock->getBlock());
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



    auto isLeftOnlyValueTypeRef = refLeftOnlyIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            isLeftValueTypeRef,
            irGenerator->generateBoolean(true)
    );
    refLeftOnlyIfBlock->getBuilder()->get()->CreateCondBr(isLeftOnlyValueTypeRef, refLeftOnlyIfThenBlock->getBlock(), refRightOnlyIfBlock->getBlock());
    refLeftOnlyIfThenBlock->getBuilder()->get()->CreateRet(
            refLeftOnlyIfThenBlock->getBuilder()->get()->CreateCall(
                    irContext->getIRModule()->getEqualRefLeftOnlyFunction()->getFunctionType(),
                    irContext->getIRModule()->getEqualRefLeftOnlyFunction(),
                    {
                        function->getArg(0),
                        function->getArg(1),
                        function->getArg(2)
                    }
            )
    );

    auto isRightOnlyValueTypeRef = refRightOnlyIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            isRightValueTypeRef,
            irGenerator->generateBoolean(true)
    );
    refRightOnlyIfBlock->getBuilder()->get()->CreateCondBr(isRightOnlyValueTypeRef, refRightOnlyIfThenBlock->getBlock(), endBlock->getBlock());
    refRightOnlyIfThenBlock->getBuilder()->get()->CreateRet(
            refRightOnlyIfThenBlock->getBuilder()->get()->CreateCall(
                    irContext->getIRModule()->getEqualRefRightOnlyFunction()->getFunctionType(),
                    irContext->getIRModule()->getEqualRefRightOnlyFunction(),
                    {
                        function->getArg(0),
                        function->getArg(1),
                        function->getArg(3)
                    }
            )
    );

    endBlock->getBuilder()->get()->CreateRet(irGenerator->generateBoolean(false));
}