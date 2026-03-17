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
    ASTClassMethodDefinitionNode* _classMethodDefinition;
    ASTFunctionParameterListNode* _parameters;
    std::optional<ASTTypeNode*> _returnType;
    ASTFunctionBlockNode* _block;
    ClassMethodTypeSignature* _typeSignature = new ClassMethodTypeSignature();
public:
    explicit ASTClassMethodDeclarationNode(ASTClassMethodDefinitionNode* classMethodDefinition, ASTFunctionParameterListNode* parameters, ASTFunctionBlockNode* content, std::optional<ASTTypeNode*> returnType = {});
    ASTClassMethodDefinitionNode* getClassMethodDefinition();
    ASTFunctionParameterListNode* getParameters();
    std::optional<ASTTypeNode*> getReturnType();
    ASTFunctionBlockNode* getBlock();
    bool isStatic();
    unsigned long numParameters();
    void setTypeSignature(ClassMethodTypeSignature* typeSignature);
    ClassMethodTypeSignature* getTypeSignature() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_METHOD_DECLARATION_NODE_H
