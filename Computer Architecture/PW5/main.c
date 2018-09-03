#include <stdio.h>
#include "direct_cache.h"

int main(int argc, char const *argv[]) {
    struct direct_cache *c = direct_cache_create(4);
    direct_cache_print(c);
    direct_cache_delete(c);

    return 0;
}
