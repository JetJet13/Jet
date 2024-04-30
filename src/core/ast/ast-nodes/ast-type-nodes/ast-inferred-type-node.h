//
// Created by Johny Georges on 2024-04-29.
//

#ifndef JETLANG_AST_INFERRED_TYPE_NODE_H
#define JETLANG_AST_INFERRED_TYPE_NODE_H

#include "ast-type-base-node.h"

class ASTInferredTypeNode : public ASTTypeBaseNode {
private:
    BaseType* _inferredType;
public:
    ASTInferredTypeNode(BaseType* inferredType);
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    BaseType* getType() override;
};

#endif //JETLANG_AST_INFERRED_TYPE_NODE_H
