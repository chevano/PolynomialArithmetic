// Name: Chevano Gordon

#include <iostream>
#include <string>
#include <climits> // use for INT_MAX and INT_MIN
#include <fstream> // use for file handling
#include <sstream> // use for string stream
#include <vector>
using namespace std;

class Node {
    public:
        int coefficient;
        int exponent;
        Node *next;

    public:
        Node();
        Node(int, int);
        Node(const Node&);
        ~Node();
        void setNext(Node *);
};

class linkedList {
    private:
        Node *listHead;

    public:
        linkedList();
        ~linkedList();
        Node *getHead();
        Node* findSpot(Node const*, Node*);
        void insertNewNode(Node*);
        void clear();
        Node* simplify(Node*);
        Node* removeLastNode(Node*);
        Node* add(Node*, Node*);
        Node* subtract(Node*, Node*);
        Node* multiply(Node*, Node*);
};

string printList(Node*);
string printList(int, int, int&);

int main(int argc, char** argv) {

    linkedList *list = new linkedList();
    vector<string> expressions;
    
    string expression, unprocessPoly1, unprocessPoly2;
    int coefficient, exponent, counter = 0;

    ifstream inFile;
    inFile.open(argv[1]);
    ofstream outFile(argv[2]);

    while(getline(inFile,expression)) {
        expressions.push_back(expression);
    }

    for(int i = 0; i < expressions.size(); i+=2) {
        unprocessPoly1 = "", unprocessPoly2 = "";
        istringstream polynomial1(expressions[i]);
        list = new linkedList();

        while(polynomial1 >> coefficient >> exponent) {
            Node *newNode1 = new Node(coefficient,exponent);
            list->insertNewNode(newNode1);
            unprocessPoly1 += printList(coefficient, exponent, counter);
            counter++;
        }

        polynomial1.clear();
        counter = 0;
        Node *headNode1 = list->getHead();
        Node* node1 = list->simplify(headNode1);

        list = new linkedList();
        istringstream polynomial2(expressions[i+1]);
        
        while(polynomial2 >> coefficient >> exponent) {
            Node *newNode2 = new Node(coefficient,exponent);
            list->insertNewNode(newNode2);
            unprocessPoly2 += printList(coefficient, exponent, counter);
            counter++;
        }
    
        polynomial2.clear();
        counter = 0;
        Node *headNode2 = list->getHead();
        Node* node2 = list->simplify(headNode2);

        outFile << "Polynomial 1 given" << endl;
        outFile << unprocessPoly1 << endl << endl;

        outFile << "Polynomial 1 simplified" << endl;
        outFile << printList(node1) << endl << endl;

        outFile << "Polynomial 2 given" << endl;
        outFile << unprocessPoly2 << endl << endl;

        outFile << "Polynomial 2 simplified" << endl;
        outFile << printList(node2) << endl << endl;

        outFile << "Polynomial 1 + Polynomial 2" << endl;
        outFile << printList(list->add(node1,node2)) << endl << endl;

        outFile << "Polynomial 1 - Polynomial 2" << endl;
        outFile << printList(list->subtract(node1,node2)) << endl << endl;

        outFile << "Polynomial 1 * Polynomial 2" << endl;
        outFile << printList(list->multiply(node1,node2)) << endl << endl << endl;
    }

    inFile.close();
    outFile.close();

    return 0;
}

Node::Node() {
    this->coefficient = INT_MAX;
    this->exponent = INT_MAX;
    this->next = NULL;
}

Node::Node(int coefficient, int exponent) {
    this->coefficient = coefficient;
    this->exponent = exponent;
    this->next = NULL;
}

Node::Node(const Node &polynomial1) {
    exponent = polynomial1.exponent;
    coefficient = polynomial1.coefficient;
}

void Node::setNext(Node *newNext) {
    next = newNext;
}

Node::~Node() {
    delete next;
}

linkedList::linkedList() {
    listHead = new Node();
}

linkedList::~linkedList() {
    Node* current = listHead;
    Node* next = NULL;

    while(current != NULL) {
        next = current->next;
        delete current;
        current = next;
    }

    current = next = listHead = NULL;
}

Node* linkedList::getHead() {
    Node *newHead = listHead->next;
    return newHead;
}

Node* linkedList::findSpot(Node const* listHead, Node* newNode)
{
	Node* spot = (Node*)listHead;
	while(spot->next != NULL)
	{	
		if(spot->next != NULL && spot->next->exponent >= newNode->exponent)
			spot = spot->next;
		else
			return spot;
	}
	return spot;
}

