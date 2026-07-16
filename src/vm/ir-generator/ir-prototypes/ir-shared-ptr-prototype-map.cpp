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