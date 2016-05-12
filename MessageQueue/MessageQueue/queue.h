//
//  queue.h
//  MessageQueue
//
//  Created by Haochen Wang on 5/10/16.
//  Copyright © 2016 Haochen Wang. All rights reserved.
//

#ifndef queue_h
#define queue_h
#include <sys/ipc.h>
#include <sys/msg.h>

class MSGQueue{
    int msgid;  //message id
    int msgflag= IPC_CREAT | 0666;
    key_t key;
    
};

#endif /* queue_h */
