#include "linked-list.h"
#include "redismodule.h"

CommandList *newCommandList() {
    CommandList *list = RedisModule_Alloc(sizeof (CommandList));
    list->len = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

CommandListNode *newCommandListNode(int operator, RedisModuleString *commandName, ArgsList *args) {
    CommandListNode *node = RedisModule_Alloc(sizeof (CommandListNode));
    node->operator = operator;
    node->commandName = commandName;
    node->args = args;
    node->next = NULL;
    return node;
}

void pushCommand(CommandList *list, int operator, RedisModuleString *commandName, ArgsList *args) {
    CommandListNode *node = newCommandListNode(operator, commandName, args);
    if (list->head == NULL) {
        list->head = node;
    }
    if (list->tail == NULL) {
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->len++;
}

void freeCommandList(CommandList *list) {
    CommandListNode *node = list->head;
    while (node != NULL) {
        freeArgList(node->args);
        RedisModule_Free(node->commandName);
        node = node->next;
    }
    RedisModule_Free(list);
}

ArgsList *newArgsList() {
    ArgsList *list = RedisModule_Alloc(sizeof (ArgsList));
    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
    return list;
}

ArgsListNode *newArgsListNode(RedisModuleString *arg) {
    ArgsListNode *node = RedisModule_Alloc(sizeof (ArgsListNode));
    node->arg = arg;
    node->next = NULL;
    return node;
}

void pushArg(ArgsList *list, RedisModuleString *arg) {
    ArgsListNode *node = newArgsListNode(arg);
    if (list->head == NULL) {
        list->head = node;
    }
    if (list->tail == NULL) {
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->len++;
}

void freeArgList(ArgsList *list) {
    ArgsListNode *node = list->head;
    while (node != NULL) {
        RedisModule_Free(node->arg);
        node = node->next;
    }
}
