#include "functions.h"

/*struct Vector rot(struct Vector q){
    //x = cos(a0)*sin(d0)
    //y = sin(a0)*cos(d0)
    //z = sin(d0)
    long double d0 = asinl(q.z);
    long double a0 = asinl( (q.y/cosl(d0)) );

    a0 = a0 + M_PI_2;
    d0 = d0 + M_PI_2;

    q.x = cosl(a0)*sinl(d0);
    q.y = sinl(a0)*cosl(d0);
    q.z = sinl(d0);

    return q;
} */

struct Vector multiples(struct Vector q1, struct Vector q2){
        struct Vector q;
    q.x = ((q1.y*q2.z) - (q1.z*q2.y));
    q.y = ((q1.z*q2.x) - (q1.x*q2.z));
    q.z = ((q1.x*q2.y) - (q1.y*q2.x));

    return q;
}

long double norm(struct Vector q){
    long double norm;
    norm = sqrtl(powl(q.x, 2) + powl(q.y, 2) + powl(q.z, 2));
    assert(norm > 0);
    return norm;
}

struct Vector sum_vec(struct Vector q1, struct Vector q2){
    struct Vector q;
    q.x = q1.x + q2.x;
    q.y = q1.y + q2.y;
    q.z = q1.z + q2.z;
    return q;
}