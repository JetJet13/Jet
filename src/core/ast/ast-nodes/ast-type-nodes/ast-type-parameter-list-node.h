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
#include "../ast-comma-node.h"

class ASTTypeParameterListNode : public ASTNode {
protected:
    std::shared_ptr<ASTTypeParameterListStartNode> _typeParameterListStartNode;
    std::shared_ptr<ASTTypeParameterListEndNode> _typeParameterListEndNode;
    std::vector<std::shared_ptr<ASTCommaNode>> _commas;
    std::vector<std::shared_ptr<ASTTypeNode>> _parameters;
public:
    ASTTypeParameterListNode(std::shared_ptr<ASTTypeParameterListStartNode> typeParameterListStartNode, std::shared_ptr<ASTTypeParameterListEndNode> typeParameterListEndNode);
    ASTTypeParameterListNode(std::shared_ptr<ASTTypeParameterListStartNode> typeParameterListStartNode, std::vector<std::shared_ptr<ASTTypeNode>> parameters, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTTypeParameterListEndNode> typeParameterListEndNode);
    std::vector<std::shared_ptr<ASTTypeNode>> getParameters();
    unsigned long numParameters();
    std::shared_ptr<ASTTypeParameterListNode> addParameter(std::shared_ptr<ASTTypeNode> parameter);
    std::shared_ptr<ASTTypeParameterListNode> addComma(std::shared_ptr<ASTCommaNode> comma);
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TYPE_PARAMETER_LIST_NODE_H
