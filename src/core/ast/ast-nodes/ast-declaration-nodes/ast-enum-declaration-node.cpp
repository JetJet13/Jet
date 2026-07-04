//
// Created by Johny Georges on 2024-03-22.
//

#include "ast-enum-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTEnumDeclarationNode::ASTEnumDeclarationNode(std::shared_ptr<ASTEnumNode> enumKeyword, std::shared_ptr<ASTEnumNameNode> name, std::shared_ptr<ASTEnumKeyValueListNode> values, std::optional<std::shared_ptr<ASTExportNode>> exportKeyword) {
    _enumKeyword = enumKeyword;
    _name = name;
    _values = values;
    _exportKeyword = exportKeyword;
    _children.push_back(_enumKeyword);
    _children.push_back(_name);
    _children.push_back(_values);
    if (_exportKeyword) {
        _children.push_back(_exportKeyword.value());
    }
}

std::shared_ptr<ASTEnumKeyValueListNode> ASTEnumDeclarationNode::getValues() {
    return _values;
}

std::shared_ptr<ASTEnumNameNode> ASTEnumDeclarationNode::getName() {
    return _name;
}

void ASTEnumDeclarationNode::setTypeSignature(std::shared_ptr<EnumTypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<EnumTypeSignature> ASTEnumDeclarationNode::getEnumTypeSignature() {
    return std::dynamic_pointer_cast<EnumTypeSignature>(_typeSignature);
}

std::shared_ptr<TypeSignature> ASTEnumDeclarationNode::getTypeSignature() {
    return _typeSignature;
}

bool ASTEnumDeclarationNode::isExportable() {
    return _exportKeyword.has_value();
}

Position* ASTEnumDeclarationNode::getStartPosition() {
    return _enumKeyword->getStartPosition();
}

Position* ASTEnumDeclarationNode::getEndPosition() {
    return _values->getEndPosition();
}

ASTNodeType ASTEnumDeclarationNode::getNodeType() {
    return AST_ENUM_DECLARATION_NODE;
}

std::string ASTEnumDeclarationNode::toString() {
    return "ENUM_DECLARATION";
}

bool ASTEnumDeclarationNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTEnumDeclarationNode>(other);

    return  this->getName()->isSameAs(otherNode->getName()) &&
            this->getValues()->isSameAs(otherNode->getValues());
}

void ASTEnumDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    _name->print();
    _values->print();
    Logger::log("----------");
}

std::string ASTEnumDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_enumKeyword)
    ->add(_name)
    ->add(_values);
    return sourceCodeBuilder.build();
}