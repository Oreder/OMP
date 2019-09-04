using System;
using System.Threading;

namespace A3_2
{
    class Person
    {
        private readonly string name;
        public Person(string name)
        {
            this.name = name;
        }

        // non-static method without parameters
        public void Run()
        {
            for (int time = 0; time < 5; ++time)
            {
                Console.WriteLine(name + " is running ...");
                Thread.Sleep(50);
            }
        }
    }
}
