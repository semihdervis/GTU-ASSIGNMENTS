#include "stdio.h"
#include "math.h"
#define PI 3.14

void main(){
    double cube_radius, cube_area, cube_volume;  // code for cube
    printf("\nEnter the edge length for cube: ");
    scanf("%lf", &cube_radius);
    cube_area = 6 * cube_radius * cube_radius;
    cube_volume = cube_radius * cube_radius * cube_radius;
    printf("Surface Area = %lf, ", cube_area);
    printf("Volume = %lf\n\n", cube_volume);

    double rect_a, rect_b, rect_c, rect_area, rect_volume; // code for rectangular prism
    printf("Enter side length for rectangular prism: ");
    scanf("%lf", &rect_a);
    printf("Enter side width: ");
    scanf("%lf", &rect_b);
    printf("Enter side height: ");
    scanf("%lf", &rect_c);
    rect_area = 2 * ((rect_a * rect_b) + (rect_b * rect_c) + (rect_a * rect_c));
    rect_volume = rect_a * rect_b * rect_c;
    printf("Surface Area = %lf, ", rect_area);
    printf("Volume = %lf\n\n", rect_volume);

    double sphere_radius, sphere_area, sphere_volume; // code for sphere
    printf("Enter the radius for sphere: ");
    scanf("%lf", &sphere_radius);
    sphere_area = 4 * PI * sphere_radius * sphere_radius;
    sphere_volume = (4/3.0) * PI * sphere_radius * sphere_radius * sphere_radius;
    printf("Surface Area = %lf, ", sphere_area);
    printf("Volume = %lf\n\n", sphere_volume);  

    double r, h, cone_area, cone_volume; // code for cone
    printf("Enter the radius for cone: ");
    scanf("%lf", &r);
    printf("Enter the height: ");
    scanf("%lf", &h);
    double a = sqrt((h * h) + (r * r));
    cone_area = (PI * r * a) + (PI * r * r);
    cone_volume = (PI * r * r * h) / 3;
    printf("Surface Area = %lf, ", cone_area);
    printf("Volume = %lf\n\n", cone_volume);
}