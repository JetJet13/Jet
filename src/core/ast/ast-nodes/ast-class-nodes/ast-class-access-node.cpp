//
// Created by Johny Georges on 2024-04-25.
//

#include "ast-class-access-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTClassAccessNode::ASTClassAccessNode(std::shared_ptr<ASTThisNode> thisNode, std::shared_ptr<ASTThisAccessNode> thisAccess) {
    _this = thisNode;
    _thisAccess = thisAccess;
    _children.push_back(_this);
    _children.push_back(_thisAccess);
}

std::shared_ptr<ASTThisNode> ASTClassAccessNode::getThis() {
    return _this;
}

std::shared_ptr<ASTThisAccessNode> ASTClassAccessNode::getThisAccess() {
    return _thisAccess;
}

void ASTClassAccessNode::setTypeSignature(std::shared_ptr<ClassTypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<ClassTypeSignature> ASTClassAccessNode::getClassTypeSignature() {
    return _typeSignature;
}

std::shared_ptr<Position> ASTClassAccessNode::getStartPosition() {
    return _this->getStartPosition();
}

std::shared_ptr<Position> ASTClassAccessNode::getEndPosition() {
    return _thisAccess->getEndPosition();
}

ASTNodeType ASTClassAccessNode::getNodeType() {
    return AST_CLASS_ACCESS_NODE;
}

std::string ASTClassAccessNode::toString() {
    return "CLASS_ACCESS";
}

bool ASTClassAccessNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())){
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTClassAccessNode>(other);
    return this->getThis()->isSameAs(otherNode->getThis()) &&
           this->getThisAccess()->isSameAs(otherNode->getThisAccess());
}

void ASTClassAccessNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _this->print();
    _thisAccess->print();
    Logger::log("----------");
}

std::string ASTClassAccessNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_this)
    ->add(_thisAccess);
    return sourceCodeBuilder.build();
}