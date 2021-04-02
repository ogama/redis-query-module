#include "redismodule.h"
#include "parser.h"

int queryCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModule_AutoMemory(ctx);
    CommandList *commands = parse(ctx, argv, argc);

    return RedisModule_ReplyWithSimpleString(ctx, "OK");
}

int RedisModule_OnLoad(RedisModuleCtx *ctx) {
    if (RedisModule_Init(ctx, "query", 1, REDISMODULE_APIVER_1) == REDISMODULE_ERR) {
        return REDISMODULE_ERR;
    }
    if (RedisModule_CreateCommand(ctx, "query", queryCommand, "write", 1, 1, 1) == REDISMODULE_ERR) {
        return REDISMODULE_ERR;
    }
    return REDISMODULE_OK;
}