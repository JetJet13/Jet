//
// Created by Johny Georges on 2024-02-17.
//

#include "lexeme-transformer.h"
#include "../../../ast/ast-nodes/ast-declaration-nodes/ast-variable-type-node.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-assignment-operator-node.h"
#include "../../../ast/ast-nodes/ast-literal-nodes/ast-int-literal-node.h"
#include "../../../ast/ast-nodes/ast-literal-nodes/ast-float-literal-node.h"
#include "../../../ast/ast-nodes/ast-literal-nodes/ast-char-literal-node.h"
#include "../../../ast/ast-nodes/ast-literal-nodes/ast-string-literal-node.h"
#include "../../../ast/ast-nodes/ast-literal-nodes/ast-boolean-literal-node.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-binary-operator-node.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-logical-operators/ast-logical-operator-node.h"
#include "../../../ast/ast-nodes/ast-terminator-node.h"
#include "../../../ast/ast-nodes/ast-base-nodes/ast-plus-base-node.h"
#include "../../../ast/ast-nodes/ast-base-nodes/ast-minus-base-node.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-unary-operators/ast-unary-operator-node.h"
#include "../../../ast/ast-nodes/ast-group-nodes/ast-group-left-node.h"
#include "../../../ast/ast-nodes/ast-group-nodes/ast-group-end-node.h"
#include "../../../ast/ast-nodes/ast-array-nodes/ast-left-bracket-node.h"
#include "../../../ast/ast-nodes/ast-array-nodes/ast-right-bracket-node.h"
#include "../../../ast/ast-nodes/ast-comma-node.h"

std::optional<ASTNode*> LexemeTransformer::transform(std::optional<Lexeme*> lexeme) {
    if (lexeme) {
        return LexemeTransformer::transform(lexeme.value());
    }
    return {};
}

ASTNode* LexemeTransformer::transform(Lexeme* lexeme) {
    auto symbol = lexeme->getToken()->getSymbol();
    if (symbol->isVarTypeQualifier()) {
        return new ASTVariableTypeNode(lexeme);
    } else if (symbol->isIdentifier()) {
        return new ASTIdentifierNode(lexeme);
    } else if (symbol->isEqual()) {
        return new ASTAssignmentOperatorNode(lexeme);
    } else if (symbol->isInt()) {
        return new ASTIntLiteralNode(lexeme);
    } else if (symbol->isFloat()) {
        return new ASTFloatLiteralNode(lexeme);
    } else if (symbol->isChar()) {
        return new ASTCharLiteralNode(lexeme);
    } else if (symbol->isString()) {
        return new ASTStringLiteralNode(lexeme);
    } else if (symbol->isBoolean()) {
        return new ASTBooleanLiteralNode(lexeme);
    } else if (symbol->isPlus()) {
        return new ASTPlusBaseNode(lexeme);
    } else if (symbol->isMinus()) {
        return new ASTMinusBaseNode(lexeme);
    } else if (symbol->isEqualityOperator()) {
        return new ASTBinaryOperatorNode(lexeme, 10);
    } else if (symbol->isInequalityOperator()) {
        return new ASTBinaryOperatorNode(lexeme, 10);
    } else if (symbol->isStar()) {
        return new ASTBinaryOperatorNode(lexeme, 2);
    } else if (symbol->isSlash()) {
        return new ASTBinaryOperatorNode(lexeme, 1);
    } else if (symbol->isModulo()) {
        return new ASTBinaryOperatorNode(lexeme, 9);
    } else if (symbol->isGreaterThan()) {
        return new ASTBinaryOperatorNode(lexeme, 10);
    } else if (symbol->isGreaterThanOrEqual()) {
        return new ASTBinaryOperatorNode(lexeme, 10);
    } else if (symbol->isLessThan()) {
        return new ASTBinaryOperatorNode(lexeme, 10);
    } else if (symbol->isLessThanOrEqual()) {
        return new ASTBinaryOperatorNode(lexeme, 10);
    } else if (symbol->isLogicalOperator()) {
        return new ASTLogicalOperatorNode(lexeme);
    }  else if (symbol->isUnaryOperator()) {
        return new ASTUnaryOperatorNode(lexeme);
    } else if (symbol->isLeftParentheses()) {
        return new ASTGroupStartNode(lexeme);
    } else if (symbol->isRightParentheses()) {
        return new ASTGroupEndNode(lexeme);
    } else if (symbol->isSemicolon()) {
        return new ASTTerminatorNode(lexeme);
    } else if (symbol->isLeftBracket()) {
        return new ASTLeftBracketNode(lexeme);
    } else if (symbol->isRightBracket()) {
        return new ASTRightBracketNode(lexeme);
    } else if (symbol->isComma()) {
        return new ASTCommaNode(lexeme);
    } else {
        return new ASTLiteralNode(lexeme);
    }
}