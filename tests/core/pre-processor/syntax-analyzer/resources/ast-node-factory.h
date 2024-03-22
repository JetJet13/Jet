//
// Created by Johny Georges on 2024-03-01.
//

#ifndef JETLANG_AST_NODE_FACTORY_H
#define JETLANG_AST_NODE_FACTORY_H

#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-identifier-expression-node.h"
#include "../../../../../src/core/symbol/symbol-factory.h"
#include "../../../../../src/core/ast/ast-nodes/ast-variable-nodes/ast-variable-init-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-int-literal-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-float-literal-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-char-literal-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-string-literal-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-boolean-literal-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-logical-operators/ast-logical-operator-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-unary-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-binary-operator-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-array-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-array-nodes/ast-array-access-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-parameter-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-variable-nodes/ast-variable-assignment-node.h"

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
    static ASTBinaryOperatorNode* greaterThan = new ASTBinaryOperatorNode(createLexeme(SymbolFactory::createGreaterThanSymbol()));
    static ASTBinaryOperatorNode* greaterThanOrEqual = new ASTBinaryOperatorNode(createLexeme(SymbolFactory::createGreaterThanOrEqualSymbol()));
    static ASTBinaryOperatorNode* lessThan = new ASTBinaryOperatorNode(createLexeme(SymbolFactory::createLessThanSymbol()));
    static ASTBinaryOperatorNode* lessThanOrEqual = new ASTBinaryOperatorNode(createLexeme(SymbolFactory::createLessThanOrEqualSymbol()));
    static ASTBinaryOperatorNode* plus = new ASTBinaryOperatorNode(createLexeme(SymbolFactory::createPlusSymbol()));
    static ASTBinaryOperatorNode* minus = new ASTBinaryOperatorNode(createLexeme(SymbolFactory::createMinusSymbol()));
    static ASTBinaryOperatorNode* star = new ASTBinaryOperatorNode(createLexeme(SymbolFactory::createStarSymbol()));
    static ASTBinaryOperatorNode* slash = new ASTBinaryOperatorNode(createLexeme(SymbolFactory::createSlashSymbol()));
    static ASTBinaryOperatorNode* modulo = new ASTBinaryOperatorNode(createLexeme(SymbolFactory::createModuloSymbol()));
    static ASTUnaryOperatorNode* unaryMinus = new ASTUnaryOperatorNode(createLexeme(SymbolFactory::createMinusSymbol()));
    static ASTUnaryOperatorNode* unaryPlus = new ASTUnaryOperatorNode(createLexeme(SymbolFactory::createPlusSymbol()));
    static ASTUnaryOperatorNode* bang = new ASTUnaryOperatorNode(createLexeme(SymbolFactory::createBangSymbol()));
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
    static ASTUnaryExpressionNode* bangInt = new ASTUnaryExpressionNode(
            ASTNodeFactory::bang,
            ASTNodeFactory::intExpression
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
    static ASTArrayAccessNode* arrayAccessInt =  new ASTArrayAccessNode(
            ASTNodeFactory::intExpression
    );
    static ASTArrayAccessNode* arrayAccessId =  new ASTArrayAccessNode(
            ASTNodeFactory::idExpression
    );
    static ASTTypeNode* intType = new ASTTypeNode(createLexeme(SymbolFactory::createIntTypeSymbol()));
    static ASTTypeNode* floatType = new ASTTypeNode(createLexeme(SymbolFactory::createFloatTypeSymbol()));
    static ASTTypeNode* stringType = new ASTTypeNode(createLexeme(SymbolFactory::createStringTypeSymbol()));
    static ASTTypeNode* charType = new ASTTypeNode(createLexeme(SymbolFactory::createCharTypeSymbol()));
    static ASTTypeNode* booleanType = new ASTTypeNode(createLexeme(SymbolFactory::createBooleanTypeSymbol()));
    static ASTTypeNode* arrayType = new ASTTypeNode(createLexeme(SymbolFactory::createArrayTypeSymbol()));
    static ASTTypeNode* idType = new ASTTypeNode(createLexeme(SymbolFactory::createIdentifierSymbol()));
    static ASTFunctionNameNode* functionName =  new ASTFunctionNameNode(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static ASTFunctionParameterNode* intFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::intType
    );
    static ASTFunctionParameterNode* floatFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::floatType
    );
    static ASTFunctionParameterNode* stringFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::stringType
    );
    static ASTFunctionParameterNode* charFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::charType
    );
    static ASTFunctionParameterNode* booleanFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::booleanType
    );
    static ASTFunctionParameterNode* arrayFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::arrayType
    );
    static ASTFunctionParameterNode* idFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::idType
    );
    static ASTVariableAssignmentNode* varAssignment =  new ASTVariableAssignmentNode(
            new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
    );


};

#endif //JETLANG_AST_NODE_FACTORY_H
