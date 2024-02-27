//
// Created by Johny Georges on 2024-01-06.
//

#include <catch2/catch_all.hpp>
#include "../../../../src/core/pre-processor/lexical-analyzer/lexical-analyzer.h"
#include "../../../../src/core/symbol/symbol-factory.h"
#include "../../../../src/shared/utils/logger/logger.h"


std::vector<Lexeme*> expectedLexemes = {
        new Lexeme(new Token(SymbolFactory::createVarSymbol()), 1, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 1, 4),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 1, 8),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 1, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 1, 11),

        new Lexeme(new Token(SymbolFactory::createVarSymbol()), 2, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 2, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 2, 8),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 2, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 2, 11),

        new Lexeme(new Token(SymbolFactory::createVarSymbol()), 3, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 3, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 3, 8),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 3, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 3, 11),

        new Lexeme(new Token(SymbolFactory::createVarSymbol()), 4, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 4, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 4, 8),
        new Lexeme(new Token(SymbolFactory::createMinusSymbol()), 4, 10),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 4, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 4, 11),

        new Lexeme(new Token(SymbolFactory::createVarSymbol()), 5, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 5, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 5, 8),
        new Lexeme(new Token(SymbolFactory::createMinusSymbol()), 5, 10),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 5, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 5, 11),

        new Lexeme(new Token(SymbolFactory::createVarSymbol()), 6, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 6, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 6, 8),
        new Lexeme(new Token(SymbolFactory::createMinusSymbol()), 6, 10),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 6, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 6, 11),

        new Lexeme(new Token(SymbolFactory::createConstSymbol()), 8, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 8, 4),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 8, 8),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 8, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 8, 11),

        new Lexeme(new Token(SymbolFactory::createConstSymbol()), 9, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 9, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 9, 8),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 9, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 9, 11),

        new Lexeme(new Token(SymbolFactory::createConstSymbol()), 10, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 10, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 10, 8),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 10, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 10, 11),

        new Lexeme(new Token(SymbolFactory::createConstSymbol()), 11, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 11, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 11, 8),
        new Lexeme(new Token(SymbolFactory::createMinusSymbol()), 11, 10),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 11, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 11, 11),

        new Lexeme(new Token(SymbolFactory::createConstSymbol()), 12, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 12, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 12, 8),
        new Lexeme(new Token(SymbolFactory::createMinusSymbol()), 12, 10),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 12, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 12, 11),

        new Lexeme(new Token(SymbolFactory::createConstSymbol()), 13, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 13, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 13, 8),
        new Lexeme(new Token(SymbolFactory::createMinusSymbol()), 13, 10),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 13, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 13, 11),

        new Lexeme(new Token(SymbolFactory::createVarSymbol()), 17, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 17, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 17, 8),
        new Lexeme(new Token(SymbolFactory::createTrueSymbol()), 17, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 17, 10),

        new Lexeme(new Token(SymbolFactory::createVarSymbol()), 18, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 18, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 18, 8),
        new Lexeme(new Token(SymbolFactory::createFalseSymbol()), 18, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 18, 10),

        new Lexeme(new Token(SymbolFactory::createVarSymbol()), 19, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 19, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 19, 8),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 19, 10),
        new Lexeme(new Token(SymbolFactory::createAndSymbol()), 19, 10),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 19, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 19, 10),

        new Lexeme(new Token(SymbolFactory::createVarSymbol()), 20, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 20, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 20, 8),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 20, 10),
        new Lexeme(new Token(SymbolFactory::createOrSymbol()), 20, 10),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 20, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 20, 10),

        new Lexeme(new Token(SymbolFactory::createVarSymbol()), 21, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 21, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 21, 8),
        new Lexeme(new Token(SymbolFactory::createBangSymbol()), 21, 10),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 21, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 21, 10),

        new Lexeme(new Token(SymbolFactory::createVarSymbol()), 22, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 22, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 22, 8),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 22, 10),
        new Lexeme(new Token(SymbolFactory::createBangEqualSymbol()), 22, 10),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 22, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 22, 10),

        new Lexeme(new Token(SymbolFactory::createVarSymbol()), 23, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 23, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 23, 8),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 23, 10),
        new Lexeme(new Token(SymbolFactory::createEqualEqualSymbol()), 23, 10),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 23, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 23, 10),

        new Lexeme(new Token(SymbolFactory::createConstSymbol()), 25, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 25, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 25, 8),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 25, 10),
        new Lexeme(new Token(SymbolFactory::createLessThanSymbol()), 25, 10),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 25, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 25, 10),

        new Lexeme(new Token(SymbolFactory::createConstSymbol()), 26, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 26, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 26, 8),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 26, 10),
        new Lexeme(new Token(SymbolFactory::createGreaterThanSymbol()), 26, 10),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 26, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 26, 10),

        new Lexeme(new Token(SymbolFactory::createConstSymbol()), 28, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 28, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 28, 8),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 28, 10),
        new Lexeme(new Token(SymbolFactory::createPlusSymbol()), 28, 10),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 28, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 28, 10),

        new Lexeme(new Token(SymbolFactory::createConstSymbol()), 29, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 29, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 29, 8),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 29, 10),
        new Lexeme(new Token(SymbolFactory::createMinusSymbol()), 29, 10),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 29, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 29, 10),

        new Lexeme(new Token(SymbolFactory::createConstSymbol()), 30, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 30, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 30, 8),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 30, 10),
        new Lexeme(new Token(SymbolFactory::createStarSymbol()), 30, 10),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 30, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 30, 10),

        new Lexeme(new Token(SymbolFactory::createConstSymbol()), 31, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 31, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 31, 8),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 31, 10),
        new Lexeme(new Token(SymbolFactory::createSlashSymbol()), 31, 10),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 31, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 31, 10),

        new Lexeme(new Token(SymbolFactory::createConstSymbol()), 33, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 33, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 33, 8),
        new Lexeme(new Token(SymbolFactory::createLeftBraceSymbol()), 33, 10),

        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 34, 0),
        new Lexeme(new Token(SymbolFactory::createColonSymbol()), 34, 3),
        new Lexeme(new Token(SymbolFactory::createTrueSymbol()), 34, 8),
        new Lexeme(new Token(SymbolFactory::createCommaSymbol()), 34, 10),

        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 35, 0),
        new Lexeme(new Token(SymbolFactory::createColonSymbol()), 35, 3),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 35, 8),

        new Lexeme(new Token(SymbolFactory::createRightBraceSymbol()), 36, 0),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 36, 3),

        new Lexeme(new Token(SymbolFactory::createVarSymbol()), 38, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 38, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 38, 8),
        new Lexeme(new Token(SymbolFactory::createLeftBracketSymbol()), 38, 10),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 38, 10),
        new Lexeme(new Token(SymbolFactory::createCommaSymbol()), 38, 10),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 38, 10),
        new Lexeme(new Token(SymbolFactory::createCommaSymbol()), 38, 10),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 38, 10),
        new Lexeme(new Token(SymbolFactory::createRightBracketSymbol()), 38, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 38, 10),

        new Lexeme(new Token(SymbolFactory::createConstSymbol()), 40, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 40, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 40, 8),
        new Lexeme(new Token(SymbolFactory::createLeftParenSymbol()), 40, 10),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 40, 10),
        new Lexeme(new Token(SymbolFactory::createPlusSymbol()), 40, 10),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 40, 10),
        new Lexeme(new Token(SymbolFactory::createRightParenSymbol()), 40, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 40, 10),

        new Lexeme(new Token(SymbolFactory::createVarSymbol()), 42, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 42, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 42, 8),
        new Lexeme(new Token(SymbolFactory::createStringSymbol()), 42, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 42, 10),

        new Lexeme(new Token(SymbolFactory::createVarSymbol()), 43, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 43, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 43, 8),
        new Lexeme(new Token(SymbolFactory::createCharSymbol()), 43, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 43, 10),

        new Lexeme(new Token(SymbolFactory::createVarSymbol()), 44, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 44, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 44, 8),
        new Lexeme(new Token(SymbolFactory::createCharSymbol()), 44, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 44, 10),

        new Lexeme(new Token(SymbolFactory::createConstSymbol()), 46, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 46, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 46, 8),
        new Lexeme(new Token(SymbolFactory::createFloatSymbol()), 46, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 46, 10),

        new Lexeme(new Token(SymbolFactory::createConstSymbol()), 47, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 47, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 47, 8),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 47, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 47, 10),

        new Lexeme(new Token(SymbolFactory::createVarSymbol()), 49, 0),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol()), 49, 3),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol()), 49, 8),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 49, 10),
        new Lexeme(new Token(SymbolFactory::createModuloSymbol()), 49, 10),
        new Lexeme(new Token(SymbolFactory::createIntSymbol()), 49, 10),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol()), 49, 10),
};

TEST_CASE( "should create 217 lexemes with the correct token symbol type" ) {
    std::string filePath = "./lexical-analyzer-test-file.jet";
    auto lexicalAnalyzer = LexicalAnalyzer(new TokenTable(), new ReservedKeywords());
    lexicalAnalyzer.start(filePath);
    auto tokenCounter = 0;
    auto lexeme = lexicalAnalyzer.next();
    while (lexeme) {
        auto expectedLexeme = expectedLexemes[tokenCounter];

        REQUIRE(lexeme.value()->getToken()->getSymbolType() == expectedLexeme->getToken()->getSymbolType());
        REQUIRE(lexeme.value()->getLine() == expectedLexeme->getLine());
//        REQUIRE(lexeme->getPosition() == expectedLexeme->getPosition());
        tokenCounter++;
        lexeme = lexicalAnalyzer.next();
    }
    REQUIRE(tokenCounter == 217);
}