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
public class EventLocationPredicate extends EventPredicate {
    private final int tag;
    private final long classId;
    private final long methodId;
    private final long index;

    public EventLocationPredicate(int modifier, int tag, long classId, long methodId, long index) {
        super(modifier);
        this.tag = tag;
        this.classId = classId;
        this.methodId = methodId;
        this.index = index;
    }

    public long classId() {
        return classId;
    }

    public long methodId() {
        return methodId;
    }

    public long index() {
        return index;
    }

    @Override
    public boolean test(EventData eventData) {
        /*
        VmStackTrace location = eventData.getStoppeedLocation();
        if (location == null)
            return false;
        return classId == location.classInfo().refId() && methodId == location.methodInfo().refId() &&
                index == location.lineNumber();
        */
        throw new UnsupportedOperationException();
    }

    @Override
    public String toString() {
        return "Location{" + "classId=" + classId + ", methodId=" + methodId + ", index=" + index +"} ";
    }
}