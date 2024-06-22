//
// Created by Johny Georges on 2024-06-21.
//

#include "array-access-expression-ir-strategy.h"

llvm::Value* ArrayAccessExpressionIRStrategy::ArrayAccessExpressionIRStrategy::generate(ASTArrayAccessExpressionNode* node, std::unique_ptr<llvm::LLVMContext>* context, IRGenerator* irGenerator, IRLookupTable* scope) {
    // todo: implement once pointers are supported
    return llvm::ConstantInt::get(**context, llvm::APInt(CHAR_BIT, 'A'));
}