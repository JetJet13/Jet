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

class ASTClassDeclarationNode : public ASTDeclarationNode {
private:
    ASTClassNode* _classKeyword;
    ASTClassNameNode* _name;
    ASTClassBlockNode* _block;
    ClassTypeSignature* _typeSignature = new ClassTypeSignature();
public:
    explicit ASTClassDeclarationNode(ASTClassNode* classKeyword, ASTClassNameNode* name, ASTClassBlockNode* block);
    ASTClassBlockNode* getBlock();
    ASTClassNameNode* getName();
    void setTypeSignature(ClassTypeSignature* typeSignature);
    ClassTypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_DECLARATION_NODE_H
