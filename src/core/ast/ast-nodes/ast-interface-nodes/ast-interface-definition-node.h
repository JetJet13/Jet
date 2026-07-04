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
    std::shared_ptr<ASTInterfaceNode> _interfaceKeyword;
    std::shared_ptr<ASTInterfaceNameNode> _name;
public:
    explicit ASTInterfaceDefinitionNode(std::shared_ptr<ASTInterfaceNode> interfaceKeyword, std::shared_ptr<ASTInterfaceNameNode> name);
    std::shared_ptr<ASTInterfaceNameNode> getName();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_INTERFACE_DEFINITION_NODE_H
