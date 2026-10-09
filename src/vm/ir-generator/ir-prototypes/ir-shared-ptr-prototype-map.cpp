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
// Created by Johny Georges on 2025-10-25.
//

#include "ir-shared-ptr-prototype-map.h"
#include "../ir-util-functions/shares-with-ir-function/shares-with-ir-function.h"
#include "../ir-util-functions/get-ref-count-ir-function/get-ref-count-ir-function.h"

std::optional<IRSharedPtrPrototypeFunctionId> SharedPtrPrototypeMap::getIRSharedPtrPrototypeFunction(std::string id) {
    if (id == "sharesWith") {
        return SPP_SHARES_WITH_FUNCTION;
    } else if (id == "refCount") {
        return SPP_REF_COUNT_FUNCTION;
    }
    return {};
}

std::optional<std::string> SharedPtrPrototypeMap::getIRName(const std::string& id) {
    auto prototypeFunctionId = SharedPtrPrototypeMap::getIRSharedPtrPrototypeFunction(id);
    if (prototypeFunctionId) {
        return SharedPtrPrototypeMap::getIRName(prototypeFunctionId.value());
    }
    return {};
}

std::string SharedPtrPrototypeMap::getIRName(IRSharedPtrPrototypeFunctionId irSharedPtrPrototypeFunction) {
    switch (irSharedPtrPrototypeFunction) {
        case SPP_SHARES_WITH_FUNCTION:
            return SharesWithIRFunction::getSharesWithIRFunctionName();
        case SPP_REF_COUNT_FUNCTION:
            return GetRefCountIRFunction::getGetRefCountIRFunctionName();
    }
    throw std::logic_error("unable to find ref prototype name");
}