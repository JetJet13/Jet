//
// Created by Johny Georges on 2024-03-22.
//

#ifndef JETLANG_AST_ENUM_KEY_VALUE_NODE_H
#define JETLANG_AST_ENUM_KEY_VALUE_NODE_H

#include <string>
#include <optional>
#include "../ast-expression-nodes/ast-expression-node.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"
#include "../ast-literal-nodes/ast-literal-node.h"
#include "ast-enum-key-node.h"

class ASTEnumKeyValueNode : public ASTNode {
private:
    ASTEnumKeyNode* _key;
    std::optional<ASTLiteralNode*> _value;
public:
    ASTEnumKeyValueNode(ASTEnumKeyNode* key);
    ASTEnumKeyValueNode(ASTEnumKeyNode* key, ASTLiteralNode* value);
    ASTEnumKeyNode* getKey();
    std::optional<ASTLiteralNode*> getValue();
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
};

#endif //JETLANG_AST_ENUM_KEY_VALUE_NODE_H
