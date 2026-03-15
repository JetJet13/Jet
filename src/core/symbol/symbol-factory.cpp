//
// Created by Johny Georges on 2023-12-27.
//

#include "symbol-factory.h"
#include "symbol.h"

namespace SymbolFactory {

    std::shared_ptr<Symbol> createConstSymbol() {
        return std::make_shared<Symbol>(SYM_CONST, "const");
    }

    std::shared_ptr<Symbol> createEqualSymbol() {
        return std::make_shared<Symbol>(SYM_EQUAL, "=");
    }

    std::shared_ptr<Symbol> createColonEqualSymbol() {
        return std::make_shared<Symbol>(SYM_COLON_EQUAL, ":=");
    }

    std::shared_ptr<Symbol> createIdentifierSymbol() {
        return std::make_shared<Symbol>(SYM_IDENTIFIER, "id");
    }

    std::shared_ptr<Symbol> createIntSymbol() {
        return std::make_shared<Symbol>(SYM_INT, "int");
    }

    std::shared_ptr<Symbol> createFloatSymbol() {
        return std::make_shared<Symbol>(SYM_FLOAT, "float");
    }

    std::shared_ptr<Symbol> createSemicolonSymbol() {
        return std::make_shared<Symbol>(SYM_SEMICOLON, ";");
    }

    std::shared_ptr<Symbol> createLetSymbol() {
        return std::make_shared<Symbol>(SYM_LET, "let");
    }

    std::shared_ptr<Symbol> createModuloSymbol() {
        return std::make_shared<Symbol>(SYM_MODULO, "mod");
    }

    std::shared_ptr<Symbol> createPlusSymbol() {
        return std::make_shared<Symbol>(SYM_PLUS, "+");
    }

    std::shared_ptr<Symbol> createMinusSymbol() {
        return std::make_shared<Symbol>(SYM_MINUS, "-");
    }

    std::shared_ptr<Symbol> createStarSymbol() {
        return std::make_shared<Symbol>(SYM_STAR, "*");
    }

    std::shared_ptr<Symbol> createSlashSymbol() {
        return std::make_shared<Symbol>(SYM_SLASH, "/");
    }

    std::shared_ptr<Symbol> createLessThanSymbol() {
        return std::make_shared<Symbol>(SYM_LESS_THAN, "<");
    }

    std::shared_ptr<Symbol> createLessThanOrEqualSymbol() {
        return std::make_shared<Symbol>(SYM_LESS_THAN_OR_EQUAL, "<=");
    }

    std::shared_ptr<Symbol> createGreaterThanSymbol() {
        return std::make_shared<Symbol>(SYM_GREATER_THAN, ">");
    }

    std::shared_ptr<Symbol> createGreaterThanOrEqualSymbol() {
        return std::make_shared<Symbol>(SYM_GREATER_THAN_OR_EQUAL, ">=");
    }

    std::shared_ptr<Symbol> createTrueSymbol() {
        return std::make_shared<Symbol>(SYM_TRUE, "true");
    }

    std::shared_ptr<Symbol> createFalseSymbol() {
        return std::make_shared<Symbol>(SYM_FALSE, "false");
    }

    std::shared_ptr<Symbol> createAndSymbol() {
        return std::make_shared<Symbol>(SYM_AND, "&&");
    }

    std::shared_ptr<Symbol> createOrSymbol() {
        return std::make_shared<Symbol>(SYM_OR, "||");
    }

    std::shared_ptr<Symbol> createLeftParenSymbol() {
        return std::make_shared<Symbol>(SYM_LEFT_PAREN, "(");
    }

    std::shared_ptr<Symbol> createRightParenSymbol() {
        return std::make_shared<Symbol>(SYM_RIGHT_PAREN, ")");
    }

    std::shared_ptr<Symbol> createLeftBraceSymbol() {
        return std::make_shared<Symbol>(SYM_LEFT_BRACE, "{");
    }

    std::shared_ptr<Symbol> createRightBraceSymbol() {
        return std::make_shared<Symbol>(SYM_RIGHT_BRACE, "}");
    }

    std::shared_ptr<Symbol> createLeftBracketSymbol() {
        return std::make_shared<Symbol>(SYM_LEFT_BRACKET, "[");
    }

