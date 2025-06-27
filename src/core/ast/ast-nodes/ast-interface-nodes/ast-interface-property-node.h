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
#include "../../../type-signature/interface-property-type-signature/interface-property-type-signature.h"
#include "ast-interface-property-name-node.h"
#include "ast-interface-colon-node.h"

class ASTInterfacePropertyNode : public ASTNode {
private:
    ASTInterfacePropertyNameNode* _name;
    ASTInterfaceColonNode* _colon;
    ASTTypeNode* _type;
    InterfacePropertyTypeSignature* _typeSignature = new InterfacePropertyTypeSignature("_", new UnknownTypeSignature());
public:
    ASTInterfacePropertyNode(ASTInterfacePropertyNameNode* name, ASTInterfaceColonNode* colon, ASTTypeNode* type);
    ASTInterfacePropertyNameNode* getName();
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
