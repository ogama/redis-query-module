#include "executor.h"

int execute(RedisModuleCtx *ctx, CommandList *list) {
    CommandListNode *commandToExecute = list->head;
    RedisModuleCallReply *reply = NULL;
    while (commandToExecute != NULL) {
        if (commandToExecute->operator == OPERATOR_COMMAND) {
            char *fmt = RedisModule_Alloc(sizeof (char) * commandToExecute->args->len);
            RedisModuleString **arguments = RedisModule_Alloc(sizeof (RedisModuleString*) * commandToExecute->args->len);
            ArgsListNode *arg = commandToExecute->args->head;
            int i = 0;
            while (arg != NULL) {
                fmt[i] = 's';
                arguments[i] = arg->arg;
                i++;
                arg = arg->next;
            }
            fmt[i] = '\0';
            const char *commandStr = RedisModule_StringPtrLen(commandToExecute->commandName, NULL);
            if (commandToExecute->args->len == 0) {
                reply = RedisModule_Call(ctx, commandStr, "");
            }
            if (commandToExecute->args->len == 1) {
                reply = RedisModule_Call(ctx, commandStr, fmt, arguments[0]);
            }
            if (commandToExecute->args->len == 2) {
                reply = RedisModule_Call(ctx, commandStr, fmt, arguments[0], arguments[1]);
            }
        }
        commandToExecute = commandToExecute->next;
    }
    return RedisModule_ReplyWithCallReply(ctx, reply);
}
