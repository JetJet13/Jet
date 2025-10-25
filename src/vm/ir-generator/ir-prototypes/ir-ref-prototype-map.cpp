//
// Created by Johny Georges on 2025-10-25.
//

#include "ir-ref-prototype-map.h"
#include "../ir-util-functions/ref-of-ir-function/ref-of-ir-function.h"
#include "../ir-util-functions/sref-with-ir-function/sref-with-ir-function.h"

IRRefPrototypeFunctionId RefPrototypeMap::getIRRefPrototypeFunction(std::string id) {
    if (id == "refOf") {
        return RP_REF_OF_FUNCTION;
    } else if (id == "srefWith") {
        return RP_SREF_WITH_FUNCTION;
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
    }
    throw std::logic_error("unable to find ref prototype name");
}