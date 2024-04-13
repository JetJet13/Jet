//
// Created by Johny Georges on 2024-04-13.
//

#ifndef JETLANG_AST_IMPORT_MODULE_NAME_NODE_H
#define JETLANG_AST_IMPORT_MODULE_NAME_NODE_H

#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"
#include "../ast-identifier-node.h"

class ASTImportModuleNameNode : public ASTNode {
private:
    ASTIdentifierNode* _identifier;
public:
    ASTImportModuleNameNode(ASTIdentifierNode* identifier);
    ASTIdentifierNode* getIdentifier();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};


#endif //JETLANG_AST_IMPORT_MODULE_NAME_NODE_H
