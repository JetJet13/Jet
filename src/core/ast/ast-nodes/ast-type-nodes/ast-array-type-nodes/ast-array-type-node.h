//
// Created by Johny Georges on 2024-04-09.
//

#ifndef JETLANG_AST_ARRAY_TYPE_NODE_H
#define JETLANG_AST_ARRAY_TYPE_NODE_H

#include <string>
#include "../ast-type-base-node.h"
#include "../ast-type-parameter-list-node.h"
#include "../../ast-array-nodes/ast-array-node.h"
#include "ast-array-type-start-node.h"
#include "ast-array-type-end-node.h"

class ASTArrayTypeNode : public ASTTypeBaseNode {
private:
    std::shared_ptr<ASTArrayTypeStartNode> _arrayStart;
    std::shared_ptr<ASTTypeNode> _elementType;
    std::shared_ptr<ASTArrayTypeEndNode> _arrayEnd;
public:
    ASTArrayTypeNode(std::shared_ptr<ASTArrayTypeStartNode> arrayStart, std::shared_ptr<ASTTypeNode> elementType, std::shared_ptr<ASTArrayTypeEndNode> arrayEnd);
    std::shared_ptr<ASTTypeNode> getElementType();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ARRAY_TYPE_NODE_H
