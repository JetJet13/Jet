//
// Created by Johny Georges on 2024-04-09.
//

#ifndef JETLANG_AST_ARRAY_TYPE_NODE_H
#define JETLANG_AST_ARRAY_TYPE_NODE_H

#include <string>
#include "../ast-type-nodes/ast-type-base-node.h"
#include "../ast-type-nodes/ast-type-parameter-list-node.h"

class ASTArrayTypeNode : public ASTTypeBaseNode {
private:
    ASTTypeParameterListNode* _typeParameterList;
public:
    ASTArrayTypeNode(ASTTypeParameterListNode* arrayTypeParameterList);
    ASTTypeParameterListNode* getParameterList();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_ARRAY_TYPE_NODE_H
