/*
 * Copyright (C) 2019 Digitoy Games.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.cava.debugger.handler.eventrequest.events.predicates;

import com.cava.debugger.handler.eventrequest.events.EventData;

/**
 *
 * @author mustafa
 */
public class EventStepModPredicate extends EventPredicate {
    private final long threadId;
    private final int size;
    private final int depth;

    public EventStepModPredicate(int modifier, long threadId, int size, int depth) {
        super(modifier);
        this.threadId = threadId;
        this.size = size;
        this.depth = depth;
    }

    public long threadId() {
        return threadId;
    }

    public int size() {
        return size;
    }

    public int depth() {
        return depth;
    }

    @Override
    public String toString() {
        return "step{" + "threadId=" + threadId + ", size=" + size + ", depth=" + depth + "} ";
    }

    @Override
    public boolean test(EventData eventData) {
        return false;
    }
}
