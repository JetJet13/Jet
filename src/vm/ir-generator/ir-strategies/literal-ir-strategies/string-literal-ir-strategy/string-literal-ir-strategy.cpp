//
// Created by Johny Georges on 2024-06-15.
//

#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/ADT/ArrayRef.h>
#include "string-literal-ir-strategy.h"

llvm::Value* StringLiteralIRStrategy::generate(ASTStringLiteralNode* node, std::unique_ptr<llvm::LLVMContext>* context) {
    auto chars = std::vector<llvm::Constant*>();
    auto stringNode = (ASTStringLiteralNode*)node;
    for (auto character : stringNode->getValue()) {
        chars.push_back(llvm::ConstantInt::get(**context, llvm::APInt(CHAR_BIT, character)));
    }
    return llvm::ConstantArray::get(
            llvm::ArrayType::get(
                    llvm::IntegerType::getInt8Ty(**context),
                    chars.size()
            ),
            llvm::ArrayRef(chars)
    );
}