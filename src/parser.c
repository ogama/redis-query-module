#include "parser.h"

CommandList *parse(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModuleString *pipe = RedisModule_CreateString(ctx, "|", 1);
    RedisModuleString *chain = RedisModule_CreateString(ctx, ";", 1);
    CommandList *list = newCommandList();
    int i = 1;
    while (i < argc) {
        if (RedisModule_StringCompare(argv[i], pipe) == 0) {
            i++;
            pushCommand(list, OPERATOR_PIPE, argv[i], newArgsList());
        } else if (RedisModule_StringCompare(argv[i], chain) == 0) {
            i++;
            pushCommand(list, OPERATOR_CHAIN, argv[i], newArgsList());
        } else {
            if (list->len == 0 || list->tail->operator != OPERATOR_COMMAND) {
                pushCommand(list, OPERATOR_COMMAND, argv[i], newArgsList());
                i++;
            } else {
                pushArg(list->tail->args, argv[i]);
                i++;
            }
        }
    }
    return list;
}