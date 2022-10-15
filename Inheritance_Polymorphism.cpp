//Kareem Shabaka 400294647

#include <iostream>
#include <math.h>

using namespace std;

class Stats {
    protected:
        int length;
        int max;
        int* array1 = new int[length];

        double mean;
        double stdev;

    public:
        Stats(int* arr,int n);
        Stats();


        virtual void computeStats();
        virtual void printStats();

        virtual ~Stats();
};

Stats::Stats(){
    length=0;
    max=0;
}

Stats::Stats(int* arr,int n){
    max = 0;
    length=n;
    for (int i=0;i<n;i++){
        array1[i]=arr[i];
        if (arr[i]>max){
            max=arr[i];
        }
    }
}

void Stats::computeStats(){
    double sum=0;
    for (int i=0;i<length;i++){
        sum+=array1[i];
    }
    mean=sum/length;

    double var=0;
    for (int j=0;j<length;j++){
        var+=pow((array1[j]-mean),2);
    }

    var=var/length;
    stdev=sqrt(var);
}

void Stats::printStats(){
    cout << "mean= " << mean << ", std= " << stdev << endl;
}


Stats::~Stats(){ delete[] array1; }

    
class OneVarStats : public Stats{
    private:
        int histLength;
        int* hist = new int[max+1];

    public:
        OneVarStats(int* arr,int n);

        void computeStats();
        void printStats();

        ~OneVarStats();

};

OneVarStats::OneVarStats(int* arr, int n) : Stats(arr,n) {}

    
void OneVarStats::computeStats(){
    double sum=0;
    for (int i=0;i<length;i++){
        sum+=array1[i];
    }
    mean=sum/length;

    double var=0;
    for (int j=0;j<length;j++){
        var+=pow((array1[j]-mean),2);
    }

    var=var/length;
    stdev=sqrt(var);

    histLength=max+1;
    for (int i=0;i<histLength;i++) {
        int count=0;
        for (int j=0;j<length;j++){
            if (array1[j]==i){ count++; }
        }
        hist[i]=count;
        
    }
}

void OneVarStats::printStats(){
    cout << "mean= " << mean << ", std= " << stdev << endl;
    
    for (int i=0;i<histLength;i++){
        cout << hist[i] << " ";
    }
    cout << endl;
}


OneVarStats::~OneVarStats(){ delete[] hist; }

class TwoVarStats : public Stats {

    protected:
        int* array2 = new int[length];
        double ccf;

    public:
        TwoVarStats(int* arr1, int* arr2, int n);

        double computeCorrCoef();
        void computeStats();
        void printStats();
        ~TwoVarStats();
};

double TwoVarStats::computeCorrCoef() {  // works on array1 and array2 and count
    double sumX = 0.0, sumY = 0.0, sumXY = 0.0;  // hold S(x), S(y), S(xy) respectively.
    double sumX2 = 0.0, sumY2 = 0.0;  // hold S(x^2), S(y^2) respectively.
    
    for (int i=0; i< length; i++){
        sumX += array1[i];
        sumY += array2[i];
        sumXY += array1[i] * array2[i];

        sumX2 += array1[i] *  array1[i];
        sumY2 += array2[i] *  array2[i];
    } 
    double corr_coef = (length * sumXY - sumX * sumY)/ (sqrt((length * sumX2 - sumX * sumX) * (length * sumY2 -  sumY * sumY))); 

    return corr_coef;
}


TwoVarStats::TwoVarStats(int* arr1, int* arr2, int n) : Stats(arr1,n) {
    for (int i=0;i<n;i++){
        array2[i]=arr2[i];
    }
}

void TwoVarStats::computeStats() {
    double sum=0;
    for (int i=0;i<length;i++){
        sum+=array1[i];
    }
    mean=sum/length;

    double var=0;
    for (int j=0;j<length;j++){
        var+=pow((array1[j]-mean),2);
    }

    var=var/length;
    stdev=sqrt(var);

    ccf = computeCorrCoef();

}

void TwoVarStats::printStats() {
    cout << "mean= " << mean << ", std= " << stdev << endl << "corr coef= " << ccf << endl;
    
}

TwoVarStats::~TwoVarStats(){ delete[] array2; }

int main(){
    int x[] = {2, 4, 7, 11, 5};
    int y[] = {5, 9, 14, 20, 10};
    int z[] = {14, 7, 4, 9, 21};
    int stats_len = 4;
    Stats* pp[stats_len];
    pp[0] = new Stats(x, 5);
    pp[1] = new OneVarStats (x, 5);
    pp[2] = new TwoVarStats (x, y, 5);
    pp[3] = new TwoVarStats (y, z, 5);
    for (int i=0; i < stats_len; i++){
        pp[i]->computeStats();
        cout << "\n";
    }
    for (int i=0; i < stats_len; i++){
        pp[i]->printStats();
        cout << "\n";
    }

    return EXIT_SUCCESS;
}