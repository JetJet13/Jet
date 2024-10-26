//
// Created by Johny Georges on 2024-10-25.
//

#ifndef JETLANG_AST_PROCEDURE_DEFINITION_NODE_H
#define JETLANG_AST_PROCEDURE_DEFINITION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-function-nodes/ast-function-name-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "ast-procedure-node.h"

class ASTProcedureDefinitionNode : public ASTNode {
private:
    ASTProcedureNode* _procedureKeyword;
    ASTFunctionNameNode* _name;
    ASTFunctionParameterListNode* _parameters;
public:
    explicit ASTProcedureDefinitionNode(ASTProcedureNode* functionKeyword, ASTFunctionNameNode* name, ASTFunctionParameterListNode* parameters);
    ASTFunctionParameterListNode* getParameters();
    ASTFunctionNameNode* getName();
    unsigned long numParameters();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_PROCEDURE_DEFINITION_NODE_H
