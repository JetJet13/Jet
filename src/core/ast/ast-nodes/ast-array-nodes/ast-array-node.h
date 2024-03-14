//
// Created by Johny Georges on 2024-03-11.
//

#ifndef JETLANG_AST_ARRAY_NODE_H
#define JETLANG_AST_ARRAY_NODE_H

#include <optional>
#include <string>
#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"

class ASTArrayNode : public ASTNode {
private:
    std::vector<ASTExpressionNode*>* _elements;
public:
    explicit ASTArrayNode();
    explicit ASTArrayNode(std::vector<ASTExpressionNode*> elements);
    ASTArrayNode* addElement(ASTExpressionNode* element);
    std::optional<ASTExpressionNode*> getFirstElement();
    std::vector<ASTExpressionNode*>* getElements();
    ASTNodeType getNodeType() override;
    std::string toString() override;
};

#endif //JETLANG_AST_ARRAY_NODE_H
