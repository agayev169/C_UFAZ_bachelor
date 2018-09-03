#include <stdio.h>
#include "Stack.h"

int main() {
    Stack s = S_new();
    for (int i = 0; i < 5; i++) {
        s = S_push(s, i);
    }

    S_showFor(s, "Stack");

    s = S_pop(s);
    S_showFor(s, "Stack");

    return 0;
}
