#include <iostream>
using namespace std;

/*
We will also provide for you the code that is used to create the list and the code to traverse and display the list
elements.  You can also assume that lists being processed already exist, and that the pointers for new lists are
initialized to NULL.  For the examples below,  unless specified otherwise assume the list we are starting with is
the list: 2->8->5->11->3->9->6
*/

struct Node {
    int data;
    Node *pNext;
};

void displayList(Node *pHead){
    while(pHead != NULL){
        cout << pHead->data;
        if (pHead->pNext != NULL){
            cout << "->";
        }
        pHead = pHead->pNext;
    }
    cout << endl;
}

/*
1. Split a list at the node with a designated value.  The function header would be:
   splitList( Node *pOriginal, int splitValue, Node *&pHeadA, Node *&pHeadB)
Assume the list we are starting with is the list: 2->8->5->11->3->9->6
Calling splitList(…) from within main would look like:
    cout << "Enter value: ";
    cin >> userInput;
    splitList(pHead, userInput, pHeadA, pHeadB);
    displayList( pHeadA);
    displayList( pHeadB);
and it would result in the following output:
    Enter value for split: 11
    2->8->5->11
    3->9->6
*/
void splitList( Node *pOriginal, int splitValue, Node *&pHeadA, Node *&pHeadB){
    bool splitValueFound = false;
    Node *pTemp;
    while(pOriginal != NULL){
        if(!splitValueFound){
            pTemp = new Node;
            pTemp->data = pOriginal->data;
            pTemp->pNext = NULL;
            Node *pLastA = pHeadA;
            while( pLastA != NULL && pLastA->pNext != NULL){
                pLastA = pLastA->pNext;
            }
            if (pLastA == NULL){
                pHeadA = pTemp;
            }
            else {
                pLastA->pNext = pTemp;
            }
        }
        else{
            pTemp = new Node;
            pTemp->data = pOriginal->data;
            pTemp->pNext = NULL;
            Node *pLastB = pHeadB;
            while( pLastB != NULL && pLastB->pNext != NULL){
                pLastB = pLastB->pNext;
            }
            if (pLastB == NULL){
                pHeadB = pTemp;
            }
            else {
                pLastB->pNext = pTemp;
            }
        }
        if(pOriginal->data == splitValue){
            splitValueFound = true;
        }
        pOriginal = pOriginal->pNext;
    }
}

/*
2. Prompt for a boundary number and traverse a list, creating two new lists: one with
   all the values less than the boundary number, and the other with all the values greater
   than the boundary number.  The boundary number value itself, if found, is not put on
   either list. The function header would be:
        lessGreaterLists( Node *pOriginal, Node *&pHeadLess, Node *&pHeadGreater)
Assume the list we are starting with is the list: 2->8->5->11->3->9->6
Calling lessGreaterLists(…) from within main would look like the following:
   cout << "Enter value: ";
   cin >> userInput;
   lessGreaterLists( pHead, userInput, pHeadA, pHeadB);
   displayList( pHeadA);
   displayList( pHeadB);
and for an input of  7 it would result in the following output:
   2->5->3->6
   8->11->9
*/
void lessGreaterLists( Node *pOriginal, int inputValue, Node *&pHeadLess, Node *&pHeadGreater){
    Node *pTemp;
    while(pOriginal != NULL){
        pTemp = new Node;
        pTemp->data = pOriginal->data;
        pTemp->pNext = NULL;
        if( pTemp->data < inputValue){
            Node *pLastLess = pHeadLess;
            while( pLastLess != NULL && pLastLess->pNext != NULL){
                pLastLess = pLastLess->pNext;
            }
            if (pLastLess == NULL){
                pHeadLess = pTemp;
            }
            else {
                pLastLess->pNext = pTemp;
            }
        }
        if (pTemp->data > inputValue){
            Node *pLastGreater = pHeadGreater;
            while( pLastGreater != NULL && pLastGreater->pNext != NULL){
                pLastGreater = pLastGreater->pNext;
            }
            if (pLastGreater == NULL){
                pHeadGreater = pTemp;
            }
            else {
                pLastGreater->pNext = pTemp;
            }
        }
        pOriginal = pOriginal->pNext;
    }

}

/*
3. Traverse a list and get the sum of all even numbers and the sum of all odd numbers.
   The function header would be:
        evenOddSum( Node *&pHead, int &evenSum, int &oddSum)
Assume the list we are starting with is the list: 2->8->5->11->3->9->6
Calling evenOddSum(…) from within main would look like the following:
   int evenSum = 0;
   int oddSum = 0;
   evenOddSum( pHead, evenSum, oddSum);
   cout << "Even and odd sums are: " << evenSum << " " << oddSum << endl;
and it would result in the following output:
   Even and odd sums are: 16 28
*/
void evenOddSum( Node *pHead, int &evenSum, int &oddSum){
    while(pHead != NULL){
        if(pHead->data % 2 == 0){ evenSum += pHead->data;}
        if(pHead->data % 2 != 0){ oddSum += pHead->data;}
        pHead = pHead->pNext;
    }
}

