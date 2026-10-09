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
// Created by Johny Georges on 2024-04-20.
//

#include "ast-class-method-call-node.h"
#include "../../../../shared/utils/logger/logger.h"

void ASTClassMethodCallNode::setTypeSignature(std::shared_ptr<ClassMethodTypeSignature> classMethodTypeSignature) {
    _typeSignature = classMethodTypeSignature;
}

std::shared_ptr<ClassMethodTypeSignature> ASTClassMethodCallNode::getMethodTypeSignature() {
    return std::dynamic_pointer_cast<ClassMethodTypeSignature>(_typeSignature);
}

std::shared_ptr<TypeSignature> ASTClassMethodCallNode::getTypeSignature() {
    return _typeSignature;
}

ASTNodeType ASTClassMethodCallNode::getNodeType() {
    return AST_CLASS_METHOD_CALL_NODE;
}

std::string ASTClassMethodCallNode::toString() {
    return "CLASS_METHOD_CALL";
}