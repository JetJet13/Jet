//
// Created by Johny Georges on 2024-03-26.
//

#ifndef JETLANG_AST_TUPLE_ACCESS_NODE_H
#define JETLANG_AST_TUPLE_ACCESS_NODE_H

#include <string>
#include "../../../lexeme/lexeme.h"
#include "../ast-node.h"
#include "../../types/ast-node-type.h"

class ASTTupleAccessNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    ASTTupleAccessNode(Lexeme* lexeme);
    Lexeme* getLexeme();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};


#endif //JETLANG_AST_TUPLE_ACCESS_NODE_H
