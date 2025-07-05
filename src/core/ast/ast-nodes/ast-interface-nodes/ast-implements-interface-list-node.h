//
// Created by Johny Georges on 2025-07-05.
//

#ifndef JETLANG_AST_IMPLEMENTS_INTERFACE_LIST_NODE_H
#define JETLANG_AST_IMPLEMENTS_INTERFACE_LIST_NODE_H

#include <string>
#include "../ast-node.h"
#include "ast-interface-start-node.h"
#include "ast-interface-end-node.h"
#include "ast-interface-property-node.h"
#include "ast-implements-node.h"
#include "ast-implements-interface-name-node.h"

class ASTImplementsInterfaceListNode : public ASTNode {
private:
    ASTImplementsNode* _implements;
    std::vector<ASTImplementsInterfaceNameNode*> _interfaceNames;
public:
    ASTImplementsInterfaceListNode(ASTImplementsNode* implementsKeyword);
    ASTImplementsInterfaceListNode(ASTImplementsNode* implementsKeyword, std::vector<ASTImplementsInterfaceNameNode*> interfaceNames);
    std::vector<ASTImplementsInterfaceNameNode*> getInterfaceNames();
    unsigned long numInterfaces();
    ASTImplementsInterfaceListNode* addInterface(ASTImplementsInterfaceNameNode* interfaceName);
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IMPLEMENTS_INTERFACE_LIST_NODE_H
