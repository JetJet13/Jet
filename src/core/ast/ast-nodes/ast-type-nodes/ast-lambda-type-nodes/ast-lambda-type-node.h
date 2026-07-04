//
// Created by Johny Georges on 2025-07-09.
//

#ifndef JETLANG_AST_LAMBDA_TYPE_NODE_H
#define JETLANG_AST_LAMBDA_TYPE_NODE_H

#include "../ast-type-base-node.h"
#include "../../ast-lambda-nodes/ast-lambda-type-fat-arrow-node.h"
#include "ast-lambda-type-parameter-list-node.h"

class ASTLambdaTypeNode : public ASTTypeBaseNode {
private:
    std::shared_ptr<ASTLambdaTypeParameterListNode> _parameterList;
    std::shared_ptr<ASTLambdaTypeFatArrowNode> _fatArrowNode;
    std::shared_ptr<ASTTypeNode> _returnType;
public:
    ASTLambdaTypeNode(std::shared_ptr<ASTLambdaTypeParameterListNode> parameterList, std::shared_ptr<ASTLambdaTypeFatArrowNode> fatArrowNode, std::shared_ptr<ASTTypeNode> returnType);
    std::shared_ptr<ASTLambdaTypeParameterListNode> getParameterList();
    std::shared_ptr<ASTTypeNode> getReturnType();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_LAMBDA_TYPE_NODE_H