/*
4. Traverse a list, finding the minimum and maximum values, also then adding 1 to each list element.
   The function header would be:
        minMaxAddOne( Node *pHead, int &min, int &max)
Assume the list we are starting with is the list:      2->8->5->11->3->9->6
Calling minMaxAddOne(…) from within main would look like the following:
   int min=0;
   int max=0;
   minMaxAddOne( pHead, min, max);
   displayList( pListA);
   cout << "Min and max values: " << min << " " << max << endl;
and it would result in the following output:
   3->9->6->12->4->10->7
   Min and max values: 2 11
*/
void minMaxAddOne( Node *pHead, int &min, int &max){
    min = pHead-> data;
    max = pHead->data;
    Node *pCurrent = pHead;
    while(pCurrent != NULL){
        if (pCurrent->data > max){
            max = pCurrent->data;
        }
        if (pCurrent->data < min){
            min = pCurrent->data;
        }
        pCurrent->data++;
        pCurrent = pCurrent->pNext;
    }
}

/*
5. Traverse a list.  For every node add its following neighbor value to its own value, except for
   the last node which doesn't have a following neighbor. The function header would be:
        addNeighbor( Node *pHead)
Assume the list we are starting with is the list: 2->8->5->11->3->9->6
Calling addNeighbor(…) from within main would look like the following:
   addNeighbor( pHead);
   displayList( pHead);
and it would result in the following output:
   10->13->16->14->12->15->6
*/
void addNeighbor( Node *pHead){
    Node *pCurrent = pHead;
    while(pCurrent->pNext != NULL){
        pCurrent->data += pCurrent->pNext->data;
        pCurrent = pCurrent->pNext;
    }
}

/*
6. Delete all the list nodes that contain even numbers. The function header would be:
        deleteEvenNumbers( Node *&pHead)
 Assume the list we are starting with is the list: 2->3->5->6->8->9->11
 Calling deleteEvenNumbers(…)from within main would look like the following:
    deleteEvenNumbers( pHead);
    displayList( pHead);
and it would result in the following output:
    3->5->9->11
*/
void deleteEvenNumbers(Node *&pHead){
    Node *pCurrent = pHead;
    while (pCurrent != NULL){
        if (pCurrent->data % 2 == 0){
            if(pCurrent == pHead){
                Node *pTemp = pHead;
                pHead = pHead->pNext;
                pCurrent = pCurrent->pNext;
                delete pTemp;
            }
            else if (pCurrent->pNext == NULL){
                Node *pTemp = pCurrent;
                Node *pPrev = pHead;
                while (pPrev->pNext != pTemp){
                    pPrev = pPrev->pNext;
                }
                pPrev->pNext = NULL;
                pCurrent = NULL;
                delete pTemp;
            }
            else{
                Node *pTemp = pCurrent;
                pCurrent = pCurrent->pNext;
                Node *pPrev = pHead;
                while (pPrev->pNext != pTemp){
                    pPrev = pPrev->pNext;
                }
                pPrev->pNext = pCurrent;
                delete pTemp;
            }
        }
        else{
            pCurrent = pCurrent->pNext;
        }
    }
}

int main() {
    Node *pHead = NULL;  // pointer to the head of the list
    Node *pTemp;         // pointer used to get new nodes
    Node *pHeadA = NULL; // List A head pointer initialized to NULL
    Node *pHeadB = NULL; // List B head pointer initialized to NULL
    int userInput;
    int evenSum;
    int oddSum;
    int min;
    int max;
    int choice = 0;

    cout << "Enter as many integers > 0 as you would like " << endl
         << "  followed by the value -1. " << endl
         << endl
         << "The numbers are: ";

    int number = 0;
    while( number != -1){
        cin >> number;
        if(number != -1){
            pTemp = new Node;
            pTemp->data = number;
            pTemp->pNext = pHead;
            pHead = pTemp;
        }
    }
    displayList(pHead);
    while(true){
        cout << "Your choices:\n"
             << "1. Split List\n"
             << "2. Create lesser and greater lists\n"
             << "3. Create lists with sum of all even and odd numbers\n"
             << "4. Find min and max values in list and add one to each node\n"
             << "5. Add neighbour node to current node\n"
             << "6. Delete all nodes with even numbers\n"
             << "7. Exit the program\n"
             << "Your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter value for split: ";
                cin >> userInput;
                splitList(pHead, userInput, pHeadA, pHeadB);
                displayList( pHeadA);
                displayList( pHeadB);
                break;
            case 2:
                cout << "Enter value: ";
                cin >> userInput;
                lessGreaterLists( pHead, userInput, pHeadA, pHeadB);
                displayList( pHeadA);
                displayList( pHeadB);
                break;
            case 3:
                evenSum = 0;
                oddSum = 0;
                evenOddSum( pHead, evenSum, oddSum);
                cout << "Even and odd sums are: " << evenSum << " " << oddSum << endl;
                break;
            case 4:
                min=0;
                max=0;
                minMaxAddOne(pHead, min, max);
                displayList( pHead);
                cout << "Min and max values: " << min << " " << max << endl;
                break;
            case 5:
                addNeighbor( pHead);
                displayList( pHead);
                break;
            case 6:
                deleteEvenNumbers( pHead);
                displayList( pHead);
                break;
            case 7:
                cout << "Exiting the program..." << endl;
                exit(0);
            default:
                cout << "Please enter a valid choice. Try again!" << endl;
        }
    }
    return 0;
}
