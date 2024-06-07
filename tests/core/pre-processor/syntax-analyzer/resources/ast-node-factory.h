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
#include "../../../../../src/core/ast/ast-nodes/ast-enum-nodes/ast-enum-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-enum-nodes/ast-enum-key-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-enum-nodes/ast-enum-key-value-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-call-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-tuple-nodes/ast-tuple-access-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-object-nodes/ast-object-access-source-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-object-nodes/ast-object-access-target-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-for-variable-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-for-source-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-skip-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-break-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-type-nodes/ast-type-node-factory.h"
#include "../../../../../src/core/ast/ast-nodes/ast-module-nodes/ast-module-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-module-nodes/ast-module-alias-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-module-nodes/ast-module-list-items/ast-module-list-alias-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-module-nodes/ast-module-list-items/ast-module-list-spread-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-module-nodes/ast-module-list-items/ast-module-list-normal-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-module-nodes/ast-module-list-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-path-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-module-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-wildcard-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-module-list-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-module-alias-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-alias-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-normal-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-spread-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-module-list-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-by-group-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-list-items/ast-import-module-list-by-wildcard-item-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-class-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-class-property-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-access-modifier-nodes/ast-public-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-access-modifier-nodes/ast-protected-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-access-modifier-nodes/ast-private-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-class-method-name-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-class-property-access-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-class-property-access-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-this-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-class-property-assignment-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-class-method-call-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-constructor-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-catch-error-variable-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-parameter-list-start-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-parameter-list-end-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-return-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-block-nodes/ast-block-start-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-block-nodes/ast-block-end-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-struct-nodes/ast-struct-start-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-struct-nodes/ast-struct-end-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-period-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-struct-nodes/ast-struct-key-value-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-struct-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-object-access-expression-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-tuple-access-expression.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-block-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-block-nodes/ast-block-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-enum-nodes/ast-enum-key-value-list-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-enum-nodes/ast-enum-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-argument-list-start-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-argument-list-end-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-function-nodes/ast-function-argument-list-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-tuple-nodes/ast-tuple-list-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-control-flow-block-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-if-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-else-if-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-try-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-catch-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/try-catch-finally/ast-finally-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-for-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-for-in-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-control-flow-nodes/ast-while-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-module-nodes/ast-module-list-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-module-nodes/ast-module-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-import-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-package-node/ast-use-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-import-nodes/ast-from-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-static-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-const-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-new-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-class-block-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-class-nodes/ast-class-node.h"
#include "../../../../../src/core/ast/ast-nodes/ast-lambda-nodes/ast-lambda-expression-fat-arrow-node.h"

