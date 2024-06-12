//
// Created by Johny Georges on 2024-06-11.
//

#include "ir-generator.h"

IRGenerator::IRGenerator(TokenTable* tokenTable) {
    _context = std::make_unique<llvm::LLVMContext>();
    _module = std::make_unique<llvm::Module>("JET LANG", *_context);
    _builder = std::make_unique<llvm::IRBuilder<>>(*_context);
    _tokenTable = tokenTable;
}

llvm::Value* IRGenerator::generateFor(ASTLiteralNode* node, IRLookupTable* scope) {
    switch (node->getNodeType()) {
        case AST_INT_LITERAL_NODE:
            return llvm::ConstantInt::get(*_context, llvm::APSInt(node->getLiteral()->getToken()->getRawValue()));
        default:
            return llvm::ConstantFP::get(*_context, llvm::APFloat(0.1));
    }
}