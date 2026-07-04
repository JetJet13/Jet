//
// Created by Johny Georges on 2024-03-22.
//

#include "ast-procedure-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTProcedureDeclarationNode::ASTProcedureDeclarationNode(std::shared_ptr<ASTProcedureDefinitionNode> procedureDefinition, std::shared_ptr<ASTFunctionBlockNode> content, std::optional<std::shared_ptr<ASTExportNode>> exportKeyword) {
    _procedureDefinition = procedureDefinition;
    _block = content;
    _exportKeyword = exportKeyword;
    _children.push_back(_procedureDefinition);
    _children.push_back(_block);

    if (_exportKeyword) {
        _children.push_back(_exportKeyword.value());
    }

}

std::shared_ptr<ASTFunctionParameterListNode> ASTProcedureDeclarationNode::getParameters() {
    return _procedureDefinition->getParameters();
}

std::shared_ptr<ASTFunctionNameNode> ASTProcedureDeclarationNode::getName() {
    return _procedureDefinition->getName();
}

std::shared_ptr<ASTFunctionBlockNode> ASTProcedureDeclarationNode::getBlock() {
    return _block;
}

std::shared_ptr<ASTProcedureDefinitionNode> ASTProcedureDeclarationNode::getDefinition() {
    return _procedureDefinition;
}

unsigned long ASTProcedureDeclarationNode::numParameters() {
    return _procedureDefinition->numParameters();
}

bool ASTProcedureDeclarationNode::isExportable() {
    return _exportKeyword.has_value();
}

void ASTProcedureDeclarationNode::setTypeSignature(std::shared_ptr<ProcedureTypeSignature> typeSignature) {
    _typeSignature = typeSignature;
}

std::shared_ptr<ProcedureTypeSignature> ASTProcedureDeclarationNode::getProcedureTypeSignature() {
    return std::dynamic_pointer_cast<ProcedureTypeSignature>(_typeSignature);
}

std::shared_ptr<TypeSignature> ASTProcedureDeclarationNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTProcedureDeclarationNode::getStartPosition() {
    return _procedureDefinition->getStartPosition();
}

Position* ASTProcedureDeclarationNode::getEndPosition() {
    return _block->getEndPosition();
}

ASTNodeType ASTProcedureDeclarationNode::getNodeType() {
    return AST_PROCEDURE_DECLARATION_NODE;
}

std::string ASTProcedureDeclarationNode::toString() {
    return "PROCEDURE_DECLARATION";
}

bool ASTProcedureDeclarationNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTProcedureDeclarationNode>(other);

    return  this->getName()->isSameAs(otherNode->getName()) &&
            this->getParameters()->isSameAs(otherNode->getParameters()) &&
            this->getBlock()->isSameAs(otherNode->getBlock());
}

void ASTProcedureDeclarationNode::print() {
    Logger::log("----------", this->toString(), "----------");
    if (_exportKeyword) {
        _exportKeyword.value()->print();
    }
    _block->print();
    Logger::log("----------");
}

std::string ASTProcedureDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    if (_exportKeyword) {
        sourceCodeBuilder.add(_exportKeyword.value())->add(_procedureDefinition);
    } else {
        sourceCodeBuilder.add(_procedureDefinition);
    }
    sourceCodeBuilder.add(_block);
    return sourceCodeBuilder.build();
}