    std::shared_ptr<Symbol> createRightBracketSymbol() {
        return std::make_shared<Symbol>(SYM_RIGHT_BRACKET, "]");
    }

    std::shared_ptr<Symbol> createColonSymbol() {
        return std::make_shared<Symbol>(SYM_COLON, ":");
    }

    std::shared_ptr<Symbol> createCommaSymbol() {
        return std::make_shared<Symbol>(SYM_COMMA, ",");
    }

    std::shared_ptr<Symbol> createPeriodSymbol() {
        return std::make_shared<Symbol>(SYM_PERIOD, ".");
    }

    std::shared_ptr<Symbol> createBangSymbol() {
        return std::make_shared<Symbol>(SYM_BANG, "!");
    }

    std::shared_ptr<Symbol> createBangEqualSymbol() {
        return std::make_shared<Symbol>(SYM_BANG_EQUAL, "!=");
    }

    std::shared_ptr<Symbol> createEqualEqualSymbol() {
        return std::make_shared<Symbol>(SYM_EQUAL_EQUAL, "==");
    }

    std::shared_ptr<Symbol> createCharSymbol() {
        return std::make_shared<Symbol>(SYM_CHAR, "char");
    }

    std::shared_ptr<Symbol> createStringSymbol() {
        return std::make_shared<Symbol>(SYM_STRING, "string");
    }

    std::shared_ptr<Symbol> createMalformedSymbol(std::string malformedText) {
        return std::make_shared<Symbol>(SYM_MALFORMED, "[MALFORMED] - " + malformedText);
    }

    std::shared_ptr<Symbol> createFunctionSymbol() {
        return std::make_shared<Symbol>(SYM_FUNCTION, "func");
    }

    std::shared_ptr<Symbol> createReturnSymbol() {
        return std::make_shared<Symbol>(SYM_RETURN, "return");
    }

    std::shared_ptr<Symbol> createProcedureSymbol() {
        return std::make_shared<Symbol>(SYM_PROCEDURE, "proc");
    }

    std::shared_ptr<Symbol> createEnumSymbol() {
        return std::make_shared<Symbol>(SYM_ENUM, "enum");
    }

    std::shared_ptr<Symbol> createTupleSymbol() {
        return std::make_shared<Symbol>(SYM_TUPLE, "tuple");
    }

    std::shared_ptr<Symbol> createIfSymbol() {
        return std::make_shared<Symbol>(SYM_IF, "if");
    }

    std::shared_ptr<Symbol> createElseSymbol() {
        return std::make_shared<Symbol>(SYM_ELSE, "else");
    }

    std::shared_ptr<Symbol> createForSymbol() {
        return std::make_shared<Symbol>(SYM_FOR, "for");
    }

    std::shared_ptr<Symbol> createInSymbol() {
        return std::make_shared<Symbol>(SYM_IN, "in");
    }

    std::shared_ptr<Symbol> createWhileSymbol() {
        return std::make_shared<Symbol>(SYM_WHILE, "while");
    }

    std::shared_ptr<Symbol> createBreakSymbol() {
        return std::make_shared<Symbol>(SYM_BREAK, "break");
    }

    std::shared_ptr<Symbol> createSkipSymbol() {
        return std::make_shared<Symbol>(SYM_SKIP, "skip");
    }

    std::shared_ptr<Symbol> createTrySymbol() {
        return std::make_shared<Symbol>(SYM_TRY, "try");
    }

    std::shared_ptr<Symbol> createCatchSymbol() {
        return std::make_shared<Symbol>(SYM_CATCH, "catch");
    }

    std::shared_ptr<Symbol> createFinallySymbol() {
        return std::make_shared<Symbol>(SYM_FINALLY, "finally");
    }

    std::shared_ptr<Symbol> createFatArrowSymbol() {
        return std::make_shared<Symbol>(SYM_FAT_ARROW, "=>");
    }

    std::shared_ptr<Symbol> createVoidSymbol() {
        return std::make_shared<Symbol>(SYM_VOID_TYPE, "void_type");
    }

    std::shared_ptr<Symbol> createIntTypeSymbol() {
        return std::make_shared<Symbol>(SYM_INT_TYPE, "int_type");
    }

    std::shared_ptr<Symbol> createFloatTypeSymbol() {
        return std::make_shared<Symbol>(SYM_FLOAT_TYPE, "float_type");
    }

