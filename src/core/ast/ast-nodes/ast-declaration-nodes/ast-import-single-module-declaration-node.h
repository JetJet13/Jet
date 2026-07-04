//
// Created by Johny Georges on 2024-04-13.
//

#ifndef JETLANG_AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE_H
#define JETLANG_AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE_H

#include "../ast-node.h"
#include "../ast-import-nodes/ast-import-module-name-node.h"
#include "../ast-import-nodes/ast-import-path-node.h"
#include "ast-declaration-node.h"
#include "../ast-import-nodes/ast-import-node.h"
#include "../ast-import-nodes/ast-from-node.h"

class ASTImportSingleModuleDeclarationNode : public ASTDeclarationNode {
private:
    std::shared_ptr<ASTImportNode> _importKeyword;
    std::shared_ptr<ASTImportModuleNameNode> _moduleName;
    std::shared_ptr<ASTFromNode> _fromKeyword;
    std::shared_ptr<ASTImportPathNode> _path;
public:
    explicit ASTImportSingleModuleDeclarationNode(std::shared_ptr<ASTImportNode> importKeyword, std::shared_ptr<ASTImportModuleNameNode> moduleName, std::shared_ptr<ASTFromNode> fromKeyword, std::shared_ptr<ASTImportPathNode> path);
    std::shared_ptr<ASTImportModuleNameNode> getModuleName();
    std::shared_ptr<ASTImportPathNode> getPath();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_IMPORT_SINGLE_MODULE_DECLARATION_NODE_H
