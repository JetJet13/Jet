//
// Created by Johny Georges on 2024-03-26.
//

#ifndef JETLANG_AST_TUPLE_LIST_END_NODE_H
#define JETLANG_AST_TUPLE_LIST_END_NODE_H

#include <string>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"

class ASTTupleListEndNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    ASTTupleListEndNode(Lexeme* lexeme);
    Lexeme* getLexeme();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};


#endif //JETLANG_AST_TUPLE_LIST_END_NODE_H
