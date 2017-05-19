#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "skipList.h"
#include <time.h>

/* ************************************************************************
Main Function
 ************************************************************************ */
/* Test function:
 param: no parameters
 pre:	no parameres
 post: prints out the contents of the skip list */

int main()
{
	printf("*****************************************************TEST*******************************************************\n");
	test();
	printf("*****************************************************MERGE****************************************************\n\n");

	int i;
	struct skipList *one, *two;
	one = (struct skipList *) malloc(sizeof(struct skipList));
	two =  (struct skipList *) malloc(sizeof(struct skipList));	

	initSkipList(one);
	initSkipList(two);

	for(i = 0; i < 20; i++)
	{
		addSkipList(one, rand()%100+1);
		addSkipList(two, rand()%100+1);
	}

	printf("Skip list one: \n\n");
	printSkipList(one);
	
	printf("\n\nSkip list two: \n\n");
	printSkipList(two);

	mergeSkipList(one, two);

	printf("\n\nmerged skip list: \n\n");
	printSkipList(one);

	free(one);

	return 0;
}

void test()
{
	int i,j;
	int M = 20;
	struct skipList *slst;
	
	srand ( time(NULL) );
	
	slst=(struct skipList *)malloc(sizeof(struct skipList));  /*2*/
	assert(slst);
	
	/*  Initialize the skip list */

	initSkipList(slst);
	
        /*  FIX ME */

	/*  Add to the skip list  M = 20 random integers in [0,100] */

	for(i = 0; i < M; i++)
	{
		addSkipList(slst, rand()%100+1);
	}

        /*  FIX ME */
	
	/*  Print out the contents of the skip list in the breadth-first order, 
            starting from top. 
	    While printing the elements, 
            move to a new line every time you reach the end of one level, 
	    and move down to the lower level of the skip list. 
	    For example, the print out of a skip list with 5 elements 
            should look like
	 
	    7
	    7 14 29
	    3 7 9 14 20
	 */
	printf("Contents of original skip list:\n\n");	
	printSkipList(slst);

        /*  FIX ME */


	
	/* Develop 3 test cases for printing out the contents of skip list 
           after remove function:  
	         int removeSkipList(struct skipList *slst, TYPE e)
	 */

	int removed[3];

	for(j = 1; j <= 3; j++)
	{
		printf("\n");
		int random;
		printf("Removal #%d\n", j);
		while(!(containsSkipList(slst, random)))
		{		
			random = rand()%100+1;
		}

		printf("removing: %d\n\n", random);
	
		removeSkipList(slst, random);

		printSkipList(slst);
		removed[j-1] = random;
	}

        /*  FIX ME */
	
	printf("\n");

	for(j = 0; j < 3; j++)
	{
		printf("contains %d: ", removed[j]);

		if(!(containsSkipList(slst, removed[j]))) 
			printf("false\n");

		else	
			printf("true\n");
	}



         /* Develop 3 test cases corresponding to the above 3 test cases
            for printing out the output of contains function when e is equal to
            the elements you removed above:  
	          int containsSkipList(struct skipList *slst, TYPE e) 
	 */


        /*  FIX ME */
	        
	free(slst);
}


/* ************************************************************************
Internal Functions
 ************************************************************************ */

/* Coin toss function:
 param: 	no parameters
 pre:	no parameres
 post: output is a random intiger number in {0,1} */
int flipSkipLink(void)
{
	return rand() % 2; 	
}

/* Move to the right as long as the next element is smaller than the input value:
 param: 	current -- pointer to a place in the list from where we need to slide to the right
 param:	e --  input value
 pre:	current is not NULL
 post: returns one link before the link that contains the input value e */
struct skipLink * slideRightSkipList(struct skipLink *current, TYPE e){
	while ((current->next != 0) && LT(current->next->value, e))
		current = current->next;
	return current;
}


/* Create a new skip link for a value
	param: e	 -- the value to create a link for
	param: nextLnk	 -- the new link's next should point to nextLnk
	param: downLnk -- the new link's down should point to downLnk
	pre:	none
	post:	a link to store the value */
struct skipLink* newSkipLink(TYPE e, struct skipLink * nextLnk, struct skipLink* downLnk) {
	struct skipLink * tmp = (struct skipLink *) malloc(sizeof(struct skipLink));
	assert(tmp != 0);
	tmp->value = e;
	tmp->next = nextLnk;
	tmp->down = downLnk;
	return tmp;
}


/* Add a new skip link recursively
 param: current -- pointer to a place in the list where the new element should be inserted
 param: e	 -- the value to create a link for
 pre:	current is not NULL
 post: a link to store the value */
