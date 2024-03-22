//
// Created by Johny Georges on 2024-03-13.
//

#ifndef JETLANG_AST_BLOCK_END_NODE_H
#define JETLANG_AST_BLOCK_END_NODE_H

#include <optional>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"

class ASTBlockEndNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    explicit ASTBlockEndNode(Lexeme* lexeme);
    ASTNode* transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_BLOCK_END_NODE_H
