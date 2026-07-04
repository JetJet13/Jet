//
// Created by Johny Georges on 2024-03-22.
//

#ifndef JETLANG_AST_VARIABLE_ASSIGNMENT_NODE_H
#define JETLANG_AST_VARIABLE_ASSIGNMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "ast-variable-type-node.h"
#include "../ast-operator-nodes/ast-assignment-operator-node.h"

class ASTVariableAssignmentNode : public ASTNode {
private:
    std::shared_ptr<ASTIdentifierNode> _identifier;
    std::shared_ptr<ASTAssignmentOperatorNode> _assignmentOperator;
    std::shared_ptr<TypeSignature> _typeSignature = std::make_shared<UnknownTypeSignature>();
public:
    explicit ASTVariableAssignmentNode(std::shared_ptr<ASTIdentifierNode> astIdentifierNode, std::shared_ptr<ASTAssignmentOperatorNode> assignmentOperator);
    std::shared_ptr<ASTIdentifierNode> getIdentifierNode();
    void setTypeSignature(std::shared_ptr<TypeSignature> typeSignature);
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_VARIABLE_ASSIGNMENT_NODE_H
