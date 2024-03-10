//
// Created by Johny Georges on 2024-03-09.
//

#ifndef JETLANG_AST_LEFT_BRACKET_NODE_H
#define JETLANG_AST_LEFT_BRACKET_NODE_H

#include <optional>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"

class ASTLeftBracketNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    explicit ASTLeftBracketNode(Lexeme* lexeme);
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_LEFT_BRACKET_NODE_H
