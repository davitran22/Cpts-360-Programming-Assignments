/* Steps to simulate Cache system
* 1. Parse command line arguments for s,E,b
* 2. Create Cache structure with (E) the number of lines per set
* 3. parse the file for set index, block offset, and tag
* 4. search each line for Cache hit or miss then update the hit_count and miss_count
* 5. if set is full use LRU to keep track (LRU < E)
*
*/

#define _CRT_SECURE_NO_WARNINGS
// getopt will not work now but once ran in a linux enviroment it will work
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <stdint.h>
#include "Cache.h"
// other headers as needed

#define ADDRESS_LENGTH 64  // 64-bit memory addressing

// The cache looks like this [TAG] [Cache Index (set index)] [Cache offset (block offset)]


// other variables as needed


/*
 * this function provides a standard way for your cache
 * simulator to display its final statistics (i.e., hit and miss)
 */
void print_summary(int hits, int misses, int evictions)
{
    printf("hits:%d misses:%d evictions:%d\n", hits, misses, evictions);
}

/*
 * print usage info
 */
void print_usage(char* argv[])
{
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\nExamples:\n");
    printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/trace01.dat\n", argv[0]);
    printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/trace01.dat\n", argv[0]);
    exit(0);
}

/*
*/
int decimaltobinary(int number) // part of decimal to binary conversion logic snippet credit to https://www.scaler.com/topics/decimal-to-binary-in-c/
{
    int conversion[64]; // for this simulator we are using a 64 bit memory addressing
    int index = 0;
    int i = 0;
    int result = 0;
    int remainder = 0;
    int converted_decimal = 0;

    /* Decimal to binary conversion here */

    // if the address is 0 then there is nothing to parse
    if (number == 0)
    {
        return 0;
    }

    // check if the decimal number is 0
    while (number > 0)
    {
        // divide the decimal by 2 until it is zero
        conversion[index++] = number % 2;
        number / 2;
    }

    // iterate through the array which contains number
    // start from the right of the array
    //
    for (int i = index - 1; i > 0; i--)
    {
        // move towards the left while coping all the numbers or elements in the array
        result = result * 10 + conversion[i];
    }


    return result;
}

//
//int decimal_to_binary_bits(uint64_t binary_number)
//{
//    for (int index = 64; index > 0; index--)
//    {
//
//    }
//}


/*
 * starting point
 */
int main(int argc, char* argv[])
{
    // variables cache simulator
    int E = 0;
    int c = 0;
    //char* trace_file_handle = NULL;
    int set_index_bits = 0;
    int block_offset_bits = 0;
    char* trace_file = NULL;
    int cache_size = 0;
    int binary_address = 0;
    int remainder = 0;
    int index = 0;
    int eviction_tracker = 0;
    //double set_index = 0.0;
    //double block_offset = 0.0;

    // trace file variables
    char operation = '\0';
    int address = 0;
    int size = 0;
    long tag_trace_file = 0;
    long set_index_trace_file = 0;
    long blockoffset_trace_file = 0;

    // we will need to update these variables through the program
    int hit_count = 0;
    int miss_count = 0;
    int eviction_count = 0;
    int LRU = 0;


    // complete your simulator

    // getopt() function parses command line arguments
    // Note* getopt does not work in windows only in linux so don't worry
    while ((c = getopt(argc, argv, "s:E:b:t:vh")) != -1)
    {
        switch (c)
        {
        case 's': // get the number of set index bits
            set_index_bits = atoi(optarg);

        case 'E': // get the number of lines per set
            E = atoi(optarg);

        case 'b': // get the block offset
            block_offset_bits = atoi(optarg);

        case 't': // get trace file
            trace_file = optarg;

        case 'v': // verbose mode
            print_usage(argv);
            exit(0);

        case 'h': // print the help message
            print_usage(argv);
            exit(0);

        default:
            print_usage(argv);
            exit(1);
        }
    }

    // malloc is in the stdlib.h library
    // dynamically allocate space for the cache based on the set of lines
    // this allows us to store multiple instances of the cache
    Cache* caches = malloc(E * sizeof(Cache));


    // use log2() function to determine how many bits of set index and block offset are needed for the cache
    // since log2(double num) we need to cast our bits as a double
    //double set_index = log2((double)set_index_bits);
    //double block_offset = log2((double)block_offset_bits);

    //set_index_bits = (int)set_index;
    //block_offset_bits = (int)block_offset;

    // set up the specifcations for the cache
    caches->set_index = set_index_bits;
    caches->block_offset = block_offset_bits;

    // check to make sure allocation for cache was successfully
    if (caches == NULL)
    {
        printf("Memory allocation for the cache unsuccessfull ");
        //exit(1);
    }


    // open the trace file
    FILE* trace_file_handle = fopen(trace_file, "r");

    // check to see if file opened successfully
    while (trace_file_handle != NULL)
    {
        // read each line of the file for cache information
        fscanf(trace_file_handle, "%c%d%d", &operation, &address, &size);
    }

    // convert the address in the trace file to binary
    binary_address = decimaltobinary(address);


    // make sure the address length is 64 bits if not pad 0


    // break up the address and determine the TAG, Set index, block offset
    // use the set index and block offset from the command line to break up the address
    // extract the digits from the address based on the bits needed for the block_offset and set index
    blockoffset_trace_file = binary_address % block_offset_bits;
    set_index_trace_file = binary_address % set_index_bits;

    // now the remaining bits are for the tag
    // while there are still remaining bits in the address
    while (binary_address != 0)
    {
        // extract the remaining bits for the tag
        tag_trace_file = binary_address % 10;
    }

    // cache size here
    cache_size = set_index_bits * E * block_offset_bits; // cache size = S x E x B

    // use the TAG, SI, BO for the address to compare compare for hits, misses and LRU while updating the variables
    while (LRU < E) // if all the set lines are filled up then the cache is full
    {
        if (caches->set_index == set_index_trace_file) // first go to the corresponding set
        {
            if (caches->tag == tag_trace_file) // check if tag matches
            {
                // tags match we have a hit
                // update the number of hits
                hit_count++;
                LRU++; // use this to track if the cache is full or not

            }
            else
            {
                // tags do not match we have a miss

                LRU++; // even though it is a miss it will get the data from main memory and insert it into the cache
                miss_count++;  // update the number of misses
            }
        }
    }

    if (LRU > E) // checks if the cache is full
    {
        // evict the most recently used cache
        // we access the last block within our array of struct
        eviction_tracker = E - 1;
        Cache cache_eviction = caches[eviction_tracker]; //
        eviction_count++; // update the number of evictions
        free(caches); // evict that block

    }


    printf("Hello World \n");

    // output cache hit and miss statistics
    print_summary(hit_count, miss_count, eviction_count);


    // assignment done. life is good!
    return 0;
}
