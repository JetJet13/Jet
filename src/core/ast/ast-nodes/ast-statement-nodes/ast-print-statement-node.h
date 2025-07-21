//
// Created by Johny Georges on 2025-07-21.
//

#ifndef JETLANG_AST_PRINT_STATEMENT_NODE_H
#define JETLANG_AST_PRINT_STATEMENT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "../ast-variable-nodes/ast-variable-assignment-node.h"
#include "ast-statement-node.h"
#include "../ast-function-nodes/ast-function-argument-list-node.h"
#include "../ast-print-node.h"
#include "../../../type-signature/void-type-signature/void-type-signature.h"

class ASTPrintStatementNode : public ASTStatementNode {
private:
    ASTPrintNode* _print;
    ASTFunctionArgumentListNode* _arguments;
public:
    explicit ASTPrintStatementNode(ASTPrintNode* print, ASTFunctionArgumentListNode* arguments);
    ASTFunctionArgumentListNode* getArguments();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_PRINT_STATEMENT_NODE_H