void linkedList::clear() {
    listHead = new Node();
}

void linkedList::insertNewNode(Node* newNode)
{
	Node* temp = findSpot(listHead, newNode);
	newNode->next = temp->next;
	temp->next = newNode;
}

string printList(int coefficient, int exponent, int& counter) {
    string polynomial = "";

    if(counter == 0) {
        
        if(coefficient == 1 && (exponent < 0 || exponent > 1) ) {
            polynomial += "x^" + to_string(exponent);
        }

        else if(coefficient == 1 && exponent == 1) {
            polynomial += "x";
        }

        else if( (coefficient < 0 || coefficient > 1)
                                && 
            (exponent < 0 || exponent > 1) ) {

            polynomial += to_string(coefficient) + "x^" + to_string(exponent);
        }

        else if( (coefficient < 0 || coefficient > 1) 
                                && 
                (exponent == 0) ) {

            polynomial += to_string(coefficient);
        } 

        else if( (coefficient < 0 || coefficient > 1) 
                                && 
                (exponent == 1) ) {

            polynomial += to_string(coefficient) + "x";
        }

        else if(coefficient == 0){
            polynomial += "";
        }
    }
        
    else {

        if(coefficient == 1 && (exponent < 0 || exponent > 1) )
            polynomial += "+x^" + to_string(exponent);

        else if(coefficient == 1 && exponent == 1) {
            polynomial += "+x";
        }

        else if( (coefficient < 0 || coefficient > 1)
                                && 
            (exponent < 0 || exponent > 1) ) {

            if(coefficient < 0) 
                polynomial += to_string(coefficient) + "x^" + to_string(exponent);
            
            else 
                polynomial += "+" + to_string(coefficient) + "x^" + to_string(exponent);
        }

        else if( (coefficient < 0 || coefficient > 1) 
                                && 
                (exponent == 0) ) {

            if(coefficient < 0) 
                polynomial += to_string(coefficient);
            
            else 
                polynomial += "+" + to_string(coefficient);
            
        } 

        else if( (coefficient < 0 || coefficient > 1) 
                                && 
                (exponent == 1) ) {

            if(coefficient < 0) 
                polynomial += to_string(coefficient) + "x";
        
            else 
                polynomial += "+" + to_string(coefficient) + "x";
        }

        else if(coefficient == 0)
            polynomial += "";
    }

    return polynomial;
}

string printList(Node *nodeHead) {

    string polynomial = "";

    if(nodeHead == NULL) {
        polynomial += "Empty list \n";
        return polynomial;
    }

    Node *current = nodeHead;

    if(current->coefficient == 1 && (current->exponent < 0 || current->exponent > 1) ) {
        polynomial += "x^" + to_string(current->exponent);
        current = current->next;
    }

    else if(current->coefficient == 1 && current->exponent == 1) {
        polynomial += "x";
        current = current->next;
    }

    else if( (current->coefficient < 0 || current->coefficient > 1)
                            && 
        (current->exponent < 0 || current->exponent > 1) ) {

        polynomial += to_string(current->coefficient) + "x^" + to_string(current->exponent);
        current = current->next;
    }

    else if( (current->coefficient < 0 || current->coefficient > 1) 
                            && 
            (current->exponent == 0) ) {

        polynomial += to_string(current->coefficient);
        current = current->next;
    } 

    else if( (current->coefficient < 0 || current->coefficient > 1) 
                            && 
            (current->exponent == 1) ) {

        polynomial += to_string(current->coefficient) + "x";
        current = current->next;
    }

    else if(current->coefficient == 0){
        polynomial += "";
        current = current->next;
    }
        
    while(current != NULL) {

        if(current->coefficient == 1 && (current->exponent < 0 || current->exponent > 1) )
            polynomial += "+x^" + to_string(current->exponent);

        else if(current->coefficient == 1 && current->exponent == 1) {
            polynomial += "+x";
            current = current->next;
        }

        else if( (current->coefficient < 0 || current->coefficient > 1)
                                && 
            (current->exponent < 0 || current->exponent > 1) ) {

            if(current->coefficient < 0) 
                polynomial += to_string(current->coefficient) + "x^" + to_string(current->exponent);
            
            else 
                polynomial += "+" + to_string(current->coefficient) + "x^" + to_string(current->exponent);
        }

        else if( (current->coefficient < 0 || current->coefficient > 1) 
                                && 
                (current->exponent == 0) ) {

            if(current->coefficient < 0) 
                polynomial += to_string(current->coefficient);
            
            else 
                polynomial += "+" + to_string(current->coefficient);
            
        } 

        else if( (current->coefficient < 0 || current->coefficient > 1) 
                                && 
                (current->exponent == 1) ) {

            if(current->coefficient < 0) 
                polynomial += to_string(current->coefficient) + "x";
        
            else 
                polynomial += "+" + to_string(current->coefficient) + "x";
        }

        else if(current->coefficient == 0)
            polynomial += "";

        if(current) {
            current = current->next;
        }
    }

    return polynomial;
}

