//
// Created by Johny Georges on 2024-01-15.
//

#ifndef JETLANG_AST_FILE_NODE_H
#define JETLANG_AST_FILE_NODE_H

#include <vector>
#include "ast-node.h"
#include "ast-block-nodes/ast-block-node.h"

class ASTFileNode : public ASTNode {
private:
    ASTBlockNode* _body;
public:
    ASTFileNode(ASTBlockNode* body);
    void append(ASTNode* node);
    ASTBlockNode* getBody();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_FILE_NODE_H
