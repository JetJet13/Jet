//
// Created by Johny Georges on 2024-02-17.
//

#ifndef JETLANG_LEXEME_TRANSFORMER_H
#define JETLANG_LEXEME_TRANSFORMER_H

#include <optional>
#include "../../../ast/ast-nodes/ast-node.h"
#include "../../../lexeme/lexeme.h"


class LexemeTransformer {
public:
    ASTNode* transform(Lexeme lexeme);
};

#endif //JETLANG_LEXEME_TRANSFORMER_H
