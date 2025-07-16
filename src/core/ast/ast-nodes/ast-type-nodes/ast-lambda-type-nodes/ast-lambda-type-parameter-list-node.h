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
    ASTLambdaTypeParameterListStartNode* _startNode;
    ASTLambdaTypeParameterListEndNode* _endNode;
    std::vector<ASTCommaNode*> _commas;
    std::vector<ASTTypeNode*> _parameters;
public:
    ASTLambdaTypeParameterListNode(ASTLambdaTypeParameterListStartNode* startNode, ASTLambdaTypeParameterListEndNode* endNode);
    ASTLambdaTypeParameterListNode(ASTLambdaTypeParameterListStartNode* startNode, std::vector<ASTTypeNode*> parameters, std::vector<ASTCommaNode*> commas, ASTLambdaTypeParameterListEndNode* endNode);
    std::vector<ASTTypeNode*> getParameters();
    unsigned long numParameters();
    ASTLambdaTypeParameterListNode* addParameter(ASTTypeNode* parameter);
    ASTLambdaTypeParameterListNode* addComma(ASTCommaNode* comma);
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_LAMBDA_TYPE_PARAMETER_LIST_NODE_H
