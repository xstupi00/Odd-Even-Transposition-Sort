//inspirovane z http://www.fit.vutbr.cz/~ikalmar/PRL/odd-even-trans/odd-even.cpp

#include <mpi.h>
#include <iostream>
#include <fstream>

using namespace std;

#define TAG 0

#define MEASURE_TIME

int main(int argc, char *argv[]) {
    int numprocs;               //pocet procesoru
    int myid;                   //muj rank
    int neighnumber;            //hodnota souseda
    int mynumber;               //moje hodnota
    MPI_Status stat;            //struct- obsahuje kod- source, tag, error

#ifdef MEASURE_TIME
    double start = 0.0;
#endif

    //MPI INIT
    MPI_Init(&argc, &argv);                         // inicializace MPI
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);       // zjistĂ­me, kolik procesĹŻ bÄ›ĹľĂ­
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);           // zjistĂ­me id svĂ©ho procesu

    unsigned int array[numprocs];                   //pole pro cisla

    if (myid == 0) {
        int number;
        int arr_idx = 0;
        fstream fin;
        fin.open("numbers", ios::in);

        fin.seekg(0, ios::end);
        int fileSize = fin.tellg();
        fin.seekg(0, ios::beg);

        while (fin.good()) {
            number = fin.get();
            if (!fin.good()) break;
            array[arr_idx++] = number;
        }
        fin.close();

        for (int i = 0; i < fileSize; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
    }

    MPI_Scatter(&array, 1, MPI_INT, &mynumber, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //LIMIT PRO INDEXY
    int oddlimit = (numprocs % 2 ? numprocs - 2 : numprocs - 1);           //posledni parne
    int evenlimit = (numprocs % 2 ? numprocs - 1 : numprocs - 2);          //posledni neparne

    if (myid == 0) {
        start = MPI_Wtime();
    }

    for(int j=1; j<=numprocs; j++){
        if (j%2 == 1){
            if((myid%2 == 1) && (myid<evenlimit)){
                MPI_Send(&mynumber, 1, MPI_INT, myid+1, TAG, MPI_COMM_WORLD);           //poslu sousedovi svoje cislo
                MPI_Recv(&neighnumber, 1, MPI_INT, myid+1, TAG, MPI_COMM_WORLD, &stat); //prijimam jeho
                mynumber = min(neighnumber, mynumber);                                  //nechavam si mensi
            }//if liche
            else if(myid<=evenlimit && myid!=0){
                MPI_Send(&mynumber, 1, MPI_INT, myid-1, TAG, MPI_COMM_WORLD);           //poslu sousedovi svoje cislo
                MPI_Recv(&neighnumber, 1, MPI_INT, myid-1, TAG, MPI_COMM_WORLD, &stat); //prijimam jeho
                mynumber = max(neighnumber, mynumber);                                  //nechavam si vaecsi
            }
        }else{
            if((myid%2 == 0) && (myid<oddlimit)){
                MPI_Send(&mynumber, 1, MPI_INT, myid+1, TAG, MPI_COMM_WORLD);          //poslu sousedovi svoje cislo
                MPI_Recv(&neighnumber, 1, MPI_INT, myid+1, TAG, MPI_COMM_WORLD, &stat); //prijimam jeho
                mynumber = min(neighnumber, mynumber);                                  //nechavam si mensi
            }//if sude
            else if(myid<=oddlimit){
                MPI_Send(&mynumber, 1, MPI_INT, myid-1, TAG, MPI_COMM_WORLD);           //poslu sousedovi svoje cislo
                MPI_Recv(&neighnumber, 1, MPI_INT, myid-1, TAG, MPI_COMM_WORLD, &stat); //prijimam jeho
                mynumber = max(neighnumber, mynumber);                                  //nechavam si vetsi
            }
        }
    }

if (myid == 0) {
double end = MPI_Wtime();
printf("%lu\n", (size_t)((end - start)* 1000000000));
}


    unsigned int* final= new unsigned int [numprocs];
    MPI_Gather(&mynumber, 1, MPI_INT, final, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(myid == 0){
        for(int i=0; i<numprocs; i++){
            printf("%d\n", final[i]);
        }
    }

    MPI_Finalize();
    return 0;
}//main
