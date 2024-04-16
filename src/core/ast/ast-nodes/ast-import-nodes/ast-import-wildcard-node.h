//
// Created by Johny Georges on 2024-04-15.
//

#ifndef JETLANG_AST_IMPORT_WILDCARD_NODE_H
#define JETLANG_AST_IMPORT_WILDCARD_NODE_H

#include <string>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"

class ASTImportWildcardNode : public ASTNode {
private:
    Lexeme* _lexeme;
public:
    ASTImportWildcardNode(Lexeme* lexeme);
    Lexeme* getLexeme();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};


#endif //JETLANG_AST_IMPORT_WILDCARD_NODE_H
