//
// Created by Johny Georges on 2024-02-23.
//

#include <catch2/catch_all.hpp>
#include "../../../../src/core/token/token-table.h"
#include "../../../../src/core/reserved-keywords/reserved-keywords.h"
#include "../../../../src/core/pre-processor/lexical-analyzer/lexical-analyzer.h"
#include "../../../../src/core/pre-processor/syntax-analyzer/syntax-analyzer.h"
#include "../../../../src/core/ast/ast-nodes/ast-declaration-nodes/ast-variable-declaration-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-literal-expression-node.h"
#include "../../../../src/core/symbol/symbol-factory.h"
#include "../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-int-literal-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-float-literal-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-string-literal-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-char-literal-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-literal-nodes/ast-boolean-literal-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-expression-nodes/ast-binary-expression-node.h"
#include "../../../../src/core/ast/ast-nodes/ast-operator-nodes/ast-binary-operators/ast-arithmetic-operators/ast-plus-operator-node.h"

Lexeme* createLexeme(Symbol* symbol) {
    return new Lexeme(new Token(symbol), 1, 0);
}

std::vector<ASTNode*> expectedNodes = {
        //        LET VARIABLE DECLARATION
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createVarSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                        ),
                new ASTLiteralExpressionNode(
                        new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createVarSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTFloatLiteralNode(createLexeme(SymbolFactory::createFloatSymbol()))
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createVarSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTStringLiteralNode(createLexeme(SymbolFactory::createStringSymbol()))
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createVarSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTCharLiteralNode(createLexeme(SymbolFactory::createCharSymbol()))
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createVarSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createTrueSymbol()))
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createVarSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createFalseSymbol()))
                )
        ),
//        CONST VARIABLE DECLARATION
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTFloatLiteralNode(createLexeme(SymbolFactory::createFloatSymbol()))
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTStringLiteralNode(createLexeme(SymbolFactory::createStringSymbol()))
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTCharLiteralNode(createLexeme(SymbolFactory::createCharSymbol()))
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createTrueSymbol()))
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol())                                )
                ),
                new ASTLiteralExpressionNode(
                        new ASTBooleanLiteralNode(createLexeme(SymbolFactory::createFalseSymbol()))
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTBinaryExpressionNode(
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        ),
                        new ASTPlusOperatorNode(createLexeme(SymbolFactory::createPlusSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        )
                )
        ),
        new ASTVariableDeclarationNode(
                new ASTVariableInitNode(
                        new ASTVariableTypeNode(createLexeme(SymbolFactory::createConstSymbol())),
                        new ASTIdentifierNode(createLexeme(SymbolFactory::createIdentifierSymbol()))
                ),
                new ASTBinaryExpressionNode(
                        new ASTBinaryExpressionNode(
                                new ASTLiteralExpressionNode(
                                        new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                                ),
                                new ASTPlusOperatorNode(createLexeme(SymbolFactory::createPlusSymbol())),
                                new ASTLiteralExpressionNode(
                                        new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                                )
                        ),
                        new ASTPlusOperatorNode(createLexeme(SymbolFactory::createPlusSymbol())),
                        new ASTLiteralExpressionNode(
                                new ASTIntLiteralNode(createLexeme(SymbolFactory::createIntSymbol()))
                        )
                )
        )

};

TEST_CASE( "should print the expected reduced nodes" ) {
std::string filePath = "./syntax-analyzer-test-file.jet";
auto tokenTable = new TokenTable();
auto reservedKeywords = new ReservedKeywords();
auto lexicalAnalyzer = new LexicalAnalyzer(tokenTable, reservedKeywords);
auto syntaxAnalyzer = SyntaxAnalyzer(tokenTable, lexicalAnalyzer);
auto fileNodeResult = syntaxAnalyzer.analyze(filePath);
Logger::log("===== TEST LOGS =====");
REQUIRE(fileNodeResult->getBody().size() == 16);
    for (int i = 0; i < 14; i++) {
        Logger::log("=====",fileNodeResult->getBody()[i]->toString(),"=====");
        REQUIRE(fileNodeResult->getBody()[i]->isEqual(expectedNodes[i]));
        Logger::log("====================================");

        // TODO IMPLEMENT isEqual overrides! (DONE)
    }

}