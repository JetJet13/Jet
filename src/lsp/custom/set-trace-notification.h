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
// Created by Johny Georges on 2026-10-31.
//

#ifndef JETLANG_SET_TRACE_NOTIFICATION_H
#define JETLANG_SET_TRACE_NOTIFICATION_H

#include "LibLsp/LspCpp.h"
#include "LibLsp/JsonRpc/NotificationInMessage.h"
#include <string>

struct SetTraceParams
{
    std::string value;
    MAKE_SWAP_METHOD(SetTraceParams, value);
};
MAKE_REFLECT_STRUCT(SetTraceParams, value);

DEFINE_NOTIFICATION_TYPE(Notify_SetTrace, SetTraceParams, "$/setTrace");

#endif //JETLANG_SET_TRACE_NOTIFICATION_H
