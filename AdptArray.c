/**
 * Sources: Solution to Moad A question 4 in the 
 * "Systems Programming A" test from last semester 
 * (2022-2023)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC prntFnc;
}AdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC prntFnc_)
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
    pArr->prntFnc = prntFnc_;
	return pArr;
}

void DeleteAdptArray(PAdptArray pArr){
    int i;
	if (pArr == NULL)
		return;
	for(i = 0; i < pArr->ArrSize; ++i)
	{
        if((pArr->pElemArr)[i] != NULL){
            pArr->delFunc((pArr->pElemArr)[i]);
            // printf("element %d was deleted\n", i);
        }   
	}
	free(pArr->pElemArr);
	free(pArr);
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
    PElement* newpElemArr;
	if (pArr == NULL)
		return FAIL;

    // Extend Array
	if (idx >= pArr->ArrSize)
	{
		if ((newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
			return FAIL;
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
		free(pArr->pElemArr);
		pArr->pElemArr = newpElemArr;
	}

	// Delete Previous Elem
    if((pArr->pElemArr)[idx] != NULL){
        pArr->delFunc((pArr->pElemArr)[idx]);
    }
	(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);

	// Update Array Size
    if(idx >= pArr->ArrSize){
        pArr->ArrSize = idx + 1;
    }
	return SUCCESS;
}


PElement GetAdptArrayAt(PAdptArray pArr, int index){
    if (pArr == NULL || (pArr->ArrSize <= index)){
        return FAIL;
    }
    if((pArr->pElemArr)[index] != NULL){
        return (pArr->copyFunc((pArr->pElemArr)[index]));
    }
    else{ return NULL; }
}

int GetAdptArraySize(PAdptArray pArr){
    if (pArr == NULL)
        return FAIL;
    return pArr->ArrSize;
}

void PrintDB(PAdptArray pArr){
    int i;
	if (pArr == NULL)
		return;
	for(i = 0; i < pArr->ArrSize; ++i)
	{
        if((pArr->pElemArr)[i] != NULL){
            pArr->prntFnc((pArr->pElemArr)[i]);
        }	
	}
}