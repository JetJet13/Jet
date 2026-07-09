//
// Created by Johny Georges on 2024-03-29.
//

#ifndef JETLANG_AST_FOR_IN_SOURCE_NODE_H
#define JETLANG_AST_FOR_IN_SOURCE_NODE_H

#include "../../../lexeme/lexeme.h"
#include "../ast-identifier-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"

class ASTForInSourceNode : public ASTNode {
private:
    std::shared_ptr<ASTExpressionNode> _source;
    std::shared_ptr<TypeSignature> _typeSignature = std::make_shared<UnknownTypeSignature>();
public:
    explicit ASTForInSourceNode(std::shared_ptr<ASTExpressionNode> source);
    std::shared_ptr<ASTExpressionNode> getSource();
    void setTypeSignature(std::shared_ptr<TypeSignature> typeSignature);
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FOR_IN_SOURCE_NODE_H