    std::shared_ptr<Symbol> createStringTypeSymbol() {
        return std::make_shared<Symbol>(SYM_STRING_TYPE, "string_type");
    }

    std::shared_ptr<Symbol> createCharTypeSymbol() {
        return std::make_shared<Symbol>(SYM_CHAR_TYPE, "char_type");
    }

    std::shared_ptr<Symbol> createBooleanTypeSymbol() {
        return std::make_shared<Symbol>(SYM_BOOLEAN_TYPE, "boolean_type");
    }

    std::shared_ptr<Symbol> createModuleSymbol() {
        return std::make_shared<Symbol>(SYM_MODULE, "module");
    }

    std::shared_ptr<Symbol> createAsSymbol() {
        return std::make_shared<Symbol>(SYM_AS, "as");
    }

    std::shared_ptr<Symbol> createImportSymbol() {
        return std::make_shared<Symbol>(SYM_IMPORT, "import");
    }

    std::shared_ptr<Symbol> createUseSymbol() {
        return std::make_shared<Symbol>(SYM_USE, "use");
    }

    std::shared_ptr<Symbol> createFromSymbol() {
        return std::make_shared<Symbol>(SYM_FROM, "from");
    }

    std::shared_ptr<Symbol> createDotDotSymbol() {
        return std::make_shared<Symbol>(SYM_DOT_DOT, "..");
    }

    std::shared_ptr<Symbol> createDotDotDotSymbol() {
        return std::make_shared<Symbol>(SYM_DOT_DOT_DOT, "...");
    }

    std::shared_ptr<Symbol> createColonColonSymbol() {
        return std::make_shared<Symbol>(SYM_COLON_COLON, "::");
    }

    std::shared_ptr<Symbol> createClassSymbol()  {
        return std::make_shared<Symbol>(SYM_CLASS, "class");
    }

    std::shared_ptr<Symbol> createPublicSymbol()  {
        return std::make_shared<Symbol>(SYM_PUBLIC, "public");
    }

    std::shared_ptr<Symbol> createProtectedSymbol()  {
        return std::make_shared<Symbol>(SYM_PROTECTED, "protected");
    }

    std::shared_ptr<Symbol> createPrivateSymbol()  {
        return std::make_shared<Symbol>(SYM_PRIVATE, "private");
    }

    std::shared_ptr<Symbol> createStaticSymbol()  {
        return std::make_shared<Symbol>(SYM_STATIC, "static");
    }

    std::shared_ptr<Symbol> createThisSymbol()  {
        return std::make_shared<Symbol>(SYM_THIS, "this");
    }

    std::shared_ptr<Symbol> createConstructorSymbol()  {
        return std::make_shared<Symbol>(SYM_CONSTRUCTOR, "constructor");
    }

    std::shared_ptr<Symbol> createNewSymbol()  {
        return std::make_shared<Symbol>(SYM_NEW, "new");
    }

    std::shared_ptr<Symbol> createExportSymbol()  {
        return std::make_shared<Symbol>(SYM_EXPORT, "export");
    }

    std::shared_ptr<Symbol> createRefSymbol()  {
        return std::make_shared<Symbol>(SYM_REF, "ref");
    }

    std::shared_ptr<Symbol> createDrefSymbol()  {
        return std::make_shared<Symbol>(SYM_DREF, "dref");
    }

    std::shared_ptr<Symbol> createSrefSymbol()  {
        return std::make_shared<Symbol>(SYM_SREF, "sref");
    }

    std::shared_ptr<Symbol> createConcatSymbol()  {
        return std::make_shared<Symbol>(SYM_CONCAT, "++");
    }

    std::shared_ptr<Symbol> createInterfaceSymbol()  {
        return std::make_shared<Symbol>(SYM_INTERFACE, "interface");
    }

    std::shared_ptr<Symbol> createImplementsSymbol()  {
        return std::make_shared<Symbol>(SYM_IMPLEMENTS, "implements");
    }

    std::shared_ptr<Symbol> createTypeSymbol()  {
        return std::make_shared<Symbol>(SYM_TYPE, "type");
    }

    std::shared_ptr<Symbol> createPrintSymbol()  {
        return std::make_shared<Symbol>(SYM_PRINT, "print");
    }
}