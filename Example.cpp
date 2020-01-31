#include "Processing.h"

class Pr:public Processing{
    public:
        Pr():Processing(100,100,"A"){};
    void setup(){

    }
    void draw(){
        stroke(255);
        line(0,0,width,height);
    }
};
int main(){
    Pr().run();
}