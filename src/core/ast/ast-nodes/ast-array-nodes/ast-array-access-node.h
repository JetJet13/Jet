//
// Created by Johny Georges on 2024-03-12.
//

#ifndef JETLANG_AST_ARRAY_ACCESS_NODE_H
#define JETLANG_AST_ARRAY_ACCESS_NODE_H

#include <string>
#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"

class ASTArrayAccessNode : public ASTNode {
private:
    ASTExpressionNode* _index;
public:
    explicit ASTArrayAccessNode(ASTExpressionNode* index);
    ASTExpressionNode* getIndex();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};


#endif //JETLANG_AST_ARRAY_ACCESS_NODE_H
