#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include "redismodule.h"

#define OPERATOR_COMMAND 0
#define OPERATOR_PIPE 1
#define OPERATOR_CHAIN 2

typedef struct ArgsListNode {
    RedisModuleString *arg;
    struct ArgsListNode *next;
} ArgsListNode;

typedef struct ArgsList {
    size_t len;
    ArgsListNode *head;
    ArgsListNode *tail;
} ArgsList;

typedef struct CommandListNode {
    int operator;
    RedisModuleString *commandName;
    ArgsList *args;
    struct CommandListNode *next;
} CommandListNode;

typedef struct CommandList {
    size_t len;
    CommandListNode *head;
    CommandListNode *tail;
} CommandList;

CommandList *newCommandList();
void pushCommand(CommandList *list, int operator, RedisModuleString *commandName, ArgsList *args);
void freeCommandList(CommandList *list);
ArgsList *newArgsList();
void pushArg(ArgsList *list, RedisModuleString *arg);
void freeArgList(ArgsList *list);
#endif