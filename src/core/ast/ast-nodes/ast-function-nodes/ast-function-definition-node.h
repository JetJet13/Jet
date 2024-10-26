//
// Created by Johny Georges on 2024-10-25.
//

#ifndef JETLANG_AST_FUNCTION_DEFINITION_NODE_H
#define JETLANG_AST_FUNCTION_DEFINITION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-function-nodes/ast-function-node.h"
#include "../ast-function-nodes/ast-function-name-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-type-nodes/ast-type-node.h"

class ASTFunctionDefinitionNode : public ASTNode {
private:
    ASTFunctionNode* _functionKeyword;
    ASTFunctionNameNode* _name;
    ASTFunctionParameterListNode* _parameters;
    ASTTypeNode* _returnType;
public:
    explicit ASTFunctionDefinitionNode(ASTFunctionNode* functionKeyword, ASTFunctionNameNode* name, ASTFunctionParameterListNode* parameters, ASTTypeNode* returnType);
    ASTFunctionParameterListNode* getParameters();
    ASTFunctionNameNode* getName();
    ASTTypeNode* getReturnType();
    unsigned long numParameters();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};


#endif //JETLANG_AST_FUNCTION_DEFINITION_NODE_H
