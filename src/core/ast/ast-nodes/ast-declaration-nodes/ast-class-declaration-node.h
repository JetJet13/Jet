//
// Created by Johny Georges on 2024-04-20.
//

#ifndef JETLANG_AST_CLASS_DECLARATION_NODE_H
#define JETLANG_AST_CLASS_DECLARATION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "ast-declaration-node.h"
#include "../ast-class-nodes/ast-class-node.h"
#include "../ast-class-nodes/ast-class-name-node.h"
#include "../ast-class-nodes/ast-class-block-node.h"
#include "../../../type-signature/class-type-signature/class-type-signature.h"
#include "../ast-interface-nodes/ast-implements-interface-list-node.h"
#include "../ast-export-node.h"

class ASTClassDeclarationNode : public ASTDeclarationNode {
private:
    ASTClassNode* _classKeyword;
    ASTClassNameNode* _name;
    ASTClassBlockNode* _block;
    std::optional<ASTImplementsInterfaceListNode*> _implementsInterfaceList = {};
    std::optional<ASTExportNode*> _exportKeyword = {};
    ClassTypeSignature* _typeSignature = new ClassTypeSignature();
public:
    explicit ASTClassDeclarationNode(ASTClassNode* classKeyword, ASTClassNameNode* name, ASTClassBlockNode* block, std::optional<ASTImplementsInterfaceListNode*> implementsInterfaceList = {});
    explicit ASTClassDeclarationNode(ASTClassNode* classKeyword, ASTClassNameNode* name, ASTClassBlockNode* block, ASTExportNode* exportKeyword);
    ASTClassBlockNode* getBlock();
    ASTClassNameNode* getName();
    void setTypeSignature(ClassTypeSignature* typeSignature);
    std::optional<ASTImplementsInterfaceListNode*>* getImplementsInterfaceList();
    ClassTypeSignature* getTypeSignature() override;
    bool isExportable() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_DECLARATION_NODE_H
