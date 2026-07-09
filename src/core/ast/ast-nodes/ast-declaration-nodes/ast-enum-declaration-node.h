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
    std::shared_ptr<ASTEnumNode> _enumKeyword;
    std::shared_ptr<ASTEnumNameNode> _name;
    std::shared_ptr<ASTEnumKeyValueListNode> _values;
    std::optional<std::shared_ptr<ASTExportNode>> _exportKeyword = {};
    std::shared_ptr<EnumTypeSignature> _typeSignature = std::make_shared<EnumTypeSignature>();
public:
    explicit ASTEnumDeclarationNode(std::shared_ptr<ASTEnumNode> enumKeyword, std::shared_ptr<ASTEnumNameNode> name, std::shared_ptr<ASTEnumKeyValueListNode> values, std::optional<std::shared_ptr<ASTExportNode>> exportKeyword = {});
    std::shared_ptr<ASTEnumKeyValueListNode> getValues();
    std::shared_ptr<ASTEnumNameNode> getName();
    void setTypeSignature(std::shared_ptr<EnumTypeSignature> typeSignature);
    std::shared_ptr<EnumTypeSignature> getEnumTypeSignature();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    bool isExportable() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ENUM_DECLARATION_NODE_H
