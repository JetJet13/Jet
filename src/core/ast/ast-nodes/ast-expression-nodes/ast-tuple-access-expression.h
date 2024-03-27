//
// Created by Johny Georges on 2024-03-26.
//

#ifndef JETLANG_AST_TUPLE_ACCESS_EXPRESSION_H
#define JETLANG_AST_TUPLE_ACCESS_EXPRESSION_H

#include "ast-expression-node.h"
#include "ast-array-expression-node.h"
#include "../ast-tuple-nodes/ast-tuple-access-node.h"
#include "../ast-object-nodes/ast-object-access-source-node.h"

class ASTTupleAccessExpressionNode : public ASTExpressionNode {
private:
    ASTObjectAccessSourceNode* _source;
    ASTTupleAccessNode* _index;
public:
    ASTTupleAccessExpressionNode(ASTObjectAccessSourceNode* source, ASTTupleAccessNode* index);
    ASTObjectAccessSourceNode* getSource();
    ASTTupleAccessNode* getIndex();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_TUPLE_ACCESS_EXPRESSION_H
