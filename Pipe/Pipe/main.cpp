//
//  main.cpp
//  Pipe
//
//  Created by Haochen Wang on 5/10/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//

#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <fstream>
#include <unistd.h>

void pipe(std::string &input_string){
    int pip[2], pid;
    char instring[100];
    (void)pipe(pip);
    while (true) {
        pid=fork();
        if (pid==0) {
            std::cout<<"Writing string: "<<input_string<<std::endl;
            write(pip[1], &input_string, input_string.size());
        }else{
            std::cout<<"Reading string: "<<input_string<<std::endl;
            read(pip[0], instring, input_string.size());
        }
    }
    
}

int main(int argc, const char * argv[]) {
    std::string instring="Hello";
    pipe(instring);
    return 0;
}
