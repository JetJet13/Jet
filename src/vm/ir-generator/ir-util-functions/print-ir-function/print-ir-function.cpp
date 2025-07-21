//
// Created by Johny Georges on 2024-10-12.
//

#include "llvm/ADT/StringExtras.h"
#include "print-ir-function.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-function-parameter-declaration-node.h"

std::string PrintIRFunction::getPrintIRFunctionName() {
    return "jet.print";
}

void PrintIRFunction::generatePrintFunction(IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context, IRModuleNode* irModuleNode) {
    auto intType = irGenerator->generateIntType();
    auto voidType = irGenerator->generateVoidType();
    auto pointerType = irGenerator->generatePointerType();
    auto arrayPointerType = irGenerator->generateArrayPointerType();
    auto printf = irModuleNode->getModule()->getOrInsertFunction("printf", llvm::FunctionType::get(intType, { pointerType }, true));
    auto functionType = llvm::FunctionType::get(voidType->getType(), { arrayPointerType }, false);
    auto function = llvm::Function::Create(functionType, llvm::GlobalValue::InternalLinkage, 0, PrintIRFunction::getPrintIRFunctionName(), irModuleNode->getModule());
    auto functionBlock = irGenerator->generateFunctionBlock(function);

    auto formatString = std::vector<char> { '%', 'd', '\n', '\0' };
    auto chars = std::vector<llvm::Constant*>();
    for (auto character : formatString) {
        chars.push_back(llvm::ConstantInt::get(**context, llvm::APInt(CHAR_BIT, character)));
    }
    auto stringArray = llvm::ConstantArray::get(
            llvm::ArrayType::get(irGenerator->generateCharType(), chars.size()),
            llvm::ArrayRef(chars)
    );
    auto formatStringAllocation = functionBlock->getBuilder()->get()->CreateAlloca(stringArray->getType());
    functionBlock->getBuilder()->get()->CreateStore(stringArray, formatStringAllocation);
    auto zeroIndex = irGenerator->generateIntConstant(0);
    auto pointerToFirstCharOfFormatString = functionBlock->getBuilder()->get()->CreateInBoundsGEP(formatStringAllocation->getAllocatedType(), formatStringAllocation, { zeroIndex, zeroIndex });
    functionBlock->getBuilder()->get()->CreateCall(printf, { pointerToFirstCharOfFormatString, function->getArg(0) });
    functionBlock->addVoidReturn();
}