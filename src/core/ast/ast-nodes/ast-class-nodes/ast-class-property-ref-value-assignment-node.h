//
// Created by Johny Georges on 2026-02-18.
//

#ifndef JETLANG_AST_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_NODE_H
#define JETLANG_AST_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_NODE_H

#include <string>
#include "ast-class-property-name-node.h"
#include "../ast-node.h"
#include "./ast-class-property-access-node.h"
#include "../../../type-signature/unknown-type-signature/unknown-type-signature.h"
#include "../ast-operator-nodes/ast-ref-value-assignment-operator-node.h"

class ASTClassPropertyRefValueAssignmentNode : public ASTNode {
private:
    std::shared_ptr<ASTClassPropertyAccessNode> _classPropertyAccess;
    std::shared_ptr<ASTRefValueAssignmentOperatorNode> _assignmentOperator;
    TypeSignature* _typeSignature = new UnknownTypeSignature();
public:
    explicit ASTClassPropertyRefValueAssignmentNode(std::shared_ptr<ASTClassPropertyAccessNode> classPropertyAccess, std::shared_ptr<ASTRefValueAssignmentOperatorNode> assignmentOperator);
    std::shared_ptr<ASTClassAccessNode> getClassAccess();
    std::shared_ptr<ASTClassPropertyNameNode> getProperty();
    void setTypeSignature(TypeSignature* typeSignature);
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_REF_VALUE_ASSIGNMENT_NODE_H
