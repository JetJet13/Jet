//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_AST_LAMBDA_TYPE_NODE_H
#define JETLANG_AST_LAMBDA_TYPE_NODE_H

#include "ast-type-base-node.h"
#include "ast-type-parameter-list-node.h"

class ASTLambdaTypeNode : public ASTTypeBaseNode {
private:
    ASTTypeParameterListNode* _parameterList;
    std::optional<ASTTypeNode*> _returnType;
public:
    ASTLambdaTypeNode(ASTTypeParameterListNode* parameterList, std::optional<ASTTypeNode*> returnType = {});
    ASTTypeParameterListNode* getParameterList();
    std::optional<ASTTypeNode*> getReturnType();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_LAMBDA_TYPE_NODE_H
