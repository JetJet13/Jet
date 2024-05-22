//
// Created by Johny Georges on 2024-03-22.
//

#ifndef JETLANG_AST_ENUM_DECLARATION_NODE_H
#define JETLANG_AST_ENUM_DECLARATION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-enum-nodes/ast-enum-name-node.h"
#include "../ast-enum-nodes/ast-enum-key-value-list-node.h"
#include "ast-declaration-node.h"
#include "../../../type-signature/enum-type-signature/enum-type-signature.h"

class ASTEnumDeclarationNode : public ASTDeclarationNode {
private:
    ASTEnumNameNode* _name;
    ASTEnumKeyValueListNode* _values;
    EnumTypeSignature* _typeSignature = new EnumTypeSignature();
public:
    explicit ASTEnumDeclarationNode(ASTEnumNameNode* name, ASTEnumKeyValueListNode* values);
    ASTEnumKeyValueListNode* getValues();
    ASTEnumNameNode* getName();
    void setTypeSignature(EnumTypeSignature* typeSignature);
    EnumTypeSignature* getTypeSignature() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_ENUM_DECLARATION_NODE_H
