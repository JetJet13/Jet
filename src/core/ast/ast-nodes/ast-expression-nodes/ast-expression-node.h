//
// Created by Johny Georges on 2024-01-12.
//

#ifndef JETLANG_AST_EXPRESSION_NODE_H
#define JETLANG_AST_EXPRESSION_NODE_H

#include <vector>
#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"
#include "../ast-type-nodes/ast-type-node.h"

class ASTExpressionNode : public ASTNode {
protected:
    TypeSignature* _typeSignature = new UnknownTypeSignature();
    ASTNode* baseTransformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode);
public:
    virtual void setTypeSignature(TypeSignature* typeSignature);
    virtual std::string getModuleId();
    TypeSignature* getTypeSignature() override;
    ASTNode* transformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode) override;
    bool isExpression() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
};

#endif //JETLANG_AST_EXPRESSION_NODE_H
