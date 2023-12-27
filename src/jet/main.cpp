//
// Created by Johny Georges on 2023-12-19.
//

#include "main.h"
#include "../core/symbol/symbol-types/int-symbol.h"
#include "../core/lexeme/lexeme.h"
#include "../shared/utils/logger/logger.h"
#include "../shared/types/exit-status.enum.h"


int main (int argc, const char* argv[]) {
    if (argc == 1) {
        Logger::log("no file provided...starting REPL");
        Logger::log("nevermind...REPL is not ready...exiting.");
    } else if (argc == 2) {
        const char* filePath = argv[1];
        Logger::log("executing file:", filePath);
        auto intSymbol = new IntSymbol();
        auto lex = new Lexeme<int>("num", intSymbol, 4);
        Logger::log(lex->toString());
    } else {
        Logger::log("too many arguments..exiting");
    }

    return EXIT_STATUS_OK;
}