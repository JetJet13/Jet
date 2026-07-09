//
// Created by Johny Georges on 2024-04-20.
//

#ifndef JETLANG_AST_CLASS_CONSTRUCTOR_DECLARATION_NODE_H
#define JETLANG_AST_CLASS_CONSTRUCTOR_DECLARATION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "ast-declaration-node.h"
#include "../ast-class-nodes/ast-constructor-node.h"
#include "../../../type-signature/class-type-signature/class-constructor-type-signature/class-constructor-type-signature.h"

class ASTClassConstructorDeclarationNode : public ASTDeclarationNode {
private:
    std::shared_ptr<ASTConstructorNode> _constructor;
    std::shared_ptr<ASTFunctionParameterListNode> _parameters;
    std::shared_ptr<ASTFunctionBlockNode> _block;
    std::shared_ptr<ClassConstructorTypeSignature> _typeSignature = std::make_shared<ClassConstructorTypeSignature>();
public:
    explicit ASTClassConstructorDeclarationNode(std::shared_ptr<ASTConstructorNode> constructor, std::shared_ptr<ASTFunctionParameterListNode> parameters, std::shared_ptr<ASTFunctionBlockNode> content);
    std::shared_ptr<ASTConstructorNode> getConstructor();
    std::shared_ptr<ASTFunctionParameterListNode> getParameters();
    std::shared_ptr<ASTFunctionBlockNode> getBlock();
    unsigned long numParameters();
    void setTypeSignature(std::shared_ptr<ClassConstructorTypeSignature> typeSignature);
    std::shared_ptr<ClassConstructorTypeSignature> getConstructorTypeSignature();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_CONSTRUCTOR_DECLARATION_NODE_H
