//
// Created by Johny Georges on 2024-06-11.
//

#include "ir-generator.h"
#include "ir-strategies/literal-ir-strategies/int-literal-ir-strategy/int-literal-ir-strategy.h"
#include "ir-strategies/literal-ir-strategies/float-literal-ir-strategy/float-literal-ir-strategy.h"
#include "ir-strategies/literal-ir-strategies/char-literal-ir-strategy/char-literal-ir-strategy.h"
#include "ir-strategies/literal-ir-strategies/string-literal-ir-strategy/string-literal-ir-strategy.h"
#include "ir-strategies/literal-ir-strategies/bool-literal-ir-strategy/bool-literal-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/binary-expression-ir-strategy/binary-expression-ir-strategy.h"
#include "ir-strategies/expression-ir-strategies/logical-expression-ir-strategy/logical-expression-ir-strategy.h"
#include "../../core/ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../core/ast/ast-nodes/ast-statement-nodes/ast-expression-statement-node.h"
#include "../../core/ast/ast-nodes/ast-node-utils/ast-node-utils.h"

// The IRGenerator will be responsible for programmatically generating
// vm code.
// we need to figure out how to generate vm code for an ASTNode and its
// type signature.
IRGenerator::IRGenerator() {
    _context = std::make_unique<llvm::LLVMContext>();
    _irStrategyMap = IRStrategyMap();
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
    } else if (node->is(AST_BINARY_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getBinaryExpressionIRStrategy()->generate((ASTBinaryExpressionNode*)node, &_context, this, scope);
    } else if (node->is(AST_LOGICAL_EXPRESSION_NODE)) {
        return this->_irStrategyMap.getLogicalExpressionIRStrategy()->generate((ASTLogicalExpressionNode*)node, &_context, this, scope);
    }
    throw std::logic_error("unable to generate llvm value for expression " + node->toString());
}

llvm::Value* IRGenerator::generateFor(ASTLiteralNode* node, IRLookupTable* scope) {
    switch (node->getNodeType()) {
        case AST_INT_LITERAL_NODE:
            return _irStrategyMap.getIntLiteralIRStrategy()->generate((ASTIntLiteralNode*)node, &_context);;
        case AST_FLOAT_LITERAL_NODE:
            return _irStrategyMap.getFloatLiteralIRStrategy()->generate((ASTFloatLiteralNode*)node, &_context);
        case AST_CHAR_LITERAL_NODE:
            return _irStrategyMap.getCharLiteralIRStrategy()->generate((ASTCharLiteralNode*)node, &_context);
        case AST_STRING_LITERAL_NODE:
            return _irStrategyMap.getStringLiteralIRStrategy()->generate((ASTStringLiteralNode*)node, &_context);
        case AST_BOOLEAN_LITERAL_NODE:
            return _irStrategyMap.getBoolLiteralIRStrategy()->generate((ASTBooleanLiteralNode*)node, &_context);
        default:
            throw std::logic_error("unknown literal node");
    }
}
