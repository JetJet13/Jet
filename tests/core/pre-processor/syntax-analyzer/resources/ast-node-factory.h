//
// Created by Johny Georges on 2024-03-01.
//

#ifndef JETLANG_AST_NODE_FACTORY_H
#define JETLANG_AST_NODE_FACTORY_H

#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "../../../../../src/core/symbol/symbol-factory.h"
#include "../../../../../src/core/ast/ast-nodes/ast-declaration-nodes/ast-variable-init-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-int-literal-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-float-literal-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-char-literal-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-string-literal-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-boolean-literal-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-arithmetic-operators/ast-plus-operator-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-arithmetic-operators/ast-minus-operator-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-arithmetic-operators/ast-slash-operator-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-arithmetic-operators/ast-star-operator-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-arithmetic-operators/ast-modulo-operator-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-unary-operators/ast-unary-minus-operator.h"
#include "../../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-unary-operators/ast-unary-plus-operator.h"
#include "../../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-unary-operators/ast-bang-operator-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-logical-operators/ast-logical-operator-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-unary-expression-node.h"

namespace ASTNodeFactory {
    Lexeme* createLexeme(Symbol* symbol) {
        return new Lexeme(new Token(symbol), 1, 0);
    }
    static ASTIdentifierExpressionNode* idExpression = new ASTIdentifierExpressionNode(
        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
    );

    static ASTVariableInitNode* letInit = new ASTVariableInitNode(
                new ASTVariableTypeNode(createLexeme(SymbolFactory::createVarSymbol())),
                new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
    );
    static ASTVariableInitNode* constInit = new ASTVariableInitNode(
            new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
            new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
    );
    static ASTLiteralExpressionNode* intExpression = new ASTLiteralExpressionNode(
            new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
    );
    static ASTLiteralExpressionNode* floatExpression = new ASTLiteralExpressionNode(
            new ASTFloatLiteralNode(createLexeme(SymbolFactory::createFloatSymbol()))
    );
    static ASTLiteralExpressionNode* stringExpression = new ASTLiteralExpressionNode(
            new ASTStringLiteralNode(createLexeme(SymbolFactory::createStringSymbol()))
    );
    static ASTLiteralExpressionNode* charExpression = new ASTLiteralExpressionNode(
            new ASTCharLiteralNode(createLexeme(SymbolFactory::createCharSymbol()))
    );
    static ASTLiteralExpressionNode* trueExpression = new ASTLiteralExpressionNode(
            new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createTrueSymbol()))
    );
    static ASTLiteralExpressionNode* falseExpression = new ASTLiteralExpressionNode(
            new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createFalseSymbol()))
    );
    static ASTPlusOperatorNode* plus = new ASTPlusOperatorNode(createLexeme(SymbolFactory::createPlusSymbol()));
    static ASTMinusOperatorNode* minus = new ASTMinusOperatorNode(createLexeme(SymbolFactory::createMinusSymbol()));
    static ASTStarOperatorNode* star = new ASTStarOperatorNode(createLexeme(SymbolFactory::createStarSymbol()));
    static ASTSlashOperatorNode* slash = new ASTSlashOperatorNode(createLexeme(SymbolFactory::createSlashSymbol()));
    static ASTModuloOperatorNode* modulo = new ASTModuloOperatorNode(createLexeme(SymbolFactory::createModuloSymbol()));
    static ASTUnaryMinusOperatorNode* unaryMinus = new ASTUnaryMinusOperatorNode(createLexeme(SymbolFactory::createMinusSymbol()));
    static ASTUnaryPlusOperatorNode* unaryPlus = new ASTUnaryPlusOperatorNode(createLexeme(SymbolFactory::createPlusSymbol()));
    static ASTBangOperatorNode* bang = new ASTBangOperatorNode(createLexeme(SymbolFactory::createBangSymbol()));
    static ASTLogicalOperatorNode* andOperator = new ASTLogicalOperatorNode(createLexeme(SymbolFactory::createAndSymbol()));
    static ASTLogicalOperatorNode* orOperator = new ASTLogicalOperatorNode(createLexeme(SymbolFactory::createOrSymbol()));
    static ASTUnaryExpressionNode* bangTrue = new ASTUnaryExpressionNode(
            ASTNodeFactory::bang,
            ASTNodeFactory::trueExpression
    );
    static ASTUnaryExpressionNode* bangFalse = new ASTUnaryExpressionNode(
            ASTNodeFactory::bang,
            ASTNodeFactory::falseExpression
    );
    static ASTUnaryExpressionNode* bangId = new ASTUnaryExpressionNode(
            ASTNodeFactory::bang,
            ASTNodeFactory::idExpression
    );
    static ASTUnaryExpressionNode* negativeInt = new ASTUnaryExpressionNode(
            ASTNodeFactory::unaryMinus,
            ASTNodeFactory::intExpression
    );
    static ASTUnaryExpressionNode* positiveInt = new ASTUnaryExpressionNode(
            ASTNodeFactory::unaryPlus,
            ASTNodeFactory::intExpression
    );
    static ASTUnaryExpressionNode* negativeId = new ASTUnaryExpressionNode(
            ASTNodeFactory::unaryMinus,
            ASTNodeFactory::idExpression
    );
    static ASTUnaryExpressionNode* positiveId = new ASTUnaryExpressionNode(
            ASTNodeFactory::unaryPlus,
            ASTNodeFactory::idExpression
    );
    static ASTUnaryExpressionNode* negativeFloat = new ASTUnaryExpressionNode(
            ASTNodeFactory::unaryMinus,
            ASTNodeFactory::floatExpression
    );
    static ASTUnaryExpressionNode* positiveFloat = new ASTUnaryExpressionNode(
            ASTNodeFactory::unaryPlus,
            ASTNodeFactory::floatExpression
    );

};

#endif //JETLANG_AST_NODE_FACTORY_H
