//
// Created by Johny Georges on 2024-04-24.
//

#ifndef JETLANG_AST_CLASS_PROPERTY_ASSIGNMENT_NODE_H
#define JETLANG_AST_CLASS_PROPERTY_ASSIGNMENT_NODE_H

#include <string>
#include "ast-class-property-name-node.h"
#include "../ast-node.h"
#include "../../../type-signature/unknown-type-signature/unknown-type-signature.h"

class ASTClassPropertyAssignmentNode : public ASTNode {
private:
    ASTClassPropertyNameNode* _property;
    TypeSignature* _typeSignature = new UnknownTypeSignature();
public:
    explicit ASTClassPropertyAssignmentNode(ASTClassPropertyNameNode* property);
    ASTClassPropertyNameNode* getProperty();
    void setTypeSignature(TypeSignature* typeSignature);
    TypeSignature* getTypeSignature() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_ASSIGNMENT_NODE_H
