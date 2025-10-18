//
// Created by Johny Georges on 2024-10-12.
//

#include "print-ir-function.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/IR/IntrinsicInst.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"
#include "../../../types/ir-type-id.h"
#include "../../../ir-injector/ir-injector-strategies/ir-injector-helpers/instruction-ir-injector-helper/instruction-ir-injector-helper.h"

std::string PrintIRFunction::getGlobalIntFormatStringName() {
    return "jet.print.int.format.string";
}

std::string PrintIRFunction::getGlobalFloatFormatStringName() {
    return "jet.print.float.format.string";
}

std::string PrintIRFunction::getGlobalCharFormatStringName() {
    return "jet.print.char.format.string";
}

std::string PrintIRFunction::getGlobalTrueFormatStringName() {
    return "jet.print.true.format.string";
}

std::string PrintIRFunction::getGlobalFalseFormatStringName() {
    return "jet.print.false.format.string";
}

std::string PrintIRFunction::getGlobalStringFormatStringName() {
    return "jet.print.string.format.string";
}

std::string PrintIRFunction::getGlobalPointerFormatStringName() {
    return "jet.print.pointer.format.string";
}

std::string PrintIRFunction::getGlobalRefStartFormatStringName() {
    return "jet.print.ref.start.format.string";
}

std::string PrintIRFunction::getGlobalRefEndFormatStringName() {
    return "jet.print.ref.end.format.string";
}

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

std::string PrintIRFunction::getPrintRefIRFunctionName() {
    return "jet.print.ref";
}

std::string PrintIRFunction::getPrintWhitespaceIRFunctionName() {
    return "jet.print.whitespace";
}

std::string PrintIRFunction::getPrintNewLineIRFunctionName() {
    return "jet.print.new.line";
}

std::string PrintIRFunction::getPrintDebugMarkerIRFunctionName() {
    return "jet.print.debug.marker";
}

std::string PrintIRFunction::getPrintDebugPointerIRFunctionName() {
    return "jet.print.debug.pointer";
}

std::string PrintIRFunction::getPrintDebugStringIRFunctionName() {
    return "jet.print.debug.string";
}

void PrintIRFunction::declarePrintDebugMarkerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(voidType->getType(), { intType }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintDebugMarkerIRFunctionName(), irModuleNode->getModule());
}

void PrintIRFunction::declarePrintDebugPointerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(voidType->getType(), { pointerType }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintDebugPointerIRFunctionName(), irModuleNode->getModule());
}

void PrintIRFunction::declarePrintDebugStringFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto charType = new IRType(irGenerator->generateCharType());
    auto rawStringType = irGenerator->generateIRArrayType(charType, 1);
    auto functionType = llvm::FunctionType::get(voidType->getType(), { pointerType }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintDebugStringIRFunctionName(), irModuleNode->getModule());
}

void PrintIRFunction::declarePrintWhitespaceFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(voidType->getType(), {}, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintWhitespaceIRFunctionName(), irModuleNode->getModule());
}

void PrintIRFunction::declarePrintNewLineFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(voidType->getType(), {}, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintNewLineIRFunctionName(), irModuleNode->getModule());
}

