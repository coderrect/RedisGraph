/*
 * Copyright 2018-2019 Redis Labs Ltd. and Contributors
 *
 * This file is available under the Apache License, Version 2.0,
 * modified with the Commons Clause restriction.
 */

#ifndef SERIALIZE_GRAPH_H
#define SERIALIZE_GRAPH_H

#include "../../redismodule.h"
#include "../../schema/schema.h"

void RdbLoadGraph(RedisModuleIO *rdb, Graph *g, Schema *ns, Schema *es);
void RdbSaveGraph(RedisModuleIO *rdb, void *value, Schema *ns, Schema *es);

#endif
