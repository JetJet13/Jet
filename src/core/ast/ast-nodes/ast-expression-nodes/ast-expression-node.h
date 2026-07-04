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
    std::shared_ptr<ASTNode> baseTransformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode);
public:
    virtual void setTypeSignature(TypeSignature* typeSignature);
    virtual std::string getModuleId();
    TypeSignature* getTypeSignature() override;
    std::shared_ptr<ASTNode> transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) override;
    bool isExpression() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
};

#endif //JETLANG_AST_EXPRESSION_NODE_H
