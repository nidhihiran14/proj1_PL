#include "expr.h"
#include "stdlib.h"
#include "stdio.h"


struct Expr *mk_plus(struct Expr *e1, struct Expr *e2) {
    struct Expr *ret = malloc(sizeof(struct Expr));
    ret->type = PLUS;
    ret->subexprs.e1 = e1;
    ret->subexprs.e2 = e2;

    return ret;
}

struct Expr *mk_minus(struct Expr *e1, struct Expr *e2) {
    struct Expr *ret = malloc(sizeof(struct Expr));
    ret->type = MINUS;
    ret->subexprs.e1 = e1;
    ret->subexprs.e2 = e2;

    return ret;
}

struct Expr *mk_times(struct Expr *e1, struct Expr *e2) {
    struct Expr *ret =  malloc(sizeof(struct Expr));
    ret->type = TIMES;
    ret->subexprs.e1 = e1;
    ret->subexprs.e2 = e2;

    return ret;
}

struct Expr *mk_div(struct Expr *e1, struct Expr *e2) {
    struct Expr *ret = malloc(sizeof(struct Expr));
    ret->type = DIV;
    ret->subexprs.e1 = e1;
    ret->subexprs.e2 = e2;

    return ret;
}

struct Expr *mk_float(float f) {
    struct Expr *ret = malloc(sizeof(struct Expr));
    ret->type = FLOAT;
    ret->literal = f;

    return ret;
}

/* This function should create the expr (1 + (4 * 5))
 * using the above constructors.
 */
struct Expr *mk_expr1() {
    struct Expr *e1 = mk_float(4.0);
    struct Expr *e2 = mk_float(5.0);
    struct Expr *times_expr = mk_times(e1, e2);  // (4 * 5)
    struct Expr *one = mk_float(1.0);
    return mk_plus(one, times_expr);  // 1 + (4 * 5)

}

/* This function should create the expr (1 + (7 / 8))
 * using the above constructors.
 */
struct Expr *mk_expr2() {
    struct Expr *e1 = mk_float(7.0);
    struct Expr *e2 = mk_float(8.0);
    struct Expr *div_expr = mk_div(e1, e2);  // (7 / 8)
    struct Expr *one = mk_float(1.0);
    return mk_plus(one, div_expr);  // 1 + (7 / 8)
}

/* This function should create the expr ((1 / 3) - (4 / (2 + 3)))
 * using the above constructors.
 */
struct Expr *mk_expr3() {
    struct Expr *e1 = mk_float(1.0);
    struct Expr *e2 = mk_float(3.0);
    struct Expr *div1 = mk_div(e1, e2);  // 1 / 3

    struct Expr *e3 = mk_float(2.0);
    struct Expr *e4 = mk_float(3.0);
    struct Expr *plus_expr = mk_plus(e3, e4);  // 2 + 3

    struct Expr *e5 = mk_float(4.0);
    struct Expr *div2 = mk_div(e5, plus_expr);  // 4 / (2 + 3)

    return mk_minus(div1, div2);  // (1 / 3) - (4 / (2 + 3))
}


/*
 * This function should free all memory associated 
 * with the given AST.
*/
void free_expr(struct Expr* e) {
    if (!e) return;

    // Recursively free subexpressions for PLUS, MINUS, TIMES, DIV
    if (e->type == PLUS || e->type == MINUS || e->type == TIMES || e->type == DIV) {
        free_expr(e->subexprs.e1);
        free_expr(e->subexprs.e2);
    }
    
    // Free the expression itself
    free(e);
}

/*
 * This function should evaluate the given AST and
 * return the floating-point result.
*/
float eval(struct Expr* e) {
    if (!e) return 0.0;

    switch (e->type) {
        case FLOAT:
            return e->literal;
        case PLUS:
            return eval(e->subexprs.e1) + eval(e->subexprs.e2);
        case MINUS:
            return eval(e->subexprs.e1) - eval(e->subexprs.e2);
        case TIMES:
            return eval(e->subexprs.e1) * eval(e->subexprs.e2);
        case DIV:
            return eval(e->subexprs.e1) / eval(e->subexprs.e2);
        default:
            return 0.0;  // Should never happen if the AST is valid
    }
}




