//
// Created by Johny Georges on 2024-04-09.
//

#ifndef JETLANG_AST_ARRAY_TYPE_NODE_H
#define JETLANG_AST_ARRAY_TYPE_NODE_H

#include <string>
#include "ast-type-base-node.h"
#include "ast-type-parameter-list-node.h"

class ASTArrayTypeNode : public ASTTypeBaseNode {
private:
    ASTTypeNode* _elementType;
public:
    ASTArrayTypeNode(ASTTypeNode* elementType);
    ASTTypeNode* getElementType();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_ARRAY_TYPE_NODE_H
