//
// Created by Johny Georges on 2024-02-24.
//

#ifndef JETLANG_AST_MOCK_NODE_H
#define JETLANG_AST_MOCK_NODE_H

#include "../../../src/core/ast/ast-nodes/ast-node.h"

class ASTMockNode : public ASTNode {
private:
    ASTNodeType _nodeType;
public:
    ASTMockNode(ASTNodeType astNodeType);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isEqual(ASTNode* other) override;

};

#endif //JETLANG_AST_MOCK_NODE_H
