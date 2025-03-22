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
    ASTExpressionNode* _source;
    ASTArrayAccessNode* _arrayAccess;
public:
    ASTArrayAccessExpressionNode(ASTExpressionNode* source, ASTArrayAccessNode* arrayAccess);
    ASTExpressionNode* getSource();
    ASTArrayAccessNode* getIndex();
    void markAsReferenced() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ARRAY_ACCESS_EXPRESSION_NODE_H
