//
// Created by Johny Georges on 2024-04-04.
//

#ifndef JETLANG_AST_CUSTOM_TYPE_NODE_H
#define JETLANG_AST_CUSTOM_TYPE_NODE_H

#include "ast-type-base-node.h"

class ASTCustomTypeNode : public ASTTypeBaseNode {
private:
    std::shared_ptr<Lexeme> _lexeme;
public:
    ASTCustomTypeNode(std::shared_ptr<Lexeme> lexeme, std::string id);
    std::shared_ptr<Lexeme> getLexeme();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CUSTOM_TYPE_NODE_H
