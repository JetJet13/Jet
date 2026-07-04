//
// Created by Johny Georges on 2024-04-24.
//

#ifndef JETLANG_AST_CLASS_PROPERTY_ASSIGNMENT_NODE_H
#define JETLANG_AST_CLASS_PROPERTY_ASSIGNMENT_NODE_H

#include <string>
#include "ast-class-property-name-node.h"
#include "../ast-node.h"
#include "../ast-operator-nodes/ast-assignment-operator-node.h"
#include "./ast-class-property-access-node.h"
#include "../../../type-signature/unknown-type-signature/unknown-type-signature.h"


class ASTClassPropertyAssignmentNode : public ASTNode {
private:
    std::shared_ptr<ASTClassPropertyAccessNode> _classPropertyAccess;
    std::shared_ptr<ASTAssignmentOperatorNode> _assignmentOperator;
    std::shared_ptr<TypeSignature> _typeSignature = std::make_shared<UnknownTypeSignature>();
public:
    explicit ASTClassPropertyAssignmentNode(std::shared_ptr<ASTClassPropertyAccessNode> classPropertyAccess, std::shared_ptr<ASTAssignmentOperatorNode> assignmentOperator);
    std::shared_ptr<ASTClassAccessNode> getClassAccess();
    std::shared_ptr<ASTClassPropertyNameNode> getProperty();
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

#endif //JETLANG_AST_CLASS_PROPERTY_ASSIGNMENT_NODE_H
