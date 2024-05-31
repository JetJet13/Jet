//
// Created by Johny Georges on 2024-03-19.
//

#ifndef JETLANG_AST_TYPE_NODE_H
#define JETLANG_AST_TYPE_NODE_H

#include <string>
#include "../ast-node.h"
#include "../../../lexeme/lexeme.h"
#include "ast-type-base-node.h"

class ASTTypeNode : public ASTNode {
private:
    ASTTypeBaseNode* _type;
public:
    explicit ASTTypeNode(ASTTypeBaseNode* type);
    ASTTypeBaseNode* getType();
    void setTypeSignature(TypeSignature* typeSignature);
    TypeSignature* getTypeSignature() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};


#endif //JETLANG_AST_TYPE_NODE_H
