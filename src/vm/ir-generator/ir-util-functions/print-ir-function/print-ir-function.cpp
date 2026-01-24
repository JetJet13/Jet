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

std::string PrintIRFunction::getGlobalCharPrettyFormatStringName() {
    return "jet.print.char.pretty.format.string";
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

std::string PrintIRFunction::getGlobalCommaFormatStringName() {
    return "jet.print.comma.format.string";
}

std::string PrintIRFunction::getGlobalColonFormatStringName() {
    return "jet.print.colon.format.string";
}

std::string PrintIRFunction::getGlobalRefStartFormatStringName() {
    return "jet.print.ref.start.format.string";
}

std::string PrintIRFunction::getGlobalRefEndFormatStringName() {
    return "jet.print.ref.end.format.string";
}

std::string PrintIRFunction::getGlobalArrayStartFormatStringName() {
    return "jet.print.array.start.format.string";
}

std::string PrintIRFunction::getGlobalArrayEndFormatStringName() {
    return "jet.print.array.end.format.string";
}

std::string PrintIRFunction::getGlobalStructStartFormatStringName() {
    return "jet.print.struct.start.format.string";
}

std::string PrintIRFunction::getGlobalStructEndFormatStringName() {
    return "jet.print.struct.end.format.string";
}

std::string PrintIRFunction::getGlobalLambdaStartFormatStringName() {
    return "jet.print.lambda.start.format.string";
}

std::string PrintIRFunction::getGlobalLambdaPointerFormatStringName() {
    return "jet.print.lambda.pointer.format.string";
}

std::string PrintIRFunction::getGlobalLambdaEndFormatStringName() {
    return "jet.print.lambda.end.format.string";
}

std::string PrintIRFunction::getGlobalRefCountFormatStringName() {
    return "jet.print.ref.count.format.string";
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

std::string PrintIRFunction::getPrintArrayIRFunctionName() {
    return "jet.print.array";
}

std::string PrintIRFunction::getPrintStructIRFunctionName() {
    return "jet.print.struct";
}

std::string PrintIRFunction::getPrintStructRefIRFunctionName() {
    return "jet.print.struct.ref";
}

std::string PrintIRFunction::getPrintLambdaIRFunctionName() {
    return "jet.print.lambda";
}

std::string PrintIRFunction::getPrintWhitespaceIRFunctionName() {
    return "jet.print.whitespace";
}

std::string PrintIRFunction::getPrintCommaIRFunctionName() {
    return "jet.print.comma";
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

std::string PrintIRFunction::getPrintDebugRefCountIRFunctionName() {
    return "jet.print.debug.ref.count";
}

void PrintIRFunction::declarePrintDebugMarkerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto voidType = irGenerator->getVoidType();
    auto functionType = llvm::FunctionType::get(voidType, { intType }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintDebugMarkerIRFunctionName(), irModuleNode->getModule()->get());
}

void PrintIRFunction::declarePrintDebugPointerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto voidType = irGenerator->getVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(voidType, { pointerType }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintDebugPointerIRFunctionName(), irModuleNode->getModule()->get());
}

void PrintIRFunction::declarePrintDebugStringFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto voidType = irGenerator->getVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(voidType, { pointerType }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintDebugStringIRFunctionName(), irModuleNode->getModule()->get());
}

void PrintIRFunction::declarePrintDebugRefCountFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto voidType = irGenerator->getVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(voidType, { pointerType, pointerType }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintDebugRefCountIRFunctionName(), irModuleNode->getModule()->get());
}

void PrintIRFunction::declarePrintWhitespaceFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto voidType = irGenerator->getVoidType();
    auto functionType = llvm::FunctionType::get(voidType, {}, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintWhitespaceIRFunctionName(), irModuleNode->getModule()->get());
}

void PrintIRFunction::declarePrintCommaFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto voidType = irGenerator->getVoidType();
    auto functionType = llvm::FunctionType::get(voidType, {}, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintCommaIRFunctionName(), irModuleNode->getModule()->get());
}

void PrintIRFunction::declarePrintNewLineFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto voidType = irGenerator->getVoidType();
    auto functionType = llvm::FunctionType::get(voidType, {}, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintNewLineIRFunctionName(), irModuleNode->getModule()->get());
}

void PrintIRFunction::declarePrintRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto voidType = irGenerator->getVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(voidType, { pointerType, pointerType, pointerType }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintRefIRFunctionName(), irModuleNode->getModule()->get());
}

void PrintIRFunction::declarePrintArrayFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto voidType = irGenerator->getVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(voidType, { pointerType, pointerType, pointerType }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintArrayIRFunctionName(), irModuleNode->getModule()->get());
}

void PrintIRFunction::declarePrintStructFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto voidType = irGenerator->getVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(voidType, { pointerType, pointerType, pointerType }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintStructIRFunctionName(), irModuleNode->getModule()->get());
}

void PrintIRFunction::declarePrintStructRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto voidType = irGenerator->getVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto functionType = llvm::FunctionType::get(voidType, { pointerType, pointerType, pointerType }, false);
    llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintStructRefIRFunctionName(), irModuleNode->getModule()->get());
}

