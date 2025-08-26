#include <stdio.h>
#include <math.h>
 
int main() {
    long k;
    double min = 0;
    scanf("%ld", &k);
    double max = sqrt(k - 100);
    double middle;
    double x = 100;
    while (x - k > 0.00000001 || x - k < -0.00000001)
    {
        middle = (min + max) / 2;
        x = middle * middle + sqrt(middle) + 100;
        if (x < k)
        {
            min = middle;
        }
        else if (x > k)
        {
            max = middle;
        }
 
        else
        {
            min = middle;
            break;
        }
    }
    printf("%0.10f", min);
    return 0;
}