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
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-unary-operators/ast-bang-operator-node.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-arithmetic-operators/ast-plus-operator-node.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-arithmetic-operators/ast-minus-operator-node.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-equality-operators/ast-equality-operator-node.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-equality-operators/ast-inequality-operator-node.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-arithmetic-operators/ast-star-operator-node.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-arithmetic-operators/ast-slash-operator-node.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-arithmetic-operators/ast-modulo-operator-node.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-equality-operators/ast-greater-than-operator-node.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-equality-operators/ast-greater-than-or-equal-operator.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-equality-operators/ast-less-than-or-equal-operator-node.h"
#include "../../../ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-equality-operators/ast-less-than-operator-node.h"

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
        return new ASTPlusOperatorNode(lexeme);
    } else if (symbol->isMinus()) {
        return new ASTMinusOperatorNode(lexeme);
    } else if (symbol->isEqualityOperator()) {
        return new ASTEqualityOperatorNode(lexeme);
    } else if (symbol->isInequalityOperator()) {
        return new ASTInequalityOperatorNode(lexeme);
    } else if (symbol->isStar()) {
        return new ASTStarOperatorNode(lexeme);
    } else if (symbol->isSlash()) {
        return new ASTSlashOperatorNode(lexeme);
    } else if (symbol->isModulo()) {
        return new ASTModuloOperatorNode(lexeme);
    } else if (symbol->isGreaterThan()) {
        return new ASTGreaterThanOperatorNode(lexeme);
    } else if (symbol->isGreaterThanOrEqual()) {
        return new ASTGreaterThanOrEqualOperatorNode(lexeme);
    } else if (symbol->isLessThan()) {
        return new ASTLessThanOperatorNode(lexeme);
    } else if (symbol->isLessThanOrEqual()) {
        return new ASTLessThanOrEqualOperatorNode(lexeme);
    } else if (symbol->isLogicalOperator()) {
        return new ASTLogicalOperatorNode(lexeme);
    }  else if (symbol->isUnaryOperator()) {
        return new ASTBangOperatorNode(lexeme);
    } else if (symbol->isSemicolon()) {
        return new ASTTerminatorNode(lexeme);
    } else {
        return new ASTLiteralNode(lexeme);
    }
}