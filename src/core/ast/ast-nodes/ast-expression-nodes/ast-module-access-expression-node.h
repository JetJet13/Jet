//
// Created by Johny Georges on 2024-11-05.
//

#ifndef JETLANG_AST_MODULE_ACCESS_EXPRESSION_NODE_H
#define JETLANG_AST_MODULE_ACCESS_EXPRESSION_NODE_H

#include <string>
#include "../ast-period-node.h"
#include "ast-aggregate-expression-node.h"
#include "../ast-module-nodes/ast-module-access-source-node.h"
#include "../ast-module-nodes/ast-module-access-target-node.h"
#include "../ast-module-nodes/ast-module-access-node.h"

class ASTModuleAccessExpressionNode : public ASTAggregateExpressionNode {
private:
    ASTModuleAccessSourceNode* _source;
    ASTModuleAccessNode* _moduleAccess;
    ASTModuleAccessTargetNode* _target;
public:
    ASTModuleAccessExpressionNode(ASTModuleAccessSourceNode* source, ASTModuleAccessNode* moduleAccess, ASTModuleAccessTargetNode* target);
    ASTModuleAccessSourceNode* getSource();
    ASTModuleAccessTargetNode* getTarget();
    std::string getModuleTargetName();
    std::string getModuleName();
    std::string getModuleId() override;
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_MODULE_ACCESS_EXPRESSION_NODE_H
