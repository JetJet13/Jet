//
// Created by Johny Georges on 2024-04-26.
//

#ifndef JETLANG_AST_CLASS_METHOD_DEFINITION_NODE_H
#define JETLANG_AST_CLASS_METHOD_DEFINITION_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-variable-nodes/ast-variable-type-node.h"
#include "../ast-variable-nodes/ast-variable-init-node.h"
#include "ast-class-property-name-node.h"
#include "../ast-access-modifier-nodes/ast-access-modifier-node.h"
#include "ast-class-method-name-node.h"
#include "ast-static-node.h"

class ASTClassMethodDefinitionNode : public ASTNode {
protected:
    ASTAccessModifierNode* _accessModifier;
    ASTClassMethodNameNode* _methodName;
    std::optional<ASTStaticNode*> _staticKeyword;
public:
    explicit ASTClassMethodDefinitionNode(ASTAccessModifierNode* accessModifier, ASTClassMethodNameNode* methodName, std::optional<ASTStaticNode*> staticKeyword = {});
    ASTAccessModifierNode* getAccessModifier();
    ASTClassMethodNameNode* getMethodName();
    bool isStatic();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_METHOD_DEFINITION_NODE_H
