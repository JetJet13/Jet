//
// Created by Johny Georges on 2024-03-12.
//

#ifndef JETLANG_AST_STRUCT_EXPRESSION_NODE_H
#define JETLANG_AST_STRUCT_EXPRESSION_NODE_H

#include <unordered_map>
#include "../ast-node.h"
#include "../ast-struct-nodes/ast-struct-key-value-node.h"
#include "../ast-struct-nodes/ast-struct-start-node.h"
#include "../ast-struct-nodes/ast-struct-end-node.h"
#include "../../../type-signature/struct-type-signature/struct-type-signature.h"
#include "ast-aggregate-expression-node.h"
#include "../ast-comma-node.h"

class ASTStructExpressionNode : public ASTAggregateExpressionNode {
private:
    ASTStructStartNode* _structStartNode;
    ASTStructEndNode* _structEndNode;
    std::vector<ASTStructKeyValueNode*> _keyValuePairs;
    std::vector<ASTCommaNode*> _commas;
    StructTypeSignature* _typeSignature = new StructTypeSignature();
public:
    ASTStructExpressionNode(ASTStructStartNode* structStartNode, ASTStructEndNode* structEndNode);
    ASTStructExpressionNode(ASTStructStartNode* structStartNode, std::vector<ASTStructKeyValueNode*> keyValuePairs, std::vector<ASTCommaNode*> commas, ASTStructEndNode* structEndNode);
    std::vector<ASTStructKeyValueNode*> getKeyValuePairs();
    ASTStructKeyValueNode* getKeyValuePairAt(unsigned long index);
    ASTStructExpressionNode* addKeyValuePair(ASTStructKeyValueNode* keyValuePair);
    ASTStructExpressionNode* addComma(ASTCommaNode* comma);
    StructTypeSignature* getTypeSignature() override;
    void markAsReferenced() override;
    void setTypeSignature(StructTypeSignature* structTypeSignature);
    unsigned long size();
    Position* getStartPosition() override;
    Position* getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_STRUCT_EXPRESSION_NODE_H