void PrintIRFunction::generatePrintGlobals(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intFormatString = PrintIRFunction::generateStringAllocation({ '%', 'l', 'd' }, irGenerator, context, irModuleNode);
    new llvm::GlobalVariable(
            *irModuleNode->getModule(),
            intFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            intFormatString,
            PrintIRFunction::getGlobalIntFormatStringName()
    );
    auto floatFormatString = PrintIRFunction::generateStringAllocation({ '%', 'f' }, irGenerator, context, irModuleNode);
    new llvm::GlobalVariable(
            *irModuleNode->getModule(),
            floatFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            floatFormatString,
            PrintIRFunction::getGlobalFloatFormatStringName()
    );
    auto charFormatString = PrintIRFunction::generateStringAllocation({ '%', 'c' }, irGenerator, context, irModuleNode);
    new llvm::GlobalVariable(
            *irModuleNode->getModule(),
            charFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            charFormatString,
            PrintIRFunction::getGlobalCharFormatStringName()
    );
    auto trueFormatString = PrintIRFunction::generateStringAllocation({ 't', 'r', 'u', 'e' }, irGenerator, context, irModuleNode);
    new llvm::GlobalVariable(
            *irModuleNode->getModule(),
            trueFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            trueFormatString,
            PrintIRFunction::getGlobalTrueFormatStringName()
    );
    auto falseFormatString = PrintIRFunction::generateStringAllocation({ 'f', 'a', 'l', 's', 'e' }, irGenerator, context, irModuleNode);
    new llvm::GlobalVariable(
            *irModuleNode->getModule(),
            falseFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            falseFormatString,
            PrintIRFunction::getGlobalFalseFormatStringName()
    );
    auto stringFormatString = PrintIRFunction::generateStringAllocation({ '%', 's' }, irGenerator, context, irModuleNode);
    new llvm::GlobalVariable(
            *irModuleNode->getModule(),
            stringFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            stringFormatString,
            PrintIRFunction::getGlobalStringFormatStringName()
    );
    auto pointerFormatString = PrintIRFunction::generateStringAllocation({ '%', 'p', ' ' }, irGenerator, context, irModuleNode);
    new llvm::GlobalVariable(
            *irModuleNode->getModule(),
            pointerFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            pointerFormatString,
            PrintIRFunction::getGlobalPointerFormatStringName()
    );
    auto refStartFormatString = PrintIRFunction::generateStringAllocation({ 'r', 'e', 'f', '<' }, irGenerator, context, irModuleNode);
    new llvm::GlobalVariable(
            *irModuleNode->getModule(),
            refStartFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            refStartFormatString,
            PrintIRFunction::getGlobalRefStartFormatStringName()
    );
    auto refEndFormatString = PrintIRFunction::generateStringAllocation({ '>' }, irGenerator, context, irModuleNode);
    new llvm::GlobalVariable(
            *irModuleNode->getModule(),
            refEndFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            refEndFormatString,
            PrintIRFunction::getGlobalRefEndFormatStringName()
    );
}

void PrintIRFunction::generatePrintFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto irPointerType = irGenerator->generateIrPointerType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto intIrType = new IRType(intType);
    auto charType = irGenerator->generateCharType();
    auto floatType = irGenerator->generateFloatType();
    auto boolType = irGenerator->generateBooleanType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(irGenerator->generateVoidType());
    auto functionType = llvm::FunctionType::get(voidType->getType(), { arrayPointerType->getType() }, true);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto vaStart = irModuleNode->getModule()->getOrInsertFunction("llvm.va_start", llvm::FunctionType::get(voidType->getType(), { pointerIntType->getPointerTo() }, false));
    auto vaEnd = irModuleNode->getModule()->getOrInsertFunction("llvm.va_end", llvm::FunctionType::get(voidType->getType(), { pointerIntType->getPointerTo() }, false));
    auto typeValueArrayArgument = function->getArg(0);
    auto zero = irGenerator->generateIntConstant(0);
    auto numElementsIndex = irGenerator->generateIntConstant(arrayPointerType->getNumElementsIndex());
    auto allocIndex = irGenerator->generateIntConstant(arrayPointerType->getAllocIndex());
    auto forLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext);
    auto forLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext);
    auto forLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext);
    auto addWhitespaceIfBlock = irGenerator->generateIfBlock(irContext, "whitespace.");
    auto addWhitespaceIfThenBlock = irGenerator->generateIfThenBlock(irContext, "whitespace.");
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
    auto endBlock = irGenerator->generateIfEndBlock(irContext);

    // for loop prep
    auto numElements = functionBlock->getBuilder()->get()->CreateExtractValue(typeValueArrayArgument, { arrayPointerType->getNumElementsIndex() });

    auto typeValueArrayPointer = functionBlock->getBuilder()->get()->CreateExtractValue(typeValueArrayArgument, { arrayPointerType->getAllocIndex() });
    auto vaList = functionBlock->getBuilder()->get()->CreateAlloca(pointerType, nullptr, "vaList");
    auto varArgAlloc = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { irGenerator->generateInt64Constant(intIrType->getSizeInBytes()) }
    );
    auto forLoopIndex = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            { irGenerator->generateInt64Constant(intIrType->getSizeInBytes()) }
    );
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), forLoopIndex, functionBlock);
//    functionBlock->getBuilder()->get()->CreateStore(irGenerator->generateIntConstant(0), forLoopIndex);
    functionBlock->getBuilder()->get()->CreateCall(vaStart, { vaList });
    functionBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());
    // for loop condition
    auto forLoopIndexValue = InstructionIRInjectorHelper::injectLoad(intType, forLoopIndex, forLoopConditionBlock);
