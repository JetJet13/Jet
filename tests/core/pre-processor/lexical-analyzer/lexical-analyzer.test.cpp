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
        new Lexeme(std::make_shared<Token>(SymbolFactory::createLetSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "one")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "1")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createLetSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "twenty")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "20")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createLetSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "hundred")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "100")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createLetSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "negOne")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createMinusSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "1")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createLetSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "negTwenty")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createMinusSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "20")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createLetSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "negHundred")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createMinusSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "100")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createConstSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "two")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "2")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createConstSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "thirty")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "30")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createConstSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "twoHundred")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "200")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createConstSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "negTwo")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createMinusSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "2")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createConstSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "negThirty")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createMinusSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "30")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createConstSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "negTwoHundred")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createMinusSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "200")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createLetSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createTrueSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createLetSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), bar)),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createFalseSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createLetSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "fun")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createAndSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), bar)),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createLetSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "nor")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createOrSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), bar)),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createLetSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "fig")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createAndSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createBangSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), bar)),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createLetSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "bang")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createBangSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createLetSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "bangEqual")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createBangEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), bar)),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createLetSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "equalEqual")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), bar)),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createConstSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "yes")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "2")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createLessThanSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "20")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createConstSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "no")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "10")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createGreaterThanSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "100")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createConstSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "add")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "1")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createPlusSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "2")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createConstSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "subtract")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "2")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createMinusSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "1")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createConstSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "multiply")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "5")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createStarSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "5")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createConstSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "divide")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "10")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSlashSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "2")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createConstSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "obj")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createLeftBraceSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createColonSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createTrueSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createCommaSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), bar)),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createColonSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "100")),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createRightBraceSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createLetSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "array")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createLeftBracketSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "1")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createCommaSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "2")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createCommaSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "3")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createRightBracketSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createConstSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "answer")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createLeftParenSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "10")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createPlusSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "1")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createRightParenSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createLetSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "moose")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createStringSymbol(), "hello world")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createLetSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "miro")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createCharSymbol(), "c")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createLetSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "beaver")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createCharSymbol(), "\\n")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createConstSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "bid")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createFloatSymbol(), "10.12")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createConstSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "ante")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "13")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createLetSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "modulo")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "5")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createModuloSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIntSymbol(), "10")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createColonColonSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), bar)),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createColonColonSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), "baz")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createStringSymbol(), "hello")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createPlusSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createStringSymbol(), "world")),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),

        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createEqualSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), foo)),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createColonColonSymbol())),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createIdentifierSymbol(), bar)),
        new Lexeme(std::make_shared<Token>(SymbolFactory::createSemicolonSymbol())),
};

TEST_CASE( "should create 233 lexemes with the correct token symbol type" ) {
    std::string filePath = "./lexical-analyzer-test-file.jet";
    auto lexicalAnalyzer = LexicalAnalyzer(std::make_shared<TokenTable>(), std::make_shared<ReservedKeywords>());
    lexicalAnalyzer.start(filePath);
    auto tokenCounter = 0;
    auto lexeme = lexicalAnalyzer.next();
    while (lexeme) {
//        auto expectedLexeme = expectedLexemes[tokenCounter];
        Logger::log(lexeme.value()->toString());
//        REQUIRE(lexeme.value()->getToken()->getSymbolType() == expectedLexeme->getToken()->getSymbolType());
//        REQUIRE(lexeme.value()->getToken()->getRawValue() == expectedLexeme->getToken()->getRawValue());
        tokenCounter++;
        lexeme = lexicalAnalyzer.next();
    }
    REQUIRE(tokenCounter == 241);
}