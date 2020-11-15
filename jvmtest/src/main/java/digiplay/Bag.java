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

package digiplay;

/**
 *
 * @author mustafa
 */
public class Bag<T> {
    
    private T[] items;
    private int size;
    
    public Bag() {
        this(16);
    }
    
    public Bag(int capacity) {
        items = (T[])new Object[capacity];
    }
    
    public int getSize() {
        return size;
    }
    
    public void setSize(int size) {
        this.size = size;
    }
    
    public T get(int index) {
        return items[index];
    }
    
    public T getAndClear(int index) {
        T value = items[index];
        items[index] = null;
        return value;
    }
    
    public void add(T item) {
        if(size == items.length) {
            T[] tmp = (T[])new Object[items.length * 2];
            System.arraycopy(items, 0, tmp, 0, items.length);
            items = tmp;
        }
        items[size++] = item;
    }
}
