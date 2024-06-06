//
// Created by Johny Georges on 2024-03-22.
//

#include "ast-procedure-declaration-node.h"
#include "../../../../shared/utils/logger/logger.h"
#include "../../types/source-code-builder/source-code-builder.h"

ASTProcedureDeclarationNode::ASTProcedureDeclarationNode(ASTProcedureNode* procedureKeyword, ASTFunctionNameNode* name, ASTFunctionParameterListNode* parameters, ASTFunctionBlockNode* content) {
    _procedureKeyword = procedureKeyword;
    _name = name;
    _block = content;
    _parameters = parameters;
    _children.push_back(_name);
    _children.push_back(_block);
    _children.push_back(_parameters);

}

ASTFunctionParameterListNode* ASTProcedureDeclarationNode::getParameters() {
    return _parameters;
}

ASTFunctionNameNode* ASTProcedureDeclarationNode::getName() {
    return _name;
}

ASTFunctionBlockNode* ASTProcedureDeclarationNode::getBlock() {
    return _block;
}

unsigned long ASTProcedureDeclarationNode::numParameters() {
    return _parameters->numParameters();
}

void ASTProcedureDeclarationNode::setTypeSignature(ProcedureTypeSignature* typeSignature) {
    _typeSignature = typeSignature;
}

ProcedureTypeSignature* ASTProcedureDeclarationNode::getTypeSignature() {
    return _typeSignature;
}

Position* ASTProcedureDeclarationNode::getStartPosition() {
    return _procedureKeyword->getStartPosition();
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
    _name->print();
    _parameters->print();
    _block->print();
    Logger::log("----------");
}

std::string ASTProcedureDeclarationNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    sourceCodeBuilder.add(_procedureKeyword)
    ->addWithWhitespace(_name)
    ->addWithWhitespace(_parameters)
    ->addWithWhitespace(_block);
    return sourceCodeBuilder.build();
}