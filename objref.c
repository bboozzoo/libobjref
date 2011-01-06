#include <stdint.h>
#include <objref.h>

struct objref_meta_s
{
    uint32_t refcnt;
    size_t size;
    objref_destructor_f destructor;
};

static inline struct objref_meta_s *
__objref_get_meta(void *p)
{
    return (struct objref_meta_s *)((uintptr_t) p - sizeof(struct objref_meta_s));
}

static inline void *
__objref_get_obj(struct objref_meta_s *meta)
{
    return (void *)((uintptr_t) meta + sizeof(struct objref_meta_s));
}

static inline void
__objref_free(void *p)
{
    free(p);
}

static inline void *
__objref_alloc(size_t size)
{
    return malloc(size);
}

void * 
objref_alloc(size_t size, objref_destructor_f des)
{
    struct objref_meta_s *meta = NULL;
    void *obj = NULL;

    meta = __objref_alloc(size + sizeof(struct objref_meta_s));
    if (meta)
    {
        meta->refcnt = 1;
        meta->size = size;
        meta->desctructor = des;
        obj = __objref_get_obj(meta);
    }

    return obj;
}

void * 
objref(void *obj)
{
    struct objref_meta_s *meta;

    meta = __objref_get_meta(obj);

    meta->refcnt++;

    return obj;
}

void * 
objunref(void *obj)
{
    struct objref_meta_s *meta;

    meta = __objref_get_meta(obj);

    if (meta->refcnt > 0)
    {
        /* decrease refcnt */
        meta->refcnt--;
        if (meta->refcnt == 0)
        {
            if (meta->desctructor)
                meta->destructor(obj);

            __objref_free(meta);
            obj = NULL;
        }
    }
    else
        obj = NULL;

    return obj;
}

uint32_t 
objref_refcnt(void *obj)
{
    struct objref_meta_s *meta;

    meta = __objref_get_meta(obj);

    return meta->refcnt;
}



