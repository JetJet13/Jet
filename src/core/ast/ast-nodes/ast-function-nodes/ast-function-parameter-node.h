//
// Created by Johny Georges on 2024-03-20.
//

#ifndef JETLANG_AST_FUNCTION_PARAMETER_NODE_H
#define JETLANG_AST_FUNCTION_PARAMETER_NODE_H

#include <string>
#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"
#include "../../types/ast-node-type.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"
#include "../ast-type-node.h"

class ASTFunctionParameterNode : public ASTNode {
private:
    ASTIdentifierExpressionNode* _identifier;
    ASTTypeNode* _type;
public:
    ASTFunctionParameterNode(ASTIdentifierExpressionNode* identifier, ASTTypeNode* type);
    ASTIdentifierExpressionNode* getIdentifier();
    ASTTypeNode* getType();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_FUNCTION_PARAMETER_NODE_H
