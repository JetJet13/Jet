//
// Created by Johny Georges on 2025-06-28.
//

#ifndef JETLANG_AST_STRUCT_TYPE_NODE_H
#define JETLANG_AST_STRUCT_TYPE_NODE_H

#include <string>
#include "../ast-type-base-node.h"
#include "ast-struct-type-start-node.h"
#include "ast-struct-type-end-node.h"
#include "ast-struct-type-key-value-node.h"

class ASTStructTypeNode : public ASTTypeBaseNode {
protected:
    ASTStructTypeStartNode* _structTypeStartNode;
    ASTStructTypeEndNode* _structTypeEndNode;
    std::vector<ASTStructTypeKeyValueNode*> _keyValueTypes;
public:
    ASTStructTypeNode(ASTStructTypeStartNode* structTypeStartNode, ASTStructTypeEndNode* structTypeEndNode);
    ASTStructTypeNode(ASTStructTypeStartNode* structTypeStartNode, std::vector<ASTStructTypeKeyValueNode*> keyValueTypes, ASTStructTypeEndNode* structTypeEndNode);
    std::vector<ASTStructTypeKeyValueNode*> getKeyValueTypes();
    unsigned long numKeyValueTypes();
    ASTStructTypeNode* addKeyValueType(ASTStructTypeKeyValueNode* keyValueType);
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_STRUCT_TYPE_NODE_H
