//
// Created by Johny Georges on 2024-03-26.
//

#ifndef JETLANG_AST_OBJECT_ACCESS_SOURCE_NODE_H
#define JETLANG_AST_OBJECT_ACCESS_SOURCE_NODE_H

#include "../ast-expression-nodes/ast-expression-node.h"

class ASTObjectAccessSourceNode : public ASTNode {
private:
    std::shared_ptr<ASTExpressionNode> _source;
public:
    explicit ASTObjectAccessSourceNode(std::shared_ptr<ASTExpressionNode> source);
    std::shared_ptr<ASTExpressionNode> getSource();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_OBJECT_ACCESS_SOURCE_NODE_H
