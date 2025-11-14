//
//  variable.cpp
//  dpslang
//
//  Created by Sora Sugiyama on 11/1/25.
//

#include "variable.hpp"
#include <cstddef>

VarManager<float_t>varfloat;
VarManager<char16_t>varUTF16;
VarManager<char32_t>varUTF32;
VarManager<int32_t>varInt32;
VarManager<int64_t>varInt64;
VarManager<uint32_t>varUInt32;
VarManager<uint64_t>varUInt64;
VarManager<double_t>varDouble;
