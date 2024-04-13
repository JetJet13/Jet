//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_IMPORT_MODULE_LIST_START_NODE_H
#define JETLANG_AST_MODULE_LIST_START_NODE_H

#include <string>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"

class ASTModuleListStartNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    ASTModuleListStartNode(Lexeme* lexeme);
    Lexeme* getLexeme();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_IMPORT_MODULE_LIST_START_NODE_H
