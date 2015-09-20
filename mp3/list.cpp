/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    /// @todo Graded in MP3.1
	clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    /// @todo Graded in MP3.1
	ListNode * temp = head;
   while(temp != NULL){
	temp= temp->next;	
	delete head;
	head = temp;
	}
   delete temp;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
    /// @todo Graded in MP3.1
   ListNode * temp = new ListNode(ndata);
   if (head == NULL)
    {
        head = temp;
		length = 1;
		tail = head;
    } else {
	   temp->next = head;
	   head->prev = temp;
	   head = temp;
	   length++;
	}
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
    /// @todo Graded in MP3.1

    ListNode * temp = new ListNode(ndata);
    if (head == NULL)
    {
        head = temp;
		length = 1;
		tail = head;
    }
    else
    {
        tail->next = temp;
        temp->prev = tail;
        ++length;
	   	tail = tail->next;
    }
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{
	//ListNode* a = head->next;
	//ListNode* b = tail->prev;
    //reverse(a, b);
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
    /// @todo Graded in MP3.1

	if(startPoint == NULL)
		return;

	ListNode * first = startPoint -> prev;
	ListNode * last = endPoint -> next;
	
	ListNode * next = NULL;
	ListNode * curr = startPoint;
	
	ListNode* endNext = endPoint->next;
   
	while(curr != endNext){
		next = curr->next;
		curr -> next = curr->prev;
		curr->prev = next;
		curr = next;
	}
	
	
	
 	//swap start and end
	ListNode* t = startPoint;
	startPoint = endPoint;
	endPoint = t;
	
	if(first != NULL)
		first -> next = startPoint;
	startPoint -> prev = first;
	if(last != NULL)
		last -> prev = endPoint;
	endPoint -> next = last;
	
	startPoint-> prev = first;
	endPoint -> next = last;
	
}


/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{
    /// @todo Graded in MP3.1
    
    if(head == NULL && tail == NULL && length == 0) 
    	return;
		    
    if(n <= 0)
    	return;	
    
    
	int i = n;
	ListNode * temphead = head;
	ListNode * temphead2 = NULL;
	ListNode * temptail = head;
	ListNode * temp = NULL;

	while(temphead != NULL){
	temptail = temphead;
	for(i=n-1; i>0; i--){
	   if(temptail->next != NULL)
		temptail=temptail->next;
	}
	temphead2 = temptail->next ;
	reverse(temphead,temptail);
	
	temp = temphead;
	temphead = temptail;
	temptail = temp;
	
	temphead = temphead2;	

	}
	
	
	while(tail->next != NULL)
	   tail = tail->next;
	
	while(head->prev != NULL)
		head = head->prev;

}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{

	if(head == NULL && tail == NULL)
		return;

	ListNode * curr = head;
	ListNode * newend = NULL;
	ListNode * prev = head;

	while(curr->next != NULL && curr->next->next != NULL){
	
	prev = curr;
	newend = curr->next;
	curr->next = newend->next;
	tail->next = newend;
	newend -> prev = tail;
	newend -> next = NULL;
	tail = tail -> next;
	curr = curr->next;
	curr -> prev = prev;

	

	}
	

    /// @todo Graded in MP3.1
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
    /// @todo Graded in MP3.2
    
    ListNode * two = start;
    ListNode * firstlast = NULL;
    
     for (int i = 0; i < splitPoint; i++)
    {
        firstlast = two;
        two = two->next;
    }
    
    two->prev = NULL;
    firstlast -> next = NULL;
    
    
    
    return two; // change me!
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
    /// @todo Graded in MP3.2
    
    ListNode * final = NULL;
   
    
    if( first->data < second->data  ){
    	final = first;
    	final->prev = NULL;
    	first = first->next;	
    }
    else{
    	final = second;
    	final->prev = NULL;
    	second = second -> next;
    }
    
      while(second != NULL || first != NULL){
		 if(second == NULL){
		 	final->next = first;
			first->prev = final;
    		first = first->next;
    		final = final -> next;	
		 }
		 else if(first == NULL){
		 	final->next = second;
    		second ->prev = final;
    		second = second -> next;
    		final = final -> next;	
		 }
    
    	 else if(first->data < second->data ){
    		final->next = first;
			first->prev = final;
    		first = first->next;
    		final = final -> next;	
   		 }
  		  else{
    		final->next = second;
    		second ->prev = final;
    		second = second -> next;
    		final = final -> next;
   		 }
    
    }
    
   
    while(final->prev != NULL)
    	final = final->prev;
       
    return final; // change me!
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
    /// @todo Graded in MP3.2
    
    ListNode * final = NULL;
   
    if(chainLength == 1){
    	final = start;
    }else{
    	int length1 = chainLength/2;
	    int length2 = chainLength - length1;
    	
    	ListNode * first = start;
    	ListNode * second = split(start,chainLength/2);
	    final = merge(mergesort(first,length1),mergesort(second,length2));
    }
    
    
    
    
    return final; // change me!
}
