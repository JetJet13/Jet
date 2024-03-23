//
// Created by Johny Georges on 2024-03-23.
//

#ifndef JETLANG_AST_ENUM_KEY_VALUE_LIST_END_NODE_H
#define JETLANG_AST_ENUM_KEY_VALUE_LIST_END_NODE_H

#include <string>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"

class ASTEnumKeyValueListEndNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    ASTEnumKeyValueListEndNode(Lexeme* lexeme);
    Lexeme* getLexeme();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_ENUM_KEY_VALUE_LIST_END_NODE_H
