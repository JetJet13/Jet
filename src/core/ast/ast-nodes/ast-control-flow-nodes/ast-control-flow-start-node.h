//
// Created by Johny Georges on 2024-03-28.
//

#ifndef JETLANG_AST_CONTROL_FLOW_START_NODE_H
#define JETLANG_AST_CONTROL_FLOW_START_NODE_H

#include <string>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"

class ASTControlFlowStartNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    ASTControlFlowStartNode(Lexeme* lexeme);
    Lexeme* getLexeme();
    ASTNode *transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode,
                                  SyntaxAnalyzerMode mode) override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_CONTROL_FLOW_START_NODE_H
