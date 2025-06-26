//
// Created by Johny Georges on 2025-06-25.
//

#ifndef JETLANG_AST_INTERFACE_TYPE_DECLARATION_NODE_H
#define JETLANG_AST_INTERFACE_TYPE_DECLARATION_NODE_H

#include "./ast-type-declaration-node.h"
#include "../ast-interface-nodes/ast-interface-definition-node.h"
#include "../ast-interface-nodes/ast-interface-property-list-node.h"
#include "../../../type-signature/interface-type-signature/interface-type-signature.h"
#include "../ast-export-node.h"

class ASTInterfaceTypeDeclarationNode : public ASTTypeDeclarationNode {
private:
    ASTInterfaceDefinitionNode* _interfaceDefinition;
    ASTInterfacePropertyListNode* _propertyList;
    std::optional<ASTExportNode*> _exportKeyword = {};
    InterfaceTypeSignature* _typeSignature = new InterfaceTypeSignature();
public:
    explicit ASTInterfaceTypeDeclarationNode(ASTInterfaceDefinitionNode* interfaceDefinition, ASTInterfacePropertyListNode* propertyList, std::optional<ASTExportNode*> exportKeyword = {});
    ASTInterfacePropertyListNode* getProperties();
    ASTInterfaceNameNode* getName();
    unsigned long numProperties();
    bool isExportable() override;
    void setTypeSignature(InterfaceTypeSignature* typeSignature);
    InterfaceTypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_INTERFACE_TYPE_DECLARATION_NODE_H
