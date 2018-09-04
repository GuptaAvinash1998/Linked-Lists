#include<stdio.h>
#include<stdlib.h>
//Here we define what each node in the list looks like
//Each node has a value and a pointer to the next value in the linked list
typedef struct node{

  int val;
  struct node*next;
}Node;

//Prototypes
Node *newList(void); //This is where we make a new list
Node *insertNode(Node *prev, int a);//This is where we insert a new node
int length(Node *head);//This is where we calculate the length of the list
Node *Sorting_func(Node*head, Node*last, int a);//This is where we add the element in ascending order
void printList(Node *head);//This is where we print the list
void deleteList(Node *head);//frees all allocations

int main(){

  #ifndef FUNCS_CNTR //These are variables that are used to see how manyt times the functions have been called and these also help test the functions
	int newList_cntr = 0;
	int sortingFunc_with_insertNode_cntr = 0;
	int printList_cntr = 0;
	int deleteList_cntr = 0;
  #endif
  
  Node *head = newList();//makes the new list

  #ifndef FUNCS_CNTR
	newList_cntr++;
  #endif

  Node *last = head;//keeps track of the last element in the list
  int r = 0; //stores the random number;
  int looper = 1;//counts how many random number have been geberated
  
  srandom(9180);//initializes the random number generator

  while(looper <= 10){
	
	r = random()%1000;//generates numbers between 0 and 1000
	
	last = Sorting_func(head,last,r);//updates the last pointer to the element that has just been added
	printList(head->next);

	#ifndef FUNCS_CNTR
		sortingFunc_with_insertNode_cntr++;
		printList_cntr++;
	#endif
	looper++;//increments the cntr
  }

  Node *tmp = head->next;
  free(head);
  head = tmp;

  deleteList(head);
  #ifndef FUNCS_CNTR
	deleteList_cntr++;

	printf("\n");
	printf("These are the number of time each function has been called\n");
	printf("newList: %d, Sorting_func and insertNode: %d, printList: %d, deleteList: %d\n",newList_cntr, sortingFunc_with_insertNode_cntr, printList_cntr, deleteList_cntr);
  #endif
  return 1;
}

Node *newList(void){//Returns a head of a new empty list

  Node *newNode = malloc(sizeof(Node));//makes space dynamically for the new node of size Node
  newNode->val = 0;//initializes the value and the pointer
  newNode->next = NULL;
  return newNode;//returns the pointer
}

Node *insertNode(Node *prev, int a){ //inserts a new node with data fields after prev

  Node *inserted = malloc(sizeof(Node));
  inserted->val = a;
  inserted->next = prev->next;
  prev->next = inserted;
  return inserted;
  
}

Node *Sorting_func(Node*head, Node*last, int a){

  Node *tmp = head;//makes a temporary reference that points to the head
  
  while(tmp != NULL){
  
	if(tmp->next == NULL){//if there is only one element in the list or it is at the end of the list
	//basically if the value is the greatest in the list
		Node *freshNode = malloc(sizeof(Node));//makes a new node of size Node
		freshNode->val = a;//initializes the value and the pointer
		freshNode->next = NULL;
		tmp->next = freshNode;//sets the last element in the list to this new node
		return freshNode;//returns the new node	

	}else if(tmp->val < a && a < tmp->next->val){//if the value to be inserted is in the middle of 2 values

		Node *t = insertNode(tmp,a);//calls the insert function where it takes care of this situation
		return t;//returns the new node
	}else{

		tmp = tmp->next;//if both of the conditions do not pass, then it moves to the next element
	}
  }
}

int length(Node *head){//number of elements in the list
  
  int len = 0;//will keep track of the size
  Node *temp = head;//temporary reference to the head

  while(temp != NULL){//as long as the temporary reference is not null
	
	len++;//the length variable wil be incremented
	temp = temp->next;//the reference will be set to the next element
  }

  return len;//returns the length
}

void printList(Node *head){

  Node*tmp = head;//temporary reference
  int len = length(head);//stores the length
  int i = 0;//trash variable just keeping track until the secon last element so that the printing is neat
  
  while(i<len){

	//printf("%d -> ",tmp->val);

	if(i == len-1){//if i is equal to the 2nd last element, then it will print the element without the -> symbol after it

	  printf("%d\n",tmp->val);

	}else{

	  printf("%d -> ",tmp->val);
	}
	tmp = tmp->next;//goes to the next element
	i++;
  }
}

void deleteList(Node *head){

  Node *tmp1 = head;//assigns first pointer to point to the head
  Node *tmp2;

  while(tmp1 != NULL){//as long as the first pointer is not pointing to NULL

	tmp2 = tmp1->next;//the second pointer will point to the node after the first pointer
	free(tmp1);//frees the first pointer
	tmp1 = tmp2;//reassigns forst pointer
  }
}
