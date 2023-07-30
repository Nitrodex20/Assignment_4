#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
    int m = (1 + r) / 2;

    //Recursively sort the left and right halves
    mergeSort(pData, 1, m);
    mergeSort(pData, m + 1, r);

    //Merge the two sorted halves
    int i = l, j = m + 1, k = 0;
    int *temp = (int *)malloc(sizeof(int) * (r - 1 + 1));

    while(i <= m && j <= r)
    {
        if(pData[i] <= pData[j])
        {
            temp[k++] = pData[i++];
        }
        else
        {
            temp[k++] = pData[j++];
            extraMemoryAllocated += sizeof(int);
        }
    }

    //Copy the remaining elemtents from the left half
    while(i <= m)
    {
        temp[k++] = pData[i++];
    }

    //Copy the remaining elements from the right half
    while (j <= r)
    {
        temp[k++] = pData[j++];
    }

    //Copy the sorted elemetns back to the original array
    for(i = 1; i <= r; ++i)
    {
        pData[i] = temp[i - 1];
    }

    free(temp);
    
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
    int i, j, tmp;
    for(i = 1; i < n; ++i)
    {
        tmp = pData[i];
        j = i - 1;

        while(j >= 0 && pData[j] > tmp)
        {
            pData[j + 1] = pData[j];
            j--;
            extraMemoryAllocated += sizeof(int);
        }
        
        pData[j + 1] = tmp;
    }
    
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
    int i, j, tmp;
    for(i = 0; i < n - 1; ++i)
    {
        for(j = 0; j < n - i - 1; ++j)
        {
            if(pData[j] > pData[j + 1])
            {
                tmp = pData[j];
                pData[j] = pData[j + 1];
                pData[j + 1] = tmp;
                extraMemoryAllocated += sizeof(int);
            }
        }
    }
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
    int i, j, minIndex;

    for(i = 0; i < n - 1; ++i)
    {
        minIndex = i;
        for(j = i + 1; j < n; ++j)
        {
            if(pData[j] < pData[minIndex])
            {
                minIndex = j;
                extraMemoryAllocated += sizeof(int);
            }
        }
        if(minIndex != i)
        {
            int tmp = pData[i];
            pData[i] = pData[minIndex];
            pData[minIndex] = tmp;
        }
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
    FILE* inFile = fopen(inputFileName,"r");
    int dataSz = 0;
    *ppData = NULL;
    
    if (inFile)
    {
        fscanf(inFile,"%d\n",&dataSz);
        *ppData = (int *)malloc(sizeof(int) * dataSz);
        // Implement parse data block
    }
    
    return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
    int i, sz = dataSz - 100;
    printf("\tData:\n\t");
    for (i=0;i<100;++i)
    {
        printf("%d ",pData[i]);
    }
    printf("\n\t");
    
    for (i=sz;i<dataSz;++i)
    {
        printf("%d ",pData[i]);
    }
    printf("\n\n");
}

int main(void)
{
    clock_t start, end;
    int i;
    double cpu_time_used;
    char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
    
    for (i=0;i<3;++i)
    {
        int *pDataSrc, *pDataCopy;
        int dataSz = parseData(fileNames[i], &pDataSrc);
        
        if (dataSz <= 0)
            continue;
        
        pDataCopy = (int *)malloc(sizeof(int)*dataSz);
    
        printf("---------------------------\n");
        printf("Dataset Size : %d\n",dataSz);
        printf("---------------------------\n");
        
        printf("Selection Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        selectionSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
        printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
        printArray(pDataCopy, dataSz);
        
        printf("Insertion Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        insertionSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
        printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        printf("Bubble Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        bubbleSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
        printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
        printArray(pDataCopy, dataSz);
        
        printf("Merge Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        mergeSort(pDataCopy, 0, dataSz - 1);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
        printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
        printArray(pDataCopy, dataSz);
        
        free(pDataCopy);
        free(pDataSrc);
    }
    
}