//Kareem Shabaka 400294637
#include <iostream>
#include <math.h>
using namespace std;

class Point {
    public:
        Point();
        Point(int ux, int uy);
        int getX();
        int getY();
        double distanceTo(Point& otherP);
        friend istream & operator >> (istream& in, Point& p);
        friend ostream & operator << (ostream& out, Point& p);
    private:
        int x;
        int y;

};

Point::Point(){
    x=0;
    y=0;
}

Point::Point(int ux,int uy){
    x=ux;
    y=uy;
}

int Point::getX(){
    return x;
}

int Point::getY(){
    return y;
}

double Point::distanceTo(Point& otherP) {
    return sqrt(pow((otherP.getX()-x),2)+pow((otherP.getY()-y),2));
}

istream & operator >> (istream& in, Point& p){
    cout << "Enter x value: ";
    cin >> p.x;
    cout << "Enter y value: ";
    cin >> p.y;
    return in;
}

ostream & operator << (ostream& out, Point& p) {
    cout << "P(" << p.x << "," << p.y << ")";
    return out;
}


class Polygon {
    public:
        Polygon(int size=10);
        Polygon(int size, Point* list);
        double perimeter();
        friend istream & operator >> (istream& in, Polygon& poly);
        friend ostream & operator << (ostream& out, Polygon& poly);
        ~Polygon();
    private:
        int num;
        Point* points;
};

Polygon::Polygon(int size){
    num=size;
    points = new Point[size];
}

Polygon::Polygon(int size, Point* list){
    num=size;
    points = list;
}

Polygon::~Polygon(){
    delete points;
}


double Polygon::perimeter(){
    double sum=0;
    for (int i=0;i<num;i++){
        if (num!=3){
            sum+=points[i].distanceTo(points[i+1]);
        } else {
            sum+=points[i].distanceTo(points[0]);
        }
    }
    return sum;
}



istream & operator >> (istream& in, Polygon& poly){
    for (int i=0;i<poly.num;i++) {
        int x,y;
        cout << "Enter x value: ";
        cin >> x;
        cout << "Enter y value: ";
        cin >> y;
        poly.points[i]=Point(x,y);
    }
    return in;
}

ostream & operator << (ostream& out, Polygon& poly) {
    for (int i=0;i<poly.num;i++){
        cout << poly.points[i] << " ";
    }
    cout << endl;
    return out;
}


int main(){
    Polygon poly1(5);
    Point* points_list = new Point[4];
    points_list[0] = Point(0, 0);
    points_list[1] = Point(0, 1);
    points_list[2] = Point(1, 1);
    points_list[3] = Point(1, 0);
    Polygon rectangle(4, points_list);
    //cout << rectangle.perimeter();
    cout << rectangle;
    return EXIT_SUCCESS;
}