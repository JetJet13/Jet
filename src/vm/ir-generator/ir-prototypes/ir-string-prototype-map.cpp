//
// Created by Johny Georges on 2026-03-21.
//

#include "ir-string-prototype-map.h"
#include "../ir-util-functions/array-prepend-ir-function/array-prepend-ir-function.h"
#include "../ir-util-functions/array-append-ir-function/array-append-ir-function.h"
#include "../ir-util-functions/array-last-ir-function/array-last-ir-function.h"
#include "../ir-util-functions/array-drop-ir-function/array-drop-ir-function.h"
#include "../ir-util-functions/array-drop-last-ir-function/array-drop-last-ir-function.h"
#include "../ir-util-functions/array-take-ir-function/array-take-ir-function.h"
#include "../ir-util-functions/array-take-last-ir-function/array-take-last-ir-function.h"
#include "../ir-util-functions/array-head-ir-function/array-head-ir-function.h"
#include "../ir-util-functions/array-tail-ir-function/array-tail-ir-function.h"
#include "../ir-util-functions/array-size-ir-function/array-size-ir-function.h"
#include "../ir-util-functions/array-empty-ir-function/array-empty-ir-function.h"
#include "../ir-util-functions/string-drop-ir-function/string-drop-ir-function.h"
#include "../ir-util-functions/string-drop-last-ir-function/string-drop-last-ir-function.h"
#include "../ir-util-functions/string-empty-ir-function/string-empty-ir-function.h"
#include "../ir-util-functions/string-size-ir-function/string-size-ir-function.h"
#include "../ir-util-functions/string-last-ir-function/string-last-ir-function.h"
#include "../ir-util-functions/string-tail-ir-function/string-tail-ir-function.h"
#include "../ir-util-functions/string-take-ir-function/string-take-ir-function.h"
#include "../ir-util-functions/string-take-last-ir-function/string-take-last-ir-function.h"
#include "../ir-util-functions/string-head-ir-function/string-head-ir-function.h"

IRStringPrototypeFunctionId StringPrototypeMap::getIRStringPrototypeFunction(std::string id) {
    if (id == "drop") {
        return SP_DROP_FUNCTION;
    } else if (id == "dropLast") {
        return SP_DROP_LAST_FUNCTION;
    } else if (id == "take") {
        return SP_TAKE_FUNCTION;
    } else if (id == "takeLast") {
        return SP_TAKE_LAST_FUNCTION;
    } else if (id == "head") {
        return SP_HEAD_FUNCTION;
    } else if (id == "tail") {
        return SP_TAIL_FUNCTION;
    } else if (id == "last") {
        return SP_LAST_FUNCTION;
    } else if (id == "size") {
        return SP_SIZE_FUNCTION;
    } else if (id == "empty") {
        return SP_EMPTY_FUNCTION;
    }
    throw std::logic_error("unable to find array prototype function for id provided: " + id);
}

std::string StringPrototypeMap::getIRName(std::string id) {
    return StringPrototypeMap::getIRName(StringPrototypeMap::getIRStringPrototypeFunction(id));
}

std::string StringPrototypeMap::getIRName(IRStringPrototypeFunctionId irStringPrototypeFunction) {
    switch (irStringPrototypeFunction) {
        case SP_DROP_FUNCTION:
            return StringDropIRFunction::getStringDropIRFunctionName();
        case SP_DROP_LAST_FUNCTION:
            return StringDropLastIRFunction::getStringDropLastIRFunctionName();
        case SP_TAKE_FUNCTION:
            return StringTakeIRFunction::getStringTakeIRFunctionName();
        case SP_TAKE_LAST_FUNCTION:
            return StringTakeLastIRFunction::getStringTakeLastIRFunctionName();
        case SP_TAIL_FUNCTION:
            return StringTailIRFunction::getStringTailIRFunctionName();
        case SP_HEAD_FUNCTION:
            return StringHeadIRFunction::getStringHeadIRFunctionName();
        case SP_LAST_FUNCTION:
            return StringLastIRFunction::getStringLastIRFunctionName();
        case SP_SIZE_FUNCTION:
            return StringSizeIRFunction::getStringSizeIRFunctionName();
        case SP_EMPTY_FUNCTION:
            return StringEmptyIRFunction::getStringEmptyIRFunctionName();
    }
    throw std::logic_error("unable to find string prototype name");
}