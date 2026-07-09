//
// Created by Johny Georges on 2024-11-05.
//

#ifndef JETLANG_AST_MODULE_ACCESS_SOURCE_NODE_H
#define JETLANG_AST_MODULE_ACCESS_SOURCE_NODE_H

#include "../ast-expression-nodes/ast-identifier-expression-node.h"

class ASTModuleAccessSourceNode : public ASTNode {
private:
    std::shared_ptr<ASTIdentifierExpressionNode> _source;
public:
    explicit ASTModuleAccessSourceNode(std::shared_ptr<ASTIdentifierExpressionNode> source);
    std::shared_ptr<ASTIdentifierExpressionNode> getSource();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_MODULE_ACCESS_SOURCE_NODE_H
