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
    ASTArrayTypeStartNode* _arrayStart;
    ASTTypeNode* _elementType;
    ASTArrayTypeEndNode* _arrayEnd;
public:
    ASTArrayTypeNode(ASTArrayTypeStartNode* arrayStart, ASTTypeNode* elementType, ASTArrayTypeEndNode* arrayEnd);
    ASTTypeNode* getElementType();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ARRAY_TYPE_NODE_H
