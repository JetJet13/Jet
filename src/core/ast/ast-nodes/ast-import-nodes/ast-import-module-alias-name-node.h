//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_IMPORT_MODULE_ALIAS_NAME_NODE_H
#define JETLANG_AST_IMPORT_MODULE_ALIAS_NAME_NODE_H

#include <string>
#include "../ast-node.h"
#include "../ast-base-nodes/ast-identifier-base-node.h"

class ASTImportModuleAliasNameNode : public ASTNode {
private:
    ASTIdentifierBaseNode* _identifier;
public:
    ASTImportModuleAliasNameNode(ASTIdentifierBaseNode* identifier);
    ASTIdentifierBaseNode* getIdentifier();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IMPORT_MODULE_ALIAS_NAME_NODE_H
