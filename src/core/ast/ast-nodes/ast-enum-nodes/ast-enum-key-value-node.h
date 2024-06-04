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
#include "../../../type-signature/literal-type-signature/literal-type-signature.h"
#include "../ast-operator-nodes/ast-assignment-operator-node.h"

class ASTEnumKeyValueNode : public ASTNode {
private:
    ASTEnumKeyNode* _key;
    std::optional<ASTAssignmentOperatorNode*> _assignmentOperator = {};
    std::optional<ASTLiteralNode*> _value = {};
    LiteralTypeSignature* _typeSignature = new LiteralTypeSignature();
public:
    ASTEnumKeyValueNode(ASTEnumKeyNode* key);
    ASTEnumKeyValueNode(ASTEnumKeyNode* key, ASTAssignmentOperatorNode* assignmentOperator, ASTLiteralNode* value);
    ASTEnumKeyNode* getKey();
    std::optional<ASTLiteralNode*> getValue();
    void setTypeSignature(LiteralTypeSignature* typeSignature);
    LiteralTypeSignature* getTypeSignature() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(ASTNode* other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ENUM_KEY_VALUE_NODE_H
