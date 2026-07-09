//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_MODULE_NAME_NODE_H
#define JETLANG_AST_MODULE_NAME_NODE_H

#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"
#include "../ast-identifier-node.h"

class ASTModuleNameNode : public ASTNode {
private:
    std::shared_ptr<ASTIdentifierNode> _identifier;
public:
    ASTModuleNameNode(std::shared_ptr<ASTIdentifierNode> identifier);
    std::shared_ptr<ASTIdentifierNode> getIdentifier();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_MODULE_NAME_NODE_H
