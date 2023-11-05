#ifndef PIXELWORK_FUNCTIONS_H
#define PIXELWORK_FUNCTIONS_H

#include "../Quat.h"

struct Vector rot(struct Vector q);
struct Vector multiples(struct Vector q1, struct Vector q2);
long double norm(struct Vector q);
struct Vector sum_vec(struct Vector q1, struct Vector q2);

#endif //PIXELWORK_FUNCTIONS_H
