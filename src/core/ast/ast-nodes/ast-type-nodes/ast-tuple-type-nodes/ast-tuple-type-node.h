//
// Created by Johny Georges on 2026-03-14.
//

#ifndef JETLANG_AST_TUPLE_TYPE_NODE_H
#define JETLANG_AST_TUPLE_TYPE_NODE_H

#include <string>
#include "../ast-type-base-node.h"
#include "ast-tuple-type-start-node.h"
#include "ast-tuple-type-end-node.h"
#include "../../ast-comma-node.h"
#include "../ast-type-node.h"

class ASTTupleTypeNode : public ASTTypeBaseNode {
private:
    ASTTupleTypeStartNode* _tupleTypeStartNode;
    ASTTupleTypeEndNode* _tupleTypeEndNode;
    std::vector<ASTCommaNode*> _commas;
    std::vector<ASTTypeNode*> _types;
public:
    ASTTupleTypeNode(ASTTupleTypeStartNode* tupleTypeStartNode, ASTTupleTypeEndNode* tupleTypeEndNode);
    ASTTupleTypeNode(ASTTupleTypeStartNode* tupleTypeStartNode, std::vector<ASTTypeNode*> keyValueTypes, std::vector<ASTCommaNode*> commas, ASTTupleTypeEndNode* tupleTypeEndNode);
    std::vector<ASTTypeNode*> getValueTypes();
    unsigned long numValueTypes();
    ASTTupleTypeNode* addComma(ASTCommaNode* comma);
    ASTTupleTypeNode* addValueType(ASTTypeNode* type);
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_TUPLE_TYPE_NODE_H