void PrintIRFunction::generatePrintDebugGlobals(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto charFormatString = irGenerator->generateRawString("%c");
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            charFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            charFormatString,
            PrintIRFunction::getGlobalCharFormatStringName()
    );
    auto pointerFormatString = irGenerator->generateRawString("%p ");
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            pointerFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            pointerFormatString,
            PrintIRFunction::getGlobalPointerFormatStringName()
    );
    auto commaFormatString = irGenerator->generateRawString("%c ");
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            commaFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            commaFormatString,
            PrintIRFunction::getGlobalCommaFormatStringName()
    );
    auto intFormatString = irGenerator->generateRawString("%ld");
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            intFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            intFormatString,
            PrintIRFunction::getGlobalIntFormatStringName()
    );
    auto refCountFormatString = irGenerator->generateRawString("[ref_count] %d, %s\n");
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            refCountFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            refCountFormatString,
            PrintIRFunction::getGlobalRefCountFormatStringName()
    );
}

void PrintIRFunction::generatePrintGlobals(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto floatFormatString = irGenerator->generateRawString("%f");
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            floatFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            floatFormatString,
            PrintIRFunction::getGlobalFloatFormatStringName()
    );
    auto charPrettyFormatString = irGenerator->generateRawString("\'%c\'");
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            charPrettyFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            charPrettyFormatString,
            PrintIRFunction::getGlobalCharPrettyFormatStringName()
    );
    auto trueFormatString = irGenerator->generateRawString("true");
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            trueFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            trueFormatString,
            PrintIRFunction::getGlobalTrueFormatStringName()
    );
    auto falseFormatString = irGenerator->generateRawString("false");
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            falseFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            falseFormatString,
            PrintIRFunction::getGlobalFalseFormatStringName()
    );
    auto stringFormatString = irGenerator->generateRawString("\"%s\"");
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            stringFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            stringFormatString,
            PrintIRFunction::getGlobalStringFormatStringName()
    );
    auto refStartFormatString = irGenerator->generateRawString("ref<");
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            refStartFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            refStartFormatString,
            PrintIRFunction::getGlobalRefStartFormatStringName()
    );
    auto refEndFormatString = irGenerator->generateRawString(">");
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            refEndFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            refEndFormatString,
            PrintIRFunction::getGlobalRefEndFormatStringName()
    );
    auto arrayStartFormatString = irGenerator->generateRawString("[");
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            arrayStartFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            arrayStartFormatString,
            PrintIRFunction::getGlobalArrayStartFormatStringName()
    );
    auto arrayEndFormatString = irGenerator->generateRawString("]");
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            arrayEndFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            arrayEndFormatString,
            PrintIRFunction::getGlobalArrayEndFormatStringName()
    );
    auto structStartFormatString = irGenerator->generateRawString("{ ");
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            structStartFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            structStartFormatString,
            PrintIRFunction::getGlobalStructStartFormatStringName()
    );
    auto structEndFormatString = irGenerator->generateRawString(" }");
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            structEndFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            structEndFormatString,
            PrintIRFunction::getGlobalStructEndFormatStringName()
    );
    auto lambdaStartFormatString = irGenerator->generateRawString("lambda<");
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            lambdaStartFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            lambdaStartFormatString,
            PrintIRFunction::getGlobalLambdaStartFormatStringName()
    );
    auto lambdaPointerFormatString = irGenerator->generateRawString("%p");
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            lambdaPointerFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            lambdaPointerFormatString,
            PrintIRFunction::getGlobalLambdaPointerFormatStringName()
    );
    auto lambdaEndFormatString = irGenerator->generateRawString(">");
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            lambdaEndFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            lambdaEndFormatString,
            PrintIRFunction::getGlobalLambdaEndFormatStringName()
    );
    auto colonFormatString = irGenerator->generateRawString(": ");
    new llvm::GlobalVariable(
            *irModuleNode->getModule()->get(),
            colonFormatString->getType(),
            true,
            llvm::GlobalValue::ExternalLinkage,
            colonFormatString,
            PrintIRFunction::getGlobalColonFormatStringName()
    );
}