//    auto forLoopIndexValue = forLoopConditionBlock->getBuilder()->get()->CreateLoad(intType, forLoopIndex);
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
    auto typeValueAtIndex = InstructionIRInjectorHelper::injectLoad(typeValueType->getType(), pointerToTypeValueAtIndex, forLoopBodyBlock, typeValueType);
    auto typeValueIdAtIndex = forLoopBody->CreateExtractValue(typeValueAtIndex, typeValueType->getIdIndex());
    auto varArg = forLoopBody->CreateVAArg(vaList, pointerType);
    InstructionIRInjectorHelper::injectStore(varArg, varArgAlloc, forLoopBodyBlock);

    forLoopBody->CreateBr(addWhitespaceIfBlock->getBlock());
    auto forLoopIndexGreaterThenZero = addWhitespaceIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SGT,
            forLoopIndexValue,
            zero
    );
    addWhitespaceIfBlock->getBuilder()->get()->CreateCondBr(
            forLoopIndexGreaterThenZero,
            addWhitespaceIfThenBlock->getBlock(),
            intIfBlock->getBlock()
    );
    addWhitespaceIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintWhitespaceFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintWhitespaceFunction()
    );
    addWhitespaceIfThenBlock->getBuilder()->get()->CreateBr(intIfBlock->getBlock());

    auto isValueTypeInteger = intIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.INT)
    );
    intIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeInteger, intIfThenBlock->getBlock(), floatIfBlock->getBlock());
    intIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintIntFunction(),
            { varArgAlloc }
    );

    auto isValueTypeFloat = floatIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.FLOAT)
    );
    floatIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeFloat, floatIfThenBlock->getBlock(), charIfBlock->getBlock());
    floatIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintFloatFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintFloatFunction(),
            { varArgAlloc }
    );

    auto isValueTypeChar = charIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.CHAR)
    );
    charIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeChar, charIfThenBlock->getBlock(), boolIfBlock->getBlock());
    charIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintCharFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintCharFunction(),
            { varArgAlloc }
    );

    auto isValueTypeBool = boolIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.BOOL)
    );
    boolIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeBool, boolIfThenBlock->getBlock(), stringIfBlock->getBlock());
    boolIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintBoolFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintBoolFunction(),
            { varArgAlloc }
    );

    auto isValueTypeString = stringIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRING)
    );
    stringIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeString, stringIfThenBlock->getBlock(), refIfBlock->getBlock());
    stringIfThenBlock->getBuilder()->get()->CreateCall(
        irContext->getIRModule()->getPrintStringFunction()->getFunctionType(),
        irContext->getIRModule()->getPrintStringFunction(),
        { varArgAlloc }
    );

    auto isValueTypeRef = refIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.REF)
    );
    refIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeRef, refIfThenBlock->getBlock(), endBlock->getBlock());
    refIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintRefFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintRefFunction(),
            { varArgAlloc, typeValueArrayPointer, forLoopIndex }
    );

    intIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    floatIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    charIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    boolIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    stringIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    refIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());

    // end block for if/else chain
    auto newForLoopIndexValue = endBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, forLoopIndexValue, irGenerator->generateIntConstant(1));
    InstructionIRInjectorHelper::injectStore(newForLoopIndexValue, forLoopIndex, endBlock);
