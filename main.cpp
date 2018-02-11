#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "CVector.h"

using namespace std;

int main(){
    CVector v1 = CVector(3.0,2.0,1.0);
    cout << "X : " << v1.getX() << "Y :" << v1.getY() << "Z : " << v1.getZ() << endl;
	return 0;
}
