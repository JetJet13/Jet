//
// Created by Johny Georges on 2024-06-26.
//

#include "identifier-ir-strategy.h"

llvm::Value* IdentifierIRStrategy::generate(ASTIdentifierExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context) {
    return IdentifierIRStrategy::generate(node->getIdentifierNode(), context);
}

llvm::Value* IdentifierIRStrategy::generate(ASTIdentifierNode* node, std::unique_ptr<llvm::LLVMContext>* context) {
    auto chars = std::vector<llvm::Constant*>();
    for (auto character : node->getId()) {
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