//    endBlock->getBuilder()->get()->CreateStore(newForLoopIndexValue, forLoopIndex);
    endBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());

    forLoopEndBlock->getBuilder()->get()->CreateCall(vaEnd, { vaList });
    forLoopEndBlock->getBuilder()->get()->CreateCall(irModuleNode->getMallocFreeFunction(), { varArgAlloc });
    forLoopEndBlock->getBuilder()->get()->CreateCall(irModuleNode->getMallocFreeFunction(), { forLoopIndex });
    forLoopEndBlock->getBuilder()->get()->CreateCall(
        irContext->getIRModule()->getPrintNewLineFunction()->getFunctionType(),
        irContext->getIRModule()->getPrintNewLineFunction()
    );
    forLoopEndBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintIntFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto functionType = llvm::FunctionType::get(voidType->getType(), { pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintIntIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(pointerType, function->getArg(0), functionBlock);
//    auto loadedPointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType, function->getArg(0));
    auto loadedInt = InstructionIRInjectorHelper::injectLoad(intType, loadedPointer, functionBlock);
//    auto loadedInt = functionBlock->getBuilder()->get()->CreateLoad(intType, loadedPointer);
    auto formatStringAllocation = irModuleNode->getModule()->getGlobalVariable(PrintIRFunction::getGlobalIntFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, loadedInt });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintFloatFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto floatType = irGenerator->generateFloatType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto functionType = llvm::FunctionType::get(voidType->getType(), { pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintFloatIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
//    auto loadedPointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType, function->getArg(0));
//    auto floatValue = functionBlock->getBuilder()->get()->CreateLoad(floatType, loadedPointer);
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(pointerType, function->getArg(0), functionBlock);
    auto floatValue = InstructionIRInjectorHelper::injectLoad(floatType, loadedPointer, functionBlock);
    auto doubleCastValue = functionBlock->getBuilder()->get()->CreateFPExt(floatValue, irGenerator->generateDoubleType());
    auto formatStringAllocation = irModuleNode->getModule()->getGlobalVariable(PrintIRFunction::getGlobalFloatFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, doubleCastValue });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintCharFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto charType = irGenerator->generateCharType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto functionType = llvm::FunctionType::get(voidType->getType(), { pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintCharIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
//    auto loadedPointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType, function->getArg(0));
//    auto charValue = functionBlock->getBuilder()->get()->CreateLoad(charType, loadedPointer);
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(pointerType, function->getArg(0), functionBlock);
    auto charValue = InstructionIRInjectorHelper::injectLoad(charType, loadedPointer, functionBlock);
    auto formatStringAllocation = irModuleNode->getModule()->getGlobalVariable(PrintIRFunction::getGlobalCharFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, charValue });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintBoolFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto boolType = irGenerator->generateBooleanType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto functionType = llvm::FunctionType::get(voidType->getType(), { pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintBoolIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto printTrueIfBlock = irGenerator->generateIfBlock(irContext);
    auto printTrueIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto elseBlock = irGenerator->generateIfElseBlock(irContext);
    auto endBlock = irGenerator->generateIfEndBlock(irContext);

//    auto loadedPointer = functionBlock->getBuilder()->get()->CreateLoad(pointerType, function->getArg(0));
//    auto boolValue = functionBlock->getBuilder()->get()->CreateLoad(boolType, loadedPointer);
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(pointerType, function->getArg(0), functionBlock);
    auto boolValue = InstructionIRInjectorHelper::injectLoad(boolType, loadedPointer, functionBlock);
    functionBlock->getBuilder()->get()->CreateBr(printTrueIfBlock->getBlock());

    auto isValueTrue = printTrueIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            boolValue,
            irGenerator->generateBoolean(true)
    );
    printTrueIfBlock->getBuilder()->get()->CreateCondBr(isValueTrue, printTrueIfThenBlock->getBlock(), elseBlock->getBlock());

    // true (print true)
    auto trueStringAllocation = irModuleNode->getModule()->getGlobalVariable(PrintIRFunction::getGlobalTrueFormatStringName());
    printTrueIfThenBlock->getBuilder()->get()->CreateCall(
        printf,
        { trueStringAllocation }
    );
    printTrueIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());

    // else (print false)
    auto falseStringAllocation = irModuleNode->getModule()->getGlobalVariable(PrintIRFunction::getGlobalFalseFormatStringName());
    elseBlock->getBuilder()->get()->CreateCall(
        printf,
        { falseStringAllocation }
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
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto functionType = llvm::FunctionType::get(voidType->getType(), { pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintStringIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(pointerType, function->getArg(0), functionBlock);
    auto loadedString = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getType(), loadedPointer, functionBlock, arrayPointerType);
    auto pointerToStringAllocation = functionBlock->getBuilder()->get()->CreateExtractValue(loadedString, { arrayPointerType->getAllocIndex() });
    auto formatStringAllocation = irModuleNode->getModule()->getGlobalVariable(PrintIRFunction::getGlobalStringFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, pointerToStringAllocation });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto refType = irGenerator->generateIrRefType(irGenerator->generateVoidType());
    auto charType = new IRType(irGenerator->generateCharType());
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(charType);
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto functionType = llvm::FunctionType::get(voidType->getType(), { pointerType, pointerType, pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintRefIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto typeValueIdIndex = irGenerator->generateIntConstant(typeValueType->getIdIndex());

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
    auto endBlock = irGenerator->generateIfEndBlock(irContext);

    auto forLoopIndexValue = InstructionIRInjectorHelper::injectLoad(intType, function->getArg(2), functionBlock);
    auto pointerToTypeValueAtIndex = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), function->getArg(1), { forLoopIndexValue });
    auto refTypeValue = InstructionIRInjectorHelper::injectLoad(typeValueType->getType(), pointerToTypeValueAtIndex, functionBlock, typeValueType);
    auto refValueTypeValuePointer = functionBlock->getBuilder()->get()->CreateExtractValue(refTypeValue, { typeValueType->getAllocIndex() }, "refValueTypeValue");
    auto refValueTypeValueIdPointer = functionBlock->getBuilder()->get()->CreateStructGEP(typeValueType->getType(), refValueTypeValuePointer, typeValueType->getIdIndex());
    auto refValueTypeId = InstructionIRInjectorHelper::injectLoad(intType, refValueTypeValueIdPointer, functionBlock);
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(pointerType, function->getArg(0), functionBlock);
    auto loadedRef = InstructionIRInjectorHelper::injectLoad(refType->getType(), loadedPointer, functionBlock);
    auto pointerToRefValue = functionBlock->getBuilder()->get()->CreateExtractValue(loadedRef, { refType->getRefValueIndex() });
    auto refValueAlloc = functionBlock->getBuilder()->get()->CreateAlloca(pointerType);
    InstructionIRInjectorHelper::injectStore(pointerToRefValue, refValueAlloc, functionBlock);
    auto refStartString = irModuleNode->getModule()->getGlobalVariable(PrintIRFunction::getGlobalRefStartFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { refStartString });
    functionBlock->getBuilder()->get()->CreateBr(intIfBlock->getBlock());

    auto isValueTypeInteger = intIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            refValueTypeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.INT)
    );
    intIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeInteger, intIfThenBlock->getBlock(), floatIfBlock->getBlock());
    intIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintIntFunction(),
            { refValueAlloc }
    );

    auto isValueTypeFloat = floatIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            refValueTypeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.FLOAT)
    );
    floatIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeFloat, floatIfThenBlock->getBlock(), charIfBlock->getBlock());
    floatIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintFloatFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintFloatFunction(),
            { refValueAlloc }
    );

    auto isValueTypeChar = charIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            refValueTypeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.CHAR)
    );
    charIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeChar, charIfThenBlock->getBlock(), boolIfBlock->getBlock());
    charIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintCharFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintCharFunction(),
            { refValueAlloc }
    );

    auto isValueTypeBool = boolIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            refValueTypeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.BOOL)
    );
    boolIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeBool, boolIfThenBlock->getBlock(), stringIfBlock->getBlock());
    boolIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintBoolFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintBoolFunction(),
            { refValueAlloc }
    );

    auto isValueTypeString = stringIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            refValueTypeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRING)
    );
    stringIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeString, stringIfThenBlock->getBlock(), endBlock->getBlock());
    stringIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintStringFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintStringFunction(),
            { refValueAlloc }
    );

    intIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    floatIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    charIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    boolIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    stringIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());

    auto refEndString = irModuleNode->getModule()->getGlobalVariable(PrintIRFunction::getGlobalRefEndFormatStringName());
    endBlock->getBuilder()->get()->CreateCall(printf, { refEndString });
    endBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintWhitespaceFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto function = irModuleNode->getPrintWhitespaceFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto whitespace = PrintIRFunction::generateStringAllocation(
            { ' ' },
            irGenerator,
            context,
            irModuleNode
    );
    auto formatStringAllocation = irModuleNode->getModule()->getGlobalVariable(PrintIRFunction::getGlobalCharFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, whitespace });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintNewLineFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto function = irModuleNode->getPrintNewLineFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto newLine = PrintIRFunction::generateStringAllocation(
            { '\n' },
            irGenerator,
            context,
            irModuleNode
    );
    auto formatStringAllocation = irModuleNode->getModule()->getGlobalVariable(PrintIRFunction::getGlobalCharFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, newLine });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintDebugMarkerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto function = irModuleNode->getPrintDebugMarkerFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto formatStringAllocation = irModuleNode->getModule()->getGlobalVariable(PrintIRFunction::getGlobalIntFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, function->getArg(0) });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintDebugPointerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto function = irModuleNode->getPrintDebugPointerFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto formatStringAllocation = irModuleNode->getModule()->getGlobalVariable(PrintIRFunction::getGlobalPointerFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, function->getArg(0) });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintDebugStringFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto charType = new IRType(irGenerator->generateCharType());
    auto rawStringType = irGenerator->generateIRArrayType(charType, 1);
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto function = irModuleNode->getPrintDebugStringFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto formatStringAllocation = irModuleNode->getModule()->getGlobalVariable(PrintIRFunction::getGlobalStringFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, function->getArg(0) });
    functionBlock->addVoidReturn();
}

llvm::Constant* PrintIRFunction::generateStringAllocation(std::vector<char> formatString, IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    formatString.push_back('\0');
    auto chars = std::vector<llvm::Constant*>();
    for (auto character : formatString) {
        chars.push_back(irGenerator->generateChar(character));
    }
    auto charType = new IRType(irGenerator->generateCharType());
    auto stringArrayType = irGenerator->generateIRArrayType(charType, chars.size());
    return llvm::ConstantArray::get(
            stringArrayType->getType(),
            llvm::ArrayRef(chars)
    );
}