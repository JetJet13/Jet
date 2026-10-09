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
// Created by Johny Georges on 2024-03-22.
//

#ifndef JETLANG_AST_PROCEDURE_DECLARATION_NODE_H
#define JETLANG_AST_PROCEDURE_DECLARATION_NODE_H

#include <vector>
#include "../ast-node.h"
#include "../ast-identifier-node.h"
#include "../ast-export-node.h"
#include "../ast-expression-nodes/ast-identifier-expression-node.h"
#include "../ast-function-nodes/ast-function-parameter-list-node.h"
#include "../ast-function-nodes/ast-function-name-node.h"
#include "../ast-function-nodes/ast-function-block-node.h"
#include "ast-declaration-node.h"
#include "../ast-procedure-nodes/ast-procedure-node.h"
#include "../../../type-signature/invocable-type-signature/procedure-type-signature/procedure-type-signature.h"
#include "../ast-procedure-nodes/ast-procedure-definition-node.h"

class ASTProcedureDeclarationNode : public ASTDeclarationNode {
private:
    std::shared_ptr<ASTProcedureDefinitionNode> _procedureDefinition;
    std::shared_ptr<ASTFunctionBlockNode> _block;
    std::optional<std::shared_ptr<ASTExportNode>> _exportKeyword = {};
    std::shared_ptr<ProcedureTypeSignature> _typeSignature = std::make_shared<ProcedureTypeSignature>();
public:
    explicit ASTProcedureDeclarationNode(std::shared_ptr<ASTProcedureDefinitionNode> _procedureDefinition, std::shared_ptr<ASTFunctionBlockNode> content, std::optional<std::shared_ptr<ASTExportNode>> exportKeyword = {});
    std::shared_ptr<ASTFunctionParameterListNode> getParameters();
    std::shared_ptr<ASTFunctionNameNode> getName();
    std::shared_ptr<ASTFunctionBlockNode> getBlock();
    std::shared_ptr<ASTProcedureDefinitionNode> getDefinition();
    uint64_t numParameters();
    bool isExportable() override;
    void setTypeSignature(std::shared_ptr<ProcedureTypeSignature> typeSignature);
    std::shared_ptr<ProcedureTypeSignature> getProcedureTypeSignature();
    std::shared_ptr<TypeSignature> getTypeSignature() override;
    std::shared_ptr<Position> getStartPosition() override;
    std::shared_ptr<Position> getEndPosition() override;
    ASTNodeType getNodeType() override;
    std::string toString() override;
    bool isSameAs(std::shared_ptr<ASTNode> other) override;
    void print() override;
    std::string toSourceCode() override;
};

#endif //JETLANG_AST_PROCEDURE_DECLARATION_NODE_H
