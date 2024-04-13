//
// Created by Johny Georges on 2024-04-13.
//

#ifndef JETLANG_AST_STAR_BASE_NODE_H
#define JETLANG_AST_STAR_BASE_NODE_H

#include <string>
#include "../ast-node.h"
#include "../../types/ast-node-type.h"
#include "../../../pre-processor/syntax-analyzer/types/syntax-analyzer-mode.h"

class ASTStarBaseNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    explicit ASTStarBaseNode(Lexeme* lexeme);
    ASTNode* transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
};


#endif //JETLANG_AST_STAR_BASE_NODE_H
