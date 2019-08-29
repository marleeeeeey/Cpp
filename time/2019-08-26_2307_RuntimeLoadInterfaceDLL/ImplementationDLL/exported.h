#pragma once

#include "../Item_ITF/include/item_interface.h"

#ifdef __cplusplus    // If used by C++ code, 
extern "C" {          // we need to export the C interface
#endif
    
__declspec (dllexport) int __cdecl createModule(ItemInterface**);


#ifdef __cplusplus
}
#endif