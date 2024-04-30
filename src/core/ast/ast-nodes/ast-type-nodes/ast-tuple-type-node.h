//
// Created by Johny Georges on 2024-04-09.
//

#ifndef JETLANG_AST_TUPLE_TYPE_NODE_H
#define JETLANG_AST_TUPLE_TYPE_NODE_H

#include <string>
#include "ast-type-base-node.h"
#include "ast-type-parameter-list-node.h"

class ASTTupleTypeNode : public ASTTypeBaseNode {
private:
    ASTTypeParameterListNode* _typeParameterList;
public:
    ASTTupleTypeNode(ASTTypeParameterListNode* tupleTypeParameterList);
    ASTTypeParameterListNode* getParameterList();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    BaseType* getType() override;
};

#endif //JETLANG_AST_TUPLE_TYPE_NODE_H