struct skipLink* skipLinkAdd(struct skipLink * lnk, TYPE e) 
{
	struct skipLink *new, *down;
	new = 0;
	assert(lnk);
	
	if(lnk->down == 0)
	{
		new = newSkipLink(e, lnk->next, 0);
		lnk->next = new;
	}

	else
	{
		down = skipLinkAdd(slideRightSkipList(lnk->down, e), e);
		if(down && flipSkipLink())
		{
			new = newSkipLink(e, lnk->next, down);
			lnk->next = new;
		}
	}

	return new;

}


/* ************************************************************************
Public Functions
 ************************************************************************ */

/* Initialize skip list:
 param:  slst -- pointer to the skip list
 pre:	slst is not null
 post: the sentinels are allocated, the pointers are set, and the list size equals zero */
void initSkipList (struct skipList *slst) 
{

	slst->size=0;
	slst->topSentinel=(struct skipLink * )malloc(sizeof(struct skipLink));
	assert(slst->topSentinel);
	slst->topSentinel->next=NULL;
	slst->topSentinel->down=NULL;
}

/* Checks if an element is in the skip list:
 param: slst -- pointer to the skip list
 param: e -- element to be checked
 pre:	slst is not null
 post: returns true or false  */
int containsSkipList(struct skipList *slst, TYPE e)
{
	struct skipLink *tmp = slst->topSentinel;
	while (tmp != 0) {  /* 2pts */
		tmp = slideRightSkipList(tmp, e); /* 1pt */
		if ((tmp->next != 0) && EQ(e, tmp->next->value)) /* 2pts */
			return 1;
		tmp = tmp->down;  /* 1pt */
	}
	return 0;
}


/* Remove an element from the skip list:
 param: slst -- pointer to the skip list
 param: e -- element to be removed
 pre:	slst is not null
 post: the new element is removed from all internal sorted lists */
void removeSkipList(struct skipList *slst, TYPE e)
{
	struct skipLink *current, *tmp;
	current = slst->topSentinel; /* 1pts */
	while (current != 0) {  /* 2pts */
		current = slideRightSkipList(current, e);
		if (current->next != 0 && EQ(e, current->next->value)) {  /* 2pts */
			tmp = current->next; /* 2pts */
			current->next = current->next->next;
			free(tmp);    /* 2pts */
			if (current->down == NULL)
				slst->size--;   /* 2pts */
		}
		current = current->down; /* 1pt */
	}
}




/* Add a new element to the skip list:
	param: slst -- pointer to the skip list
	param: e -- element to be added
	pre:	slst is not null
	post:	the new element is added to the lowest list and randomly to higher-level lists */
void addSkipList(struct skipList *slst, TYPE e)
{
	struct skipLink *downLink, *newLink;
	downLink = skipLinkAdd(slideRightSkipList(slst->topSentinel, e), e);

	if(downLink && flipSkipLink())
	{
		newLink = newSkipLink(e, 0, downLink);
		slst->topSentinel = newSkipLink(0, newLink, slst->topSentinel);
	}

	slst->size++;
}

/* Find the number of elements in the skip list:
 param: slst -- pointer to the skip list
 pre:	slst is not null
 post: the number of elements */
int sizeSkipList(struct skipList *slst){
	
	return slst->size;
	
}


/* Print the links in the skip list:
	param: slst -- pointer to the skip list
	pre:	slst is not null and slst is not empty
	post: the links in the skip list are printed breadth-first, top-down */
void printSkipList(struct skipList *slst)
{

	struct skipLink *current, *root;
	int val;

	current = slst->topSentinel;
	root = current;
	while(root != 0)
	{
		current = current->next;
		while(current != 0)
		{
			val = current->value;
			printf("%d ", val);
			current = current->next;
		}
		root = root->down;
		current = root;
		printf("\n");
	}
}


/* Merge two skip lists, by adding elements of skip list 2 to skip list 1 
 that are not already contained in skip list 1. 
 The function is also supposed to remove the entire skip list 2 from the memory.
 param: slst1 -- pointer to the skip list 1
 param: slst2 -- pointer to the skip list 2
 pre: slst1 and slst2 are not null, and skip list 1 and skip list 2 are not empty
 post: slst1 points to the merger skip list,  slst2 is null*/
void mergeSkipList(struct skipList *slst1, struct skipList *slst2)
{
	struct skipLink *root;
	root = slst2->topSentinel;
	assert(slst1);
	assert(slst2);

	while(root->down != 0)
	{
		root = root->down;
	}

	root = root->next;

	while(root != 0)
	{
		if(!(containsSkipList(slst1, root->value)))
		{
			addSkipList(slst1, root->value);
		}

		root = root->next;
	}

	free(slst2);
	slst2 = 0;

		
} /* end of the function */
	


