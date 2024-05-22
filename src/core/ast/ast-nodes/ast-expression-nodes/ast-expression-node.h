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
private:
    TypeSignature* _typeSignature = new UnknownTypeSignature();
protected:
    ASTNode* baseTransformIfNecessary(std::optional<ASTNode*> prevNode, std::optional<ASTNode*> nextNode, SyntaxAnalyzerMode mode);
public:
    void setTypeSignature(TypeSignature* typeSignature);
    TypeSignature* getTypeSignature() override;
    ASTNode* transformIfNecessary(std::optional<ASTNode *> prevNode, std::optional<ASTNode *> nextNode, SyntaxAnalyzerMode mode) override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
};

#endif //JETLANG_AST_EXPRESSION_NODE_H
