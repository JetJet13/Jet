//
// Created by Johny Georges on 2024-04-19.
//

#ifndef JETLANG_AST_CLASS_METHOD_DECLARATION_NODE_H
#define JETLANG_AST_CLASS_METHOD_DECLARATION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-identifier-node.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "../ast-class-nodes/ast-class-method-name-node.h"
#include "../ast-access-modifier-nodes/ast-access-modifier-node.h"
#include "../ast-class-nodes/ast-class-method-definition-node.h"
#include "ast-declaration-node.h"
#include "../../../type-signature/class-type-signature/class-method-type-signature/class-method-type-signature.h"

class ASTClassMethodDeclarationNode : public ASTDeclarationNode {
private:
    std::shared_ptr<ASTClassMethodDefinitionNode> _classMethodDefinition;
    std::shared_ptr<ASTFunctionParameterListNode> _parameters;
    std::optional<std::shared_ptr<ASTTypeColonNode>> _typeColon;
    std::optional<std::shared_ptr<ASTTypeNode>> _returnType;
    std::shared_ptr<ASTFunctionBlockNode> _block;
    std::shared_ptr<ClassMethodTypeSignature> _typeSignature = std::make_shared<ClassMethodTypeSignature>();
public:
    explicit ASTClassMethodDeclarationNode(std::shared_ptr<ASTClassMethodDefinitionNode> classMethodDefinition, std::shared_ptr<ASTFunctionParameterListNode> parameters, std::shared_ptr<ASTFunctionBlockNode> content);
    explicit ASTClassMethodDeclarationNode(std::shared_ptr<ASTClassMethodDefinitionNode> classMethodDefinition, std::shared_ptr<ASTFunctionParameterListNode> parameters, std::shared_ptr<ASTFunctionBlockNode> content, std::shared_ptr<ASTTypeColonNode> typeColon, std::shared_ptr<ASTTypeNode> returnType);
    std::shared_ptr<ASTClassMethodDefinitionNode> getClassMethodDefinition();
    std::shared_ptr<ASTFunctionParameterListNode> getParameters();
    std::optional<std::shared_ptr<ASTTypeNode>> getReturnType();
    std::shared_ptr<ASTFunctionBlockNode> getBlock();
    bool isStatic();
    unsigned long numParameters();
    void setTypeSignature(std::shared_ptr<ClassMethodTypeSignature> typeSignature);
    std::shared_ptr<ClassMethodTypeSignature> getMethodTypeSignature();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_METHOD_DECLARATION_NODE_H
