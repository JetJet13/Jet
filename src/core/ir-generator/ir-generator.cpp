//
// Created by Johny Georges on 2024-06-11.
//

#include "ir-generator.h"
#include "../ast/ast-nodes/ast-literal-nodes/ast-boolean-literal-node.h"
#include "../ast/ast-nodes/ast-literal-nodes/ast-string-literal-node.h"

// The IRGenerator will be responsible for programmatically generating
// llvm code.
// we need to figure out how to generate llvm code for an ASTNode and its
// type signature.
IRGenerator::IRGenerator(TokenTable* tokenTable) {
    _context = std::make_unique<llvm::LLVMContext>();
    _module = std::make_unique<llvm::Module>("JET LANG", *_context);
    _builder = std::make_unique<llvm::IRBuilder<>>(*_context);
    _tokenTable = tokenTable;
}

llvm::Value* IRGenerator::generateFor(ASTLiteralNode* node, IRLookupTable* scope) {
    if (node->is(AST_INT_LITERAL_NODE)) {
        return llvm::ConstantInt::get(*_context, llvm::APSInt(node->getLiteral()->getToken()->getRawValue()));
    } else if (node->is(AST_FLOAT_LITERAL_NODE)) {
        return llvm::ConstantFP::get(*_context, llvm::APFloat(_tokenTable->getFloat(node->getLiteral()->getToken()->getValueId().value())));
    } else if (node->is(AST_CHAR_LITERAL_NODE)) {
        return llvm::ConstantInt::get(*_context, llvm::APInt(8, _tokenTable->getChar(node->getLiteral()->getToken()->getValueId().value())));
    } else if (node->is(AST_STRING_LITERAL_NODE)) {
        auto chars = std::vector<llvm::Constant*>();
        auto stringNode = (ASTStringLiteralNode*)node;
        for (auto character : stringNode->getValue()) {
            chars.push_back(llvm::ConstantInt::get(*_context, llvm::APInt(8, character)));
        }
        return llvm::ConstantArray::get(
                llvm::ArrayType::get(
                        llvm::IntegerType::getInt8Ty(*_context),
                        chars.size()
                ),
                llvm::ArrayRef(chars)
        );
    } else if (node->is(AST_BOOLEAN_LITERAL_NODE)) {
        return ((ASTBooleanLiteralNode*)node)->getValue()
               ? llvm::ConstantInt::get(*_context, llvm::APSInt("1"))
               : llvm::ConstantInt::get(*_context, llvm::APSInt("0"));
    }

    throw std::logic_error("unknown literal node");
}