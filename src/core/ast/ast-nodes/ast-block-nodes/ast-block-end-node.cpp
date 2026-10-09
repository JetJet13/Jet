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
// Created by Johny Georges on 2024-03-13.
//

#include "ast-block-end-node.h"
#include "../ast-struct-nodes/ast-struct-end-node.h"
#include "../ast-enum-nodes/ast-enum-key-value-list-end-node.h"
#include "../ast-tuple-nodes/ast-tuple-list-end-node.h"
#include "../ast-module-nodes/ast-module-list-end-node.h"
#include "../ast-import-nodes/ast-import-module-list-end-node.h"
#include "../ast-interface-nodes/ast-interface-end-node.h"
#include "../ast-type-nodes/ast-struct-type-nodes/ast-struct-type-end-node.h"
#include "../ast-type-nodes/ast-tuple-type-nodes/ast-tuple-type-end-node.h"

std::shared_ptr<ASTNode> ASTBlockEndNode::transformIfNecessary(std::optional<std::shared_ptr<ASTNode>> prevNode, std::optional<std::shared_ptr<ASTNode>> nextNode,
                                                SyntaxAnalyzerMode mode) {
    if (mode == SA_STRUCT_MODE) {
        return std::make_shared<ASTStructEndNode>(_lexeme);
    }

    if (mode == SA_ENUM_KEY_VALUE_LIST_MODE) {
        return std::make_shared<ASTEnumKeyValueListEndNode>(_lexeme);
    }

    if (mode == SA_STRUCT_TYPE_MODE) {
        return std::make_shared<ASTStructTypeEndNode>(_lexeme);
    }

    if (mode == SA_TUPLE_TYPE_MODE) {
        return std::make_shared<ASTTupleTypeEndNode>(_lexeme);
    }

    if (mode == SA_TUPLE_LIST_MODE) {
        return std::make_shared<ASTTupleListEndNode>(_lexeme);
    }

    if (mode == SA_INTERFACE_MODE) {
        return std::make_shared<ASTInterfaceEndNode>(_lexeme);
    }

    if (mode == SA_MODULE_LIST_MODE) {
        return std::make_shared<ASTModuleListEndNode>(_lexeme);
    }

    if (mode == SA_IMPORT_MODULE_LIST_MODE) {
        return std::make_shared<ASTImportModuleListEndNode>(_lexeme);
    }

    return shared_from_this();
}

ASTNodeType ASTBlockEndNode::getNodeType() {
    return AST_BLOCK_END_NODE;
}

std::string ASTBlockEndNode::toString() {
    return "BLOCK_END";
}