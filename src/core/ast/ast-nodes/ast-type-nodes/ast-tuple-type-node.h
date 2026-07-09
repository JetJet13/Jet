//
// Created by Johny Georges on 2024-04-09.
//

#ifndef JETLANG_AST_TUPLE_TYPE_NODE_H
#define JETLANG_AST_TUPLE_TYPE_NODE_H

#include <string>
#include "ast-type-base-node.h"
#include "ast-type-parameter-list-node.h"
#include "../ast-tuple-nodes/ast-tuple-node.h"

class ASTTupleTypeNode : public ASTTypeBaseNode {
private:
    std::shared_ptr<ASTTupleNode> _tupleNode;
    std::shared_ptr<ASTTypeParameterListNode> _typeParameterList;
public:
    explicit ASTTupleTypeNode(std::shared_ptr<ASTTupleNode> tupleNode, std::shared_ptr<ASTTypeParameterListNode> tupleTypeParameterList);
    std::shared_ptr<ASTTypeParameterListNode> getParameterList();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TUPLE_TYPE_NODE_H
