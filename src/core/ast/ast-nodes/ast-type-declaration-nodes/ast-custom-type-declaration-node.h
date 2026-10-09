// Copyright 2026 Johny Georges
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//
// Created by Johny Georges on 2025-07-07.
//

#ifndef JETLANG_AST_CUSTOM_TYPE_DECLARATION_NODE_H
#define JETLANG_AST_CUSTOM_TYPE_DECLARATION_NODE_H

#include "./ast-type-declaration-node.h"
#include "../ast-interface-nodes/ast-interface-definition-node.h"
#include "../ast-interface-nodes/ast-interface-property-list-node.h"
#include "../../../type-signature/interface-type-signature/interface-type-signature.h"
#include "../ast-export-node.h"
#include "../ast-type-nodes/ast-type-keyword-node.h"
#include "../ast-type-nodes/ast-type-name-node.h"
#include "../ast-type-nodes/ast-type-assignment-operator-node.h"

class ASTCustomTypeDeclarationNode : public ASTTypeDeclarationNode {
private:
    std::shared_ptr<ASTTypeKeywordNode> _typeKeyword;
    std::shared_ptr<ASTTypeNameNode> _typeName;
    std::shared_ptr<ASTTypeAssignmentOperatorNode> _assignmentOperator;
    std::shared_ptr<ASTTypeNode> _type;
    std::optional<std::shared_ptr<ASTExportNode>> _exportKeyword = {};
    std::shared_ptr<TypeSignature> _typeSignature = std::make_shared<UnknownTypeSignature>();
public:
    explicit ASTCustomTypeDeclarationNode(std::shared_ptr<ASTTypeKeywordNode> typeKeyword, std::shared_ptr<ASTTypeNameNode> typeName, std::shared_ptr<ASTTypeAssignmentOperatorNode> assignmentOperator, std::shared_ptr<ASTTypeNode> type, std::optional<std::shared_ptr<ASTExportNode>> exportKeyword = {});
    std::shared_ptr<ASTTypeNode> getType();
    std::shared_ptr<ASTTypeNameNode> getName();
    bool isExportable() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_CUSTOM_TYPE_DECLARATION_NODE_H
