//
// Created by Johny Georges on 2025-06-25.
//

#ifndef JETLANG_AST_INTERFACE_PROPERTY_NODE_H
#define JETLANG_AST_INTERFACE_PROPERTY_NODE_H

#include <string>
#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"
#include "../../types/ast-node-type.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-type-nodes/ast-type-colon-node.h"
#include "../../../type-signature/interface-property-type-signature/interface-property-type-signature.h"

class ASTInterfacePropertyNode : public ASTNode {
private:
    ASTIdentifierExpressionNode* _identifier;
    ASTTypeColonNode* _colon;
    ASTTypeNode* _type;
    InterfacePropertyTypeSignature* _typeSignature = new InterfacePropertyTypeSignature("_", new UnknownTypeSignature());
public:
    ASTInterfacePropertyNode(ASTIdentifierExpressionNode* identifier, ASTTypeColonNode* colon, ASTTypeNode* type);
    ASTIdentifierExpressionNode* getIdentifier();
    ASTTypeNode* getType();
    void setTypeSignature(InterfacePropertyTypeSignature* typeSignature);
    InterfacePropertyTypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_INTERFACE_PROPERTY_NODE_H
