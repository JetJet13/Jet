//
// Created by Johny Georges on 2024-04-06.
//

#ifndef JETLANG_AST_FUNCTION_LAMBDA_TYPE_PARAMETER_LIST_NODE_H
#define JETLANG_AST_FUNCTION_LAMBDA_TYPE_PARAMETER_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-type-nodes/ast-type-parameter-list-node.h"
#include "../ast-function-nodes/ast-function-node.h"

class ASTFunctionLambdaTypeParameterListNode : public ASTNode {
private:
    ASTFunctionNode* _functionKeyword;
    ASTTypeParameterListNode* _typeParameterList;
public:
    ASTFunctionLambdaTypeParameterListNode(ASTFunctionNode* functionKeyword, ASTTypeParameterListNode* typeParameterList);
    ASTTypeParameterListNode* getTypeParameterList();
    std::vector<ASTTypeNode*> getParameters();
    unsigned long numParameters();
    ASTFunctionLambdaTypeParameterListNode* addParameter(ASTTypeNode* parameter);
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FUNCTION_LAMBDA_TYPE_PARAMETER_LIST_NODE_H
