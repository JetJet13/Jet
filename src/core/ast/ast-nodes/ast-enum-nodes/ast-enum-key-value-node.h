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
    std::shared_ptr<ASTEnumKeyNode> _key;
    std::optional<std::shared_ptr<ASTAssignmentOperatorNode>> _assignmentOperator = {};
    std::optional<std::shared_ptr<ASTLiteralNode>> _value = {};
    std::shared_ptr<LiteralTypeSignature> _typeSignature = std::make_shared<LiteralTypeSignature>();
public:
    ASTEnumKeyValueNode(std::shared_ptr<ASTEnumKeyNode> key);
    ASTEnumKeyValueNode(std::shared_ptr<ASTEnumKeyNode> key, std::shared_ptr<ASTAssignmentOperatorNode> assignmentOperator, std::shared_ptr<ASTLiteralNode> value);
    std::shared_ptr<ASTEnumKeyNode> getKey();
    std::optional<std::shared_ptr<ASTLiteralNode>> getValue();
    void setTypeSignature(std::shared_ptr<LiteralTypeSignature> typeSignature);
    std::shared_ptr<LiteralTypeSignature> getLiteralTypeSignature();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_ENUM_KEY_VALUE_NODE_H
