//
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"


ASTClassDeclarationNode::ASTClassDeclarationNode(std::shared_ptr<ASTClassNode> classKeyword, std::shared_ptr<ASTClassNameNode> name, std::shared_ptr<ASTClassBlockNode> block, std::optional<std::shared_ptr<ASTImplementsInterfaceListNode>> implementsInterfaceList) {
    _classKeyword = classKeyword;
    _name = name;
    _block = block;
    _implementsInterfaceList = implementsInterfaceList;
    _children.push_back(_classKeyword);
    _children.push_back(_name);
    if (_implementsInterfaceList) {
        _children.push_back(_implementsInterfaceList.value());
    }
    _children.push_back(_block);
}

ASTClassDeclarationNode::ASTClassDeclarationNode(std::shared_ptr<ASTClassNode> classKeyword, std::shared_ptr<ASTClassNameNode> name, std::shared_ptr<ASTClassBlockNode> block, std::shared_ptr<ASTExportNode> exportKeyword) {
    _classKeyword = classKeyword;
    _name = name;
    _block = block;
    _exportKeyword = exportKeyword;
    _children.push_back(_classKeyword);
    _children.push_back(_name);
    _children.push_back(_exportKeyword.value());
    _children.push_back(_block);
}

std::shared_ptr<ASTClassBlockNode> ASTClassDeclarationNode::getBlock() {
    return _block;
}

std::shared_ptr<ASTClassNameNode> ASTClassDeclarationNode::getName() {
    return _name;
}

void ASTClassDeclarationNode::setTypeSignature(std::shared_ptr<ClassTypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::optional<std::shared_ptr<ASTImplementsInterfaceListNode>>* ASTClassDeclarationNode::getImplementsInterfaceList() {
    return &_implementsInterfaceList;
}

std::shared_ptr<ClassTypeSignature> ASTClassDeclarationNode::getClassTypeSignature() {
    return std::dynamic_pointer_cast<ClassTypeSignature>(_typeSignature);
}

std::shared_ptr<TypeSignature> ASTClassDeclarationNode::getTypeSignature() {
    return _typeSignature;
}

bool ASTClassDeclarationNode::isExportable() {
    return _exportKeyword.has_value();
}

Position* ASTClassDeclarationNode::getStartPosition() {
    return _classKeyword->getStartPosition();
}

Position* ASTClassDeclarationNode::getEndPosition() {
    return _block->getEndPosition();
}

ASTNodeType ASTClassDeclarationNode::getNodeType() {
    return AST_CLASS_DECLARATION_NODE;
}

std::string ASTClassDeclarationNode::toString() {
    return "CLASS_DECLARATION";
}

bool ASTClassDeclarationNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTClassDeclarationNode>(other);

    if (!_implementsInterfaceList.has_value() && otherNode->getImplementsInterfaceList()->has_value() ||
        _implementsInterfaceList.has_value() && !otherNode->getImplementsInterfaceList()->has_value()) {
        return false;
    }

    if (_implementsInterfaceList.has_value() && otherNode->getImplementsInterfaceList()->has_value() &&
        !_implementsInterfaceList.value()->isSameAs(otherNode->getImplementsInterfaceList()->value())) {
        return false;
    }

    return this->getName()->isSameAs(otherNode->getName()) &&
           this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTClassDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    if (_implementsInterfaceList) {
        _implementsInterfaceList.value()->print();
    }
    _block->print();
    Logger::log("----------");
}

std::string ASTClassDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_classKeyword)
    ->add(_name);
    if (_implementsInterfaceList) {
        sourceCodeBuilder.add(_implementsInterfaceList.value());
    }
    sourceCodeBuilder.add(_block);
    return sourceCodeBuilder.build();
}