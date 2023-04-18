//
//  Distributions.cpp
//  MarkovChain - Galton-Watson
//
//  Created by Broos  Maenhout on 22/09/2017.
//  Copyright © 2017 Broos  Maenhout. All rights reserved.
//

#include "general.h"

double personnel::Exponential_distribution(double lambda)
{
    j1 = float (rand()%1000)/1000;              // Random number
    if (j1 == 0)                                        // Random number should lie in interval ]0,1[
        j1 += 0.0001;
    j2 = -log(j1)/lambda;                               // Inversion method

    return j2;

}


int personnel::Poisson_distribution(double lambda)
{   double k, L;
    int p;
    j1 = float (rand()%1000)/1000;                  // Random number
    k = 0;
    L = exp(-lambda);
    j3 = 0;
    do                                                      // Inversion method
    {
        j2 = L * pow(lambda, k);
        p = 1;
        for (i6 = 0; i6 <= k; i6++)
        {   if (i6 == 0)
                p = 1;
            else
                p *= i6;

        }
        j2 /= p;
        j3 += j2;
        k++;
    } while (j1 >= j3);

    return k-1;

}

int personnel::Normal_distribution(double mean, double stdev)
{   // TO MODEL BASED ON CUMULATIVE DENSITY FUNCTION OF NORMAL DISTRIBUTION BASED ON BOOK OF SHELDON ROSS, Simulation, The polar method, p80.

    double v1, v2, t;
    int x;
    do
    {
        v1 = float (rand()%1000)*2;
        v1 /= 1000;
        v1 -= 1;
        v2 = float (rand()%1000)*2;
        v2 /= 1000;
        v2 -= 1;
        t=v1*v1+v2*v2;
    }
    while(t>=1||t==0);
    double multiplier = sqrt(-2*log(t)/t);
    x = v1 * multiplier * stdev + mean;
    return x;


}

int personnel::Bernouilli_distribution(double prob)
{   j1 = float (rand()%1000)/1000;          // random number
    if (j1 < prob)                                  // Inversion method
        return 0;
    else
        return 1;


}

int personnel::Uniform_distribution(double a, double b)
{   int x;
    j1 = float (rand()%1000)/1000;              // random number
    x = a + (b-a) * j1;                                   // Inversion method

    return x;
}


int personnel::Triangular_distribution(int a, int b, int c)
{   double mean, stdev;
    double x, L;

    mean = (a+b+c)/3;
    stdev = (pow(a,2)+pow(b,2)+pow(c,2)-a*b-a*c-b*c)/18;
    stdev = sqrt(stdev);
    j1 = float (rand()%1000)/1000;
    x = a;

    do
    {   if (x <= b)
            L = pow((x-a),2)/((c-a)*(b-a));
        else
            L = 1-(pow(c-x,2)/((c-a)*(c-b)));
        x++;
    } while (j1 >= L);

    return x-1;

}





