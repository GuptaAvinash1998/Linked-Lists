#include<stdio.h>
#include<stdlib.h>

enum Number {A,One,Two,Three,Four,Five,Six,Seven,Eight,Nine,Ten,Jack,Queen,King};//This is the enum that defines the numbers that the card has

enum Suits {S,D,C,H};//This is the enum that defines the suits that the card has

typedef struct card{//This is the representation of the card

  enum Number num;
  enum Suits suit;
  struct card *next;
}Card;

//prototypes
Card *newList(void);//Makes a dummy node to starts the list
Card *removeList(Card *prev);//removes the node ater prev
Card *insertNode(Card *prev, Card *newNode);//inserts the node into the deck
int length(Card *h);//calculates the length of the deck
void printList(Card *head, char numVals[], char suitVals[]);//prints out the list
Card *randomShuffle(Card *head);//shuffles the deck and makes a new deck
void deleteDeck(Card *head);//frees all the allocations

int main(){
 
  #ifndef FUNCS_CNTR
	int newList_cntr = 0;
	int randomShuffle_cntr = 0;
	int printList_cntr = 0;
	int deleteDeck_cntr = 0;
	int insertNode_cntr = 0;
  #endif 

  enum Number n = 0;//represents the number
  enum Suits s = 0;//represents the suit
  
  int i= 0;
  int j = 0;
  
  Card *head = newList();//starts the deck

  #ifndef FUNCS_CNTR
  	newList_cntr++;
  #endif

  Card *last = head;//points to the most current Card
 
  char CardNumVals[14] = {'A','1','2','3','4','5','6','7','8','9','0','J','Q','K'};//since we cannot print out the enum value, we make an array characters each character representing the value in the enum 
  char CardSuits[4] = {'S','D','C','H'};
 
  for(i=0;i<4;i++){
	
	j = 0;
	
	for(j=0;j<14;j++){//to make te deck we have to make a nested loop where we iterate through the suits and the numbers
		
		Card *tmp = malloc(sizeof(Card));//makes a new heap in memory
		
		n = j;
		tmp->num = n;//sets the suit and the number

		s = i;
		tmp->suit = i;
		
		last = insertNode(last,tmp);//inserts the node
		#ifndef FUNCS_CNTR
			insertNode_cntr++;
		#endif
	}
  }

  Card*tmp = head->next;//since we made a dummy node we are deleting that node 
  free(head);
  head = tmp;
  printList(head,CardNumVals,CardSuits);//prints the original deck 
  #ifndef FUNCS_CNTR
	printList_cntr++;
  #endif

  Card *newDeck = randomShuffle(head);//here is where the deck gets shiffled, we shuffle the deck, and make a new one
  #ifndef FUNCS_CNTR
	randomShuffle_cntr++;
  #endif
  Card *tmp1 = newDeck->next;//same procedure as last time, we are deleting the dummy node
  free(newDeck);
  newDeck = tmp1;
  
  printf("\n");
  printf("The new shuffled deck\n");
  printList(newDeck,CardNumVals,CardSuits);//prints out the new shuffled deck
  #ifndef FUNCS_CNTR
	printList_cntr++;
  #endif

  deleteDeck(head);//onece we have finshed making a deck and shiffled that deck, we loop through each deck and free all the allocations to avoid memory leaks
  #ifndef FUNCS_CNTR
	deleteDeck_cntr++;
  #endif
  deleteDeck(newDeck);
  #ifndef FUNCS_CNTR
	deleteDeck_cntr++;

	printf("\n");
	printf("This is how many times each function has been called\n");
	printf("newList: %d, randomShuffle: %d, printList: %d, deleteDeck: %d\n",newList_cntr, randomShuffle_cntr, printList_cntr, deleteDeck_cntr);
  #endif
  return 1;
}

Card *newList(){

  Card *newDeck = malloc(sizeof(Card));//makes a new place in memory
  newDeck->next = NULL;//sets the pointer to NULL and has no values
  return newDeck;
}

Card *insertNode(Card *prev, Card *newNode){

  newNode->next = prev->next;//sets the new node to be inserted to what orevious is pointing to
  prev->next = newNode; //previous is not set to point to the new node
  return newNode;
}

int length(Card *head){

  int len = 0;//This is a counter
  Card *tmp = head;//temporary pointer set to the head

  while(tmp != NULL){//until the pointer is pointing to NULL, it loops though every Card in the deck and increments the counter

	len++;
	tmp = tmp->next;
  }

  return len;
}

void printList(Card *head, char numVals[], char suitVals[]){//we pass in the arrays of the cards and suits because we cant print out the enum constant

  Card*temp = head;//temporary pointer set to the head
  int size = length(temp);//calculates the size of the deck which is supposed to be 56
  int i = 0;
  
  while(i<size){//as long as i is less than 56

	if(i == size-1){//if i is 55, basically whe it reaches the last card, it prints the card without a space after it

		printf("(%c, %c)\n",numVals[temp->num], suitVals[temp->suit]);
	}else{//else it does
	    printf("(%c, %c) ",numVals[temp->num], suitVals[temp->suit]);
	}

	i++;//increments i and moves to the next card
	temp = temp->next;
  }
}

Card *removeList(Card *prev){
  
  
  Card *ntmp = NULL;//this is a new tmporary 

  Card *tmp = prev;//temporary pointer set to point to head

  if(tmp->next != NULL){//as long as the temporary's next pointer is not pointing to NULL 
      
  	ntmp = tmp->next;//the new temporary will point to the temporary's next
  
  	tmp->next = ntmp->next;//temporary's next will point to the card 2 spaces away

  	ntmp->next = NULL;//the middle card is now isolated
  	
  	return ntmp;
  	
  }else{//if it does point to a NULL
    
    Card *newCard = malloc(sizeof(Card));//then we make a new card with the same data as the card that has to be deleted
    newCard->num = tmp->num;
    newCard->suit = tmp->suit;
    newCard->next = NULL; 
    
    return newCard;
  }
}

Card *randomShuffle(Card *oldDeck){
  
  int len = length(oldDeck);//gets the length of the deck (56)

  Card *temp = oldDeck;//This point to the old deck
  
  Card *newDeck = newList();//a new deck is made

  Card *tmp = newDeck;//This points to the new deck

  Card *removedCard;//This is the pointer that points to the card that is removed and returned from the remove function

  long j = 0;

  for(int i=len;i>=0;i--){//we are starting i as 56 because when the initial size of the deck is 56 and as we remove a card from the deck , the size reduces by 1 so after every iteration, we reduce i by 1

    temp = oldDeck;//in every iteration we start the pointer that points to the old deck to start at the forst node again
    
	j = random()%(i+1);//generates a random number
	
	int cntr = 0;//This is a counter

	while(temp != NULL && cntr < j){//as long as the pointer is not pointing to NULL and the counter is 1 number less than the random number

		cntr++;//we traverse the deck until we get the required card or hit the end of the deck , which ever comes first
		temp = temp->next;
	}

	removedCard = removeList(temp);//we pass that card into the fuction for it to be removed from the deck

	insertNode(newDeck,removedCard);//we insert that removed card into the new deck
  }

  return newDeck;//then we return the new deck
}

void deleteDeck(Card *head){

  Card *tmp1 = head;//first pointer to the head
  Card *tmp2;

  while(tmp1 != NULL){//as long as the first pointer is not pointing to NULL

	tmp2 = tmp1->next;//the second pointer points to the next element
	free(tmp1);//we free the element temp1 points to 
	tmp1 = tmp2;//re assign the first pointer to what the second pointer is pointing to
  }
}
