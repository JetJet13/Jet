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
// Created by Johny Georges on 2025-06-16.
//

#include "ir-array-prototype-map.h"
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

IRArrayPrototypeFunctionId ArrayPrototypeMap::getIRArrayPrototypeFunction(std::string id) {
    if (id == "drop") {
        return AP_DROP_FUNCTION;
    } else if (id == "dropLast") {
        return AP_DROP_LAST_FUNCTION;
    } else if (id == "take") {
        return AP_TAKE_FUNCTION;
    } else if (id == "takeLast") {
        return AP_TAKE_LAST_FUNCTION;
    } else if (id == "head") {
        return AP_HEAD_FUNCTION;
    } else if (id == "tail") {
        return AP_TAIL_FUNCTION;
    } else if (id == "last") {
        return AP_LAST_FUNCTION;
    } else if (id == "append") {
        return AP_APPEND_FUNCTION;
    } else if (id == "prepend") {
        return AP_PREPEND_FUNCTION;
    } else if (id == "size") {
        return AP_SIZE_FUNCTION;
    } else if (id == "empty") {
        return AP_EMPTY_FUNCTION;
    }
    throw std::logic_error("unable to find array prototype function for id provided: " + id);
}

std::string ArrayPrototypeMap::getIRName(std::string id) {
    return ArrayPrototypeMap::getIRName(ArrayPrototypeMap::getIRArrayPrototypeFunction(id));
}

std::string ArrayPrototypeMap::getIRName(IRArrayPrototypeFunctionId irArrayPrototypeFunction) {
    switch (irArrayPrototypeFunction) {
        case AP_DROP_FUNCTION:
            return ArrayDropIRFunction::getArrayDropIRFunctionName();
        case AP_DROP_LAST_FUNCTION:
            return ArrayDropLastIRFunction::getArrayDropLastIRFunctionName();
        case AP_TAKE_FUNCTION:
            return ArrayTakeIRFunction::getArrayTakeIRFunctionName();
        case AP_TAKE_LAST_FUNCTION:
            return ArrayTakeLastIRFunction::getArrayTakeLastIRFunctionName();
        case AP_HEAD_FUNCTION:
            return ArrayHeadIRFunction::getArrayHeadIRFunctionName();
        case AP_TAIL_FUNCTION:
            return ArrayTailIRFunction::getArrayTailIRFunctionName();
        case AP_LAST_FUNCTION:
            return ArrayLastIRFunction::getArrayLastIRFunctionName();
        case AP_APPEND_FUNCTION:
            return ArrayAppendIRFunction::getArrayAppendIRFunctionName();
        case AP_PREPEND_FUNCTION:
            return ArrayPrependIRFunction::getArrayPrependIRFunctionName();
        case AP_SIZE_FUNCTION:
            return ArraySizeIRFunction::getArraySizeIRFunctionName();
        case AP_EMPTY_FUNCTION:
            return ArrayEmptyIRFunction::getArrayEmptyIRFunctionName();
    }
    throw std::logic_error("unable to find array prototype name");
}