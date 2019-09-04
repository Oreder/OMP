using System;
using System.Threading;

namespace A3_6
{
    class Program
    {
        static void Main(string[] args)
        {
            var childThread = new Thread(
                delegate (object times)
                {
                    for (int i = 0; i < (int)times; ++i)
                    {
                        Console.WriteLine(Thread.CurrentThread.Name + " is working at " + i);
                        Thread.Sleep(50);
                    }
                }
            )
            {
                Name = "Child"
            };

            Thread.CurrentThread.Name = "Father";

            childThread.Start(20);

            // By using JOIN method, child thread announced that father thread (here is Main)
            // should wait until child finishes it's job.
            childThread.Join();

            Console.WriteLine(Thread.CurrentThread.Name + " finished.");
            Console.ReadLine();
        }
    }
}
