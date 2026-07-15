//
// Created by Johny Georges on 2026-02-18.
//

#ifndef JETLANG_AST_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_NODE_H
#define JETLANG_AST_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_NODE_H

#include <string>
#include "ast-class-property-name-node.h"
#include "../ast-node.h"
#include "./ast-class-property-access-node.h"
#include "../../../type-signature/unknown-type-signature/unknown-type-signature.h"
#include "../ast-operator-nodes/ast-shared-value-assignment-operator-node.h"

class ASTClassPropertySharedValueAssignmentNode : public ASTNode {
private:
    std::shared_ptr<ASTClassPropertyAccessNode> _classPropertyAccess;
    std::shared_ptr<ASTSharedValueAssignmentOperatorNode> _assignmentOperator;
    std::shared_ptr<TypeSignature> _typeSignature = std::make_shared<UnknownTypeSignature>();
public:
    explicit ASTClassPropertySharedValueAssignmentNode(std::shared_ptr<ASTClassPropertyAccessNode> classPropertyAccess, std::shared_ptr<ASTSharedValueAssignmentOperatorNode> assignmentOperator);
    std::shared_ptr<ASTClassAccessNode> getClassAccess();
    std::shared_ptr<ASTClassPropertyNameNode> getProperty();
    void setTypeSignature(std::shared_ptr<TypeSignature> typeSignature);
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_SHARED_VALUE_ASSIGNMENT_NODE_H
