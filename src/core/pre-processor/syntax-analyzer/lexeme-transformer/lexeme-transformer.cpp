//
// Created by Johny Georges on 2024-02-17.
//

#include "lexeme-transformer.h"
#include "../../../ast/ast-nodes/ast-variable-nodes/ast-variable-type-node.h"
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
#include "../../../ast/ast-nodes/ast-group-nodes/ast-group-start-node.h"
#include "../../../ast/ast-nodes/ast-group-nodes/ast-group-end-node.h"
#include "../../../ast/ast-nodes/ast-array-nodes/ast-left-bracket-node.h"
#include "../../../ast/ast-nodes/ast-array-nodes/ast-right-bracket-node.h"
#include "../../../ast/ast-nodes/ast-comma-node.h"
#include "../../../ast/ast-nodes/ast-colon-node.h"
#include "../../../ast/ast-nodes/ast-block-nodes/ast-block-end-node.h"
#include "../../../ast/ast-nodes/ast-block-nodes/ast-block-start-node.h"
#include "../../../ast/ast-nodes/ast-period-node.h"
#include "../../../ast/ast-nodes/ast-function-nodes/ast-function-return-node.h"
#include "../../../ast/ast-nodes/ast-function-nodes/ast-function-node.h"
#include "../../../ast/ast-nodes/ast-type-node.h"
#include "../../../ast/ast-nodes/ast-procedure-nodes/ast-procedure-node.h"
#include "../../../ast/ast-nodes/ast-enum-nodes/ast-enum-node.h"
#include "../../../ast/ast-nodes/ast-tuple-nodes/ast-tuple-node.h"
#include "../../../ast/ast-nodes/ast-control-flow-nodes/ast-if-node.h"
#include "../../../ast/ast-nodes/ast-control-flow-nodes/ast-else-node.h"
#include "../../../ast/ast-nodes/ast-control-flow-nodes/ast-while-node.h"

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
    } else if (symbol->isEqualityOperator() ||
               symbol->isInequalityOperator() ||
               symbol->isGreaterThan() ||
               symbol->isGreaterThanOrEqual() ||
               symbol->isLessThan() ||
               symbol->isLessThanOrEqual() ||
               symbol->isStar() ||
               symbol->isSlash() ||
               symbol->isModulo()) {
        return new ASTBinaryOperatorNode(lexeme);
    } else if (symbol->isLogicalOperator()) {
        return new ASTLogicalOperatorNode(lexeme);
    } else if (symbol->isUnaryOperator()) {
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
    } else if (symbol->isLeftBrace()) {
        return new ASTBlockStartNode(lexeme);
    } else if (symbol->isRightBrace()) {
        return new ASTBlockEndNode(lexeme);
    } else if (symbol->isComma()) {
        return new ASTCommaNode(lexeme);
    } else if (symbol->isColon()) {
        return new ASTColonNode(lexeme);
    } else if (symbol->isPeriod()) {
        return new ASTPeriodNode(lexeme);
    }  else if (symbol->isFunction()) {
        return new ASTFunctionNode(lexeme);
    }  else if (symbol->isReturn()) {
        return new ASTFunctionReturnNode(lexeme);
    } else if (symbol->isProcedure()) {
        return new ASTProcedureNode(lexeme);
    } else if (symbol->isEnum()) {
        return new ASTEnumNode(lexeme);
    } else if (symbol->isTuple()) {
        return new ASTTupleNode(lexeme);
    } else if (symbol->isIf()) {
        return new ASTIfNode(lexeme);
    } else if (symbol->isElse()) {
        return new ASTElseNode(lexeme);
//    } else if (symbol->isFor()) {
//        return new ASTTupleNode(lexeme);
//    } else if (symbol->isIn()) {
//        return new ASTTupleNode(lexeme);
    } else if (symbol->isWhile()) {
        return new ASTWhileNode(lexeme);
    } else if (symbol->isType()) {
        return new ASTTypeNode(lexeme);
    } else {
        return new ASTLiteralNode(lexeme);
    }
}