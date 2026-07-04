//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_MODULE_DECLARATION_NODE_H
#define JETLANG_AST_MODULE_DECLARATION_NODE_H

#include "../ast-node.h"
#include "../ast-module-nodes/ast-module-name-node.h"
#include "../ast-module-nodes/ast-module-list-node.h"
#include "ast-declaration-node.h"
#include "../ast-module-nodes/ast-module-node.h"
#include "../../../type-signature/module-type-signature/module-type-signature.h"

class ASTModuleDeclarationNode : public ASTDeclarationNode {
private:
    std::shared_ptr<ASTModuleNode> _moduleKeyword;
    std::shared_ptr<ASTModuleNameNode> _name;
    ModuleTypeSignature* _typeSignature = new ModuleTypeSignature();
    std::vector<std::shared_ptr<ASTNode>> _exportedDeclarations = std::vector<std::shared_ptr<ASTNode>>();
public:
    explicit ASTModuleDeclarationNode(std::shared_ptr<ASTModuleNode> moduleKeyword, std::shared_ptr<ASTModuleNameNode> name);
    std::shared_ptr<ASTModuleNameNode> getName();
    std::vector<std::shared_ptr<ASTNode>>* getExports();
    void addExportedDeclaration(std::shared_ptr<ASTNode> declarationNode);
    void setTypeSignature(ModuleTypeSignature* typeSignature);
    ModuleTypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_MODULE_DECLARATION_NODE_H
