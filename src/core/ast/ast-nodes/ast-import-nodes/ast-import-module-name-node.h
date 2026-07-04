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
    std::shared_ptr<ASTIdentifierNode> _identifier;
public:
    ASTImportModuleNameNode(std::shared_ptr<ASTIdentifierNode> identifier);
    std::shared_ptr<ASTIdentifierNode> getIdentifier();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};


#endif //JETLANG_AST_IMPORT_MODULE_NAME_NODE_H
