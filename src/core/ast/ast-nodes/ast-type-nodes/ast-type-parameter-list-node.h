//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_AST_TYPE_PARAMETER_LIST_NODE_H
#define JETLANG_AST_TYPE_PARAMETER_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-type-node.h"

class ASTTypeParameterListNode : public ASTNode {
private:
    std::vector<ASTTypeNode*> _parameters;
public:
    ASTTypeParameterListNode();
    ASTTypeParameterListNode(std::vector<ASTTypeNode*> parameters);
    std::vector<ASTTypeNode*> getParameters();
    unsigned long numParameters();
    ASTTypeParameterListNode* addParameter(ASTTypeNode* parameter);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_TYPE_PARAMETER_LIST_NODE_H
