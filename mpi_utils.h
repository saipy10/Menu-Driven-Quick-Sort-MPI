#ifndef MPI_UTILS_H
#define MPI_UTILS_H

#include <mpi.h>
#include <string>
#include "quicksort.h"

using namespace std;

// ----------------------------------
// Send Product via MPI
// ----------------------------------
inline void sendProduct(const Product& p, int dest, int tag) {
    int len = p.name.size();
    MPI_Send(&len, 1, MPI_INT, dest, tag, MPI_COMM_WORLD);
    MPI_Send(p.name.c_str(), len, MPI_CHAR, dest, tag, MPI_COMM_WORLD);
    MPI_Send(&p.price, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
    MPI_Send(&p.rating, 1, MPI_DOUBLE, dest, tag, MPI_COMM_WORLD);
}

// ----------------------------------
// Receive Product via MPI
// ----------------------------------
inline Product recvProduct(int source, int tag) {
    Product p;
    int len;
    char buffer[1024];
    
    MPI_Recv(&len, 1, MPI_INT, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    
    if (len > 1023) {
        len = 1023;
    }
    
    MPI_Recv(buffer, len, MPI_CHAR, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    buffer[len] = '\0';
    p.name = buffer;
    
    MPI_Recv(&p.price, 1, MPI_DOUBLE, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&p.rating, 1, MPI_DOUBLE, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    
    return p;
}

#endif // MPI_UTILS_H
