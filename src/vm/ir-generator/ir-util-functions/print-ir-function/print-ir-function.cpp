//
// Created by Johny Georges on 2024-10-12.
//

#include "print-ir-function.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/IR/IntrinsicInst.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../../types/ir-type-id.h"

std::string PrintIRFunction::getPrintIRFunctionName() {
    return "jet.print";
}

std::string PrintIRFunction::getPrintIntIRFunctionName() {
    return "jet.print.int";
}

std::string PrintIRFunction::getPrintFloatIRFunctionName() {
    return "jet.print.float";
}

std::string PrintIRFunction::getPrintCharIRFunctionName() {
    return "jet.print.char";
}

std::string PrintIRFunction::getPrintBoolIRFunctionName() {
    return "jet.print.bool";
}

std::string PrintIRFunction::getPrintStringIRFunctionName() {
    return "jet.print.string";
}

void PrintIRFunction::generatePrintFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto floatType = irGenerator->generateFloatType();
    auto charType = irGenerator->generateCharType();
    auto boolType = irGenerator->generateBooleanType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto functionType = llvm::FunctionType::get(voidType->getType(), { pointerType }, true);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    // todo: setup for loop for print! extract num of var args first.
    auto vaStart = irModuleNode->getModule()->getOrInsertFunction("llvm.va_start", llvm::FunctionType::get(voidType->getType(), { pointerIntType->getPointerTo() }, false));
    auto vaEnd = irModuleNode->getModule()->getOrInsertFunction("llvm.va_end", llvm::FunctionType::get(voidType->getType(), { pointerIntType->getPointerTo() }, false));
    auto typeValueArrayArgument = function->getArg(0);
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());
    auto pointerToNumElements = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), typeValueArrayArgument, { zeroIndex, numElementsIndex });
    auto numElements = functionBlock->getBuilder()->get()->CreateLoad(intType, pointerToNumElements);
    auto pointerToTypeValuesArrayPointer = functionBlock->getBuilder()->get()->CreateInBoundsGEP(arrayPointerType->getType(), typeValueArrayArgument, { zeroIndex, allocIndex });
    auto typeValueArrayPointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType, pointerToTypeValuesArrayPointer);
    auto vaList = functionBlock->getBuilder()->get()->CreateAlloca(pointerIntType);
    functionBlock->getBuilder()->get()->CreateCall(vaStart, { vaList });
    auto forLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext);
    auto forLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext);
    auto forLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext);
    auto intIfBlock = irGenerator->generateIfBlock(irContext, "int.");
    auto intIfThenBlock = irGenerator->generateIfThenBlock(irContext, "int.");
    auto floatIfBlock = irGenerator->generateIfBlock(irContext, "float.");
    auto floatIfThenBlock = irGenerator->generateIfThenBlock(irContext, "float.");
    auto charIfBlock = irGenerator->generateIfBlock(irContext, "char.");
    auto charIfThenBlock = irGenerator->generateIfThenBlock(irContext, "char.");
    auto boolIfBlock = irGenerator->generateIfBlock(irContext, "bool.");
    auto boolIfThenBlock = irGenerator->generateIfThenBlock(irContext, "bool.");
    auto stringIfThenBlock = irGenerator->generateIfThenBlock(irContext, "string.");
    auto endBlock = irGenerator->generateIfEndBlock(irContext);

    // for loop prep
    auto forLoopIndex = functionBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "forLoopIndex");
    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), forLoopIndex);
    functionBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());

    // for loop condition
    auto forLoopIndexValue = forLoopConditionBlock->getBuilder()->get()->CreateLoad(intType, forLoopIndex);
    auto forLoopIndexLessThanNumElements = forLoopConditionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            forLoopIndexValue,
            numElements
    );
    forLoopConditionBlock->getBuilder()->get()->CreateCondBr(
            forLoopIndexLessThanNumElements,
            forLoopBodyBlock->getBlock(),
            forLoopEndBlock->getBlock()
    );

    // for loop body
    auto forLoopBody = forLoopBodyBlock->getBuilder()->get();
    auto pointerToTypeValueAtIndex = forLoopBody->CreateInBoundsGEP(typeValueType->getType(), typeValueArrayPointer, { forLoopIndexValue });
    auto typeValueAtIndex = forLoopBody->CreateLoad(typeValueType->getType(), pointerToTypeValueAtIndex);
    auto typeValueIdAtIndex = forLoopBody->CreateExtractValue(typeValueAtIndex, typeValueType->getIdIndex());
    forLoopBody->CreateBr(intIfBlock->getBlock());

    auto isValueTypeInteger = intIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.INT)
    );
    intIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeInteger, intIfThenBlock->getBlock(), floatIfBlock->getBlock());
    auto intVarArg = intIfThenBlock->getBuilder()->get()->CreateVAArg(vaList, pointerType);
    intIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintIntFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintIntFunction(),
            { intVarArg }
    );

    auto isValueTypePointer = floatIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.FLOAT)
    );
    floatIfBlock->getBuilder()->get()->CreateCondBr(isValueTypePointer, floatIfThenBlock->getBlock(), charIfBlock->getBlock());
    auto floatVarArg = floatIfThenBlock->getBuilder()->get()->CreateVAArg(vaList, floatType);
    floatIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintFloatFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintFloatFunction(),
            { floatVarArg }
    );

    auto isValueTypeRef = charIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.CHAR)
    );
    charIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeRef, charIfThenBlock->getBlock(), boolIfBlock->getBlock());
    auto charVarArg = charIfThenBlock->getBuilder()->get()->CreateVAArg(vaList, charType);
    charIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintCharFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintCharFunction(),
            { charVarArg }
    );

    auto isValueTypeBool = boolIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.BOOL)
    );
    boolIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeBool, boolIfThenBlock->getBlock(), stringIfThenBlock->getBlock());
    auto boolVarArg = boolIfThenBlock->getBuilder()->get()->CreateVAArg(vaList, boolType);
    boolIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintBoolFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintBoolFunction(),
            { boolVarArg }
    );

    auto stringVarArg = stringIfThenBlock->getBuilder()->get()->CreateVAArg(vaList, pointerType);
    stringIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintStringFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintStringFunction(),
            { stringVarArg }
    );

    intIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    floatIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    charIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    boolIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    stringIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());

    // end block for if/else chain
    auto newForLoopIndexValue = endBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, forLoopIndexValue, irGenerator->generateIntConstant(1));
    endBlock->getBuilder()->get()->CreateStore(newForLoopIndexValue, forLoopIndex);
    endBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());

    forLoopEndBlock->getBuilder()->get()->CreateCall(vaEnd, { vaList });
    forLoopEndBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintIntFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(intType, { pointerType }, true));
    auto functionType = llvm::FunctionType::get(voidType->getType(), { intType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintIntIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto formatStringAllocation = PrintIRFunction::generateStringAllocation(
            functionBlock,
            { '%', 'd' },
            irGenerator,
            context,
            irModuleNode
    );
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, function->getArg(0) });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintFloatFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto floatType = irGenerator->generateFloatType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(intType, { pointerType }, true));
    auto functionType = llvm::FunctionType::get(voidType->getType(), { floatType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintFloatIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto formatStringAllocation = PrintIRFunction::generateStringAllocation(
            functionBlock,
            { '%', 'f' },
            irGenerator,
            context,
            irModuleNode
    );
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, function->getArg(0) });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintCharFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto charType = irGenerator->generateCharType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(intType, { pointerType }, true));
    auto functionType = llvm::FunctionType::get(voidType->getType(), { charType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintCharIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto formatStringAllocation = PrintIRFunction::generateStringAllocation(
            functionBlock,
            { '%', 'c' },
            irGenerator,
            context,
            irModuleNode
    );
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, function->getArg(0) });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintBoolFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto boolType = irGenerator->generateBooleanType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(intType, { pointerType }, true));
    auto functionType = llvm::FunctionType::get(voidType->getType(), { boolType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintBoolIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto printTrueIfBlock = irGenerator->generateIfBlock(irContext);
    auto printTrueIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto elseBlock = irGenerator->generateIfElseBlock(irContext);
    auto endBlock = irGenerator->generateIfEndBlock(irContext);


    auto formatStringAllocation = PrintIRFunction::generateStringAllocation(
            functionBlock,
            { '%', 's' },
            irGenerator,
            context,
            irModuleNode
    );

    functionBlock->getBuilder()->get()->CreateBr(printTrueIfBlock->getBlock());

    auto isValueTrue = printTrueIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            function->getArg(0),
            irGenerator->generateBoolean(true)
    );
    printTrueIfBlock->getBuilder()->get()->CreateCondBr(isValueTrue, printTrueIfThenBlock->getBlock(), elseBlock->getBlock());

    // true (print true)
    auto trueStringAllocation = PrintIRFunction::generateStringAllocation(
            printTrueIfThenBlock,
            { 't', 'r', 'u', 'e' },
            irGenerator,
            context,
            irModuleNode
    );
    printTrueIfThenBlock->getBuilder()->get()->CreateCall(
        printf,
        { formatStringAllocation, trueStringAllocation }
    );
    printTrueIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());

    // else (print false)
    auto falseStringAllocation = PrintIRFunction::generateStringAllocation(
            elseBlock,
            { 'f', 'a', 'l', 's', 'e' },
            irGenerator,
            context,
            irModuleNode
    );
    elseBlock->getBuilder()->get()->CreateCall(
        printf,
        { formatStringAllocation, falseStringAllocation }
    );
    elseBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());

    endBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintStringFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto charType = new IRType(irGenerator->generateCharType());
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(charType);
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(intType, { pointerType }, true));
    auto functionType = llvm::FunctionType::get(voidType->getType(), { arrayPointerType->getType() }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintStringIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto formatStringAllocation = PrintIRFunction::generateStringAllocation(
            functionBlock,
            { '%', 's' },
            irGenerator,
            context,
            irModuleNode
    );
    auto stringAllocation = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(0), { arrayPointerType->getAllocIndex() });
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, stringAllocation });
    functionBlock->addVoidReturn();
}

llvm::AllocaInst* PrintIRFunction::generateStringAllocation(IRBlockNode* irBlock, std::vector<char> formatString, IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    formatString.push_back('\0');
    auto chars = std::vector<llvm::Constant*>();
    for (auto character : formatString) {
        chars.push_back(irGenerator->generateChar(character));
    }
    auto stringArray = llvm::ConstantArray::get(
            llvm::ArrayType::get(irGenerator->generateCharType(), chars.size()),
            llvm::ArrayRef(chars)
    );
    auto stringAllocation = irBlock->getBuilder()->get()->CreateAlloca(stringArray->getType());
    irBlock->getBuilder()->get()->CreateStore(stringArray, stringAllocation);
    return stringAllocation;
}