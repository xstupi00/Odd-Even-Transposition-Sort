/**************************************************************
 * File:		ots.h
 * Author:		Šimon Stupinský
 * University: 	Brno University of Technology
 * Faculty: 	Faculty of Information Technology
 * Course:	    Parallel and Distributed Algorithms
 * Date:		13.03.2020
 * Last change:	14.04.2020
 *
 * Subscribe:	The header module of the Odd-Even Transposition sort algorithm.
 *
**************************************************************/

/**
 * @file    ots.h
 * @brief   The header module of the Odd-Even Transposition sort algorithm.
 */

#include <cmath>
#include <mpi.h>

// The rank of the master processor
#define MASTER 0
// Number of elements send in the MPI_Send and MPI_Recv
#define COUNT 1
// Message tag in the MPI_Send and MPI_Recv
#define TAG 0
// Flag for measuring the elapsed time in the sorting algorithm
#define MEASURE_TIME

using namespace std;

/**
 * Loads the numbers from the given input stream and store
 * it to the given array and also store their count.
 *
 * @param numbers   The reference to the array to the store input sequence of numbers.
 * @param n         The reference to the variable to store the count of numbers in the input sequence.
 */
void read_input_stream(unsigned char** numbers, size_t* n);

/**
 * Loads the numbers and their count from the input stream and subsequently distributes
 * numbers to the individual processors and print it out at the same.
 */
void distribute_numbers_to_processors();

/**
 * Sends the given number of the processor to its right neighbour and subsequently
 * will wait to receive the number from this neighbour processor.
 *
 * @param number    The reference to the relevant number of the individual processor.
 * @param rank      The rank of the current individual processor.
 * @param mpi_stat  The reference to the structure that represents the status of the received message
 */
void send_and_wait(unsigned char* number, int rank, MPI_Status* mpi_stat);

/**
 * Receives number from processors right neighbour, compare received number with own
 * number and subsequently send back to the right neighbour larger of them.
 *
 * @param number    The reference to the relevant number of the individual processor.
 * @param rank      The rank of the current individual processor.
 * @param mpi_stat  The reference to the structure that represents the status of the received message.
 */
void recv_compare_and_send(unsigned char* number, int rank, MPI_Status* mpi_stat);

/**
 * The each processor contains the relevant number. In the first step, all odd processors compare its
 * values with the right neighbours and when the value of the current processor is larger, then they
 * switch numbers between each other. In the next step all even processors perform the same jobs. At
 * the most after n steps are the numbers ordered in the individual processors.
 *
 * @param number    The reference to the relevant number of the individual processor.
 * @param rank      The rank of the current individual processor.
 * @param mpi_stat  The reference to the structure that represents the status of the received message.
 * @param size      The count of the numbers in the stored number sequence.
 */
void odd_even_transposition_sort(unsigned char* number, int rank, MPI_Status* mpi_stat, int size);

/**
 * The each processor, with except master, send the own number to the master
 * processor. The master processor gradually receives all sent numbers from
 * other processors and store them to the ordered array.
 *
 * @param ordered_numbers   The reference to the array to store the final ordered number sequence.
 * @param size              The count of the numbers in the stored number sequence.
 * @param rank              The rank of the current individual processor.
 * @param number            The reference to the relevant number of the individual processor.
 * @param mpi_stat          The reference to the structure that represents the status of the received message.
 */
void distribute_ordered_sequence_to_master(
        unsigned char** ordered_numbers, int size, int rank, unsigned char* number, MPI_Status* mpi_stat
);

/**
 * Prints the given sequence of numbers to the standard output by the
 * way of the individual numbers at the individual new lines.
 *
 * @param numbers   The reference to the array with the stored number sequence.
 * @param size      The count of the numbers in the stored number sequence.
 */
void print_ordered_numbers(unsigned char* numbers, int size);
