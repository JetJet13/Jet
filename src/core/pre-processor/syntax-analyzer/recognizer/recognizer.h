//
// Created by Johny Georges on 2024-03-23.
//

#ifndef JETLANG_RECOGNIZER_H
#define JETLANG_RECOGNIZER_H

#include "../recognizer-result/recognizer-result.h"
#include "../handle/handle.h"
#include "types/recognizer-mode.h"
#include "../syntax-dfa/syntax-dfa.h"

class Recognizer {
private:
    SyntaxDfa* _syntaxDfa;
    RecognizerMode determineMode(Handle* handle);
    bool isBacktrackNode(std::optional<ASTNode*> astNode);
    bool isEndNode(std::optional<ASTNode*> lastReducedNode, std::optional<ASTNode*> peekNode);
public:
    Recognizer();
    RecognizerResult* recognize(Handle* handle);
};

#endif //JETLANG_RECOGNIZER_H