Node* linkedList::simplify(Node* head) {
    if(head == NULL)
        return NULL;

    Node *current = head;
    Node *newNode = new Node();
    Node *newHead = newNode;
    int coefficentSum, maxExponent;

    if(current != NULL) {
        coefficentSum = current->coefficient;
        maxExponent = current->exponent;
    }

    while(current->next != NULL) {
        if(maxExponent == current->next->exponent) {
            coefficentSum += current->next->coefficient;
            current = current->next;
        }

        if(current->next != NULL) {
            if(maxExponent > current->next->exponent) {
                newNode->coefficient = coefficentSum;
                newNode->exponent = current->exponent;

                Node *simplify = new Node();
                newNode->next = simplify;
                newNode = newNode->next;

                maxExponent = current->next->exponent;
                coefficentSum = current->next->coefficient; // update sum
                current = current->next;
            }
        }
    }

    newNode->coefficient = coefficentSum;
    newNode->exponent = current->exponent;

    return newHead;
}

Node* linkedList::add(Node* polynomial1, Node* polynomial2) {
    Node* sum = new Node();
    Node* sumHead = sum;
    Node* polynomial01 = polynomial1;
    Node* polynomial02 = polynomial2;
    bool isLastNodeJunk = true;

    if(polynomial01->next == NULL || polynomial02->next == NULL)
        isLastNodeJunk = false;

    while( (polynomial01 != NULL) && (polynomial02 != NULL) ) {
        // If power of 1st polynomial is greater then 2nd, then store 1st as it is 
        // and move its pointer 

        if(polynomial01->exponent > polynomial02->exponent) {
            sum->exponent = polynomial01->exponent;
            sum->coefficient = polynomial01->coefficient;
            polynomial01 = polynomial01->next;
        }

        // If power of 2nd polynomial is greater then 1st, then store 2nd as it is 
        // and move its pointer 
        else if(polynomial01->exponent < polynomial02->exponent){ 
            sum->exponent = polynomial02->exponent; 
            sum->coefficient = polynomial02->coefficient; 
            polynomial02 = polynomial02->next; 
        } 

        // If power of both polynomial numbers is same then add their coefficients 
        else if(polynomial01->exponent == polynomial02->exponent){ 
            sum->exponent = polynomial01->exponent; 
            sum->coefficient = polynomial01->coefficient+polynomial02->coefficient; 
            polynomial01 = polynomial01->next; 
            polynomial02 = polynomial02->next; 
        }

        // Dynamically create new Node then traverse to the next node
        Node *newNode = new Node();
        sum->next = newNode;
        sum = sum->next;
    }

    while( (polynomial01 != NULL) || (polynomial02 != NULL) ) {
        if(polynomial01 != NULL) {
            sum->exponent = polynomial01->exponent;
            sum->coefficient = polynomial01->coefficient;
            polynomial01 = polynomial01->next;
        }

        else if(polynomial02 != NULL) {
            sum->exponent = polynomial02->exponent;
            sum->coefficient = polynomial02->coefficient;
            polynomial02 = polynomial02->next;
        }

        Node *newNode = new Node();
        sum->next = newNode;
        sum = sum->next;
    }

    if( (polynomial01 != NULL && polynomial02 != NULL)
                        &&
        (polynomial01->exponent == polynomial02->exponent) ) {
            sum->exponent = polynomial01->exponent;
            sum->coefficient = polynomial01->coefficient + polynomial02->coefficient;
        }

    else if( (polynomial01 != NULL)
                        &&
        (polynomial01->exponent != polynomial02->exponent) ) {
        sum->exponent = polynomial01->exponent;
        sum->coefficient = polynomial01->coefficient;
    }
    
    else if( (polynomial02 != NULL)
                        &&
        (polynomial01->exponent != polynomial02->exponent) ) {
        sum->exponent = polynomial02->exponent;
        sum->coefficient = polynomial02->coefficient;
    }

    if(isLastNodeJunk == true)
        removeLastNode(sumHead);
    
    return removeLastNode(sumHead);
}

