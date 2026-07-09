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
    std::shared_ptr<ASTClassNode> _classKeyword;
    std::shared_ptr<ASTClassNameNode> _name;
    std::shared_ptr<ASTClassBlockNode> _block;
    std::optional<std::shared_ptr<ASTImplementsInterfaceListNode>> _implementsInterfaceList = {};
    std::optional<std::shared_ptr<ASTExportNode>> _exportKeyword = {};
    std::shared_ptr<ClassTypeSignature> _typeSignature = std::make_shared<ClassTypeSignature>();
public:
    explicit ASTClassDeclarationNode(std::shared_ptr<ASTClassNode> classKeyword, std::shared_ptr<ASTClassNameNode> name, std::shared_ptr<ASTClassBlockNode> block, std::optional<std::shared_ptr<ASTImplementsInterfaceListNode>> implementsInterfaceList = {});
    explicit ASTClassDeclarationNode(std::shared_ptr<ASTClassNode> classKeyword, std::shared_ptr<ASTClassNameNode> name, std::shared_ptr<ASTClassBlockNode> block, std::shared_ptr<ASTExportNode> exportKeyword);
    std::shared_ptr<ASTClassBlockNode> getBlock();
    std::shared_ptr<ASTClassNameNode> getName();
    void setTypeSignature(std::shared_ptr<ClassTypeSignature> typeSignature);
    std::optional<std::shared_ptr<ASTImplementsInterfaceListNode>>* getImplementsInterfaceList();
    std::shared_ptr<ClassTypeSignature> getClassTypeSignature();
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

#endif //JETLANG_AST_CLASS_DECLARATION_NODE_H
