//
// Created by Johny Georges on 2024-03-11.
//

#ifndef JETLANG_AST_ARRAY_ACCESS_EXPRESSION_NODE_H
#define JETLANG_AST_ARRAY_ACCESS_EXPRESSION_NODE_H

#include "ast-expression-node.h"
#include "ast-array-expression-node.h"
#include "../ast-array-nodes/ast-array-access-node.h"

class ASTArrayAccessExpressionNode : public ASTExpressionNode {
private:
    std::shared_ptr<ASTExpressionNode> _source;
    std::shared_ptr<ASTArrayAccessNode> _arrayAccess;
public:
    ASTArrayAccessExpressionNode(std::shared_ptr<ASTExpressionNode> source, std::shared_ptr<ASTArrayAccessNode> arrayAccess);
    std::shared_ptr<ASTExpressionNode> getSource();
    std::shared_ptr<ASTArrayAccessNode> getIndex();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ARRAY_ACCESS_EXPRESSION_NODE_H
