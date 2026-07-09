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
    std::shared_ptr<ASTTypeBaseNode> _type;
public:
    explicit ASTTypeNode(std::shared_ptr<ASTTypeBaseNode> type);
    std::shared_ptr<ASTTypeBaseNode> getType();
    void setTypeSignature(std::shared_ptr<TypeSignature> typeSignature);
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};


#endif //JETLANG_AST_TYPE_NODE_H
