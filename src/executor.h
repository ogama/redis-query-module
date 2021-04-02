#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "linked-list.h"

int execute(RedisModuleCtx *ctx, CommandList *list);
#endif
