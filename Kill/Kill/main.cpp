//
//  main.cpp
//  Kill
//
//  Created by Haochen Wang on 5/10/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//

#include <signal.h>
#include <iostream>

int send_signal(pid_t pid){
    /*Signal name	Signal value	Effect
    SIGHUP	1	Hangup
    SIGINT	2	Interrupt from keyboard
    SIGKILL	9	Kill signal
    SIGTERM	15	Termination signal
    SIGSTOP	17,19,23	Stop the process
     */
    return kill(pid, 9);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int ret=send_signal(6561);
    if(ret>0) std::cout<<"The process whose identifier is pid."<<std::endl;
    else if (ret==0) std::cout<<"All processes in the same process group as the sender."<<std::endl;
    else if (ret==-1) std::cout<<"If the process is privileged, send the signal to all processes except for some special system processes. Otherwise, send the signal to all processes with the same effective user ID."<<std::endl;
    else std::cout<<"The process group whose identifier is -pid."<<std::endl;
    return 0;
}
