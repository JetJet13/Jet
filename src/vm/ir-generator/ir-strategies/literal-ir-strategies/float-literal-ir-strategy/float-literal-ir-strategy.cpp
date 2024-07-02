//
// Created by Johny Georges on 2024-06-15.
//

#include <llvm/ADT/APFloat.h>
#include "float-literal-ir-strategy.h"

IRFloatLiteralNode* FloatLiteralIRStrategy::generate(ASTFloatLiteralNode* node, std::unique_ptr<llvm::LLVMContext>* context) {
    return new IRFloatLiteralNode(node, llvm::ConstantFP::get(**context, llvm::APFloat(node->getValue())));
}