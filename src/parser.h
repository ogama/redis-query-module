#ifndef PARSER_H
#define PARSER_H

#include "linked-list.h"

CommandList *parse(RedisModuleCtx *ctx, RedisModuleString **argv, int argc);

#endif