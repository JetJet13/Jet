//
// Created by Johny Georges on 2024-10-12.
//

#include "llvm/ADT/StringExtras.h"
#include "print-ir-function.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"

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

void PrintIRFunction::generatePrintIntFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(intType, { pointerType }, true));
    auto functionType = llvm::FunctionType::get(voidType->getType(), { intType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, PrintIRFunction::getPrintIntIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto formatStringAllocation = PrintIRFunction::generateStringAllocation(
            functionBlock,
            { '%', 'd', '\0' },
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
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, PrintIRFunction::getPrintFloatIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto formatStringAllocation = PrintIRFunction::generateStringAllocation(
            functionBlock,
            { '%', 'f', '\0' },
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
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, PrintIRFunction::getPrintCharIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto formatStringAllocation = PrintIRFunction::generateStringAllocation(
            functionBlock,
            { '%', 'c', '\0' },
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
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, PrintIRFunction::getPrintBoolIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);
    auto irContext = new IRContext(functionBlock, irModuleNode, context);
    auto printTrueIfBlock = irGenerator->generateIfBlock(irContext);
    auto printTrueIfThenBlock = irGenerator->generateIfThenBlock(irContext);
    auto elseBlock = irGenerator->generateIfElseBlock(irContext);
    auto endBlock = irGenerator->generateIfEndBlock(irContext);


    auto formatStringAllocation = PrintIRFunction::generateStringAllocation(
            functionBlock,
            { '%', 's', '\0' },
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
            { 't', 'r', 'u', 'e', '\0' },
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
            { 'f', 'a', 'l', 's', 'e', '\0' },
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
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, PrintIRFunction::getPrintStringIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto formatStringAllocation = PrintIRFunction::generateStringAllocation(
            functionBlock,
            { '%', 's', '\0' },
            irGenerator,
            context,
            irModuleNode
    );
    auto stringAllocation = functionBlock->getBuilder()->get()->CreateExtractValue(function->getArg(0), { arrayPointerType->getAllocIndex() });
    functionBlock->getBuilder()->get()->CreateCall(printf, { formatStringAllocation, stringAllocation });
    functionBlock->addVoidReturn();
}

llvm::AllocaInst* PrintIRFunction::generateStringAllocation(IRBlockNode* irBlock, std::vector<char> formatString, IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto chars = std::vector<llvm::Constant*>();
    for (auto character : formatString) {
        chars.push_back(llvm::ConstantInt::get(**context, llvm::APInt(CHAR_BIT, character)));
    }
    auto stringArray = llvm::ConstantArray::get(
            llvm::ArrayType::get(irGenerator->generateCharType(), chars.size()),
            llvm::ArrayRef(chars)
    );
    auto stringAllocation = irBlock->getBuilder()->get()->CreateAlloca(stringArray->getType());
    irBlock->getBuilder()->get()->CreateStore(stringArray, stringAllocation);
    return stringAllocation;
}