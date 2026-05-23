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
#include "../ast-enum-nodes/ast-enum-node.h"
#include "../ast-export-node.h"

class ASTEnumDeclarationNode : public ASTDeclarationNode {
private:
    ASTEnumNode* _enumKeyword;
    ASTEnumNameNode* _name;
    ASTEnumKeyValueListNode* _values;
    std::optional<ASTExportNode*> _exportKeyword = {};
    EnumTypeSignature* _typeSignature = new EnumTypeSignature();
public:
    explicit ASTEnumDeclarationNode(ASTEnumNode* enumKeyword, ASTEnumNameNode* name, ASTEnumKeyValueListNode* values, std::optional<ASTExportNode*> exportKeyword = {});
    ASTEnumKeyValueListNode* getValues();
    ASTEnumNameNode* getName();
    void setTypeSignature(EnumTypeSignature* typeSignature);
    EnumTypeSignature* getTypeSignature() override;
    bool isExportable() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ENUM_DECLARATION_NODE_H
