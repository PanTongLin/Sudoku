#include <stdlib.h>
#include <stdbool.h>


//	List Data Type Defintions 
typedef struct node
{
    int vertex;
    struct node* link;
}NODE;

typedef struct
{
    int count;
    NODE* pos;
    NODE* head;
    NODE* rear;
}LIST;

/*	=============== createList ==============
	Allocates dynamic memory for a list head
	node and returns its address to caller
	   Pre    compare is address of compare function 
	          used to compare two nodes.
	   Post   head has allocated or error returned
	   Return head node pointer or null if overflow 
*/
LIST* createList()
{
//	Local Definitions 
	LIST* list;

//	Statements 
	list = (LIST*) malloc (sizeof (LIST));
	if (list)
    {
        list->head    = NULL;
        list->pos     = NULL;
        list->rear    = NULL;
        list->count   = 0;
    } // if 

	return list;
}	// createList 

/*	================== destroyList =================
	Deletes all data in list and recycles memory
	   Pre    List is a pointer to a valid list.
	   Post   All data and head structure deleted
	   Return null head pointer
*/
LIST* destroyList (LIST* pList) 
{
//	Local Definitions 
	NODE* deletePtr;

//	Statements 
	if (pList)
    {
        while (pList->count > 0) 
        { 
            // Now delete node 
            deletePtr    = pList->head;
            pList->head  = pList->head->link; 
            pList->count--;
            free (deletePtr); 
        } // while 
        free (pList);
    } // if 
	return NULL;
}	// destroyList 

/*	================== addNode =================
	Inserts data into list.
	   Pre    pList is pointer to valid list
	          v is the index of the node
	   Post   node added or error
	   Return boolean, true  if successful, 
	                   false if memory overflow 
*/
bool addNode (LIST* pList, int v)
{
//	Local Definitions 
	NODE* pNew;

//	Statements 
	if (!(pNew = (NODE*) malloc(sizeof(NODE))))
	   return false;

	pNew->vertex    = v; 
	pNew->link      = NULL; 
 
	if (pList->count == 0)
    {
        // Adding to empty list. 
        pList->head      = pNew;
        pList->rear      = pNew;
    } // if pPre 
	else
    {
        // Adding in middle or at end 
        pList->rear->link  = pNew;
        pList->rear        = pNew;
    } // if else 

	(pList->count)++;
	return true;
}	// addNode 