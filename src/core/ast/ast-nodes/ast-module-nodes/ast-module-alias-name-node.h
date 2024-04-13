//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_IMPORT_MODULE_ALIAS_NAME_NODE_H
#define JETLANG_AST_MODULE_ALIAS_NAME_NODE_H

#include <string>
#include "../ast-node.h"
#include "../ast-identifier-node.h"


class ASTModuleAliasNameNode : public ASTNode {
private:
    ASTIdentifierNode* _identifier;
public:
    ASTModuleAliasNameNode(ASTIdentifierNode* identifier);
    ASTIdentifierNode* getIdentifier();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_IMPORT_MODULE_ALIAS_NAME_NODE_H
