//
// Created by Johny Georges on 2024-03-12.
//

#include "ast-struct-key-value-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTStructKeyValueNode::ASTStructKeyValueNode(ASTIdentifierExpressionNode* key, ASTStructColonNode* colon, ASTExpressionNode* value) {
    _key = key;
    _colon = colon;
    _value = value;
    _children.push_back(_key);
    _children.push_back(_colon);
    _children.push_back(_value);
}

ASTIdentifierExpressionNode* ASTStructKeyValueNode::getKey() {
    return _key;
}

ASTExpressionNode* ASTStructKeyValueNode::getValue() {
    return _value;
}

Position* ASTStructKeyValueNode::getStartPosition() {
    return _key->getStartPosition();
}

Position* ASTStructKeyValueNode::getEndPosition() {
    return _value->getEndPosition();
}

ASTNodeType ASTStructKeyValueNode::getNodeType() {
    return AST_STRUCT_KEY_VALUE_NODE;
}

std::string ASTStructKeyValueNode::toString() {
    return "STRUCT_KEY_VALUE";
}

bool ASTStructKeyValueNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTStructKeyValueNode*)other;
    return _key->isSameAs(otherNode->getKey()) && _value->isSameAs(otherNode->getValue());
}

void ASTStructKeyValueNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _key->print();
    _value->print();
    Logger::log("----------");
}

std::string ASTStructKeyValueNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder
    .add(_key)
    ->add(_colon)
    ->add(_value);
    return sourceCodeBuilder.build();
}