Node* linkedList::multiply(Node *polynomial1, Node *polynomial2) {
    Node *current = new Node();
    Node *newHead = current;
    Node *startOfPoly1 = polynomial1;
    Node *startOfPoly2 = polynomial2;


    while(startOfPoly1 != NULL) {
        while(startOfPoly2 != NULL) {
            current->exponent = startOfPoly2->exponent + startOfPoly1->exponent;
            current->coefficient = startOfPoly2->coefficient * startOfPoly1->coefficient;

            startOfPoly2 = startOfPoly2->next;

            Node *newNode = new Node();
            current->next = newNode;
            current = current->next;
        }
        startOfPoly1 = startOfPoly1->next;
        startOfPoly2 = polynomial2;
    }
    
    return simplify(removeLastNode(newHead));
}

Node* linkedList::removeLastNode(Node *head) 
{ 
    if (head == NULL) 
        return NULL; 
  
    if (head->next == NULL) { 
        delete head; 
        return NULL; 
    } 
  
    // Find the second last node 
    Node* second_last = head; 
    while (second_last->next->next != NULL) 
        second_last = second_last->next; 
  
    // Delete last node 
    delete (second_last->next); 
  
    // Change next of second last 
    second_last->next = NULL; 
  
    return head; 
} 

Node* linkedList::subtract(Node *polynomial1, Node *polynomial2) {
    Node* sum = new Node();
    Node* sumHead = sum;
    Node* polynomial01 = polynomial1;
    Node* polynomial02 = polynomial2;
    bool isLastNodeJunk = true;

    if(polynomial01->next == NULL || polynomial02->next == NULL)
        isLastNodeJunk = false;

    while( (polynomial01 != NULL) && (polynomial02 != NULL) ) {
        // If power of 1st polynomial is greater then 2nd, then store 1st as it is 
        // and move its pointer 

        if(polynomial01->exponent > polynomial02->exponent) {
            sum->exponent = polynomial01->exponent;
            sum->coefficient = polynomial01->coefficient;
            polynomial01 = polynomial01->next;
        }

        // If power of 2nd polynomial is greater then 1st, then store 2nd as it is 
        // and move its pointer 
        else if(polynomial01->exponent < polynomial02->exponent){ 
            sum->exponent = polynomial02->exponent; 
            sum->coefficient = polynomial02->coefficient; 
            polynomial02 = polynomial02->next; 
        } 

        // If power of both polynomial numbers is same then add their coefficients 
        else if(polynomial01->exponent == polynomial02->exponent){ 
            sum->exponent = polynomial01->exponent; 
            sum->coefficient = polynomial01->coefficient - polynomial02->coefficient; 
            polynomial01 = polynomial01->next; 
            polynomial02 = polynomial02->next; 
        }

        // Dynamically create new Node then traverse to the next node
        Node *newNode = new Node();
        sum->next = newNode;
        sum = sum->next;
    }

    while( (polynomial01 != NULL) || (polynomial02 != NULL) ) {
        if(polynomial01 != NULL) {
            sum->exponent = polynomial01->exponent;
            sum->coefficient = polynomial01->coefficient;
            polynomial01 = polynomial01->next;
        }

        else if(polynomial02 != NULL) {
            sum->exponent = polynomial02->exponent;
            sum->coefficient = polynomial02->coefficient;
            polynomial02 = polynomial02->next;
        }

        Node *newNode = new Node();
        sum->next = newNode;
        sum = sum->next;
    }

    if( (polynomial01 != NULL && polynomial02 != NULL)
                        &&
        (polynomial01->exponent == polynomial02->exponent) ) {
            sum->exponent = polynomial01->exponent;
            sum->coefficient = polynomial01->coefficient - polynomial02->coefficient;
        }

    else if( (polynomial01 != NULL)
                        &&
        (polynomial01->exponent != polynomial02->exponent) ) {
        sum->exponent = polynomial01->exponent;
        sum->coefficient = polynomial01->coefficient;
    }
    
    else if( (polynomial02 != NULL)
                        &&
        (polynomial01->exponent != polynomial02->exponent) ) {
        sum->exponent = polynomial02->exponent;
        sum->coefficient = polynomial02->coefficient;
    }
    
    if(isLastNodeJunk == true)
        removeLastNode(sumHead);

    return removeLastNode(sumHead);
}