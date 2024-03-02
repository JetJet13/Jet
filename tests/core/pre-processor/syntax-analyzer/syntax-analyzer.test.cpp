//
// Created by Johny Georges on 2024-02-23.
//

#include <catch2/catch_all.hpp>
#include "./resources/ast-node-factory.h"
#include "../../../../src/core/reserved-keywords/reserved-keywords.h"
#include "../../../../src/core/pre-processor/lexical-analyzer/lexical-analyzer.h"
#include "../../../../src/core/pre-processor/syntax-analyzer/syntax-analyzer.h"
#include "../../../../src/core/ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-binary-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-logical-expression-node.h"


std::unordered_map<int, ASTNode*> expectedNodes = {
        {1, new ASTVariableDeclarationNode(
                ASTNodeFactory::letInit,
                ASTNodeFactory::intExpression
        )},
        {2, new ASTVariableDeclarationNode(
                ASTNodeFactory::letInit,
                ASTNodeFactory::floatExpression
        )},
        {3, new ASTVariableDeclarationNode(
                ASTNodeFactory::letInit,
                ASTNodeFactory::stringExpression
        )},
        {4, new ASTVariableDeclarationNode(
                ASTNodeFactory::letInit,
                ASTNodeFactory::charExpression
        )},
        {5, new ASTVariableDeclarationNode(
                ASTNodeFactory::letInit,
                ASTNodeFactory::trueExpression
        )},
        {6, new ASTVariableDeclarationNode(
                ASTNodeFactory::letInit,
                ASTNodeFactory::falseExpression
        )},
        {7, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::intExpression
        )},
        {8, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::floatExpression
        )},
        {9, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::stringExpression
        )},
        {10, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::charExpression
        )},
        {11, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::trueExpression
        )},
        {12, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::falseExpression
        )},
        {13, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::plus,
                        ASTNodeFactory::intExpression
                )
        )},
        {14, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        new ASTBinaryExpressionNode(
                                ASTNodeFactory::intExpression,
                                ASTNodeFactory::plus,
                                ASTNodeFactory::intExpression
                        ),
                        ASTNodeFactory::plus,
                        ASTNodeFactory::intExpression
                )
        )},
        {15, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::minus,
                        ASTNodeFactory::intExpression
                )
        )},
        {16, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::star,
                        ASTNodeFactory::intExpression
                )
        )},
        {17, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::slash,
                        ASTNodeFactory::intExpression
                )
        )},
        {18, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::intExpression,
                        ASTNodeFactory::modulo,
                        ASTNodeFactory::intExpression
                )
        )},
        {19, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::stringExpression,
                        ASTNodeFactory::plus,
                        ASTNodeFactory::stringExpression
                )
        )},
        {20, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::negativeInt
        )},
        {21, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::negativeInt,
                        ASTNodeFactory::plus,
                        ASTNodeFactory::intExpression
                )
        )},
        {22, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::negativeInt,
                        ASTNodeFactory::minus,
                        ASTNodeFactory::intExpression
                )
        )},
        {23, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::negativeInt,
                        ASTNodeFactory::star,
                        ASTNodeFactory::intExpression
                )
        )},
        {24, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::negativeInt,
                        ASTNodeFactory::slash,
                        ASTNodeFactory::intExpression
                )
        )},
        {25, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::negativeInt,
                        ASTNodeFactory::slash,
                        ASTNodeFactory::positiveInt
                )
        )},
        {26, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::positiveInt
        )},
        {27, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::positiveInt,
                        ASTNodeFactory::plus,
                        ASTNodeFactory::intExpression
                )
        )},
        {28, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::positiveInt,
                        ASTNodeFactory::minus,
                        ASTNodeFactory::intExpression
                )
        )},
        {29, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::positiveInt,
                        ASTNodeFactory::star,
                        ASTNodeFactory::intExpression
                )
        )},
        {30, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::positiveInt,
                        ASTNodeFactory::slash,
                        ASTNodeFactory::intExpression
                )
        )},
        {31, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTBinaryExpressionNode(
                        ASTNodeFactory::positiveInt,
                        ASTNodeFactory::slash,
                        ASTNodeFactory::negativeInt
                )
        )},
        {32, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTUnaryExpressionNode(
                        ASTNodeFactory::unaryMinus,
                        ASTNodeFactory::idExpression
                )
        )},
        {33, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::bangTrue
        )},
        {34, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::bangFalse
        )},
        {35, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                ASTNodeFactory::bangId
        )},
        {36, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::trueExpression,
                        ASTNodeFactory::andOperator,
                        ASTNodeFactory::falseExpression
                )
        )},
        {37, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::trueExpression,
                        ASTNodeFactory::orOperator,
                        ASTNodeFactory::falseExpression
                )
        )},
        {38, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::bangId,
                        ASTNodeFactory::andOperator,
                        ASTNodeFactory::trueExpression
                )
        )},
        {39, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::bangFalse,
                        ASTNodeFactory::andOperator,
                        ASTNodeFactory::trueExpression
                )
        )},
        {40, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::bangId,
                        ASTNodeFactory::orOperator,
                        ASTNodeFactory::trueExpression
                )
        )},
        {41, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        ASTNodeFactory::bangFalse,
                        ASTNodeFactory::orOperator,
                        ASTNodeFactory::trueExpression
                )
        )},
        {42, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        new ASTLogicalExpressionNode(
                                ASTNodeFactory::trueExpression,
                                ASTNodeFactory::andOperator,
                                ASTNodeFactory::falseExpression
                        ),
                        ASTNodeFactory::orOperator,
                        ASTNodeFactory::trueExpression
                )
        )},
        {43, new ASTVariableDeclarationNode(
                ASTNodeFactory::constInit,
                new ASTLogicalExpressionNode(
                        new ASTLogicalExpressionNode(
                                ASTNodeFactory::bangTrue,
                                ASTNodeFactory::andOperator,
                                ASTNodeFactory::falseExpression
                        ),
                        ASTNodeFactory::orOperator,
                        ASTNodeFactory::trueExpression
                )
        )},
};

TEST_CASE( "should print the expected reduced nodes" ) {
std::string filePath = "./syntax-analyzer-test-file.jet";
auto tokenTable = new TokenTable();
auto reservedKeywords = new ReservedKeywords();
auto lexicalAnalyzer = new LexicalAnalyzer(tokenTable, reservedKeywords);
auto syntaxAnalyzer = SyntaxAnalyzer(tokenTable, lexicalAnalyzer);
auto fileNodeResult = syntaxAnalyzer.analyze(filePath);
Logger::log("===== TEST LOGS =====");
REQUIRE(fileNodeResult->getBody().size() == 43);
    for (int i = 0; i < 43; i++) {
        Logger::log("=====", i + 1, fileNodeResult->getBody()[i]->toString(), "=====");
        REQUIRE(fileNodeResult->getBody()[i]->isEqual(expectedNodes[i+1]));
        Logger::log("====================================");
    }
}