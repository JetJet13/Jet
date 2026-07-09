//
// Created by Johny Georges on 2024-04-20.
//

#ifndef JETLANG_AST_CLASS_PROPERTY_ACCESS_NODE_H
#define JETLANG_AST_CLASS_PROPERTY_ACCESS_NODE_H

#include <string>
#include "ast-class-property-name-node.h"
#include "../ast-node.h"
#include "ast-class-access-node.h"

class ASTClassPropertyAccessNode : public ASTNode {
private:
    std::shared_ptr<ASTClassAccessNode> _classAccess;
    std::shared_ptr<ASTClassPropertyNameNode> _property;
public:
    ASTClassPropertyAccessNode(std::shared_ptr<ASTClassAccessNode> classAccess, std::shared_ptr<ASTClassPropertyNameNode> property);
    std::shared_ptr<ASTClassAccessNode> getClassAccess();
    std::shared_ptr<ASTClassPropertyNameNode> getPropertyName();
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_ACCESS_NODE_H
