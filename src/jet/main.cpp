//
// Created by Johny Georges on 2023-12-19.
//

#include <vector>
#include "main.h"
#include "../core/lexeme/lexeme.h"
#include "../shared/utils/logger/logger.h"
#include "../shared/types/exit-status.enum.h"
#include "../core/symbol/symbol-factory.h"
#include "../core/token/token-factory.h"
#include "../core/symbol/symbol-table.h"
#include "../shared/utils/file-io/file-io.h"
#include "../core/reserved-keywords/reserved-keywords.h"
#include "../core/file-reader/file-reader.h"
#include "../shared/types/new-line.h"


int main (int argc, const char* argv[]) {
    if (argc == 1) {
        Logger::log("no file provided...starting REPL");
        Logger::log("nevermind...REPL is not ready...exiting.");
    } else if (argc == 2) {
        std::string filePath = argv[1];
        Logger::log("executing file:", filePath);
        auto intToken = TokenFactory::createIntToken(4);
        auto lex = new Lexeme<int>("num", intToken);
        Logger::log(lex->toString());
        auto symbolTable = new SymbolTable();
        symbolTable->get(SYM_IDENTIFIER);
        auto reservedKeywords = new ReservedKeywords();
        auto keyword = reservedKeywords->match("int");
        if (keyword) {
            Logger::log("found reserved keyword", keyword.value()->toString());
        } else {
            Logger::log("failed to find reserved keyword");
        }
        FileReader fileReader = FileReader();
        fileReader.open(filePath);
        std::vector<std::string> texts;
        std::string text;
        while (fileReader.peek()) {
            std::string c;
            c += fileReader.advance().value();
            if (c == " ") {
                Logger::log("found whitespace");
                Logger::log("text finalized:", text);
                if (text != " " && !text.empty()){
                    texts.push_back(text);
                }
                text = "";
                Logger::log("-----------");
            } else if (reservedKeywords->match(c)) {
                Logger::log("char is reserved keyword", c);
                Logger::log("text finalized:", text);
                if (text != " " && !text.empty()){
                    texts.push_back(text);
                }
                texts.push_back(c);
                text = "";
                Logger::log("-----------");
            } else if (c[0] != NEW_LINE && c[0] != ' ') {
                text += c;
            }
        }

        for (const auto& item: texts) {
            Logger::log(":: ",item);
        }
        fileReader.close();

    } else {
        Logger::log("too many arguments..exiting");
    }

    return EXIT_STATUS_OK;
}