void PrintIRFunction::generatePrintFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
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
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto vaStart = irModuleNode->getModule()->get()->getOrInsertFunction("llvm.va_start", llvm::FunctionType::get(voidType->getType(), { pointerIntType->getPointerTo() }, false));
    auto vaEnd = irModuleNode->getModule()->get()->getOrInsertFunction("llvm.va_end", llvm::FunctionType::get(voidType->getType(), { pointerIntType->getPointerTo() }, false));
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
    auto arrayIfBlock = irGenerator->generateIfBlock(irContext, "array.");
    auto arrayIfThenBlock = irGenerator->generateIfThenBlock(irContext, "array.");
    auto structRefIfBlock = irGenerator->generateIfBlock(irContext, "struct.ref.");
    auto structRefIfThenBlock = irGenerator->generateIfThenBlock(irContext, "struct.ref.");
    auto lambdaIfBlock = irGenerator->generateIfBlock(irContext, "lambda.");
    auto lambdaIfThenBlock = irGenerator->generateIfThenBlock(irContext, "lambda.");
    auto endBlock = irGenerator->generateIfEndBlock(irContext);

    // for loop prep
    auto numElements = functionBlock->getBuilder()->get()->CreateExtractValue(typeValueArrayArgument, { arrayPointerType->getNumElementsIndex() });

    auto typeValueArrayPointer = functionBlock->getBuilder()->get()->CreateExtractValue(typeValueArrayArgument, { arrayPointerType->getAllocIndex() });
    auto vaList = functionBlock->getBuilder()->get()->CreateAlloca(pointerType, nullptr, "vaList");
    auto varArgAlloc = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            {
                irGenerator->generateInt64Constant(1),
                irGenerator->generateInt64Constant(intIrType->getSizeInBytes())
            }
    );
    auto forLoopIndex = functionBlock->getBuilder()->get()->CreateCall(
            irModuleNode->getMallocFunction(),
            {
                irGenerator->generateInt64Constant(1),
                irGenerator->generateInt64Constant(intIrType->getSizeInBytes()),
            }
    );
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), forLoopIndex, functionBlock);
    functionBlock->getBuilder()->get()->CreateCall(vaStart, { vaList });
    functionBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());
    // for loop condition
    auto forLoopIndexValue = InstructionIRInjectorHelper::injectLoad(intType, forLoopIndex, forLoopConditionBlock);
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
    refIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeRef, refIfThenBlock->getBlock(), arrayIfBlock->getBlock());
    refIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintRefFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintRefFunction(),
            { varArgAlloc, typeValueArrayPointer, forLoopIndex }
    );

    auto isValueTypeArray = arrayIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.ARRAY)
    );
    arrayIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeArray, arrayIfThenBlock->getBlock(), structRefIfBlock->getBlock());
    arrayIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintArrayFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintArrayFunction(),
            { varArgAlloc, typeValueArrayPointer, forLoopIndex }
    );

    auto isValueTypeStructRef = structRefIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT_REF)
    );
    structRefIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeStructRef, structRefIfThenBlock->getBlock(), lambdaIfBlock->getBlock());
    structRefIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintStructRefFunction(),
            { varArgAlloc, typeValueArrayPointer, forLoopIndex }
    );

    auto isValueTypeLambda = lambdaIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            typeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.LAMBDA)
    );
    lambdaIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeLambda, lambdaIfThenBlock->getBlock(), endBlock->getBlock());
    lambdaIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintLambdaFunction(),
            { varArgAlloc }
    );

    intIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    floatIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    charIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    boolIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    stringIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    refIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    arrayIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    structRefIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    lambdaIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());

    // end block for if/else chain
    auto newForLoopIndexValue = endBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, forLoopIndexValue, irGenerator->generateIntConstant(1));
    InstructionIRInjectorHelper::injectStore(newForLoopIndexValue, forLoopIndex, endBlock);
    endBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());

    forLoopEndBlock->getBuilder()->get()->CreateCall(vaEnd, { vaList });
    forLoopEndBlock->getBuilder()->get()->CreateCall(irModuleNode->getMallocFreeFunction(), { varArgAlloc });
    forLoopEndBlock->getBuilder()->get()->CreateCall(irModuleNode->getMallocFreeFunction(), { forLoopIndex });
    forLoopEndBlock->getBuilder()->get()->CreateCall(
        irContext->getIRModule()->getPrintNewLineFunction()
    );
    forLoopEndBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintIntFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto voidType = irGenerator->getVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto functionType = llvm::FunctionType::get(voidType, { pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintIntIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(pointerType, function->getArg(0), functionBlock);
    auto loadedInt = InstructionIRInjectorHelper::injectLoad(intType, loadedPointer, functionBlock);
    auto formatStringAllocation = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalIntFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, loadedInt });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintFloatFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto floatType = irGenerator->generateFloatType();
    auto voidType = irGenerator->getVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto functionType = llvm::FunctionType::get(voidType, { pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintFloatIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(pointerType, function->getArg(0), functionBlock);
    auto floatValue = InstructionIRInjectorHelper::injectLoad(floatType, loadedPointer, functionBlock);
    auto doubleCastValue = functionBlock->getBuilder()->get()->CreateFPExt(floatValue, irGenerator->generateDoubleType());
    auto formatStringAllocation = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalFloatFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, doubleCastValue });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintCharFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto charType = irGenerator->generateCharType();
    auto voidType = irGenerator->getVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto functionType = llvm::FunctionType::get(voidType, { pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintCharIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(pointerType, function->getArg(0), functionBlock);
    auto charValue = InstructionIRInjectorHelper::injectLoad(charType, loadedPointer, functionBlock);
    auto formatStringAllocation = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalCharPrettyFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, charValue });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintBoolFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto boolType = irGenerator->generateBooleanType();
    auto voidType = irGenerator->getVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto functionType = llvm::FunctionType::get(voidType, { pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintBoolIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto printTrueIfBlock = irGenerator->generateIfBlock(irContext);
    auto printTrueIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto elseBlock = irGenerator->generateIfElseBlock(irContext);
    auto endBlock = irGenerator->generateIfEndBlock(irContext);

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
    auto trueStringAllocation = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalTrueFormatStringName());
    printTrueIfThenBlock->getBuilder()->get()->CreateCall(
        printf,
        { trueStringAllocation }
    );
    printTrueIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());

    // else (print false)
    auto falseStringAllocation = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalFalseFormatStringName());
    elseBlock->getBuilder()->get()->CreateCall(
        printf,
        { falseStringAllocation }
    );
    elseBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());

    endBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintStringFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto charType = new IRType(irGenerator->generateCharType());
    auto voidType = irGenerator->getVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(charType);
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto functionType = llvm::FunctionType::get(voidType, { pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintStringIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(pointerType, function->getArg(0), functionBlock);
    auto loadedString = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getType(), loadedPointer, functionBlock, arrayPointerType);
    auto pointerToStringAllocation = functionBlock->getBuilder()->get()->CreateExtractValue(loadedString, { arrayPointerType->getAllocIndex() });
    auto formatStringAllocation = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalStringFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, pointerToStringAllocation });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto refType = irGenerator->generateIrRefType(irGenerator->generateVoidType());
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto function = irModuleNode->getPrintRefFunction();
    if (function == nullptr) {
        throw std::logic_error("print ref function is null!");
    }
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
    auto arrayIfBlock = irGenerator->generateIfBlock(irContext, "array.");
    auto arrayIfThenBlock = irGenerator->generateIfThenBlock(irContext, "array.");
    auto structRefIfBlock = irGenerator->generateIfBlock(irContext, "struct.ref.");
    auto structRefIfThenBlock = irGenerator->generateIfThenBlock(irContext, "struct.ref.");
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
    // forLoopIndexArgumentAlloc is for printRef and printArray calls only
    auto forLoopIndexArgumentAlloc = functionBlock->getBuilder()->get()->CreateAlloca(intType);
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), forLoopIndexArgumentAlloc, functionBlock);
    auto refStartString = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalRefStartFormatStringName());
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
    stringIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeString, stringIfThenBlock->getBlock(), arrayIfBlock->getBlock());
    stringIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintStringFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintStringFunction(),
            { refValueAlloc }
    );

    auto isValueTypeArray = arrayIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            refValueTypeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.ARRAY)
    );
    arrayIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeArray, arrayIfThenBlock->getBlock(), structRefIfBlock->getBlock());
    arrayIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintArrayFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintArrayFunction(),
            { refValueAlloc, refValueTypeValuePointer, forLoopIndexArgumentAlloc }
    );

    auto isValueTypeStructRef = structRefIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            refValueTypeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT_REF)
    );
    structRefIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeStructRef, structRefIfThenBlock->getBlock(), endBlock->getBlock());
    structRefIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintStructRefFunction(),
            { refValueAlloc, refValueTypeValuePointer, forLoopIndexArgumentAlloc }
    );

    intIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    floatIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    charIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    boolIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    stringIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    arrayIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());
    structRefIfThenBlock->getBuilder()->get()->CreateBr(endBlock->getBlock());


    auto refEndString = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalRefEndFormatStringName());
    endBlock->getBuilder()->get()->CreateCall(printf, { refEndString });
    endBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintArrayFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto refType = irGenerator->generateIrRefType(irGenerator->generateVoidType());
    auto charType = new IRType(irGenerator->generateCharType());
    auto pointerType = irGenerator->generatePointerType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(charType);
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto function = irModuleNode->getPrintArrayFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto typeValueIdIndex = irGenerator->generateIntConstant(typeValueType->getIdIndex());

    auto forLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext);
    auto forLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext);
    auto forLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext);
    auto addCommaIfBlock = irGenerator->generateIfBlock(irContext, "whitespace.");
    auto addCommaIfThenBlock = irGenerator->generateIfThenBlock(irContext, "whitespace.");
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
    auto arrayIfBlock = irGenerator->generateIfBlock(irContext, "array.");
    auto arrayIfThenBlock = irGenerator->generateIfThenBlock(irContext, "array.");
    auto structRefIfBlock = irGenerator->generateIfBlock(irContext, "struct.ref.");
    auto structRefIfThenBlock = irGenerator->generateIfThenBlock(irContext, "struct.ref.");
    auto endBlock = irGenerator->generateIfEndBlock(irContext);

    auto forLoopIndexParameterValue = InstructionIRInjectorHelper::injectLoad(intType, function->getArg(2), functionBlock);
    auto pointerToTypeValueAtIndex = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), function->getArg(1), { forLoopIndexParameterValue });
    auto arrayTypeValue = InstructionIRInjectorHelper::injectLoad(typeValueType->getType(), pointerToTypeValueAtIndex, functionBlock, typeValueType);
    auto arrayElementTypeValuePointer = functionBlock->getBuilder()->get()->CreateExtractValue(arrayTypeValue, { typeValueType->getAllocIndex() }, "arrayElementValueTypeValue");
    auto arrayElementTypeValueIdPointer = functionBlock->getBuilder()->get()->CreateStructGEP(typeValueType->getType(), arrayElementTypeValuePointer, typeValueType->getIdIndex());
    auto arrayElementValueTypeId = InstructionIRInjectorHelper::injectLoad(intType, arrayElementTypeValueIdPointer, functionBlock);
    auto arrayElementSizeInBytesPointer = functionBlock->getBuilder()->get()->CreateStructGEP(typeValueType->getType(), arrayElementTypeValuePointer, typeValueType->getSizeInBytesIndex());
    auto arrayElementSizeInBytes = InstructionIRInjectorHelper::injectLoad(intType, arrayElementSizeInBytesPointer, functionBlock);
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(pointerType, function->getArg(0), functionBlock);
    auto loadedArray = InstructionIRInjectorHelper::injectLoad(arrayPointerType->getType(), loadedPointer, functionBlock);
    auto arrayAlloc = functionBlock->getBuilder()->get()->CreateExtractValue(loadedArray, { arrayPointerType->getAllocIndex() });
    auto arrayNumElements = functionBlock->getBuilder()->get()->CreateExtractValue(loadedArray, { arrayPointerType->getNumElementsIndex() });
    auto forLoopIndex = functionBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "forLoopIndex");
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), forLoopIndex, functionBlock);
    auto arrayElementByteOffset = functionBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "elementByteOffset");
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), arrayElementByteOffset, functionBlock);
    auto arrayStartString = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalArrayStartFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { arrayStartString });
    // forLoopIndexArgumentAlloc is for printRef and printArray calls only
    auto forLoopIndexArgumentAlloc = functionBlock->getBuilder()->get()->CreateAlloca(intType);
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), forLoopIndexArgumentAlloc, functionBlock);
    functionBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());

    // for loop condition
    auto forLoopIndexValue = forLoopConditionBlock->getBuilder()->get()->CreateLoad(intType, forLoopIndex);
    auto isForLoopIndexLessThanNumElements = forLoopConditionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            forLoopIndexValue,
            arrayNumElements
    );
    forLoopConditionBlock->getBuilder()->get()->CreateCondBr(isForLoopIndexLessThanNumElements, forLoopBodyBlock->getBlock(), endBlock->getBlock());

    // for loop body
    auto arrayElementByteOffsetValue = InstructionIRInjectorHelper::injectLoad(intType, arrayElementByteOffset, forLoopBodyBlock);
    auto pointerToElementValue = forLoopBodyBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, arrayAlloc, { arrayElementByteOffsetValue });
    auto arrayElementValueAlloc = forLoopBodyBlock->getBuilder()->get()->CreateAlloca(pointerType);
    InstructionIRInjectorHelper::injectStore(pointerToElementValue, arrayElementValueAlloc, forLoopBodyBlock);
    forLoopBodyBlock->getBuilder()->get()->CreateBr(addCommaIfBlock->getBlock());

    auto forLoopIndexGreaterThenZero = addCommaIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SGT,
            forLoopIndexValue,
            irGenerator->generateIntConstant(0)
    );
    addCommaIfBlock->getBuilder()->get()->CreateCondBr(
            forLoopIndexGreaterThenZero,
            addCommaIfThenBlock->getBlock(),
            intIfBlock->getBlock()
    );
    addCommaIfThenBlock->getBuilder()->get()->CreateCall(irContext->getIRModule()->getPrintCommaFunction());
    addCommaIfThenBlock->getBuilder()->get()->CreateBr(intIfBlock->getBlock());

    auto isValueTypeInteger = intIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            arrayElementValueTypeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.INT)
    );
    intIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeInteger, intIfThenBlock->getBlock(), floatIfBlock->getBlock());
    intIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintIntFunction(),
            { arrayElementValueAlloc }
    );

    auto isValueTypeFloat = floatIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            arrayElementValueTypeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.FLOAT)
    );
    floatIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeFloat, floatIfThenBlock->getBlock(), charIfBlock->getBlock());
    floatIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintFloatFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintFloatFunction(),
            { arrayElementValueAlloc }
    );

    auto isValueTypeChar = charIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            arrayElementValueTypeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.CHAR)
    );
    charIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeChar, charIfThenBlock->getBlock(), boolIfBlock->getBlock());
    charIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintCharFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintCharFunction(),
            { arrayElementValueAlloc }
    );

    auto isValueTypeBool = boolIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            arrayElementValueTypeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.BOOL)
    );
    boolIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeBool, boolIfThenBlock->getBlock(), stringIfBlock->getBlock());
    boolIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintBoolFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintBoolFunction(),
            { arrayElementValueAlloc }
    );

    auto isValueTypeString = stringIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            arrayElementValueTypeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRING)
    );
    stringIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeString, stringIfThenBlock->getBlock(), refIfBlock->getBlock());
    stringIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintStringFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintStringFunction(),
            { arrayElementValueAlloc }
    );

    auto isValueTypeRef = refIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            arrayElementValueTypeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.REF)
    );
    refIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeRef, refIfThenBlock->getBlock(), arrayIfBlock->getBlock());
    refIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintRefFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintRefFunction(),
            { arrayElementValueAlloc, arrayElementTypeValuePointer, forLoopIndexArgumentAlloc }
    );

    auto isValueTypeArray = arrayIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            arrayElementValueTypeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.ARRAY)
    );
    arrayIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeArray, arrayIfThenBlock->getBlock(), structRefIfBlock->getBlock());
    arrayIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintArrayFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintArrayFunction(),
            { arrayElementValueAlloc, arrayElementTypeValuePointer, forLoopIndexArgumentAlloc }
    );

    auto isValueTypeStructRef = structRefIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            arrayElementValueTypeId,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT_REF)
    );
    structRefIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeStructRef, structRefIfThenBlock->getBlock(), forLoopEndBlock->getBlock());
    structRefIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintStructRefFunction(),
            { arrayElementValueAlloc, arrayElementTypeValuePointer, forLoopIndexArgumentAlloc }
    );

    intIfThenBlock->getBuilder()->get()->CreateBr(forLoopEndBlock->getBlock());
    floatIfThenBlock->getBuilder()->get()->CreateBr(forLoopEndBlock->getBlock());
    charIfThenBlock->getBuilder()->get()->CreateBr(forLoopEndBlock->getBlock());
    boolIfThenBlock->getBuilder()->get()->CreateBr(forLoopEndBlock->getBlock());
    stringIfThenBlock->getBuilder()->get()->CreateBr(forLoopEndBlock->getBlock());
    refIfThenBlock->getBuilder()->get()->CreateBr(forLoopEndBlock->getBlock());
    arrayIfThenBlock->getBuilder()->get()->CreateBr(forLoopEndBlock->getBlock());
    structRefIfThenBlock->getBuilder()->get()->CreateBr(forLoopEndBlock->getBlock());

    // for loop end block
    auto newElementByteOffsetValue = forLoopEndBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, arrayElementByteOffsetValue, arrayElementSizeInBytes);
    InstructionIRInjectorHelper::injectStore(newElementByteOffsetValue, arrayElementByteOffset, forLoopEndBlock);

    auto newForLoopIndexValue = forLoopEndBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, forLoopIndexValue, irGenerator->generateIntConstant(1));
    InstructionIRInjectorHelper::injectStore(newForLoopIndexValue, forLoopIndex, forLoopEndBlock);

    forLoopEndBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());

    // end block
    auto arrayEndString = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalArrayEndFormatStringName());
    endBlock->getBuilder()->get()->CreateCall(printf, { arrayEndString });
    endBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintStructFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto pointerIntType = irGenerator->generatePointerIntType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto refType = irGenerator->generateIrRefType(irGenerator->generateVoidType());
    auto charType = new IRType(irGenerator->generateCharType());
    auto pointerType = irGenerator->generatePointerType();
    auto arrayPointerType = irGenerator->generateIrArrayPointerType(charType);
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto function = irModuleNode->getPrintStructFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto typeValueIdIndex = irGenerator->generateIntConstant(typeValueType->getIdIndex());

    auto forLoopConditionBlock = irGenerator->generateForLoopConditionBlock(irContext);
    auto forLoopBodyBlock = irGenerator->generateForLoopBodyBlock(irContext);
    auto forLoopEndBlock = irGenerator->generateForLoopEndBlock(irContext);
    auto addIdBlock = irGenerator->generateIfBlock(irContext, "id.");
    auto addIdThenBlock = irGenerator->generateIfBlock(irContext, "id.");
    auto addStructStartBlock = irGenerator->generateIfBlock(irContext, "start.");
    auto addKeyBlock = irGenerator->generateIfBlock(irContext, "key.");
    auto addCommaIfBlock = irGenerator->generateIfBlock(irContext, "comma.");
    auto addCommaIfThenBlock = irGenerator->generateIfThenBlock(irContext, "comma.");
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
    auto arrayIfBlock = irGenerator->generateIfBlock(irContext, "array.");
    auto arrayIfThenBlock = irGenerator->generateIfThenBlock(irContext, "array.");
    auto structRefIfBlock = irGenerator->generateIfBlock(irContext, "struct.ref.");
    auto structRefIfThenBlock = irGenerator->generateIfThenBlock(irContext, "struct.ref.");
    auto endBlock = irGenerator->generateIfEndBlock(irContext);

    auto loadedStructPointer = InstructionIRInjectorHelper::injectLoad(pointerType, function->getArg(0), functionBlock);
    auto forLoopIndexParameterValue = InstructionIRInjectorHelper::injectLoad(intType, function->getArg(2), functionBlock);
    auto pointerToTypeValueAtIndex = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), function->getArg(1), { forLoopIndexParameterValue });
    auto structTypeValue = InstructionIRInjectorHelper::injectLoad(typeValueType->getType(), pointerToTypeValueAtIndex, functionBlock, typeValueType);
    auto structNumElements = functionBlock->getBuilder()->get()->CreateExtractValue(structTypeValue, { typeValueType->getNumTypesIndex() });
    auto structTypeValueAlloc = functionBlock->getBuilder()->get()->CreateExtractValue(structTypeValue, { typeValueType->getAllocIndex() });
    auto forLoopIndex = functionBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "forLoopIndex");
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), forLoopIndex, functionBlock);
    auto structElementByteOffset = functionBlock->getBuilder()->get()->CreateAlloca(intType, nullptr, "elementByteOffset");
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), structElementByteOffset, functionBlock);

    // forLoopIndexArgumentAlloc is for printRef, printArray and printStruct calls only
    auto forLoopIndexArgumentAlloc = functionBlock->getBuilder()->get()->CreateAlloca(intType);
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), forLoopIndexArgumentAlloc, functionBlock);
    functionBlock->getBuilder()->get()->CreateBr(addIdBlock->getBlock());

    auto structId = addIdBlock->getBuilder()->get()->CreateExtractValue(structTypeValue, { typeValueType->getValueIdIndex() });
    auto isIdNotNull = addIdBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_NE,
            structId,
            llvm::ConstantPointerNull::get(pointerType)
    );
    addIdBlock->getBuilder()->get()->CreateCondBr(isIdNotNull, addIdThenBlock->getBlock(), addStructStartBlock->getBlock());
    addIdThenBlock->getBuilder()->get()->CreateCall(printf, { structId });
    addIdThenBlock->getBuilder()->get()->CreateCall(irModuleNode->getPrintWhitespaceFunction());
    addIdThenBlock->getBuilder()->get()->CreateBr(addStructStartBlock->getBlock());

    auto structStartString = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalStructStartFormatStringName());
    addStructStartBlock->getBuilder()->get()->CreateCall(printf, { structStartString });
    addStructStartBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());


    // for loop condition
    auto forLoopIndexValue = forLoopConditionBlock->getBuilder()->get()->CreateLoad(intType, forLoopIndex);
    auto isForLoopIndexLessThanNumElements = forLoopConditionBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SLT,
            forLoopIndexValue,
            structNumElements
    );
    forLoopConditionBlock->getBuilder()->get()->CreateCondBr(isForLoopIndexLessThanNumElements, forLoopBodyBlock->getBlock(), endBlock->getBlock());

    // for loop body
    auto structElementTypeValueAtIndexPointer = forLoopBodyBlock->getBuilder()->get()->CreateInBoundsGEP(pointerType, structTypeValueAlloc, { forLoopIndexValue }, "structElementTypeValueAtIndex");
    auto structElementTypeValueAtIndexPointerLoaded = InstructionIRInjectorHelper::injectLoad(pointerType, structElementTypeValueAtIndexPointer, forLoopBodyBlock);
    auto structElementTypeValueAtIndex = InstructionIRInjectorHelper::injectLoad(typeValueType->getType(), structElementTypeValueAtIndexPointerLoaded, forLoopBodyBlock, typeValueType);
    auto structElementTypeValueIdAtIndex = forLoopBodyBlock->getBuilder()->get()->CreateExtractValue(structElementTypeValueAtIndex, typeValueType->getIdIndex());
    auto structElementKeyAtIndex = forLoopBodyBlock->getBuilder()->get()->CreateExtractValue(structElementTypeValueAtIndex, typeValueType->getKeyIndex());
    auto structElementByteOffsetValue = InstructionIRInjectorHelper::injectLoad(intType, structElementByteOffset, forLoopBodyBlock);
    auto pointerToElementValue = forLoopBodyBlock->getBuilder()->get()->CreateInBoundsGEP(pointerIntType, loadedStructPointer, { structElementByteOffsetValue });
    auto structElementValueAlloc = forLoopBodyBlock->getBuilder()->get()->CreateAlloca(pointerType);
    InstructionIRInjectorHelper::injectStore(pointerToElementValue, structElementValueAlloc, forLoopBodyBlock);
    forLoopBodyBlock->getBuilder()->get()->CreateBr(addCommaIfBlock->getBlock());

    auto forLoopIndexGreaterThenZero = addCommaIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_SGT,
            forLoopIndexValue,
            irGenerator->generateIntConstant(0)
    );
    addCommaIfBlock->getBuilder()->get()->CreateCondBr(
            forLoopIndexGreaterThenZero,
            addCommaIfThenBlock->getBlock(),
            addKeyBlock->getBlock()
    );
    addCommaIfThenBlock->getBuilder()->get()->CreateCall(irContext->getIRModule()->getPrintCommaFunction());
    addCommaIfThenBlock->getBuilder()->get()->CreateBr(addKeyBlock->getBlock());

    auto colonString = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalColonFormatStringName());
    addKeyBlock->getBuilder()->get()->CreateCall(printf, { structElementKeyAtIndex });
    addKeyBlock->getBuilder()->get()->CreateCall(printf, { colonString });
    addKeyBlock->getBuilder()->get()->CreateBr(intIfBlock->getBlock());

    auto isValueTypeInteger = intIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            structElementTypeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.INT)
    );
    intIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeInteger, intIfThenBlock->getBlock(), floatIfBlock->getBlock());
    intIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintIntFunction(),
            { structElementValueAlloc }
    );

    auto isValueTypeFloat = floatIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            structElementTypeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.FLOAT)
    );
    floatIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeFloat, floatIfThenBlock->getBlock(), charIfBlock->getBlock());
    floatIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintFloatFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintFloatFunction(),
            {structElementValueAlloc }
    );

    auto isValueTypeChar = charIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            structElementTypeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.CHAR)
    );
    charIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeChar, charIfThenBlock->getBlock(), boolIfBlock->getBlock());
    charIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintCharFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintCharFunction(),
            {structElementValueAlloc }
    );

    auto isValueTypeBool = boolIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            structElementTypeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.BOOL)
    );
    boolIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeBool, boolIfThenBlock->getBlock(), stringIfBlock->getBlock());
    boolIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintBoolFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintBoolFunction(),
            {structElementValueAlloc }
    );

    auto isValueTypeString = stringIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            structElementTypeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRING)
    );
    stringIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeString, stringIfThenBlock->getBlock(), refIfBlock->getBlock());
    stringIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintStringFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintStringFunction(),
            {structElementValueAlloc }
    );

    auto isValueTypeRef = refIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            structElementTypeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.REF)
    );
    refIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeRef, refIfThenBlock->getBlock(), arrayIfBlock->getBlock());
    refIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintRefFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintRefFunction(),
            { structElementValueAlloc, structElementTypeValueAtIndexPointerLoaded, forLoopIndexArgumentAlloc }
    );

    auto isValueTypeArray = arrayIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            structElementTypeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.ARRAY)
    );
    arrayIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeArray, arrayIfThenBlock->getBlock(), structRefIfBlock->getBlock());
    arrayIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintArrayFunction()->getFunctionType(),
            irContext->getIRModule()->getPrintArrayFunction(),
            { structElementValueAlloc, structElementTypeValueAtIndexPointerLoaded, forLoopIndexArgumentAlloc }
    );

    auto isValueTypeStructRef = structRefIfBlock->getBuilder()->get()->CreateICmp(
            llvm::CmpInst::Predicate::ICMP_EQ,
            structElementTypeValueIdAtIndex,
            irGenerator->generateIntConstant(IR_TYPE_ID.STRUCT_REF)
    );
    structRefIfBlock->getBuilder()->get()->CreateCondBr(isValueTypeStructRef, structRefIfThenBlock->getBlock(), forLoopEndBlock->getBlock());
    structRefIfThenBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintStructRefFunction(),
            { structElementValueAlloc, structElementTypeValueAtIndexPointerLoaded, forLoopIndexArgumentAlloc }
    );

    intIfThenBlock->getBuilder()->get()->CreateBr(forLoopEndBlock->getBlock());
    floatIfThenBlock->getBuilder()->get()->CreateBr(forLoopEndBlock->getBlock());
    charIfThenBlock->getBuilder()->get()->CreateBr(forLoopEndBlock->getBlock());
    boolIfThenBlock->getBuilder()->get()->CreateBr(forLoopEndBlock->getBlock());
    stringIfThenBlock->getBuilder()->get()->CreateBr(forLoopEndBlock->getBlock());
    refIfThenBlock->getBuilder()->get()->CreateBr(forLoopEndBlock->getBlock());
    arrayIfThenBlock->getBuilder()->get()->CreateBr(forLoopEndBlock->getBlock());
    structRefIfThenBlock->getBuilder()->get()->CreateBr(forLoopEndBlock->getBlock());

    // for loop end block
    auto structElementSizeInBytes = forLoopEndBlock->getBuilder()->get()->CreateExtractValue(structElementTypeValueAtIndex, typeValueType->getSizeInBytesIndex());
    auto newElementByteOffsetValue = forLoopEndBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, structElementByteOffsetValue, structElementSizeInBytes);
    InstructionIRInjectorHelper::injectStore(newElementByteOffsetValue, structElementByteOffset, forLoopEndBlock);

    auto newForLoopIndexValue = forLoopEndBlock->getBuilder()->get()->CreateBinOp(llvm::Instruction::BinaryOps::Add, forLoopIndexValue, irGenerator->generateIntConstant(1));
    InstructionIRInjectorHelper::injectStore(newForLoopIndexValue, forLoopIndex, forLoopEndBlock);
    forLoopEndBlock->getBuilder()->get()->CreateBr(forLoopConditionBlock->getBlock());

    // end block
    auto arrayEndString = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalStructEndFormatStringName());
    endBlock->getBuilder()->get()->CreateCall(printf, { arrayEndString });
    endBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintStructRefFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto typeValueType = irGenerator->generateIrTypeValueType();
    auto structRefType = irGenerator->generateIRStructRefType();
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto function = irModuleNode->getPrintStructRefFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto forLoopIndexValue = InstructionIRInjectorHelper::injectLoad(intType, function->getArg(2), functionBlock);
    auto pointerToTypeValueAtIndex = functionBlock->getBuilder()->get()->CreateInBoundsGEP(typeValueType->getType(), function->getArg(1), { forLoopIndexValue });
    auto structRefTypeValue = InstructionIRInjectorHelper::injectLoad(typeValueType->getType(), pointerToTypeValueAtIndex, functionBlock, typeValueType);
    auto structTypeValuePointer = functionBlock->getBuilder()->get()->CreateExtractValue(structRefTypeValue, {typeValueType->getAllocIndex() }, "structTypeValue");
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(pointerType, function->getArg(0), functionBlock);
    auto loadedStructRef = InstructionIRInjectorHelper::injectLoad(structRefType->getType(), loadedPointer, functionBlock);
    auto pointerToStruct = functionBlock->getBuilder()->get()->CreateExtractValue(loadedStructRef, { structRefType->getStructIndex() });
    auto structValueAlloc = functionBlock->getBuilder()->get()->CreateAlloca(pointerType);
    InstructionIRInjectorHelper::injectStore(pointerToStruct, structValueAlloc, functionBlock);
    // forLoopIndexArgumentAlloc is for printRef, printStructRef and printArray calls only
    auto forLoopIndexArgumentAlloc = functionBlock->getBuilder()->get()->CreateAlloca(intType);
    InstructionIRInjectorHelper::injectStore(irGenerator->generateIntConstant(0), forLoopIndexArgumentAlloc, functionBlock);
    functionBlock->getBuilder()->get()->CreateCall(
            irContext->getIRModule()->getPrintStructFunction(),
            { structValueAlloc, structTypeValuePointer, forLoopIndexArgumentAlloc }
    );
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintLambdaFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto invocableType = irGenerator->generateIRInvocableType();
    auto voidType = irGenerator->getVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto functionType = llvm::FunctionType::get(voidType, { pointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::ExternalLinkage, 0, PrintIRFunction::getPrintLambdaIRFunctionName(), irModuleNode->getModule()->get());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto loadedPointer = InstructionIRInjectorHelper::injectLoad(pointerType, function->getArg(0), functionBlock);
    auto lambdaValue = InstructionIRInjectorHelper::injectLoad(invocableType->getType(), loadedPointer, functionBlock);
    auto lambdaPointer = functionBlock->getBuilder()->get()->CreateExtractValue(lambdaValue, invocableType->getFunctionIndex());

    auto formatLambdaAllocation = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalLambdaPointerFormatStringName());

    auto lambdaStartString = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalLambdaStartFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { lambdaStartString });

    functionBlock->getBuilder()->get()->CreateCall(printf, { formatLambdaAllocation, lambdaPointer });

    auto lambdaEndString = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalLambdaEndFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { lambdaEndString });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintWhitespaceFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto function = irModuleNode->getPrintWhitespaceFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto whitespace = irGenerator->generateRawString(" ");
    auto formatStringAllocation = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalCharFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, whitespace });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintCommaFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto function = irModuleNode->getPrintCommaFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto comma = irGenerator->generateRawString(",");
    auto formatStringAllocation = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalCommaFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, comma });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintNewLineFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto function = irModuleNode->getPrintNewLineFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto newLine = irGenerator->generateRawString("\n");
    auto formatStringAllocation = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalCharFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, newLine });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintDebugMarkerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto function = irModuleNode->getPrintDebugMarkerFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto formatStringAllocation = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalIntFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, function->getArg(0) });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintDebugPointerFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto function = irModuleNode->getPrintDebugPointerFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto formatStringAllocation = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalPointerFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, function->getArg(0) });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintDebugStringFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto function = irModuleNode->getPrintDebugStringFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    functionBlock->getBuilder()->get()->CreateCall(printf, { function->getArg(0) });
    functionBlock->addVoidReturn();
}

void PrintIRFunction::generatePrintDebugRefCountFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, std::shared_ptr<IRModuleNode> irModuleNode) {
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->get()->getOrInsertFunction("printf", llvm::FunctionType::get(irGenerator->generateInt32Type(), { pointerType }, true));
    auto function = irModuleNode->getPrintDebugRefCountFunction();
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto formatStringAllocation = irModuleNode->getModule()->get()->getGlobalVariable(PrintIRFunction::getGlobalRefCountFormatStringName());
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, function->getArg(1), function->getArg(0) });
    functionBlock->addVoidReturn();
}