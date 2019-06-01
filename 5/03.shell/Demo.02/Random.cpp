#include <malloc.h>
#include "random.h"
#include "afx.h" 

RndGen::~RndGen()
{ 
	if (oldrand)
		free(oldrand); 
}

void RndGen::init_random(const float randomseed)
{
    float new_random  = 1.0e-9f;
    float prev_random = randomseed;        

    oldrand		= (float*)calloc(55, sizeof(float));        
    oldrand[54] = randomseed;        

#ifdef _DEBUG
    trace("before init array\n\n"); 
#endif 

    for (int i = 0; i < 53; i ++)        
    {                
		int j = (21 * (i + 1)) % 55;                
        oldrand[j] = new_random;                
        new_random = prev_random - new_random;                
        if (new_random < 0) 
            new_random ++;                
        
        prev_random = oldrand[j];     
        TRACE("%d %f\n", j, prev_random); 
	}        

#ifdef _DEBUG
    trace("\nBefore advance random\n"); 
#endif 

    advance_random();        

#ifdef _DEBUG
    trace("After 1 random\n"); 
#endif 

    advance_random();        

#ifdef _DEBUG
    trace("After 2 random\n"); 
#endif 

    advance_random();        
    n = 0;

#ifdef _DEBUG
    trace("After 3 random\n"); 
#endif 
}

void RndGen::advance_random()
{    
    float   new_random;             
    for (int i = 0; i <= 23; i ++)        
    {               
        new_random = oldrand[i] - oldrand[i+31];              
        if (new_random < 0) 
			new_random ++;               
        oldrand[i] = new_random;       
    }               
        
    for (i = 24; i <= 54; i ++) 
    {               
        new_random = oldrand[i] - oldrand[i-24];              
        if (new_random < 0)
			new_random ++;               
        oldrand[i] = new_random;       
    }
}

float RndGen::randm()
{             
	n ++;                
	if (n > 54)         
	{                       
		n = 1;                      
		advance_random();               
	}                               

	return oldrand[n];
}       

#ifdef _DEBUG
void RndGen::trace(char* lpsz)
{
    TRACE(lpsz); 
    TRACE("random array are:\n"); 
    for(int i=0; i<55; i++)
        TRACE("%f, ", oldrand[i]); 

    TRACE("\n"); 
}
#endif 