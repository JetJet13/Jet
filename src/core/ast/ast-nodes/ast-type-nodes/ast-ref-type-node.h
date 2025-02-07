//
// Created by Johny Georges on 2025-02-07.
//

#ifndef JETLANG_AST_REF_TYPE_NODE_H
#define JETLANG_AST_REF_TYPE_NODE_H

#include <string>
#include "ast-type-base-node.h"
#include "ast-type-parameter-list-node.h"
#include "../ast-array-nodes/ast-array-node.h"
#include "../ast-array-nodes/ast-array-type-keyword-node.h"
#include "../ast-base-nodes/ast-ref-base-node.h"

class ASTRefTypeNode : public ASTTypeBaseNode {
private:
    ASTRefBaseNode* _ref;
    ASTTypeParameterListNode* _typeParameterList;
public:
    ASTRefTypeNode(ASTRefBaseNode* refNode, ASTTypeParameterListNode* typeParameterList);
    ASTTypeNode* getRefType();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_REF_TYPE_NODE_H
