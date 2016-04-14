#ifndef TARANTOOL_BOX_SOPHIA_INDEX_H_INCLUDED
#define TARANTOOL_BOX_SOPHIA_INDEX_H_INCLUDED
/*
 * Copyright 2010-2015, Tarantool AUTHORS, please see AUTHORS file.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * 1. Redistributions of source code must retain the above
 *    copyright notice, this list of conditions and the
 *    following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY <COPYRIGHT HOLDER> ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * <COPYRIGHT HOLDER> OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
 * THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "index.h"
#include "tuple_id.h"

class SophiaIndex: public Index {
public:
	SophiaIndex(struct key_def *key_def);
	virtual ~SophiaIndex() override;

	virtual tuple_id
	replace(tuple_id,
		tuple_id, enum dup_replace_mode);

	virtual tuple_id
	findByKey(const char *key, uint32_t) const;

	virtual struct iterator*
	allocIterator() const;

	virtual void
	initIterator(struct iterator *iterator,
	             enum iterator_type type,
	             const char *key, uint32_t part_count) const override;

	virtual size_t  size() const override;
	virtual size_t bsize() const override;

public:
	void replace_or_insert(const char *tuple,
	                       const char *tuple_end,
	                       enum dup_replace_mode mode);
	void remove(const char *key);
	void upsert(const char *ops,
	            const char *ops_end,
	            const char *tuple,
	            const char *tuple_end,
	            uint8_t index_base);
	void *env;
	void *db;

	void *createDocument(const char *key, const char **keyend);
private:
	struct tuple_format *format;
};

#endif /* TARANTOOL_BOX_SOPHIA_INDEX_H_INCLUDED */
