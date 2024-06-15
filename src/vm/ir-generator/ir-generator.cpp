//
// Created by Johny Georges on 2024-06-11.
//

#include "ir-generator.h"
#include "../../core/ast/ast-nodes/ast-literal-nodes/ast-boolean-literal-node.h"
#include "../../core/ast/ast-nodes/ast-literal-nodes/ast-string-literal-node.h"
#include "../../core/ast/ast-nodes/ast-statement-nodes/ast-expression-statement-node.h"
#include "../../core/ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../core/ast/ast-nodes/ast-node-utils/ast-node-utils.h"

// The IRGenerator will be responsible for programmatically generating
// vm code.
// we need to figure out how to generate vm code for an ASTNode and its
// type signature.
IRGenerator::IRGenerator(TokenTable* tokenTable) {
    _context = std::make_unique<llvm::LLVMContext>();
    _tokenTable = tokenTable;
}

llvm::Value* IRGenerator::generateFor(ASTNode* node, IRLookupTable* scope) {
    if (ASTNodeUtils::isDeclarationNode(node)) {
        return this->generateFor(((ASTDeclarationNode*)node), scope);
    } else if (ASTNodeUtils::isStatementNode(node)) {
        return this->generateFor(((ASTStatementNode*)node), scope);
    }
    throw std::logic_error("unable to generate llvm value for node " + node->toString());
}

llvm::Value* IRGenerator::generateFor(ASTStatementNode* node, IRLookupTable* scope) {
    if (node->is(AST_EXPRESSION_STATEMENT_NODE)) {
        return this->generateFor(((ASTExpressionStatementNode*)node)->getExpression(), scope);
    }
    throw std::logic_error("unable to generate llvm value for declaration " + node->toString());
}

llvm::Value* IRGenerator::generateFor(ASTDeclarationNode* node, IRLookupTable* scope) {
    if (node->is(AST_VARIABLE_DECLARATION_NODE)) {
        return this->generateFor(((ASTExpressionStatementNode*)node)->getExpression(), scope);
    }
    throw std::logic_error("unable to generate llvm value for declaration " + node->toString());
}

llvm::Value* IRGenerator::generateFor(ASTExpressionNode* node, IRLookupTable* scope) {
    if (node->is(AST_LITERAL_EXPRESSION_NODE)) {
        return this->generateFor(((ASTLiteralExpressionNode*)node)->getLiteralNode(), scope);
    }
    throw std::logic_error("unable to generate llvm value for expression " + node->toString());
}

llvm::Value* IRGenerator::generateFor(ASTLiteralNode* node, IRLookupTable* scope) {
    if (node->is(AST_INT_LITERAL_NODE)) {
        return llvm::ConstantInt::get(*_context, llvm::APSInt(node->getLiteral()->getToken()->getRawValue()));
    } else if (node->is(AST_FLOAT_LITERAL_NODE)) {
        return llvm::ConstantFP::get(*_context, llvm::APFloat(_tokenTable->getFloat(node->getLiteral()->getToken()->getValueId().value())));
    } else if (node->is(AST_CHAR_LITERAL_NODE)) {
        return llvm::ConstantInt::get(*_context, llvm::APInt(CHAR_BIT, _tokenTable->getChar(node->getLiteral()->getToken()->getValueId().value())));
    } else if (node->is(AST_STRING_LITERAL_NODE)) {
        auto chars = std::vector<llvm::Constant*>();
        auto stringNode = (ASTStringLiteralNode*)node;
        for (auto character : stringNode->getValue()) {
            chars.push_back(llvm::ConstantInt::get(*_context, llvm::APInt(CHAR_BIT, character)));
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
