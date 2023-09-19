#include <stdio.h>
#include <math.h>
#define PI 3.14

typedef struct {
    double x;
    double y;
    double z;
} vector;

double find_orthogonal(vector vec_1, vector vec_2, vector* output_vec) {
    double angle_rad;
    vector orthogonal_vec;

    // Calculate angle between vec_1 and vec_2
    double dot_product = vec_1.x * vec_2.x + vec_1.y * vec_2.y + vec_1.z * vec_2.z;
    double magnitude_1 = sqrt(vec_1.x * vec_1.x + vec_1.y * vec_1.y + vec_1.z * vec_1.z);
    double magnitude_2 = sqrt(vec_2.x * vec_2.x + vec_2.y * vec_2.y + vec_2.z * vec_2.z);
    angle_rad = acos(dot_product / (magnitude_1 * magnitude_2));
    double angle_deg = angle_rad * 180.0 / PI;

    // Calculate cross product to find orthogonal vector
    orthogonal_vec.x = vec_1.y * vec_2.z - vec_1.z * vec_2.y;
    orthogonal_vec.y = vec_1.z * vec_2.x - vec_1.x * vec_2.z;
    orthogonal_vec.z = vec_1.x * vec_2.y - vec_1.y * vec_2.x;

    // Set output argument
    *output_vec = orthogonal_vec;

    // Return angle in degrees
    return angle_deg;
}

int main() {
    vector vec1 = {1.0, 2.0, 3.0};
    vector vec2 = {4.0, 5.0, 6.0};
    vector orthogonal_vec;
    double angle_deg = find_orthogonal(vec1, vec2, &orthogonal_vec);
    printf("Angle between vectors: %f degrees\n", angle_deg);
    printf("Orthogonal vector: (%f, %f, %f)\n", orthogonal_vec.x, orthogonal_vec.y, orthogonal_vec.z);
    return 0;
}