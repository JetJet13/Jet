//
// Created by Johny Georges on 2024-05-31.
//

#ifndef JETLANG_AST_PROCEDURE_TYPE_NODE_H
#define JETLANG_AST_PROCEDURE_TYPE_NODE_H

#include "ast-type-base-node.h"
#include "ast-type-parameter-list-node.h"
#include "../ast-procedure-nodes/ast-procedure-node.h"
#include "../ast-lambda-nodes/ast-procedure-lambda-type-parameter-list-node.h"

class ASTProcedureTypeNode : public ASTTypeBaseNode {
private:
    ASTProcedureLambdaTypeParameterListNode* _parameterList;
public:
    ASTProcedureTypeNode(ASTProcedureLambdaTypeParameterListNode* parameterList);
    ASTTypeParameterListNode* getParameterList();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_PROCEDURE_TYPE_NODE_H
