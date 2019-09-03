using System;
using System.Threading;

namespace A3_1
{
    class Worker
    {
        private readonly string name;
        private readonly int loop;

        public Worker(string name, int loop)
        {
            this.name = name;
            this.loop = loop;
        }

        public void DoWork(object value)
        {
            for (int i = 0; i < loop; i++)
            {
                Console.WriteLine(name + " working " + value);
                Thread.Sleep(50);
            }
        }
    }
}
