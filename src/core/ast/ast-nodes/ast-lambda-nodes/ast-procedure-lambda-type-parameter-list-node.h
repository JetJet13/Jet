//
// Created by Johny Georges on 2024-04-06.
//

#ifndef JETLANG_AST_PROCEDURE_LAMBDA_TYPE_PARAMETER_LIST_NODE_H
#define JETLANG_AST_PROCEDURE_LAMBDA_TYPE_PARAMETER_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-type-nodes/ast-type-parameter-list-node.h"
#include "../ast-procedure-nodes/ast-procedure-node.h"

class ASTProcedureLambdaTypeParameterListNode : public ASTNode {
private:
    ASTProcedureNode* _procedureKeyword;
    ASTTypeParameterListNode* _typeParameterList;
public:
    ASTProcedureLambdaTypeParameterListNode(ASTProcedureNode* procedureKeyword, ASTTypeParameterListNode* typeParameterList);
    ASTTypeParameterListNode* getTypeParameterList();
    std::vector<ASTTypeNode*> getParameters();
    unsigned long numParameters();
    ASTProcedureLambdaTypeParameterListNode* addParameter(ASTTypeNode* parameter);
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_PROCEDURE_LAMBDA_TYPE_PARAMETER_LIST_NODE_H
