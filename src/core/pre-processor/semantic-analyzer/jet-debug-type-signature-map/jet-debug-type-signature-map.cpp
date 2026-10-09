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
// Created by Johny Georges on 2026-01-10.
//

#include "jet-debug-type-signature-map.h"
#include "../../../type-signature/literal-type-signature/int-literal-type-signature.h"
#include "../../../type-signature/struct-type-signature/struct-type-signature.h"
#include "../../../type-signature/invocable-type-signature/lambda-type-signature/lambda-type-signature.h"
#include "../../../type-signature/tuple-type-signature/tuple-type-signature.h"
#include "../../../type-signature/class-type-signature/class-instance-type-signature/class-instance-type-signature.h"
#include "../../../type-signature/shared-type-signature/shared-type-signature.h"

std::string JetDebugTypeSignatureMap::getAssertDebugRefCountTypeSignatureKey() {
    return "assertDebugRefCount";
}

std::string JetDebugTypeSignatureMap::getAssertDebugStructRefCountTypeSignatureKey() {
    return "assertDebugStructRefCount";
}

std::string JetDebugTypeSignatureMap::getAssertDebugTupleRefCountTypeSignatureKey() {
    return "assertDebugTupleRefCount";
}

std::string JetDebugTypeSignatureMap::getAssertDebugClassRefCountTypeSignatureKey() {
    return "assertDebugClassRefCount";
}

std::string JetDebugTypeSignatureMap::getAssertDebugLambdaRefCountTypeSignatureKey() {
    return "assertDebugLambdaRefCount";
}

std::shared_ptr<FunctionTypeSignature> JetDebugTypeSignatureMap::getAssertDebugRefCountTypeSignature() {
    auto assertDebugRefCountTypeSignature = std::make_shared<FunctionTypeSignature>(
        std::make_shared<ParameterListTypeSignature>(std::vector {
            std::make_shared<ParameterListItemTypeSignature>("sharedValue", (std::make_shared<SharedTypeSignature>(std::make_shared<VoidTypeSignature>()))->markAsGeneric()),
            std::make_shared<ParameterListItemTypeSignature>("expectedRefCount", std::make_shared<IntLiteralTypeSignature>()),
        }),
        std::make_shared<VoidTypeSignature>()
    );
    assertDebugRefCountTypeSignature->markAsBuiltIn(BI_ASSERT_DEBUG_REF_COUNT_TYPE_SOURCE)->markAsDebug();
    return assertDebugRefCountTypeSignature;
}

std::shared_ptr<FunctionTypeSignature> JetDebugTypeSignatureMap::getAssertDebugStructRefCountTypeSignature() {
    auto assertDebugStructRefCountTypeSignature = std::make_shared<FunctionTypeSignature>(
        std::make_shared<ParameterListTypeSignature>(std::vector {
            std::make_shared<ParameterListItemTypeSignature>("structValue", (std::make_shared<StructTypeSignature>())->markAsGeneric()),
            std::make_shared<ParameterListItemTypeSignature>("expectedRefCount", std::make_shared<IntLiteralTypeSignature>()),
        }),
        std::make_shared<VoidTypeSignature>()
    );
    assertDebugStructRefCountTypeSignature->markAsBuiltIn(BI_ASSERT_DEBUG_STRUCT_REF_COUNT_TYPE_SOURCE)->markAsDebug();
    return assertDebugStructRefCountTypeSignature;
}

std::shared_ptr<FunctionTypeSignature> JetDebugTypeSignatureMap::getAssertDebugTupleRefCountTypeSignature() {
    auto assertDebugTupleRefCountTypeSignature = std::make_shared<FunctionTypeSignature>(
            std::make_shared<ParameterListTypeSignature>(std::vector {
               std::make_shared<ParameterListItemTypeSignature>("tupleValue", (std::make_shared<TupleTypeSignature>())->markAsGeneric()),
               std::make_shared<ParameterListItemTypeSignature>("expectedRefCount", std::make_shared<IntLiteralTypeSignature>()),
            }),
            std::make_shared<VoidTypeSignature>()
    );
    assertDebugTupleRefCountTypeSignature->markAsBuiltIn(BI_ASSERT_DEBUG_TUPLE_REF_COUNT_TYPE_SOURCE)->markAsDebug();
    return assertDebugTupleRefCountTypeSignature;
}

std::shared_ptr<FunctionTypeSignature> JetDebugTypeSignatureMap::getAssertDebugClassRefCountTypeSignature() {
    auto assertDebugTupleRefCountTypeSignature = std::make_shared<FunctionTypeSignature>(
            std::make_shared<ParameterListTypeSignature>(std::vector {
               std::make_shared<ParameterListItemTypeSignature>("classInstance", (std::make_shared<ClassInstanceTypeSignature>())->markAsGeneric()),
               std::make_shared<ParameterListItemTypeSignature>("expectedRefCount", std::make_shared<IntLiteralTypeSignature>()),
            }),
            std::make_shared<VoidTypeSignature>()
    );
    assertDebugTupleRefCountTypeSignature->markAsBuiltIn(BI_ASSERT_DEBUG_CLASS_REF_COUNT_TYPE_SOURCE)->markAsDebug();
    return assertDebugTupleRefCountTypeSignature;
}

std::shared_ptr<FunctionTypeSignature> JetDebugTypeSignatureMap::getAssertDebugLambdaRefCountTypeSignature() {
    auto assertDebugLambdaCountTypeSignature = std::make_shared<FunctionTypeSignature>(
        std::make_shared<ParameterListTypeSignature>(std::vector {
            std::make_shared<ParameterListItemTypeSignature>("lambdaValue", (std::make_shared<LambdaTypeSignature>())->markAsGeneric()),
            std::make_shared<ParameterListItemTypeSignature>("expectedRefCount", std::make_shared<IntLiteralTypeSignature>()),
        }),
        std::make_shared<VoidTypeSignature>()
    );
    assertDebugLambdaCountTypeSignature->markAsBuiltIn(BI_ASSERT_DEBUG_LAMBDA_REF_COUNT_TYPE_SOURCE)->markAsDebug();
    return assertDebugLambdaCountTypeSignature;
}