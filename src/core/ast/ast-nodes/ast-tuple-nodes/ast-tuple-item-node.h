//
// Created by Johny Georges on 2024-03-26.
//

#ifndef JETLANG_AST_TUPLE_ITEM_NODE_H
#define JETLANG_AST_TUPLE_ITEM_NODE_H

#include <string>
#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"
#include "../../types/ast-node-type.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"
#include "../ast-type-nodes/ast-type-node.h"

class ASTTupleItemNode : public ASTNode {
private:
    std::shared_ptr<ASTExpressionNode> _item;
public:
    ASTTupleItemNode(std::shared_ptr<ASTExpressionNode> item);
    std::shared_ptr<ASTNode> transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode, SyntaxAnalyzerMode mode) override;
    std::shared_ptr<ASTExpressionNode> getItem();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TUPLE_ITEM_NODE_H
