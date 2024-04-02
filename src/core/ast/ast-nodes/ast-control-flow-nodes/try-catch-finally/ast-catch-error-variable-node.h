//
// Created by Johny Georges on 2024-04-01.
//

#ifndef JETLANG_AST_CATCH_ERROR_VARIABLE_NODE_H
#define JETLANG_AST_CATCH_ERROR_VARIABLE_NODE_H

#include <string>
#include "../../../../lexeme/lexeme.h"
#include "../../ast-node.h"
#include "../../../types/ast-node-type.h"
#include "../../ast-identifier-node.h"

class ASTCatchErrorVariableNode : public ASTNode {
private:
    ASTIdentifierNode* _identifier;
public:
    ASTCatchErrorVariableNode(ASTIdentifierNode* identifier);
    ASTIdentifierNode* getIdentifier();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_CATCH_ERROR_VARIABLE_NODE_H
