//
// Created by Johny Georges on 2024-03-22.
//

#include "ast-procedure-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTProcedureDeclarationNode::ASTProcedureDeclarationNode(ASTProcedureDefinitionNode* procedureDefinition, ASTFunctionBlockNode* content, std::optional<ASTExportNode*> exportKeyword) {
    _procedureDefinition = procedureDefinition;
    _block = content;
    _exportKeyword = exportKeyword;
    _children.push_back(_procedureDefinition);
    _children.push_back(_block);

    if (_exportKeyword) {
        _children.push_back(_exportKeyword.value());
    }

}

ASTFunctionParameterListNode* ASTProcedureDeclarationNode::getParameters() {
    return _procedureDefinition->getParameters();
}

ASTFunctionNameNode* ASTProcedureDeclarationNode::getName() {
    return _procedureDefinition->getName();
}

ASTFunctionBlockNode* ASTProcedureDeclarationNode::getBlock() {
    return _block;
}

unsigned long ASTProcedureDeclarationNode::numParameters() {
    return _procedureDefinition->numParameters();
}

void ASTProcedureDeclarationNode::setTypeSignature(ProcedureTypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

ProcedureTypeSignature* ASTProcedureDeclarationNode::getTypeSignature() {
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

bool ASTProcedureDeclarationNode::isSameAs(ASTNode *other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = (ASTProcedureDeclarationNode*)other;

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
        sourceCodeBuilder.add(_exportKeyword.value())->addWithWhitespace(_procedureDefinition);
    } else {
        sourceCodeBuilder.add(_procedureDefinition);
    }
    sourceCodeBuilder.addWithWhitespace(_block);
    return sourceCodeBuilder.build();
}