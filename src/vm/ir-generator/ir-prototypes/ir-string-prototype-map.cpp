//
// Created by Johny Georges on 2026-03-21.
//

#include "ir-string-prototype-map.h"
#include "../ir-util-functions/array-prepend-ir-function/array-prepend-ir-function.h"
#include "../ir-util-functions/string-drop-ir-function/string-drop-ir-function.h"
#include "../ir-util-functions/string-drop-last-ir-function/string-drop-last-ir-function.h"
#include "../ir-util-functions/string-empty-ir-function/string-empty-ir-function.h"
#include "../ir-util-functions/string-size-ir-function/string-size-ir-function.h"
#include "../ir-util-functions/string-tail-ir-function/string-tail-ir-function.h"
#include "../ir-util-functions/string-take-ir-function/string-take-ir-function.h"
#include "../ir-util-functions/string-take-last-ir-function/string-take-last-ir-function.h"
#include "../ir-util-functions/string-at-ir-function/string-at-ir-function.h"
#include "../ir-util-functions/string-append-ir-function/string-append-ir-function.h"
#include "../ir-util-functions/string-prepend-ir-function/string-prepend-ir-function.h"

IRStringPrototypeFunctionId StringPrototypeMap::getIRStringPrototypeFunction(std::string id) {
    if (id == "drop") {
        return SP_DROP_FUNCTION;
    } else if (id == "dropLast") {
        return SP_DROP_LAST_FUNCTION;
    } else if (id == "take") {
        return SP_TAKE_FUNCTION;
    } else if (id == "takeLast") {
        return SP_TAKE_LAST_FUNCTION;
    } else if (id == "append") {
        return SP_APPEND_FUNCTION;
    } else if (id == "prepend") {
        return SP_PREPEND_FUNCTION;
    }
// will support head and last once we add null support
//    else if (id == "head") {
//        return SP_HEAD_FUNCTION;
//    } else if (id == "last") {
//        return SP_LAST_FUNCTION;
//    }
    else if (id == "tail") {
        return SP_TAIL_FUNCTION;
    }  else if (id == "size") {
        return SP_SIZE_FUNCTION;
    } else if (id == "empty") {
        return SP_EMPTY_FUNCTION;
    } else if (id == "at") {
        return SP_AT_FUNCTION;
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
        case SP_APPEND_FUNCTION:
            return StringAppendIRFunction::getStringAppendIRFunctionName();
        case SP_PREPEND_FUNCTION:
            return StringPrependIRFunction::getStringPrependIRFunctionName();
// will support head and last once we add null support
//        case SP_HEAD_FUNCTION:
//            return StringHeadIRFunction::getStringHeadIRFunctionName();
//        case SP_LAST_FUNCTION:
//            return StringLastIRFunction::getStringLastIRFunctionName();
        case SP_SIZE_FUNCTION:
            return StringSizeIRFunction::getStringSizeIRFunctionName();
        case SP_EMPTY_FUNCTION:
            return StringEmptyIRFunction::getStringEmptyIRFunctionName();
        case SP_AT_FUNCTION:
            return StringAtIRFunction::getStringAtIRFunctionName();
    }
    throw std::logic_error("unable to find string prototype name");
}