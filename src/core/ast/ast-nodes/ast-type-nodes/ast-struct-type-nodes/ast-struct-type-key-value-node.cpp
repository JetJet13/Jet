//
// Created by Johny Georges on 2025-06-28.
//

#include "ast-struct-type-key-value-node.h"
#include "../../../../../shared/utils/logger/logger.h"
#include "../../../types/source-code-builder/source-code-builder.h"

ASTStructTypeKeyValueNode::ASTStructTypeKeyValueNode(ASTStructTypeKeyNode* name, ASTStructTypeColonNode* colon, ASTTypeNode* type) {
    _name = name;
    _colon = colon;
    _type = type;
    _children.push_back(_name);
    _children.push_back(_colon);
    _children.push_back(_type);
}

ASTStructTypeKeyNode* ASTStructTypeKeyValueNode::getName() {
    return _name;
}

ASTTypeNode* ASTStructTypeKeyValueNode::getType() {
    return _type;
}

void ASTStructTypeKeyValueNode::setTypeSignature(TypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

TypeSignature* ASTStructTypeKeyValueNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTStructTypeKeyValueNode::getStartPosition() {
    return _name->getStartPosition();
}

Position* ASTStructTypeKeyValueNode::getEndPosition() {
    return _type->getEndPosition();
}

ASTNodeType ASTStructTypeKeyValueNode::getNodeType() {
    return AST_STRUCT_TYPE_KEY_NODE;
}

std::string ASTStructTypeKeyValueNode::toString() {
    return "STRUCT_TYPE_KEY";
}

bool ASTStructTypeKeyValueNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = (ASTStructTypeKeyValueNode*)other;
    auto result = this->getName()->isSameAs(otherNode->getName()) &&
           this->getType()->isSameAs(otherNode->getType());
    return result;
}

void ASTStructTypeKeyValueNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    _type->print();
    Logger::log("----------");
}

std::string ASTStructTypeKeyValueNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_name)
            ->add(_colon)
            ->addWithWhitespace(_type);
    return sourceCodeBuilder.build();
}