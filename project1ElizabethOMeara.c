#include <stdio.h>

/* Defining the differential equation to be used in the analysis below */

#define f(x, y) (x * x + y * y) / (x * x - y * y)

int main()
{
    /* Forwad Euler Method for Solving the Differential equation dy/dx = f(x,y) (as defined) */
    /* Assigning Variables to be Used in the Forward Euler Method Approximation */
    float x_initial_euler, y_initial_euler, step_size_euler, y_new_euler, x_new_euler;
    int i_euler, number_of_steps_euler;

    /* Providing Variables with Integer Values */
    /* Initial value of x and y */
    x_initial_euler = 0;
    y_initial_euler = 1;
    /* Value of x where we want to estimate y using the Euler Method */
    x_new_euler = 0.4;
    /* Number of steps needed to reach x_new_euler = 0.4  */
    number_of_steps_euler = 10;

    /* Calculating Step Size for the Euler Method */
    step_size_euler = (x_new_euler - x_initial_euler) / number_of_steps_euler;

    /* Using the Forward Euler Method to estimate y at x_new_euler = 0.4 */
    printf("\nx_initial_euler\ty_initial_euler\ty_new_euler\n");
    for (i_euler = 0; i_euler < number_of_steps_euler + 1; (i_euler)++)
    {
        y_new_euler = y_initial_euler + step_size_euler * f(x_initial_euler, y_initial_euler);
        printf("%0.4f\t%0.4f\t%0.4f\n", x_initial_euler, y_initial_euler, y_new_euler);
        x_initial_euler = x_initial_euler + step_size_euler;
        y_initial_euler = y_new_euler;
    }

    /* Displaying the Result of the Forward Euler Method*/
    printf("\nValue of y at x = %0.4f is %0.3f using the Forward Euler Method", x_new_euler, y_new_euler);

    /* RK2 Method for Solving the Differential equation dy/dx = f(x,y) (as defined) */
    /* Assigning Variables to be Used in the RK2 Method Approximation */
    float x_initial_RK2, y_initial_RK2, k1, k2, step_size_RK2, y_new_RK2, x_new_RK2;
    int i_RK2, number_of_steps_RK2;

    /* Providing Variables with Integer Values */
    /* Initial value of x and y */
    x_initial_RK2 = 0;
    y_initial_RK2 = 1;
    /* Value of x where we want to estimate y using the RK2 */
    x_new_RK2 = 0.4;
    /* Number of steps needed to reach x_new_euler = 0.4  */
    number_of_steps_RK2 = 10;

    /* Calculating the step size for the RK2 Method */
    step_size_RK2 = (x_new_RK2 - x_initial_RK2) / number_of_steps_RK2;

    /* Using the RK2 Method to estimate y at x_new_euler = 0.4 */
    printf("\nx_initial_RK2\ty_initial_RK2\ty_new_RK2\n");
    for (i_RK2 = 0; i_RK2 < number_of_steps_RK2 + 1; (i_RK2)++)
    {
        /* k1 and k2 are used for simplicity of the y_new_RK2 equation */
        k1 = step_size_RK2 * f(x_initial_RK2, y_initial_RK2);
        k2 = step_size_RK2 * f(x_initial_RK2 + step_size_RK2, y_initial_RK2 + k1);
        y_new_RK2 = y_initial_RK2 + (k1 + k2) / 2;
        printf("%0.4f\t%0.4f\t%0.4f\n", x_initial_RK2, y_initial_RK2, y_new_RK2);
        x_initial_RK2 = x_initial_RK2 + step_size_RK2;
        y_initial_RK2 = y_new_RK2;
    }

    /* Displaying result */
    printf("\nValue of y at x = %0.4f is %0.4f using the RK2 method", x_new_RK2, y_new_RK2);
}
