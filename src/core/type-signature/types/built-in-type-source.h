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
// Created by Johny Georges on 2025-10-30.
//

#ifndef JETLANG_BUILT_IN_TYPE_SOURCE_H
#define JETLANG_BUILT_IN_TYPE_SOURCE_H
typedef enum {
    BI_PRINT_TYPE_SOURCE,
    BI_RANGE_TYPE_SOURCE,
    BI_RANGE_2P_TYPE_SOURCE,
    BI_RANGE_3P_TYPE_SOURCE,
    BI_ASSERT_TYPE_SOURCE,
    BI_ASSERT_WITH_MESSAGE_TYPE_SOURCE,
    BI_ASSERT_DEBUG_REF_COUNT_TYPE_SOURCE,
    BI_ASSERT_DEBUG_STRUCT_REF_COUNT_TYPE_SOURCE,
    BI_ASSERT_DEBUG_TUPLE_REF_COUNT_TYPE_SOURCE,
    BI_ASSERT_DEBUG_CLASS_REF_COUNT_TYPE_SOURCE,
    BI_ASSERT_DEBUG_LAMBDA_REF_COUNT_TYPE_SOURCE,
} BuiltInTypeSource;
#endif //JETLANG_BUILT_IN_TYPE_SOURCE_H
