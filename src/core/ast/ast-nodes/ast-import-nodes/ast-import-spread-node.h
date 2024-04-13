//
// Created by Johny Georges on 2024-04-12.
//

#ifndef JETLANG_AST_IMPORT_SPREAD_NODE_H
#define JETLANG_AST_IMPORT_SPREAD_NODE_H

#include <string>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"

class ASTImportSpreadNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    ASTImportSpreadNode(Lexeme* lexeme);
    Lexeme* getLexeme();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_IMPORT_SPREAD_NODE_H
