//
// Created by Johny Georges on 2024-02-08.
//

#ifndef JETLANG_AST_ASSIGNMENT_NODE_H
#define JETLANG_AST_ASSIGNMENT_NODE_H


#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"
#include "../ast-symbol-node.h"

class ASTAssignmentOperatorNode : public ASTSymbolNode {
    using ASTSymbolNode::ASTSymbolNode;
public:
    ASTNode* transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_ASSIGNMENT_NODE_H
