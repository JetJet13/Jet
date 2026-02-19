//
// Created by Johny Georges on 2025-10-25.
//

#include "ir-ref-prototype-map.h"
#include "../ir-util-functions/ref-of-ir-function/ref-of-ir-function.h"
#include "../ir-util-functions/sref-with-ir-function/sref-with-ir-function.h"
#include "../ir-util-functions/same-ref-as-ir-function/same-ref-as-ir-function.h"
#include "../ir-util-functions/get-ref-count-ir-function/get-ref-count-ir-function.h"
#include "../ir-util-functions/set-ref-value-ir-function/set-ref-value-ir-function.h"

IRRefPrototypeFunctionId RefPrototypeMap::getIRRefPrototypeFunction(std::string id) {
    if (id == "refOf") {
        return RP_REF_OF_FUNCTION;
    } else if (id == "srefWith") {
        return RP_SREF_WITH_FUNCTION;
    } else if (id == "sameRefAs") {
        return RP_SAME_REF_AS_FUNCTION;
    } else if (id == "refCount") {
        return RP_REF_COUNT_FUNCTION;
    } else if (id == "setRefValue") {
        return RP_SET_REF_VALUE_FUNCTION;
    }
    throw std::logic_error("unable to find array prototype function for id provided: " + id);
}

std::string RefPrototypeMap::getIRName(std::string id) {
    return RefPrototypeMap::getIRName(RefPrototypeMap::getIRRefPrototypeFunction(id));
}

std::string RefPrototypeMap::getIRName(IRRefPrototypeFunctionId irRefPrototypeFunction) {
    switch (irRefPrototypeFunction) {
        case RP_REF_OF_FUNCTION:
            return RefOfIRFunction::getRefOfIRFunctionName();
        case RP_SREF_WITH_FUNCTION:
            return SrefWithIRFunction::getSrefWithIRFunctionName();
        case RP_SAME_REF_AS_FUNCTION:
            return SameRefAsIRFunction::getSameRefAsIRFunctionName();
        case RP_REF_COUNT_FUNCTION:
            return GetRefCountIRFunction::getGetRefCountIRFunctionName();
        case RP_SET_REF_VALUE_FUNCTION:
            return SetRefValueIRFunction::getSetRefValueIRFunctionName();
    }
    throw std::logic_error("unable to find ref prototype name");
}