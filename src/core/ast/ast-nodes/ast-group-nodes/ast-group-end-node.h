//
// Created by Johny Georges on 2024-03-07.
//

#ifndef JETLANG_AST_GROUP_END_NODE_H
#define JETLANG_AST_GROUP_END_NODE_H

#include <string>
#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"
#include "../../types/ast-node-type.h"
#include "../../../pre-processor/syntax-analyzer/types/syntax-analyzer-mode.h"

class ASTGroupEndNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    ASTGroupEndNode(Lexeme* lexeme);
    Lexeme* getLexeme();
    ASTNode* transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_GROUP_END_NODE_H
