//
// Created by Johny Georges on 2024-02-09.
//

#ifndef JETLANG_AST_TERMINATOR_NODE_H
#define JETLANG_AST_TERMINATOR_NODE_H

#include "ast-node.h"

class ASTTerminatorNode : public ASTNode {
private:
    Lexeme* _terminator;
public:
    ASTTerminatorNode(Lexeme* lexeme);
    ASTNodeType getNodeType() override;
};

#endif //JETLANG_AST_TERMINATOR_NODE_H
