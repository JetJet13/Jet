//
// Created by Johny Georges on 2026-05-30.
//

#ifndef JETLANG_AST_MODULE_TYPE_NODE_H
#define JETLANG_AST_MODULE_TYPE_NODE_H

#include <string>
#include "../ast-type-base-node.h"
#include "ast-module-access-type-node.h"
#include "ast-module-type-source-node.h"
#include "ast-module-type-target-node.h"

class ASTModuleTypeNode : public ASTTypeBaseNode {
private:
    std::shared_ptr<ASTModuleTypeSourceNode> _source;
    std::shared_ptr<ASTModuleAccessTypeNode> _moduleAccess;
    std::shared_ptr<ASTModuleTypeTargetNode> _target;
public:
    ASTModuleTypeNode(std::shared_ptr<ASTModuleTypeSourceNode> source, std::shared_ptr<ASTModuleAccessTypeNode> moduleAccess, std::shared_ptr<ASTModuleTypeTargetNode> target);
    std::shared_ptr<ASTModuleTypeSourceNode> getSource();
    std::shared_ptr<ASTModuleTypeTargetNode> getTarget();
    std::string getModuleTargetName();
    std::string getModuleName();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_MODULE_TYPE_NODE_H
