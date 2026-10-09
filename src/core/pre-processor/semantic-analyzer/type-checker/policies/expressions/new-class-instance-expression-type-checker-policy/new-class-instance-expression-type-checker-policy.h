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
// Created by Johny Georges on 2024-05-29.
//

#ifndef JETLANG_NEW_CLASS_INSTANCE_EXPRESSION_TYPE_CHECKER_POLICY_H
#define JETLANG_NEW_CLASS_INSTANCE_EXPRESSION_TYPE_CHECKER_POLICY_H

#include "../../../types/type-checker-result/type-checker-result.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-logical-expression-node.h"
#include "../../../../../../ast/ast-nodes/ast-expression-nodes/ast-new-class-instance-expression.h"
#include "../../../../type-signature-lookup-table/type-signature-lookup-table.h"

namespace NewClassInstanceExpressionTypeCheckerPolicy {
    void apply(std::shared_ptr<ASTNewClassInstanceExpressionNode> newClassInstanceExpression, TypeCheckerResult* typeCheckerResult, std::shared_ptr<TypeSignatureLookupTable> fileScope);
};

#endif //JETLANG_NEW_CLASS_INSTANCE_EXPRESSION_TYPE_CHECKER_POLICY_H
