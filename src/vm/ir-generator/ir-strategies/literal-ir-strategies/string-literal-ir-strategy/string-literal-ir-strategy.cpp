//
// Created by Johny Georges on 2024-06-15.
//

#include <llvm/IR/Constants.h>
#include <llvm/ADT/ArrayRef.h>
#include "string-literal-ir-strategy.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"

IRStringLiteralNode* StringLiteralIRStrategy::generate(ASTStringLiteralNode* node, IRGenerator* irGenerator, IRContext* irContext) {
    auto chars = std::vector<llvm::Constant*>();

    for (auto character : node->getValue()) {
        chars.push_back(irGenerator->generateChar(character));
    }
    chars.push_back(irGenerator->generateChar('\0'));
    auto charIrType = irGenerator->generateIRCharType();
    auto stringArrayType = irGenerator->generateIRArrayType(charIrType, chars.size());
    auto stringArray = llvm::ConstantArray::get(
            stringArrayType->getType(),
            llvm::ArrayRef(chars)
    );

    return new IRStringLiteralNode(
        node,
        stringArray,
        stringArrayType
    );
}

llvm::Constant* StringLiteralIRStrategy::generateIRString(std::string rawString, IRGenerator* irGenerator, std::unique_ptr<llvm::LLVMContext>* context) {
    auto chars = std::vector<llvm::Constant*>();

    for (auto character : rawString) {
        chars.push_back(irGenerator->generateChar(character));
    }
    chars.push_back(irGenerator->generateChar('\0'));
    auto charIrType = irGenerator->generateIRCharType();
    auto stringArrayType = irGenerator->generateIRArrayType(charIrType, chars.size());
    return llvm::ConstantArray::get(
            stringArrayType->getType(),
            llvm::ArrayRef(chars)
    );
}