namespace ASTNodeFactory {
    Lexeme* createLexeme(Symbol* symbol) {
        return new Lexeme(new Token(symbol, symbol->toString()));
    }
    static ASTBlockStartNode* blockStart = new ASTBlockStartNode(createLexeme(SymbolFactory::createIdentifierSymbol()));
    static ASTBlockEndNode* blockEnd = new ASTBlockEndNode(createLexeme(SymbolFactory::createIdentifierSymbol()));
    static ASTStructStartNode* structStart = new ASTStructStartNode(createLexeme(SymbolFactory::createLeftBraceSymbol()));
    static ASTStructEndNode* structEnd = new ASTStructEndNode(createLexeme(SymbolFactory::createRightBraceSymbol()));
    static ASTLeftBracketNode* leftBracket = new ASTLeftBracketNode(createLexeme(SymbolFactory::createLeftBracketSymbol()));
    static ASTRightBracketNode* rightBracket = new ASTRightBracketNode(createLexeme(SymbolFactory::createRightBracketSymbol()));
    static ASTFunctionParameterListStartNode* functionParameterListStart =  new ASTFunctionParameterListStartNode(createLexeme(SymbolFactory::createLeftParenSymbol()));
    static ASTFunctionParameterListEndNode* functionParameterListEnd =  new ASTFunctionParameterListEndNode(createLexeme(SymbolFactory::createRightParenSymbol()));
    static ASTFunctionArgumentListStartNode* functionArgumentListStart =  new ASTFunctionArgumentListStartNode(createLexeme(SymbolFactory::createLeftParenSymbol()));
    static ASTFunctionArgumentListEndNode* functionArgumentListEnd =  new ASTFunctionArgumentListEndNode(createLexeme(SymbolFactory::createRightParenSymbol()));
    static ASTEnumKeyValueListStartNode* enumKeyValueListStart =  new ASTEnumKeyValueListStartNode(createLexeme(SymbolFactory::createLeftBraceSymbol()));
    static ASTEnumKeyValueListEndNode* enumKeyValueListEnd =  new ASTEnumKeyValueListEndNode(createLexeme(SymbolFactory::createRightBraceSymbol()));
    static ASTTupleListStartNode* tupleListStart =  new ASTTupleListStartNode(createLexeme(SymbolFactory::createLeftBraceSymbol()));
    static ASTTupleListEndNode* tupleListEnd =  new ASTTupleListEndNode(createLexeme(SymbolFactory::createRightBraceSymbol()));
    static ASTTypeParameterListStartNode* typeParameterListStart = new ASTTypeParameterListStartNode(createLexeme(SymbolFactory::createLessThanSymbol()));
    static ASTTypeParameterListEndNode* typeParameterListEnd = new ASTTypeParameterListEndNode(createLexeme(SymbolFactory::createGreaterThanSymbol()));
    static ASTModuleListStartNode* moduleListStart = new ASTModuleListStartNode(createLexeme(SymbolFactory::createLeftBraceSymbol()));
    static ASTModuleListEndNode* moduleListEnd = new ASTModuleListEndNode(createLexeme(SymbolFactory::createRightBraceSymbol()));
    static ASTImportModuleListStartNode* importModuleListStart = new ASTImportModuleListStartNode(createLexeme(SymbolFactory::createLeftBraceSymbol()));
    static ASTImportModuleListEndNode* importModuleListEnd = new ASTImportModuleListEndNode(createLexeme(SymbolFactory::createRightBraceSymbol()));
    static ASTPeriodNode* period = new ASTPeriodNode(createLexeme(SymbolFactory::createPeriodSymbol()));
    static ASTLambdaExpressionFatArrowNode* lambdaFatArrow = new ASTLambdaExpressionFatArrowNode(createLexeme(SymbolFactory::createFatArrowSymbol()));
    static ASTLambdaTypeFatArrowNode* lambdaTypeFatArrow = new ASTLambdaTypeFatArrowNode(createLexeme(SymbolFactory::createFatArrowSymbol()));
    static ASTArrayTypeKeywordNode* arrayTypeKeyword = new ASTArrayTypeKeywordNode(createLexeme(SymbolFactory::createArrayTypeSymbol()));
    static ASTModuleAccessNode* moduleAccess = new ASTModuleAccessNode(createLexeme(SymbolFactory::createColonColonSymbol()));
    static ASTModuleSpreadNode* moduleSpread = new ASTModuleSpreadNode(
            createLexeme(SymbolFactory::createDotDotDotSymbol())
    );
    static ASTTupleNode* tupleKeyword = new ASTTupleNode(createLexeme(SymbolFactory::createTupleSymbol()));
    static ASTIfNode* ifKeyword = new ASTIfNode(createLexeme(SymbolFactory::createIfSymbol()));
    static ASTElseNode* elseKeyword = new ASTElseNode(createLexeme(SymbolFactory::createElseSymbol()));
    static ASTElseIfNode* elseIfKeyword = new ASTElseIfNode(ASTNodeFactory::elseKeyword, ASTNodeFactory::ifKeyword);
    static ASTTryNode* tryKeyword = new ASTTryNode(createLexeme(SymbolFactory::createTrySymbol()));
    static ASTCatchNode* catchKeyword = new ASTCatchNode(createLexeme(SymbolFactory::createCatchSymbol()));
    static ASTFinallyNode* finallyKeyword = new ASTFinallyNode(createLexeme(SymbolFactory::createFinallySymbol()));
    static ASTForNode* forKeyword = new ASTForNode(createLexeme(SymbolFactory::createForSymbol()));
    static ASTForInNode* forInKeyword = new ASTForInNode(createLexeme(SymbolFactory::createInSymbol()));
    static ASTWhileNode* whileKeyword = new ASTWhileNode(createLexeme(SymbolFactory::createWhileSymbol()));
    static ASTIdentifierNode* id = new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()));
    static ASTIdentifierExpressionNode* idExpression = new ASTIdentifierExpressionNode(
        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
    );
    static ASTImportSpreadNode* importSpread = new ASTImportSpreadNode(
            createLexeme(SymbolFactory::createDotDotDotSymbol())
    );
    static ASTColonNode* colon = new ASTColonNode(createLexeme(SymbolFactory::createColonSymbol()));
    static ASTVariableInitNode* letInit = new ASTVariableInitNode(
                new ASTVariableTypeNode(createLexeme(SymbolFactory::createVarSymbol())),
                new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
    );
    static ASTVariableInitNode* constInit = new ASTVariableInitNode(
            new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
            new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
    );
    static ASTVariableInitNode* createConstInitWithType(ASTTypeNode* type) {
        return new ASTVariableInitNode(
                new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())),
                ASTNodeFactory::colon,
                type
        );
    }
    static ASTIntLiteralNode* intLiteral = new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()));
    static ASTFloatLiteralNode* floatLiteral = new ASTFloatLiteralNode(createLexeme(SymbolFactory::createFloatSymbol()));
    static ASTStringLiteralNode* stringLiteral = new ASTStringLiteralNode(createLexeme(SymbolFactory::createStringSymbol()));
    static ASTCharLiteralNode* charLiteral = new ASTCharLiteralNode(createLexeme(SymbolFactory::createCharSymbol()));
    static ASTBooleanLiteralNode* trueLiteral = new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createTrueSymbol()));
    static ASTBooleanLiteralNode* falseLiteral = new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createFalseSymbol()));

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
    static ASTBinaryOperatorNode* equality = new ASTBinaryOperatorNode(createLexeme(SymbolFactory::createEqualEqualSymbol()));
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
            ASTNodeFactory::leftBracket,
            ASTNodeFactory::intExpression,
            ASTNodeFactory::rightBracket
    );
    static ASTArrayAccessNode* arrayAccessId =  new ASTArrayAccessNode(
            ASTNodeFactory::leftBracket,
            ASTNodeFactory::idExpression,
            ASTNodeFactory::rightBracket
    );
    static ASTThisNode* thisNode = new ASTThisNode(
            createLexeme(SymbolFactory::createThisSymbol())
    );
    static ASTCatchErrorVariableNode* catchErrorVariable = new ASTCatchErrorVariableNode(createLexeme(SymbolFactory::createIdentifierSymbol()));
    static ASTTypeNode* intType = ASTTypeNodeFactory::createPrimitiveTypeNode(createLexeme(SymbolFactory::createIntTypeSymbol()));
    static ASTTypeNode* floatType = ASTTypeNodeFactory::createPrimitiveTypeNode(createLexeme(SymbolFactory::createFloatTypeSymbol()));
    static ASTTypeNode* stringType = ASTTypeNodeFactory::createPrimitiveTypeNode(createLexeme(SymbolFactory::createStringTypeSymbol()));
    static ASTTypeNode* charType = ASTTypeNodeFactory::createPrimitiveTypeNode(createLexeme(SymbolFactory::createCharTypeSymbol()));
    static ASTTypeNode* booleanType = ASTTypeNodeFactory::createPrimitiveTypeNode(createLexeme(SymbolFactory::createBooleanTypeSymbol()));
    static ASTTypeNode* arrayType = ASTTypeNodeFactory::createPrimitiveTypeNode(createLexeme(SymbolFactory::createArrayTypeSymbol()));
    static ASTTypeNode* idType = ASTTypeNodeFactory::createCustomTypeNode(createLexeme(SymbolFactory::createIdentifierSymbol()), "id");
    static ASTTypeNode* thisType = ASTTypeNodeFactory::createThisTypeNode(ASTNodeFactory::thisNode);
    static ASTFunctionNode* functionKeyword =  new ASTFunctionNode(
            createLexeme(SymbolFactory::createFunctionSymbol())
    );
    static ASTProcedureNode* procedureKeyword =  new ASTProcedureNode(
            createLexeme(SymbolFactory::createProcedureSymbol())
    );
    static ASTFunctionNameNode* functionName =  new ASTFunctionNameNode(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static ASTFunctionCallNode* functionCall =  new ASTFunctionCallNode(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static ASTFunctionReturnNode* functionReturn =  new ASTFunctionReturnNode(
            createLexeme(SymbolFactory::createReturnSymbol())
    );
    static ASTFunctionReturnNode* functionReturnFatArrow =  new ASTFunctionReturnNode(
            createLexeme(SymbolFactory::createFatArrowSymbol())
    );
    static ASTFunctionParameterListStartNode* leftParen = new ASTFunctionParameterListStartNode(
            createLexeme(SymbolFactory::createLeftParenSymbol())
    );
    static ASTFunctionParameterListEndNode* rightParen = new ASTFunctionParameterListEndNode(
            createLexeme(SymbolFactory::createRightParenSymbol())
    );
    static ASTFunctionParameterNode* intFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::colon,
            ASTNodeFactory::intType
    );

    static ASTFunctionParameterNode* floatFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::colon,
            ASTNodeFactory::floatType
    );
    static ASTFunctionParameterNode* stringFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::colon,
            ASTNodeFactory::stringType
    );
    static ASTFunctionParameterNode* charFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::colon,
            ASTNodeFactory::charType
    );
    static ASTFunctionParameterNode* booleanFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::colon,
            ASTNodeFactory::booleanType
    );
    static ASTFunctionParameterNode* arrayFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::colon,
            ASTNodeFactory::arrayType
    );
    static ASTFunctionParameterNode* idFunctionParameter =  new ASTFunctionParameterNode(
            ASTNodeFactory::idExpression,
            ASTNodeFactory::colon,
            ASTNodeFactory::idType
    );
    static ASTAssignmentOperatorNode* assignment = new ASTAssignmentOperatorNode(
            createLexeme(SymbolFactory::createEqualSymbol())
    );
    static ASTVariableAssignmentNode* varAssignment =  new ASTVariableAssignmentNode(
            new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())),
            ASTNodeFactory::assignment
    );
    static ASTEnumNode* enumKeyword =  new ASTEnumNode(
            createLexeme(SymbolFactory::createEnumSymbol())
    );
    static ASTEnumNameNode* enumName =  new ASTEnumNameNode(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static ASTEnumKeyNode* enumKey =  new ASTEnumKeyNode(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static ASTEnumKeyValueNode* enumKeyOnly =  new ASTEnumKeyValueNode(
            ASTNodeFactory::enumKey
    );
    static ASTTupleAccessNode* tupleAccess =  new ASTTupleAccessNode(
            createLexeme(SymbolFactory::createIntSymbol())
    );
    static ASTObjectAccessSourceNode* objectAccessSourceId = new ASTObjectAccessSourceNode(
            ASTNodeFactory::idExpression
    );
    static ASTObjectAccessTargetNode* objectAccessTargetId = new ASTObjectAccessTargetNode(
            ASTNodeFactory::idExpression
    );
    static ASTForVariableNode* forVariable = new ASTForVariableNode(
            ASTNodeFactory::idExpression
    );
    static ASTForSourceNode* forSourceId = new ASTForSourceNode(
            ASTNodeFactory::idExpression
    );
    static ASTBreakNode* breakStatement = new ASTBreakNode(
            createLexeme(SymbolFactory::createBreakSymbol())
    );
    static ASTSkipNode* skipStatement = new ASTSkipNode(
            createLexeme(SymbolFactory::createSkipSymbol())
    );
    static ASTModuleNode* moduleKeyword = new ASTModuleNode(createLexeme(SymbolFactory::createModuleSymbol()));
    static ASTModuleNameNode* moduleName = new ASTModuleNameNode(
            ASTNodeFactory::id
    );
    static ASTModuleAliasNameNode* moduleAliasName = new ASTModuleAliasNameNode(
            ASTNodeFactory::id
    );
    static ASTModuleListItemNode* moduleNormalItem = new ASTModuleListItemNode(
            new ASTModuleListNormalItemNode(moduleName)
    );
    static ASTAsNode* as = new ASTAsNode(
            createLexeme(SymbolFactory::createAsSymbol())
    );
    static ASTModuleListItemNode* moduleAliasItem = new ASTModuleListItemNode(
            new ASTModuleListAliasItemNode(moduleName, ASTNodeFactory::as, moduleAliasName)
    );
    static ASTModuleListItemNode* moduleSpreadItem = new ASTModuleListItemNode(
            new ASTModuleListSpreadItemNode(moduleName, ASTNodeFactory::moduleSpread)
    );
    static ASTImportNode* importKeyword = new ASTImportNode(
            createLexeme(SymbolFactory::createImportSymbol())
    );
    static ASTUseNode* useKeyword = new ASTUseNode(
            createLexeme(SymbolFactory::createUseSymbol())
    );
    static ASTFromNode* fromKeyword = new ASTFromNode(
            createLexeme(SymbolFactory::createFromSymbol())
    );
    static ASTImportModuleNameNode* importModuleName = new ASTImportModuleNameNode(
            ASTNodeFactory::id
    );
    static ASTImportModuleAliasNameNode* importModuleAliasName = new ASTImportModuleAliasNameNode(
            ASTNodeFactory::id
    );
    static ASTImportWildcardNode* importModuleWildcard = new ASTImportWildcardNode(
            createLexeme(SymbolFactory::createStarSymbol())
    );
    static ASTImportModuleListItemNode* importModuleNormalItem = new ASTImportModuleListItemNode(
            new ASTImportModuleListNormalItemNode(importModuleName)
    );
    static ASTImportModuleListItemNode* importModuleAliasItem = new ASTImportModuleListItemNode(
            new ASTImportModuleListAliasItemNode(importModuleName, ASTNodeFactory::as, importModuleAliasName)
    );
    static ASTImportModuleListItemNode* importModuleSpreadItem = new ASTImportModuleListItemNode(
            new ASTImportModuleListSpreadItemNode(ASTNodeFactory::importSpread, importModuleName)
    );
    static ASTImportModuleListItemNode* importModuleWildcardItem = new ASTImportModuleListItemNode(
            new ASTImportModuleListWildcardItemNode(createLexeme(SymbolFactory::createStarSymbol()))
    );

    static ASTImportModuleListItemNode* importModuleByWildcardItem = new ASTImportModuleListItemNode(
            new ASTImportModuleListByWildcardItemNode(importModuleName, ASTNodeFactory::moduleAccess, importModuleWildcard)
    );
    static ASTImportPathNode* importPath = new ASTImportPathNode(
            ASTNodeFactory::stringLiteral
    );
    static ASTNewNode* newKeyword = new ASTNewNode(
            createLexeme(SymbolFactory::createNewSymbol())
    );
    static ASTClassNode* classKeyword = new ASTClassNode(
            createLexeme(SymbolFactory::createClassSymbol())
    );
    static ASTClassNameNode* className = new ASTClassNameNode(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static ASTClassPropertyNameNode* classPropertyName = new ASTClassPropertyNameNode(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static ASTClassMethodNameNode* classMethodName = new ASTClassMethodNameNode(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static ASTClassMethodCallNode* classMethodCall = new ASTClassMethodCallNode(
            createLexeme(SymbolFactory::createIdentifierSymbol())
    );
    static ASTConstructorNode* classConstructor = new ASTConstructorNode(
            createLexeme(SymbolFactory::createConstructorSymbol())
    );
    static ASTClassAccessNode* classAccess = new ASTClassAccessNode(
            ASTNodeFactory::thisNode,
            new ASTThisAccessNode(createLexeme(SymbolFactory::createPeriodSymbol()))
    );
    static ASTClassPropertyAccessNode* classPropertyAccess = new ASTClassPropertyAccessNode(
            ASTNodeFactory::classAccess,
            ASTNodeFactory::classPropertyName
    );
    static ASTClassPropertyAssignmentNode* classPropertyAssignment = new ASTClassPropertyAssignmentNode(
            ASTNodeFactory::classPropertyAccess,
            ASTNodeFactory::assignment
    );
    static ASTClassPropertyAccessExpressionNode* classPropertyAccessExpression = new ASTClassPropertyAccessExpressionNode(
            ASTNodeFactory::classPropertyAccess
    );
    static ASTThisExpressionNode* thisExpression = new ASTThisExpressionNode(
            ASTNodeFactory::thisNode
    );
    static ASTPublicNode* publicModifier = new ASTPublicNode(
            createLexeme(SymbolFactory::createPublicSymbol())
    );
    static ASTProtectedNode* protectedModifier = new ASTProtectedNode(
            createLexeme(SymbolFactory::createProtectedSymbol())
    );
    static ASTPrivateNode* privateModifier = new ASTPrivateNode(
            createLexeme(SymbolFactory::createPrivateSymbol())
    );
    static ASTStaticNode* staticKeyword = new ASTStaticNode(
            createLexeme(SymbolFactory::createStaticSymbol())
    );
    static ASTConstNode* constKeyword = new ASTConstNode(
            createLexeme(SymbolFactory::createConstSymbol())
    );
    static ASTArrayNode* createArray(std::vector<ASTExpressionNode*> elements) {
        return new ASTArrayNode(
            ASTNodeFactory::leftBracket,
            elements,
            ASTNodeFactory::rightBracket
        );
    }
    static ASTArrayExpressionNode* createArrayExpression(std::vector<ASTExpressionNode*> elements) {
        return new ASTArrayExpressionNode(
                    new ASTArrayNode(
                        ASTNodeFactory::leftBracket,
                        elements,
                        ASTNodeFactory::rightBracket
        ));
    }
    static ASTArrayAccessNode* createArrayAccess(ASTExpressionNode* element) {
        return new ASTArrayAccessNode(
                ASTNodeFactory::leftBracket,
                element,
                ASTNodeFactory::rightBracket
        );
    }
    static ASTStructKeyValueNode* createStructKeyValue(ASTIdentifierExpressionNode* key, ASTExpressionNode* value) {
        return new ASTStructKeyValueNode(
                key,
                ASTNodeFactory::colon,
                value
        );
    }
    static ASTStructExpressionNode* createStructExpression(std::vector<ASTStructKeyValueNode*> fields) {
        return new ASTStructExpressionNode(
                ASTNodeFactory::structStart,
                fields,
                ASTNodeFactory::structEnd
        );
    }
    static ASTObjectAccessExpressionNode* createObjectAccessExpression(ASTObjectAccessSourceNode* source, ASTObjectAccessTargetNode* target) {
        return new ASTObjectAccessExpressionNode(
                source,
                ASTNodeFactory::period,
                target
        );
    }
    static ASTTupleAccessExpressionNode* createTupleAccessExpression(ASTObjectAccessSourceNode* source, ASTTupleAccessNode* target) {
        return new ASTTupleAccessExpressionNode(
                source,
                ASTNodeFactory::period,
                target
        );
    }
    static ASTFunctionParameterNode* createFunctionParameter(ASTIdentifierExpressionNode* name, ASTTypeNode* type) {
        return new ASTFunctionParameterNode(
                name,
                ASTNodeFactory::colon,
                type
        );
    }
    static ASTFunctionParameterListNode* createFunctionParameterList(std::vector<ASTFunctionParameterNode*> parameters = {}) {
        return new ASTFunctionParameterListNode(
                ASTNodeFactory::functionParameterListStart,
                parameters,
                ASTNodeFactory::functionParameterListEnd
        );
    }
    static ASTFunctionBlockNode* createFunctionBlock(std::vector<ASTNode*> contents) {
        return new ASTFunctionBlockNode(
                ASTNodeFactory::blockStart,
                contents,
                ASTNodeFactory::blockEnd
        );
    }
    static ASTBlockNode* createBlock(std::vector<ASTNode*> contents) {
        return new ASTBlockNode(
                ASTNodeFactory::blockStart,
                contents,
                ASTNodeFactory::blockEnd
        );
    }
    static ASTControlFlowBlockNode* createControlFlowBlock(std::vector<ASTNode*> contents) {
        return new ASTControlFlowBlockNode(
                ASTNodeFactory::blockStart,
                contents,
                ASTNodeFactory::blockEnd
        );
    }
    static ASTClassBlockNode* createClassBlock(std::vector<ASTClassPropertyDeclarationNode*> properties, std::vector<ASTClassMethodDeclarationNode*> methods, std::vector<ASTClassConstructorDeclarationNode*> constructors) {
        return new ASTClassBlockNode(
                ASTNodeFactory::blockStart,
                properties,
                methods,
                constructors,
                ASTNodeFactory::blockEnd
        );
    }
    static ASTEnumKeyValueListNode* createEnumKeyValueList(std::vector<ASTEnumKeyValueNode*> contents) {
        return new ASTEnumKeyValueListNode(
                ASTNodeFactory::enumKeyValueListStart,
                contents,
                ASTNodeFactory::enumKeyValueListEnd
        );
    }
    static ASTFunctionArgumentListNode* createFunctionArgumentList(std::vector<ASTFunctionArgumentNode*> contents = {}) {
        return new ASTFunctionArgumentListNode(
                ASTNodeFactory::functionArgumentListStart,
                contents,
                ASTNodeFactory::functionArgumentListEnd
        );
    }
    static ASTTupleListNode* createTupleList(std::vector<ASTTupleItemNode*> items = {}) {
        return new ASTTupleListNode(
                ASTNodeFactory::tupleListStart,
                items,
                ASTNodeFactory::tupleListEnd
        );
    }
    static ASTTypeParameterListNode* createTypeParameterList(std::vector<ASTTypeNode*> items = {}) {
        return new ASTTypeParameterListNode(ASTNodeFactory::typeParameterListStart, items, ASTNodeFactory::typeParameterListEnd);
    }
    static ASTFunctionLambdaTypeParameterListNode* createFunctionLambdaTypeParameterList(std::vector<ASTTypeNode*> items = {}) {
        return new ASTFunctionLambdaTypeParameterListNode(
                ASTNodeFactory::functionKeyword,
                ASTNodeFactory::createTypeParameterList(items)
        );
    }
    static ASTProcedureLambdaTypeParameterListNode* createProcedureLambdaTypeParameterList(std::vector<ASTTypeNode*> items = {}) {
        return new ASTProcedureLambdaTypeParameterListNode(
                ASTNodeFactory::procedureKeyword,
                ASTNodeFactory::createTypeParameterList(items)
        );
    }
    static ASTTypeNode* createTupleType(std::vector<ASTTypeNode*> items = {}) {
        return ASTTypeNodeFactory::createTupleTypeNode(
                new ASTTupleTypeNode(
                    ASTNodeFactory::tupleKeyword,
                    ASTNodeFactory::createTypeParameterList(items)
                )
        );
    }
    static ASTTypeNode* createFunctionType(ASTTypeNode* returnType, std::vector<ASTTypeNode*> items = {}) {
        return ASTTypeNodeFactory::createFunctionTypeNode(new ASTFunctionTypeNode(
                ASTNodeFactory::createFunctionLambdaTypeParameterList(items),
                ASTNodeFactory::lambdaTypeFatArrow,
                returnType
        ));
    }
    static ASTTypeNode* createProcedureType(std::vector<ASTTypeNode*> items = {}) {
        return ASTTypeNodeFactory::createProcedureTypeNode(
                new ASTProcedureTypeNode(
                    ASTNodeFactory::createProcedureLambdaTypeParameterList(items)
        ));
    }
    static ASTTypeNode* createArrayType(ASTTypeNode* elementType) {
        return ASTTypeNodeFactory::createArrayTypeNode(
            new ASTArrayTypeNode(
                ASTNodeFactory::arrayTypeKeyword,
                ASTNodeFactory::createTypeParameterList({ elementType })
        ));
    }
    static ASTModuleListNode* createModuleList(std::vector<ASTModuleListItemNode*> items = {}) {
        return new ASTModuleListNode(
            ASTNodeFactory::moduleListStart,
            items,
            ASTNodeFactory::moduleListEnd
        );
    }
    static ASTImportModuleListNode* createImportModuleList(std::vector<ASTImportModuleListItemNode*> items = {}) {
        return new ASTImportModuleListNode(
                ASTNodeFactory::importModuleListStart,
                items,
                ASTNodeFactory::importModuleListEnd
        );
    }
    static ASTImportModuleListByGroupItemNode* createImportModuleByGroupItem(std::vector<ASTImportModuleListItemNode*> items) {
        return new ASTImportModuleListByGroupItemNode(
                ASTNodeFactory::importModuleName,
                ASTNodeFactory::moduleAccess,
                ASTNodeFactory::createImportModuleList(items)
        );
    }
    static ASTImportModuleListByWildcardItemNode* createImportModuleByWildcard() {
        return new ASTImportModuleListByWildcardItemNode(
                ASTNodeFactory::importModuleName,
                ASTNodeFactory::moduleAccess,
                ASTNodeFactory::importModuleWildcard
        );
    }
}

#endif //JETLANG_AST_NODE_FACTORY_H
