//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_AST_TYPE_PARAMETER_LIST_NODE_H
#define JETLANG_AST_TYPE_PARAMETER_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-type-node.h"
#include "ast-type-parameter-list-start-node.h"
#include "ast-type-parameter-list-end-node.h"

class ASTTypeParameterListNode : public ASTNode {
protected:
    ASTTypeParameterListStartNode* _typeParameterListStartNode;
    ASTTypeParameterListEndNode* _typeParameterListEndNode;
    std::vector<ASTTypeNode*> _parameters;
public:
    ASTTypeParameterListNode(ASTTypeParameterListStartNode* typeParameterListStartNode, ASTTypeParameterListEndNode* typeParameterListEndNode);
    ASTTypeParameterListNode(ASTTypeParameterListStartNode* typeParameterListStartNode, std::vector<ASTTypeNode*> parameters, ASTTypeParameterListEndNode* typeParameterListEndNode);
    std::vector<ASTTypeNode*> getParameters();
    unsigned long numParameters();
    ASTTypeParameterListNode* addParameter(ASTTypeNode* parameter);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TYPE_PARAMETER_LIST_NODE_H
