//
// Created by Johny Georges on 2024-06-15.
//

#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/ADT/ArrayRef.h>
#include "string-literal-ir-strategy.h"
#include "../../../../utils/address-space-generator/address-space-generator.h"
#include "../../../../utils/data-alignment-generator/data-alignment-generator.h"

IRStringLiteralNode* StringLiteralIRStrategy::generate(ASTStringLiteralNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator) {
    auto chars = std::vector<llvm::Constant*>();

    for (auto character : node->getValue()) {
        chars.push_back(llvm::ConstantInt::get(**context, llvm::APInt(CHAR_BIT, character)));
    }
    auto charIrType = new IRType(llvm::IntegerType::getInt8Ty(**context));
    auto stringArrayType = new IRArrayType(
        llvm::ArrayType::get(
            charIrType->getType(),
            chars.size()
        ),
        charIrType
    );
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