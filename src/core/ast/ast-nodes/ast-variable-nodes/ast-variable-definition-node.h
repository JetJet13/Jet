//
// Created by Johny Georges on 2024-04-10.
//

#ifndef JETLANG_AST_VARIABLE_DEFINITION_NODE_H
#define JETLANG_AST_VARIABLE_DEFINITION_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "ast-variable-type-node.h"
#include "../ast-type-nodes/ast-type-node.h"

class ASTVariableDefinitionNode : public ASTNode {
    ASTVariableTypeNode* _assignmentTypeQualifier;
    ASTIdentifierNode* _identifier;
public:
    explicit ASTVariableDefinitionNode(ASTVariableTypeNode* assignmentTypeQualifier, ASTIdentifierNode* astIdentifierNode);
    ASTVariableTypeNode* getVarTypeNode();
    ASTIdentifierNode* getIdentifierNode();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_VARIABLE_DEFINITION_NODE_H
