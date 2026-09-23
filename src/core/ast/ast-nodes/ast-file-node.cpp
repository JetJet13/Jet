//
// Created by Johny Georges on 2024-01-15.
//

#include "ast-file-node.h"
#include "../types/source-code-builder/source-code-builder.h"
#include "../../../shared/utils/logger/logger.h"
#include "ast-declaration-nodes/ast-variable-declaration-node.h"

ASTFileNode::ASTFileNode(std::vector<std::shared_ptr<ASTNode>> body, std::string path, std::vector<std::shared_ptr<ASTImportSingleModuleDeclarationNode>> imports, std::optional<std::shared_ptr<ASTModuleDeclarationNode>> module) {
    _body = body;
    _path = std::filesystem::path(path);
    _imports = imports;
    _module = module;
}

void ASTFileNode::append(std::shared_ptr<ASTNode> node) {
    _body.push_back(node);
}

std::filesystem::path ASTFileNode::getPath() {
    return _path;
}

std::string ASTFileNode::getPathDirectory() {
    return _path.relative_path().remove_filename();
}

void ASTFileNode::markGlobalVariables() {
    for (auto content: _body) {
        if (content->is(AST_VARIABLE_DECLARATION_NODE)) {
            (std::dynamic_pointer_cast<ASTVariableDeclarationNode>(content))->markAsGlobal();
        }
    }
}

void ASTFileNode::hoistTypes(const std::vector<ASTNodeType> astNodeTypes) {
    auto newContent = std::vector<std::shared_ptr<ASTNode>>();
    for (auto content: _body) {
        if (content->isOneOf(astNodeTypes)) {
            newContent.insert(newContent.begin(), content);
        } else {
            newContent.push_back(content);
        }
    }
    _body = newContent;
}

void ASTFileNode::setupModuleIfNecessary() {
    if (!_module) {
        return;
    }
    for (auto node : _body) {
        if (node->isExportable()) {
            _module.value()->addExportedDeclaration(node);
        }
    }
}

std::optional<std::shared_ptr<ASTModuleDeclarationNode>> ASTFileNode::getModule() {
    return _module;
}

std::string ASTFileNode::getModuleName() {
    if (_module) {
        return _module.value()->getName()->getIdentifier()->getId();
    }
    return "";
}

std::vector<std::shared_ptr<ASTImportSingleModuleDeclarationNode>>* ASTFileNode::getImports() {
    return &_imports;
}

std::vector<std::shared_ptr<ASTNode>>* ASTFileNode::getBody() {
    return &_body;
}

std::shared_ptr<Position> ASTFileNode::getStartPosition() {
    if (_body.empty()) {
        return std::make_shared<Position>();
    }
    return _body[0]->getStartPosition();
}

std::shared_ptr<Position> ASTFileNode::getEndPosition() {
    if (_body.empty()) {
        return std::make_shared<Position>();
    }
    return _body[_body.size() - 1]->getEndPosition();
}

ASTNodeType ASTFileNode::getNodeType() {
    return AST_FILE_NODE;
}

std::string ASTFileNode::toString() {
    return "FILE";
}

bool ASTFileNode::isSameAs(std::shared_ptr<ASTNode> other) {
    if (!other->is(this->getNodeType())) {
        return false;
    }
    auto otherNode = std::dynamic_pointer_cast<ASTFileNode>(other);
    for (uint64_t i = 0; i < _body.size(); ++i) {
        if (!_body[i]->isSameAs(otherNode->getBody()->at(i))) {
            return false;
        }
    }
    return true;
}

std::string ASTFileNode::toSourceCode() {
    auto sourceCodeBuilder = SourceCodeBuilder();
    for (auto node : _body) {
        sourceCodeBuilder.add(node);
    }
    return sourceCodeBuilder.build();
}