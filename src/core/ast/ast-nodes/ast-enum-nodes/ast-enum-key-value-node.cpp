//
// Created by Johny Georges on 2024-03-22.
//

#include "ast-enum-key-value-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTEnumKeyValueNode::ASTEnumKeyValueNode(ASTEnumKeyNode* key) {
    _key = key;
    _children.push_back(_key);
}

ASTEnumKeyValueNode::ASTEnumKeyValueNode(ASTEnumKeyNode* key, ASTAssignmentOperatorNode* assignmentOperator, ASTLiteralNode* value) {
    _key = key;
    _assignmentOperator = assignmentOperator;
    _value = value;

    _children.push_back(_key);
    _children.push_back(_assignmentOperator.value());
    _children.push_back(_value.value());

}

ASTEnumKeyNode* ASTEnumKeyValueNode::getKey() {
    return _key;
}

std::optional<ASTLiteralNode*> ASTEnumKeyValueNode::getValue() {
    return _value;
}

void ASTEnumKeyValueNode::setTypeSignature(LiteralTypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

LiteralTypeSignature* ASTEnumKeyValueNode::getTypeSignature() {
    return _typeSignature;
}

ASTNodeType ASTEnumKeyValueNode::getNodeType() {
    return AST_ENUM_KEY_VALUE_NODE;
}

std::string ASTEnumKeyValueNode::toString() {
    return "ENUM_KEY_VALUE";
}

bool ASTEnumKeyValueNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTEnumKeyValueNode*)other;
    auto isKeySame = _key->isSameAs(otherNode->getKey());
    if (!isKeySame) {
        return false;
    }

    if (_value.has_value() && otherNode->getValue().has_value()) {
        return _value.value()->isSameAs(otherNode->getValue().value());
    }
    return !_value.has_value() && !otherNode->getValue().has_value();
}

void ASTEnumKeyValueNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _key->print();
    _value.has_value() ? _value.value()->print() : Logger::log("(NO VALUE)");
    Logger::log("----------");
}

std::string ASTEnumKeyValueNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_key);

    if (_assignmentOperator) {
        sourceCodeBuilder.addWithWhitespace(_assignmentOperator.value());
    }

    if (_value) {
        sourceCodeBuilder.addWithWhitespace(_value.value());
    }

    return sourceCodeBuilder.build();
}