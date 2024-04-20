//
// Created by Johny Georges on 2024-04-19.
//

#ifndef JETLANG_AST_CLASS_BLOCK_END_NODE_H
#define JETLANG_AST_CLASS_BLOCK_END_NODE_H

#include <optional>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"
#include "../../../pre-processor/syntax-analyzer/types/syntax-analyzer-mode.h"

class ASTClassBlockEndNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    explicit ASTClassBlockEndNode(Lexeme* lexeme);
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_CLASS_BLOCK_END_NODE_H
