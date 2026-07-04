//
// Created by Johny Georges on 2025-07-09.
//

#ifndef JETLANG_AST_LAMBDA_TYPE_PARAMETER_LIST_NODE_H
#define JETLANG_AST_LAMBDA_TYPE_PARAMETER_LIST_NODE_H

#include <string>
#include "../../ast-node.h"
#include "../ast-type-node.h"
#include "ast-lambda-type-parameter-list-start-node.h"
#include "ast-lambda-type-parameter-list-end-node.h"
#include "../../ast-comma-node.h"

class ASTLambdaTypeParameterListNode : public ASTNode {
protected:
    std::shared_ptr<ASTLambdaTypeParameterListStartNode> _startNode;
    std::shared_ptr<ASTLambdaTypeParameterListEndNode> _endNode;
    std::vector<std::shared_ptr<ASTCommaNode>> _commas;
    std::vector<std::shared_ptr<ASTTypeNode>> _parameters;
public:
    ASTLambdaTypeParameterListNode(std::shared_ptr<ASTLambdaTypeParameterListStartNode> startNode, std::shared_ptr<ASTLambdaTypeParameterListEndNode> endNode);
    ASTLambdaTypeParameterListNode(std::shared_ptr<ASTLambdaTypeParameterListStartNode> startNode, std::vector<std::shared_ptr<ASTTypeNode>> parameters, std::vector<std::shared_ptr<ASTCommaNode>> commas, std::shared_ptr<ASTLambdaTypeParameterListEndNode> endNode);
    std::vector<std::shared_ptr<ASTTypeNode>> getParameters();
    unsigned long numParameters();
    std::shared_ptr<ASTLambdaTypeParameterListNode> addParameter(std::shared_ptr<ASTTypeNode> parameter);
    std::shared_ptr<ASTLambdaTypeParameterListNode> addComma(std::shared_ptr<ASTCommaNode> comma);
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_LAMBDA_TYPE_PARAMETER_LIST_NODE_H
