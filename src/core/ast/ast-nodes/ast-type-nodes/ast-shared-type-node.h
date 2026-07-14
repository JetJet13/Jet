//
// Created by Johny Georges on 2026-07-11.
//

#ifndef JETLANG_AST_SHARED_TYPE_NODE_H
#define JETLANG_AST_SHARED_TYPE_NODE_H

#include <string>
#include "ast-type-base-node.h"
#include "ast-type-parameter-list-node.h"
#include "../ast-array-nodes/ast-array-node.h"
#include "ast-ref-type-keyword-node.h"
#include "../ast-share-nodes/ast-shared-node.h"

class ASTSharedTypeNode : public ASTTypeBaseNode {
private:
    std::shared_ptr<ASTSharedNode> _shared;
    std::shared_ptr<ASTTypeParameterListNode> _typeParameterList;
public:
    ASTSharedTypeNode(std::shared_ptr<ASTSharedNode> sharedNode, std::shared_ptr<ASTTypeParameterListNode> typeParameterList);
    std::shared_ptr<ASTTypeNode> getSharedType();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_SHARED_TYPE_NODE_H
