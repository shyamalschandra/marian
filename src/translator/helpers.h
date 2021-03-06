/* All or part of this file was contributed by Intel under license:
 *   Copyright (C) 2017-2018 Intel Corporation
 *   SPDX-License-Identifier: MIT
 */

#pragma once

#include "graph/expression_graph.h"

namespace marian {

namespace cpu {

void suppressWord(Expr probs, Word id);
}

namespace gpu {

void suppressWord(Expr probs, Word id);
}

void suppressWord(Expr probs, Word id);
}  // namespace marian
