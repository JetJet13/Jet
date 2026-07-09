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
    int64_t _index;
    Lexeme* _lexeme;
public:
    explicit ASTTupleAccessNode(Lexeme* lexeme);
    Lexeme* getLexeme();
    std::shared_ptr<ASTTupleAccessNode> setIndexValue(std::string index);
    int64_t getIndexValue();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};


#endif //JETLANG_AST_TUPLE_ACCESS_NODE_H
