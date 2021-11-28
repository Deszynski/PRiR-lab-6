#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int n, p;
	float pi = 0.0; 
	float temp = 0.0;
	
    int tag = 50;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &p);
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Status status;
   
    if((p>0)&&(p<n))
    {
        MPI_Recv(&pi, 1, MPI_INT, p-1, tag, MPI_COMM_WORLD, &status);
        temp = (pow(-1.0, p))/(2*p+1);
        pi += temp;
        printf("n = %d pi = %f \n", p, pi*4);
        
        if(p!=n-1)
        { 
            MPI_Send(&pi, 1, MPI_INT ,p+1 ,tag, MPI_COMM_WORLD);
        }   
    }      
    else if(p==0)
    {
        temp = (pow(-1.0, p))/(2*p+1);
        pi += temp;
        printf("n = %d pi = %f \n", p, pi*4);
        MPI_Send(&pi, 1, MPI_INT ,p+1 ,tag, MPI_COMM_WORLD);
        MPI_Send(&pi, 1, MPI_INT ,p+1 ,tag, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
