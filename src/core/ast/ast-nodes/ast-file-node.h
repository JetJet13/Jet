//
// Created by Johny Georges on 2024-01-15.
//

#ifndef JETLANG_AST_FILE_NODE_H
#define JETLANG_AST_FILE_NODE_H

#include <vector>
#include "ast-node.h"

class ASTFileNode : public ASTNode {
private:
    std::vector<ASTNode*> _body;
public:
    ASTFileNode();
    void append(ASTNode* node);
    void prepend(ASTNode* node);
    std::vector<ASTNode*> getBody();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
};

#endif //JETLANG_AST_FILE_NODE_H
