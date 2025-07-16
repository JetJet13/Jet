//
// Created by Johny Georges on 2025-06-25.
//

#ifndef JETLANG_AST_INTERFACE_PROPERTY_LIST_NODE_H
#define JETLANG_AST_INTERFACE_PROPERTY_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-interface-start-node.h"
#include "ast-interface-end-node.h"
#include "ast-interface-property-node.h"
#include "../ast-comma-node.h"

class ASTInterfacePropertyListNode : public ASTNode {
private:
    ASTInterfaceStartNode* _startNode;
    ASTInterfaceEndNode* _endNode;
    std::vector<ASTCommaNode*> _commas;
    std::vector<ASTInterfacePropertyNode*> _properties;
public:
    ASTInterfacePropertyListNode(ASTInterfaceStartNode* startNode, ASTInterfaceEndNode* endNode);
    ASTInterfacePropertyListNode(ASTInterfaceStartNode* startNode, std::vector<ASTInterfacePropertyNode*> properties, std::vector<ASTCommaNode*> commas, ASTInterfaceEndNode* endNode);
    std::vector<ASTInterfacePropertyNode*> getProperties();
    unsigned long numProperties();
    ASTInterfacePropertyListNode* addProperty(ASTInterfacePropertyNode* property);
    ASTInterfacePropertyListNode* addComma(ASTCommaNode* comma);
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_INTERFACE_PROPERTY_LIST_NODE_H
