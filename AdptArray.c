#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"

// struct arrays
typedef struct AdptArray_ {
    int arrSize; // array size
    PElement* pElemArr; // array
    DEL_FUNC delFunc; // delete function
    COPY_FUNC copyFunc; // copy function
    PRINT_FUNC printFunc; // print function 

} AdptArray;

// init empty array
PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc){
    // allocate memory for the array
    PAdptArray pArr;

    // check if null
    if ((pArr = (PAdptArray)malloc(sizeof(AdptArray))) == NULL)
        return NULL;

    // init default properties
    pArr->arrSize = 0;
    pArr->pElemArr = NULL;
    pArr->copyFunc = copyFunc;
    pArr->delFunc = delFunc;
    pArr->printFunc = printFunc;

    return pArr;
}

// destroy array and free allocated memory
void DeleteAdptArray(PAdptArray pArr){
    // check if null
    if (pArr == NULL)
        return;

    // check if not null
    if(pArr->pElemArr != NULL){
        for (int i = 0; i<pArr->arrSize; i++)
            if((pArr->pElemArr)[i] != NULL)
                pArr->delFunc((pArr->pElemArr)[i]);

        // free array
        free(pArr->pElemArr);
    }
    // free struct
    free(pArr);
}

// set element at index
Result SetAdptArrayAt(PAdptArray pArr, int index, PElement pNewElem) {
    PElement* newpElemArr;

    // check if null
    if (pArr == NULL)
        return FAIL;

    // check index is bigger than the array size
    if (index >= pArr->arrSize) {
        if ((newpElemArr = (PElement*) calloc((index + 1), sizeof(PElement))) == NULL)
            return FAIL;

        // copy old array to new array
        memcpy(newpElemArr, pArr->pElemArr, (pArr->arrSize) * sizeof(PElement));

        // check if not null
        if (pArr->pElemArr != NULL)
            // free array
            free(pArr->pElemArr);

        pArr->pElemArr = newpElemArr;
    }

    // check if not null
    if (pArr->pElemArr[index] != NULL)
        pArr->delFunc((pArr->pElemArr)[index]);

    // save a copy of the element inside the array at index
    (pArr->pElemArr)[index] = pArr->copyFunc(pNewElem);

    // update array size
    if (index >= pArr->arrSize)
        pArr->arrSize = index + 1;

    return SUCCESS;
}

// get element in index
PElement GetAdptArrayAt(PAdptArray pArr, int index) {
    // validate the index's value can be returned
    if (index<0)
        return NULL;
    
    if (pArr == NULL)
        return NULL;

    if(pArr->pElemArr == NULL)
        return NULL;

    if(pArr->pElemArr[index] == NULL) 
        return NULL;
    
    return (PElement)pArr->copyFunc(pArr->pElemArr[index]);
}

// get array size
int GetAdptArraySize(PAdptArray pArr){
    // check if array has been initiated, 
    // if array is null, return -1 else return array size
    if (pArr == NULL)
        return -1;
    else
        return pArr->arrSize;
}

// print array
void PrintDB(PAdptArray pArr){
    // check if null
    if (pArr == NULL)
        return;

    for (int i = 0; i<pArr->arrSize; i++)
        // check if element is not null, if so, print the element
        if ((pArr->pElemArr)[i] != NULL)
            pArr->printFunc((pArr->pElemArr)[i]);  
}