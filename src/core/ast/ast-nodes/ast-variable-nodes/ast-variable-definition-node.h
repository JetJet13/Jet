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
    std::shared_ptr<ASTVariableTypeNode> _assignmentTypeQualifier;
    std::shared_ptr<ASTIdentifierNode> _identifier;
public:
    explicit ASTVariableDefinitionNode(std::shared_ptr<ASTVariableTypeNode> assignmentTypeQualifier, std::shared_ptr<ASTIdentifierNode> astIdentifierNode);
    std::shared_ptr<ASTVariableTypeNode> getVarTypeNode();
    std::shared_ptr<ASTIdentifierNode> getIdentifierNode();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_VARIABLE_DEFINITION_NODE_H
