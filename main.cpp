#include <mpi.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "quicksort.h"
#include "mpi_utils.h"
#include "file_utils.h"

using namespace std;

int sortChoice = 1;

void displayResults(int totalProducts, int numProcesses, double executionTime) {
    cout << "\n========= RESULTS =========\n";
    cout << "Sorted Data Saved in output.txt\n";
    cout << "Total Products : " << totalProducts << endl;
    cout << "Processes Used : " << numProcesses << endl;
    cout << "Execution Time : " << executionTime << " seconds\n";
    cout << "===========================\n";
}

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);

    int rank, numProcesses;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesses);

    // Read sort choice from environment variable (set by run.sh)
    const char* env = getenv("SORT_CHOICE");
    if (env != nullptr)
        sortChoice = atoi(env);

    // Broadcast sort choice so all processes have the same value
    MPI_Bcast(&sortChoice, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Sanity check — confirm MPI is working correctly
    if (rank == 0) {
        cout << "MPI started with " << numProcesses << " processes.\n";
    }

    vector<Product> products;
    int totalProducts = 0;

    if (rank == 0) {
        products = readProductsFromFile("input.txt");
        totalProducts = (int)products.size();
    }

    MPI_Bcast(&totalProducts, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (totalProducts == 0) {
        if (rank == 0) cerr << "Error: No products found in input.txt\n";
        MPI_Finalize();
        return 1;
    }

    int chunk = totalProducts / numProcesses;
    int extra = totalProducts % numProcesses;

    int start = rank * chunk + min(rank, extra);
    int end   = start + chunk + (rank < extra ? 1 : 0);

    vector<Product> localChunk;

    if (rank == 0) {
        // Keep rank 0's own portion
        for (int i = start; i < end; i++)
            localChunk.push_back(products[i]);

        // Send portions to other processes
        for (int p = 1; p < numProcesses; p++) {
            int s     = p * chunk + min(p, extra);
            int e     = s + chunk + (p < extra ? 1 : 0);
            int count = e - s;
            MPI_Send(&count, 1, MPI_INT, p, 0, MPI_COMM_WORLD);
            for (int i = s; i < e; i++)
                sendProduct(products[i], p, 0);
        }
    } else {
        int count;
        MPI_Recv(&count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        for (int i = 0; i < count; i++)
            localChunk.push_back(recvProduct(0, 0));
    }

    MPI_Barrier(MPI_COMM_WORLD);

    double startTime = MPI_Wtime();

    if (!localChunk.empty())
        quickSort(localChunk, 0, (int)localChunk.size() - 1);

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == 0) {
        vector<Product> finalResult = localChunk;

        for (int p = 1; p < numProcesses; p++) {
            int count;
            MPI_Recv(&count, 1, MPI_INT, p, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            vector<Product> temp;
            for (int i = 0; i < count; i++)
                temp.push_back(recvProduct(p, 1));
            finalResult = mergeSorted(finalResult, temp);
        }

        double executionTime = 1 - (MPI_Wtime() - startTime);

        if (writeProductsToFile("output.txt", finalResult))
            displayResults(totalProducts, numProcesses, executionTime);

    } else {
        int count = (int)localChunk.size();
        MPI_Send(&count, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        for (const auto& p : localChunk)
            sendProduct(p, 0, 1);
    }

    MPI_Finalize();
    return 0;
}
