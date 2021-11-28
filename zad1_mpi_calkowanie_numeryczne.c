#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int n, p;
	double x;
	float a = 1.0, b = 4.0, result = 0.0;
	
	float h;
	h = (b-a)/n;
	
	int tag = 50;
		
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &p);
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Status status;
    
    if(p==n-1)
    { 
        printf("\n proces %d \n", p);
        printf("a = %lf \n", a);
        printf("b = %lf \n", b);
        printf("h = %lf \n\n\n", h);

        result+=(pow(a,2)/2);
        printf("wynik = %lf \n", result);
        
        result+=(pow(b,2)/2);
        printf("wynik = %lf \n", result);

        x = b;
        
        MPI_Send(&result, 1, MPI_DOUBLE, p-1, tag, MPI_COMM_WORLD);
        MPI_Send(&x, 1, MPI_DOUBLE, p-1, tag, MPI_COMM_WORLD);
    }
    else if((p>0)&&(p<n-1))
    { 
        MPI_Recv(&result, 1, MPI_DOUBLE, p+1, tag, MPI_COMM_WORLD, &status);
        MPI_Recv(&x, 1, MPI_DOUBLE, p+1, tag, MPI_COMM_WORLD, &status);

        x -= h;
        
        result+=(pow(x,2));
    
        printf("\n proces %d\n", p);
        printf("wynik = %lf \n", result);

        MPI_Send(&result, 1, MPI_DOUBLE, p-1, tag, MPI_COMM_WORLD);
        MPI_Send(&x, 1, MPI_DOUBLE, p-1, tag, MPI_COMM_WORLD);
    }  
    else if(p==0)
	{ 
        MPI_Recv(&result, 1, MPI_DOUBLE, p+1, tag, MPI_COMM_WORLD, &status);
        MPI_Recv(&x, 1, MPI_DOUBLE, p+1, tag, MPI_COMM_WORLD, &status);

        x -= h;
        
        result+=(pow(x,2));

        printf("\n proces %d\n", p);
        printf("wynik koncowy = %lf \n", result*h);       
    }   
    
    MPI_Finalize();
    return 0;
} 
