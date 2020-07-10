using System;
using System.Collections.Generic;

namespace Test
{
    public class Test
    {
        /*
        public static List<int> intList;
        public static int intField;
        public static int? deneme;
        
        public static void G<A>(A value)
        {

            if(value is int i)
            {
                Console.Write(i*12);
            }
            Console.Write(default(A));
        }
        */
        static int T(int i) => 12 * i;

        public static int TestMe()
        {
            var r = 0d;
            for (int i = 0; i < 1000000; i++)
            {
                r += i;
            }
            return (int)r;
            /*
            var t = new Gen<int>(10);
            var v = 120;
            t.set(v);
            var t2 = new Gen<string>(10);
            t2.set("mustafa");


            /*
            var y = 0;
            for(int i=0; i<20; i++)
            {
                int x = 120 * i;
                y += x;
            }

            for(int i=0; i<20; i++)
            {
                var x = i * 90;
                y += x;
            }*/
        }
    }
}
