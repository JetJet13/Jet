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
// Created by Johny Georges on 2025-01-11.
//

#ifndef JETLANG_PROCEDURE_DECLARATION_IR_INJECTOR_STRATEGY_H
#define JETLANG_PROCEDURE_DECLARATION_IR_INJECTOR_STRATEGY_H

#include "../../../ir-lookup-table/ir-lookup-table.h"
#include "../../../ir-nodes/ir-module-node.h"
#include "../../../ir-nodes/ir-declaration-nodes/ir-procedure-declaration-node.h"
#include "../../ir-injector.h"

class ProcedureDeclarationIRInjectorStrategy {
public:
    void inject(std::shared_ptr<IRProcedureDeclarationNode> irProcedureDeclaration, std::shared_ptr<IRBlockNode> irBlock, std::shared_ptr<IRInjector> irInjector, std::shared_ptr<IRModuleNode> irModule, std::shared_ptr<IRLookupTable> scope);
};

#endif //JETLANG_PROCEDURE_DECLARATION_IR_INJECTOR_STRATEGY_H
