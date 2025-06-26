//
// Created by Johny Georges on 2025-06-25.
//

#ifndef JETLANG_AST_INTERFACE_DEFINITION_NODE_H
#define JETLANG_AST_INTERFACE_DEFINITION_NODE_H

#include <vector>
#include "../ast-node.h"

#include "../ast-type-nodes/ast-type-node.h"
#include "ast-interface-node.h"
#include "ast-interface-name-node.h"

class ASTInterfaceDefinitionNode : public ASTNode {
private:
    ASTInterfaceNode* _interfaceKeyword;
    ASTInterfaceNameNode* _name;
public:
    explicit ASTInterfaceDefinitionNode(ASTInterfaceNode* interfaceKeyword, ASTInterfaceNameNode* name);
    ASTInterfaceNameNode* getName();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_INTERFACE_DEFINITION_NODE_H
