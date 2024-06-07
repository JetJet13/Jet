//
// Created by Johny Georges on 2024-01-06.
//

#include <catch2/catch_all.hpp>
#include "../../../../src/core/pre-processor/lexical-analyzer/lexical-analyzer.h"
#include "../../../../src/core/symbol/symbol-factory.h"
#include "../../../../src/shared/utils/logger/logger.h"

std::string foo = "foo";
std::string bar = "bar";

std::vector<Lexeme*> expectedLexemes = {
        new Lexeme(new Token(SymbolFactory::createVarSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "one")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "1")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createVarSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "twenty")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "20")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createVarSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "hundred")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "100")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createVarSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "negOne")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createMinusSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "1")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createVarSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "negTwenty")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createMinusSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "20")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createVarSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "negHundred")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createMinusSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "100")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createConstSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "two")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "2")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createConstSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "thirty")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "30")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createConstSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "twoHundred")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "200")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createConstSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "negTwo")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createMinusSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "2")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createConstSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "negThirty")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createMinusSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "30")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createConstSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "negTwoHundred")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createMinusSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "200")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createVarSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createTrueSymbol())),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createVarSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), bar)),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createFalseSymbol())),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createVarSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "fun")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(new Token(SymbolFactory::createAndSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), bar)),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createVarSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "nor")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(new Token(SymbolFactory::createOrSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), bar)),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createVarSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "fig")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(new Token(SymbolFactory::createAndSymbol())),
        new Lexeme(new Token(SymbolFactory::createBangSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), bar)),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createVarSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "bang")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createBangSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createVarSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "bangEqual")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(new Token(SymbolFactory::createBangEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), bar)),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createVarSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "equalEqual")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(new Token(SymbolFactory::createEqualEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), bar)),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createConstSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "yes")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "2")),
        new Lexeme(new Token(SymbolFactory::createLessThanSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "20")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createConstSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "no")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "10")),
        new Lexeme(new Token(SymbolFactory::createGreaterThanSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "100")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createConstSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "add")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "1")),
        new Lexeme(new Token(SymbolFactory::createPlusSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "2")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createConstSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "subtract")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "2")),
        new Lexeme(new Token(SymbolFactory::createMinusSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "1")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createConstSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "multiply")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "5")),
        new Lexeme(new Token(SymbolFactory::createStarSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "5")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createConstSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "divide")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "10")),
        new Lexeme(new Token(SymbolFactory::createSlashSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "2")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createConstSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "obj")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createLeftBraceSymbol())),

        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(new Token(SymbolFactory::createColonSymbol())),
        new Lexeme(new Token(SymbolFactory::createTrueSymbol())),
        new Lexeme(new Token(SymbolFactory::createCommaSymbol())),

        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), bar)),
        new Lexeme(new Token(SymbolFactory::createColonSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "100")),

        new Lexeme(new Token(SymbolFactory::createRightBraceSymbol())),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createVarSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "arr")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createLeftBracketSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "1")),
        new Lexeme(new Token(SymbolFactory::createCommaSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "2")),
        new Lexeme(new Token(SymbolFactory::createCommaSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "3")),
        new Lexeme(new Token(SymbolFactory::createRightBracketSymbol())),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createConstSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "answer")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createLeftParenSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "10")),
        new Lexeme(new Token(SymbolFactory::createPlusSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "1")),
        new Lexeme(new Token(SymbolFactory::createRightParenSymbol())),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createVarSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "moose")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createStringSymbol(), "hello world")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createVarSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "miro")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createCharSymbol(), "c")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createVarSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "beaver")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createCharSymbol(), "\n")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createConstSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "bid")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createFloatSymbol(), "10.12")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createConstSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "ante")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "13")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createVarSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "modulo")),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "5")),
        new Lexeme(new Token(SymbolFactory::createModuloSymbol())),
        new Lexeme(new Token(SymbolFactory::createIntSymbol(), "10")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(new Token(SymbolFactory::createColonColonSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), bar)),
        new Lexeme(new Token(SymbolFactory::createColonColonSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), "baz")),
        new Lexeme(new Token(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(new Token(SymbolFactory::createStringSymbol(), "hello")),
        new Lexeme(new Token(SymbolFactory::createPlusSymbol())),
        new Lexeme(new Token(SymbolFactory::createStringSymbol(), "world")),

        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(new Token(SymbolFactory::createEqualSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(new Token(SymbolFactory::createColonColonSymbol())),
        new Lexeme(new Token(SymbolFactory::createIdentifierSymbol(), bar)),
};

TEST_CASE( "should create 233 lexemes with the correct token symbol type" ) {
    std::string filePath = "./lexical-analyzer-test-file.jet";
    auto lexicalAnalyzer = LexicalAnalyzer(new TokenTable(), new ReservedKeywords());
    lexicalAnalyzer.start(filePath);
    auto tokenCounter = 0;
    auto lexeme = lexicalAnalyzer.next();
    while (lexeme) {
        auto expectedLexeme = expectedLexemes[tokenCounter];
        REQUIRE(lexeme.value()->getToken()->getSymbolType() == expectedLexeme->getToken()->getSymbolType());
        REQUIRE(lexeme.value()->getToken()->getRawValue() == expectedLexeme->getToken()->getRawValue());
        tokenCounter++;
        lexeme = lexicalAnalyzer.next();
    }
    REQUIRE(tokenCounter == 233);
}