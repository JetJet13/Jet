//
// Created by Johny Georges on 2024-02-08.
//

#ifndef JETLANG_AST_VARIABLE_INIT_NODE_H
#define JETLANG_AST_VARIABLE_INIT_NODE_H

#include "../ast-node.h"
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-identifier-node.h"
#include "ast-variable-type-node.h"
#include "../ast-type-nodes/ast-type-node.h"
#include "../ast-colon-node.h"

class ASTVariableInitNode : public ASTNode {
    ASTVariableTypeNode* _assignmentTypeQualifier;
    ASTIdentifierNode* _identifier;
    std::optional<ASTColonNode*> _colon;
    std::optional<ASTTypeNode*> _type;
public:
    explicit ASTVariableInitNode(ASTVariableTypeNode* assignmentTypeQualifier, ASTIdentifierNode* astIdentifierNode, std::optional<ASTColonNode*> colon = {}, std::optional<ASTTypeNode*> type = {});
    ASTVariableTypeNode* getVarTypeNode();
    ASTIdentifierNode* getIdentifierNode();
    std::optional<ASTTypeNode*> getTypeNode();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_VARIABLE_INIT_NODE_H
