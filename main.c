#include "Quat.h"

int main() {
    clock_t begin = clock();
    //--------------------------------------------------------------------------------------------------------//
    struct Vector vector_1; //p1
        vector_1.x = 0.241217325649302;
        vector_1.y = 0.169549737848405;
        vector_1.z = -0.955545440155588;

    struct Vector vector_12; //p2
        vector_12.x = 0.939149897210863;
        vector_12.y = 0.304787228229243;
        vector_12.z = 0.158436788900688;


    struct Vector vector_2; //r1
        vector_2.x = 0.710627225573053;
        vector_2.y = -0.683184589209175;
        vector_2.z = -0.168130197589355;


    struct Vector vector_22 ; //r2
        vector_22.x = 0.661938653269673;
        vector_22.y = 0.338283880427402;
        vector_22.z = 0.668880583924000;

    //--------------------------------------------------------------------------------------------------------//


    //Find the Yi between of our vectors
        long double Yi = acosl((vector_2.x * vector_1.x) + (vector_2.y * vector_1.y) + (vector_2.z * vector_1.z));


    //Some MAGIC!
    //--------------------------------------------------------------------------------------------------------//
    struct Vector q, q1_q2, vector1_vector2, vector12_vector22, summ_q;
     //vector1-vector2
        vector1_vector2.x = vector_1.x - vector_2.x;
        vector1_vector2.y = vector_1.y - vector_2.y;
        vector1_vector2.z = vector_1.z - vector_2.z;

     //vector12-vector22
        vector12_vector22.x = vector_12.x - vector_22.x;
        vector12_vector22.y = vector_12.y - vector_22.y;
        vector12_vector22.z = vector_12.z - vector_22.z;


    q1_q2 = multiples(vector1_vector2, vector12_vector22);
    q = multiples(vector_1, vector_2);

    // Find const A;
    long double temp = norm(q1_q2);
    assert(temp > 0);
    long double A = ((q.x / sinl(Yi)) * (q1_q2.x / temp)) + ((q.y / sinl(Yi)) * (q1_q2.y / temp)) +
                    ((q.z / sinl(Yi)) * (q1_q2.z / temp));
    // Find const B;
    summ_q = sum_vec(vector_1, vector_2);
    long double B = (((sinl(Yi / 2) / sinl(Yi)) * summ_q.x) * (q1_q2.x / temp)) +
                    (((sinl(Yi / 2) / sinl(Yi)) * summ_q.y) * (q1_q2.y / temp)) +
                    (((sinl(Yi / 2) / sinl(Yi)) * summ_q.z) * (q1_q2.z / temp));
    //--------------------------------------------------------------------------------------------------------//

    //Now we will find angle Bi!
    long double temp_sqrt = sqrtl((A * A) + (B * B));
    assert(temp_sqrt > 0);
    long double Bi;
    Bi = (M_PI / 2) - asinl(A / temp_sqrt);


    // And now we will find Yqi angle;
    long double Yqi = 2 * atanl((1 / cosl(Bi)) * (tanl(Yi / 2)));

    //Finally, it's quaternion!
    Quaternion quaternion;

    //------------------------------------------------//
    q.x = q.x * cosl(Bi);
    q.y = q.y * cosl(Bi);
    q.z = q.z * cosl(Bi);
    summ_q.x = summ_q.x * sinl(Yi / 2) * sinl(Bi);
    summ_q.y = summ_q.y * sinl(Yi / 2) * sinl(Bi);
    summ_q.z = summ_q.z * sinl(Yi / 2) * sinl(Bi);
    struct Vector final_vector = sum_vec(q, summ_q);
    //------------------------------------------------//
    quaternion.q0 = cosl(Yqi / 2);
    quaternion.q1 = (sinl(Yqi / 2) / sinl(Yi)) * final_vector.x;
    quaternion.q2 = (sinl(Yqi / 2) / sinl(Yi)) * final_vector.y;
    quaternion.q3 = (sinl(Yqi / 2) / sinl(Yi)) * final_vector.z;

    printf(" q0:%.20Lf\n q1:%.20Lf\n q2:%.20Lf\n q3:%.20Lf ", quaternion.q0, quaternion.q1, quaternion.q2, quaternion.q3);

    // Next step is rotation matrix!
    long double **rotation_matrix = NULL;
    rotation_matrix = (long double**) malloc(SIZE_MATRIX * sizeof(long double *));
        for(int i = 0; i < SIZE_MATRIX; i++){
            rotation_matrix[i] = (long double*)malloc(SIZE_MATRIX * sizeof(long double));
        }

    rotation_matrix[0][0] = (quaternion.q0*quaternion.q0 + quaternion.q1*quaternion.q1 - quaternion.q2*quaternion.q2 - quaternion.q3*quaternion.q3);
    rotation_matrix[0][1] = 2 * (quaternion.q1 * quaternion.q2 - quaternion.q0 * quaternion.q3);
    rotation_matrix[0][2] = 2 * (quaternion.q0 * quaternion.q1 + quaternion.q1 * quaternion.q3);
    rotation_matrix[1][0] = 2 * (quaternion.q0 * quaternion.q3 + quaternion.q1 * quaternion.q2);
    rotation_matrix[1][1] = (powl(quaternion.q0, 2) - powl(quaternion.q1, 2) + powl(quaternion.q2, 2) - powl(quaternion.q3, 2));
    rotation_matrix[1][2] = 2 * (quaternion.q2 * quaternion.q3 - quaternion.q0 * quaternion.q1);
    rotation_matrix[2][0] = 2 * (quaternion.q1 * quaternion.q3 - quaternion.q0 * quaternion.q2);
    rotation_matrix[2][1] = 2 * (quaternion.q0 * quaternion.q1 + quaternion.q2 * quaternion.q3);
    rotation_matrix[2][2] = (powl(quaternion.q0, 2) - powl(quaternion.q1, 2) - powl(quaternion.q2, 2) + powl(quaternion.q3, 2));
    //------------------------------------------------//
    
    //Find our angles!
    long double Thee = asinl(rotation_matrix[0][1]);
    long double Psi = acosl(rotation_matrix[0][0]/cosl(Thee));
    long double Gamma = acosl(rotation_matrix[1][1]/cosl(Thee));
    printf("\nThee:%Lf Psi:%Lf Gamma:%Lf", ((Thee * 180)/M_PI), ((Psi * 180)/M_PI), ((Gamma * 180)/M_PI));

    
    clock_t end = clock(); //Time of work our programm (0.003 - 0.008)s
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\ntime:< %lf >", time_spent);
    return 0;
}
