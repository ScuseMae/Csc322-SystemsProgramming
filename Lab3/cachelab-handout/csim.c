/***********************************************************************
 * Name : Marcus Giarrusso
 * ID # : 
 * User :
 *
 * About :
 *     Part A - Implement a cache simulator by completing the csim.c
 *         file so that it takes the same command line arguments
 *          and produces the identical output as the reference
 *         simulator.
 *     Part B - (Extra Credit) Optimizing Matrix Transpose. Writing a
 *          transpose function in trans.c that causes as few cache
 *          misses as possible.
 ************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <strings.h>
#include <string.h>
#include <limits.h>
#include "cachelab.h"

//Function Declarations
void printInformation(char *argv[]);
void clearCache(void);

//Global Variables
typedef unsigned long long int memoryAddress;
int hitCount = 0;
int missCount = 0;
int evictCount = 0;
char LSM;
int sizeFromFile;
int LRU_value = 0;
int emptySpace = -1;
int HIT = 0;
int EVICT = 0;
int verbose;

/* Cache Parameters Struct
 * s - Number of set index bits
 * E - Associativity, lines per set
 * b - Number of block bits
 * S - Number of sets
 * B - Block size
 */
typedef struct
{
   int s;
   int E;
   int b;
   int S;
   int B;
} cacheParameters;

//cacheLine
typedef struct
{
    int validBit;
    int time;
    memoryAddress tag;
} cacheLine;

//CacheSet
typedef struct
{
    cacheLine *lines;
} cacheSet;

//CacheStruct
typedef struct
{
    cacheSet *sets;
} cacheStruct;

cacheParameters parameters;
cacheStruct cache;
memoryAddress memAddress;

//Main Method
int main(int argc, char **argv)
{
   memset(&parameters, 0, sizeof(parameters));

   char *trace_file;
   char c;

   while ((c = getopt(argc, argv, "s:E:b:t:vh")) != -1)
   {
      switch (c)
      {
         case 's' :
            parameters.s = atoi(optarg);
            break;
         case 'E' :
            parameters.E = atoi(optarg);
            break;
         case 'b' :
            parameters.b = atoi(optarg);
            break;
         case 't' :
            trace_file = optarg;
            break;
         case 'v' :
            verbose = 1;
            break;
         case 'h' :
            printInformation(argv);
            exit(0);
         default :
            printInformation(argv);
            exit(1);
      }
   }

   if (parameters.s == 0 || parameters.E == 0 || parameters.b == 0 || trace_file == NULL)
   {
       printf("Error: %s: Missing required command line argument\n", argv[0]);
       printInformation(argv);
       exit(1);
   }

   //Compute S and B from arguments
   parameters.S = (1 << parameters.s);
   parameters.B = (1 << parameters.b);

   //Initialize cache and allocate memory
   cache.sets = malloc(parameters.S * sizeof (cacheSet));
   for (int i = 0; i < parameters.S; i++)
   {
      cache.sets[i].lines = malloc(sizeof(cacheLine) * parameters.E);
   }

   //Open and read trace_file
   FILE *traceFile = fopen(trace_file, "r");

   if (traceFile != NULL)
   {
      while (fscanf(traceFile, " %c %llx,%d", &LSM, &memAddress, &sizeFromFile) == 3)
      {
         int evictFlag = 0;
         if (LSM != 'I')
         {
            //Address_tag and set_index
            memoryAddress addressTag = memAddress >> (parameters.s + parameters.b);
            int tagSize = (64 - (parameters.s + parameters.b));
            unsigned long long holderVariable = memAddress << (tagSize);
            unsigned long long ID = holderVariable >> (tagSize + parameters.b);
            cacheSet set = cache.sets[ID];
            int age_Oldest = INT_MAX;

            for (int e = 0; e < parameters.E; e++)
            {
               if (set.lines[e].validBit == 1)
               {
                  //Check for HIT
                  if (set.lines[e].tag == addressTag)
                  {
                     HIT = 1;
                     hitCount++;
                     set.lines[e].time = LRU_value;
                     LRU_value++;
                  }
                  //Check for Least Recently Used
                  else if (set.lines[e].time < age_Oldest)
                  {
                     age_Oldest = set.lines[e].time;
                     evictFlag = e;
                  }
               }
               else if(emptySpace == -1)
               {
                  emptySpace = e;
               }
            }

            if (HIT != 1)
            {
               missCount++;
               if (emptySpace > -1)
               {
                  set.lines[emptySpace].validBit = 1;
                  set.lines[emptySpace].tag = addressTag;
                  set.lines[emptySpace].time = LRU_value;
                  LRU_value++;
               }
               //Evict if set is full
               else if (emptySpace < 0)
               {
                  EVICT = 1;
                  set.lines[evictFlag].tag = addressTag;
                  set.lines[evictFlag].time = LRU_value;
                  LRU_value++;
                  evictCount++;
               }
            }

            if (LSM == 'M')
            {
               hitCount++;
            }

            if (verbose == 1)
            {
               printf("%c ", LSM);
               printf("%llx,%d", memAddress, sizeFromFile);
               if (HIT == 1)
               {
                  printf("Hit ");
               }
               else if (HIT != 1)
               {
                  printf("Miss ");
               }
               if (EVICT == 1)
               {
                  printf("Eviction ");
               }

               printf("\n");
            }
            emptySpace = -1;
            HIT = 0;
            EVICT = 0;
         }
      }
   }

   //Clear memory
   clearCache();
    
   //Print out hit, miss and evict count
   printSummary(hitCount, missCount, evictCount);
   return 0;
}

//Prints usage, commands and example inputs
void printInformation(char *argv[])
{
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file> \n", argv[0]);
    printf("Optional Commands: \n");
    printf("  -h         Prints this help message. \n");
    printf("  -v         Optional verbose flag. \n");
    printf("  -s <num>   Number of set index bits. \n");
    printf("  -E <num>   Number of lines per set. \n");
    printf("  -b <num>   Number of block offset bits. \n");
    printf("  -t <file>  Trace file. \n");
    printf("\nExample Input: \n");
    printf("  %s -s 4 -E 1 -b 4 -t traces/yi.trace \n", argv[0]);
    printf("  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace \n", argv[0]);
    exit(0);
}

//Clear up allocated memory
void clearCache()
{
    for (int i = 0; i < parameters.S; i++)
    {
        free(cache.sets[i].lines);
    }
    free(cache.sets);
}

