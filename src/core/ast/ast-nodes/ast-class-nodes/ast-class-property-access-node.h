//
// Created by Johny Georges on 2024-04-20.
//

#ifndef JETLANG_AST_CLASS_PROPERTY_ACCESS_NODE_H
#define JETLANG_AST_CLASS_PROPERTY_ACCESS_NODE_H

#include <string>
#include "ast-class-property-name-node.h"
#include "../ast-node.h"

class ASTClassPropertyAccessNode : public ASTNode {
private:
    ASTClassPropertyNameNode* _property;
public:
    ASTClassPropertyAccessNode(ASTClassPropertyNameNode* property);
    ASTClassPropertyNameNode* getProperty();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_CLASS_PROPERTY_ACCESS_NODE_H
