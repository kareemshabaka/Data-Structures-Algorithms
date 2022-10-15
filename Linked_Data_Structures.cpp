//Kareem Shabaka 400294647
#include <iostream>
#include <math.h>

using namespace std;
class Term
{
    public:
        Term(int c=0, int e=0) : coef(c), exp(e) {}
        int coef;
        int exp;
};

typedef Term Elem;				// list element type Term
class DNode {					    // doubly linked list node
    private:
        Elem elem;					// node element value
        DNode* prev;				// previous node in list
        DNode* next;				// next node in list
        friend class DLinkedList;	// allow DLinkedList access
        friend class Polynomial;
        
};

class DLinkedList {				// doubly linked list
    public:
        DLinkedList();				// constructor
        ~DLinkedList();				// destructor
        bool empty() const;				// is list empty?
        const Elem& front() const;			// get front element
        const Elem& back() const;			// get back element
        void addFront(const Elem& e);		// add to front of list
        void addBack(const Elem& e);		// add to back of list
        void removeFront();				// remove from front
        void removeBack();			// remove from back
        friend class Polynomial;
        
    private:					// local type definitions
        DNode* header;				// list sentinels
        DNode* trailer;
    protected:					// local utilities
        void add(DNode* v, const Elem& e);		// insert new node before v
        void remove(DNode* v);			// remove node v
};

DLinkedList::DLinkedList() {			// constructor
    header = new DNode;				// create sentinels
    trailer = new DNode;
    header->next = trailer;			// have them point to each other
    trailer->prev = header;
}

bool DLinkedList::empty() const		// is list empty?
    { return (header->next == trailer); }

const Elem& DLinkedList::front() const	// get front element
    { return header->next->elem; }

const Elem& DLinkedList::back() const		// get back element
    { return trailer->prev->elem; }

DLinkedList::~DLinkedList() {			// destructor
    while (!empty()) removeFront();		// remove all but sentinels
    delete header;				// remove the sentinels
    delete trailer;
}

void DLinkedList::remove(DNode* v) {		// remove node v
    DNode* u = v->prev;				// predecessor
    DNode* w = v->next;				// successor
    u->next = w;				// unlink v from list
    w->prev = u;
    delete v;
}

void DLinkedList::removeFront()		// remove from font
    { remove(header->next); }
  
void DLinkedList::removeBack()		// remove from back
    { remove(trailer->prev); }

void DLinkedList::add(DNode* v, const Elem& e) { // insert new node before v
    DNode* u = new DNode;  
    u->elem = e;		// create a new node for e
    u->next = v;				// link u in between v
    u->prev = v->prev;				// ...and v->prev
    v->prev->next = u;
    v->prev = u;
  }

void DLinkedList::addFront(const Elem& e)	// add to front of list
    { add(header->next, e); }
  
void DLinkedList::addBack(const Elem& e)	// add to back of list
    { add(trailer, e); }


class Polynomial {

    private:
        DLinkedList list;

    public:
        Polynomial();
        void insertTerm(int c,int e);
        string toString();
        double eval(double x);
        friend ostream & operator << (ostream& out, Polynomial& poly);
        Polynomial& operator+(Polynomial& p2);
        
};

Polynomial::Polynomial(){}

void Polynomial::insertTerm(int c,int e){
    if (e==0){
        list.addBack(Term(c,e));
        return;
    }
    if (c!=0) {
        if (list.empty()) {
            list.addFront(Term(c,e));
        }else{
            DNode* cursor = list.header->next;
            while (cursor->elem.exp>=e){
                if (cursor->elem.exp==e){
                    cursor->elem.coef=c;
                    return;}
                cursor=cursor->next; 
                
            }
            list.add(cursor,Term(c,e));
        }

    }
    
    //cout << list.header->next->elem.exp;
}

string Polynomial::toString() {
    string output = "";
    DNode* cursor = list.header->next->next;
    if (list.header->next->elem.exp==0){
            output+=to_string(list.header->next->elem.coef);
        } else if (list.header->next->elem.exp==1) {
            if (list.header->next->elem.coef!=1){output+=to_string(list.header->next->elem.coef);}
            if (list.header->next->elem.coef==-1){output+="-";}
            output+="x";
        } else {
            if (list.header->next->elem.coef!=1){output+=to_string(list.header->next->elem.coef);}
            if (list.header->next->elem.coef==-1){output+="-";}
            output+="x^";
            output+=to_string(list.header->next->elem.exp);
        }

    while (cursor != list.trailer){
        if (cursor->elem.coef>0){
            output+="+";
        } 
        if (cursor->elem.exp==0){
            output+=to_string(cursor->elem.coef);
        } else if (cursor->elem.exp==1) {
            if (cursor->elem.coef!=1){output+=to_string(cursor->elem.coef);}
            if (cursor->elem.coef==-1){output+="-";}
            output+="x";
        } else {
            if (cursor->elem.coef!=1){output+=to_string(cursor->elem.coef);}
            if (cursor->elem.coef==-1){output+="-";}
            output+="x^";
            output+=to_string(cursor->elem.exp);
        }
        cursor=cursor->next;
    }

    return output;
}

double Polynomial::eval(double x){
    DNode* cursor=list.header->next;
    double sum=0;
    while (cursor!=list.trailer){
        sum+=cursor->elem.coef*pow(x,cursor->elem.exp);
        cursor=cursor->next;
    }
    return sum;
}

istream & operator >> (istream& in, Polynomial& poly){
    int terms;
    cout << "Enter the number of terms: ";
    in >> terms;
    int c,e;
    for (int i=0;i<terms;i++) {
        cout << "Enter c value: ";
        in >> c;
        cout << "Enter e value: ";
        in >> e;
        cout << endl;
        
        poly.insertTerm(c,e);
    }
    return in;
}

ostream & operator << (ostream& out, Polynomial& poly){
    out << poly.toString();
    return out;
}


Polynomial& Polynomial::operator+(Polynomial& p2) {
    
    Polynomial* p3 = new Polynomial;

    DNode* cursor1= list.header->next;
    DNode* cursor2= p2.list.header->next;

    while (cursor1 !=list.trailer || cursor2 !=p2.list.trailer) {
        if (cursor1==list.trailer){
            p3->insertTerm(cursor2->elem.coef,cursor2->elem.exp);
            cursor2=cursor2->next;
        }
        else if (cursor2==p2.list.trailer) {
            p3->insertTerm(cursor1->elem.coef,cursor1->elem.exp);
            cursor1=cursor1->next;
        } else {
            if (cursor1->elem.exp == cursor2->elem.exp) {
                p3->insertTerm(cursor1->elem.coef+cursor2->elem.coef,cursor1->elem.exp);
                cursor1=cursor1->next;
                cursor2=cursor2->next;
            }
            else if (cursor1->elem.exp > cursor2->elem.exp) {
                p3->insertTerm(cursor1->elem.coef,cursor1->elem.exp);
                cursor1=cursor1->next;
            }
            else if (cursor2->elem.exp > cursor1->elem.exp) {
                p3->insertTerm(cursor2->elem.coef,cursor2->elem.exp);
                cursor2=cursor2->next;
            }   
        }
        
    }
    
    return *p3;
 
}

int main() {
    
    
}