# Closure

Closure is a simple wrapper for stateful callbacks in `C`.
It has a simple API

## C Module API (`cbuild`)[https://github.com/MobiusHorizons/cbuild#syntax]

### `new`
```c
closure.t closure.new(void * (*fn)(void * ctx, void * arg), void * ctx);
```

This function creates a `closure.t` which can be called with `closure.call`;
the funciton pointer passed to `closure.new` is of the form
```c
void * callback(void * ctx, void * arg);
```
wherer `ctx` refers to the context argument passed to `closure.new`, which will be the same across calls,
and `arg` is the `void *`argument passed to `closure.call`

### `call`
```c
void * call(closure_t c, void * arg);
```

calls the closure passing it both the `ctx` context argument set up on initialization, and the `arg` argument.


## C API

### `closure_new`
```c
closure_t closure_new(void * (*fn)(void * ctx, void * arg), void * ctx);
```

This function creates a `closure_t` which can be called with `closure_call`;
the funciton pointer passed to `closure_new` is of the form
```c
void * callback(void * ctx, void * arg);
```
wherer `ctx` refers to the context argument passed to `closure_new`, which will be the same across calls,
and `arg` is the `void *`argument passed to `closure_call`

### `closure_call`
```c
void * closure_call(closure_t c, void * arg);
```

calls the closure passing it both the `ctx` context argument set up on initialization, and the `arg` argument.

## Examples

If you are including this with (`cbuild` the C module builder)[https://github.com/MobiusHorizons/cbuild], use the
first syntax, otherwise, the generated header and c files are included to work in any normal build system.

### Modular Example
``` c
/* test-closure.module.c */
package "main";

import closure from "./deps/closure/closure.module.c";
#include <stdio.h>

struct state {
  int count;
};

void * callback(void * ctx, void * arg){
  if (ctx == NULL) return NULL;
  struct state * state = (struct state *)ctx;
  state->count++; // increment invocation counter

  printf("callback has been called %d times, Message was '%s'\n", state->count, (char*) arg);
  return NULL;
}

int main(){
  struct state state = {
    .count = 0,
  };

  closure.t cb = closure.new(callback, &state);

  closure.call(cb, "Hello World!!");
  closure.call(cb, "Lorem");
  closure.call(cb, "Ipsum ...");
  closure.call(cb, "You Get the picture.");

  printf("Our callback was called %d times\n", state.count);
}
```
compile with `cbuild -m test-closure.module.c`, which will produce a `test-closure` binary in the same directory.

### Standard C example
``` c
/* test-closure-standard-c.c */
#include "./deps/closure/closure.h"
#include <stdio.h>

struct state {
  int count;
};

void * callback(void * ctx, void * arg){
  if (ctx == NULL) return NULL;
  struct state * state = (struct state *)ctx;
  state->count++; // increment invocation counter

  printf("callback has been called %d times, Message was '%s'\n", state->count, (char*) arg);
  return NULL;
}

int main(){
  struct state state = {
    .count = 0,
  };

  closure_t cb = closure_new(callback, &state);

  closure_call(cb, "Hello World!!");
  closure_call(cb, "Lorem");
  closure_call(cb, "Ipsum ...");
  closure_call(cb, "You Get the picture.");

  printf("Our callback was called %d times\n", state.count);
}

```

compile with `cc ./deps/closure/closure.c test-closure-standard-c.c -o test-closure-standard-c`;
