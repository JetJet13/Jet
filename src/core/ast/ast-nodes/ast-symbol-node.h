//
// Created by Johny Georges on 2024-04-18.
//

#ifndef JETLANG_AST_SYMBOL_NODE_H
#define JETLANG_AST_SYMBOL_NODE_H

#include "ast-node.h"

class ASTSymbolNode : public ASTNode {
protected:
    std::shared_ptr<Lexeme> _lexeme;
public:
    explicit ASTSymbolNode(std::shared_ptr<Lexeme> lexeme);
    explicit ASTSymbolNode(std::shared_ptr<Lexeme> lexeme, std::string id);
    std::shared_ptr<Lexeme> getLexeme();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_SYMBOL_NODE_H
