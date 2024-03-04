//
// Created by Johny Georges on 2024-03-04.
//

#ifndef JETLANG_AST_PLUS_BASE_NODE_H
#define JETLANG_AST_PLUS_BASE_NODE_H

#include <string>
#include "../ast-node.h"
#include "../../types/ast-node-type.h"

class ASTPlusBaseNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    explicit ASTPlusBaseNode(Lexeme* lexeme);
    ASTNode* transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode) override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_PLUS_BASE_NODE_H
