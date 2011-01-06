#include <stdio.h>
#include <objref.h>

struct y_s
{
    int y;
};

struct x_s
{
    int x;
    struct y_s *y_obj; /* refcounted */
};

void __y_s_destructor(void *obj)
{
    printf("y_s destructor\n");
}

void __x_s_destructor(void *obj)
{
    struct x_s *__x = (struct x_s *) obj;

    printf("x_s destructor\n");

    objunref(__x->y_obj);
}

int main(void)
{
    struct x_s *__x = NULL;
    struct y_s *__y = NULL;

    /* ref == 1 after alloc */
    __x = objref_alloc(sizeof(struct x_s), __x_s_destructor);
    printf("allocated x_s, refcnt: %u\n", objref_refcnt(__x));

    /* ref == 1 after alloc */
    __x->y_obj = objref_alloc(sizeof(struct y_s), __y_s_destructor);
    printf("allocated y_s, refcnt: %u\n", objref_refcnt(__x->y_obj));

    /* ref + 1 */
    __y = objref(__x->y_obj);
    printf("ref y_obj, __y refcnt: %u y_obj refcnt: %u\n", 
           objref_refcnt(__y), objref_refcnt(__x->y_obj));
    
    /* ref - 1 */
    __y = objunref(__y);
    printf("unref y_obj, __y refcnt: %u y_obj refcnt: %u\n", 
           objref_refcnt(__y), objref_refcnt(__x->y_obj));

    /* ref should be 0 */
    __x = objunref(__x);
    printf("unref x\n");
    if (__x == NULL)
        printf("x released\n");
    else
        printf("x refcnt: %u\n", objref_refcnt(__x));

    return 0;
}
