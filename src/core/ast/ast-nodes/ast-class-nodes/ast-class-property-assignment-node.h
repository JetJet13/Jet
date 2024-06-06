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
    ASTClassPropertyAccessNode* _classPropertyAccess;
    ASTAssignmentOperatorNode* _assignmentOperator;
    TypeSignature* _typeSignature = new UnknownTypeSignature();
public:
    explicit ASTClassPropertyAssignmentNode(ASTClassPropertyAccessNode* classPropertyAccess, ASTAssignmentOperatorNode* assignmentOperator);
    ASTClassPropertyNameNode* getProperty();
    void setTypeSignature(TypeSignature* typeSignature);
    TypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_ASSIGNMENT_NODE_H
