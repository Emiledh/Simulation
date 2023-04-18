//
//  main.cpp
//  Radiology project
//
//  Created by Broos  Maenhout on 15/01/2020.
//  Copyright © 2020 Broos  Maenhout. All rights reserved.
//


#include "general.h"

personnel *MyActivityPtr;


int main(int argc, const char * argv[]) {

    MyActivityPtr=new personnel;        // initalisation
    srand(100);//time(NULL));        // seed initialisation => fixed/variable
    MyActivityPtr->procedure();          // call of procedure

    delete MyActivityPtr;

    return 0;

}

