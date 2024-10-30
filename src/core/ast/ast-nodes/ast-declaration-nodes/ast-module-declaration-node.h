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
    ASTModuleNode* _moduleKeyword;
    ASTModuleNameNode* _name;
    ModuleTypeSignature* _typeSignature = new ModuleTypeSignature();
public:
    explicit ASTModuleDeclarationNode(ASTModuleNode* moduleKeyword, ASTModuleNameNode* name);
    ASTModuleNameNode* getName();
    void setTypeSignature(ModuleTypeSignature* typeSignature);
    ModuleTypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_MODULE_DECLARATION_NODE_H
