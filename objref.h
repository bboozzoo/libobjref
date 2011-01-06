#ifndef __OBJREF_H__
#define __OBJREF_H__

#define __need_size_t
#include <stddef.h>
#include <stdint.h>

typedef void (*objref_destructor_f) (void *obj);

void * objref_alloc(size_t size, objref_destructor_f des);
void * objref(void *obj);
void * objunref(void *obj);
uint32_t objref_refcnt(void *obj);

#endif /* __OBJREF_H__ */
