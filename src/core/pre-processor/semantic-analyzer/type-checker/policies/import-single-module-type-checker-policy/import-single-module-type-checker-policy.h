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
// Created by Johny Georges on 2024-10-28.
//

#ifndef JETLANG_IMPORT_SINGLE_MODULE_TYPE_CHECKER_POLICY_H
#define JETLANG_IMPORT_SINGLE_MODULE_TYPE_CHECKER_POLICY_H

#include "../../types/type-checker-result/type-checker-result.h"
#include "../../../../../ast/ast-nodes/ast-function-nodes/ast-function-parameter-node.h"
#include "../../../../../ast/ast-nodes/ast-declaration-nodes/ast-import-single-module-declaration-node.h"
#include "../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace ImportSingleModuleTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTImportSingleModuleDeclarationNode> importSingleModuleDeclarationNode, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_IMPORT_SINGLE_MODULE_TYPE_CHECKER_POLICY_H
