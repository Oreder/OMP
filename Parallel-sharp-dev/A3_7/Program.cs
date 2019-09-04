using System;
using System.Threading;

namespace A3_7
{
    class Program
    {
        private static DateTime ___importantEndTime;
        private static DateTime nonImportantEndTime;

        static void Main(string[] args)
        {
            // initialize two thread with different priorities
            var thread1 = new Thread(Work1)
            {
                Name = "T1",
                Priority = ThreadPriority.Highest
            };

            var thread2 = new Thread(Work2)
            {
                Name = "T2",
                Priority = ThreadPriority.Lowest
            };

            // set beginning timers and start 2 threads
            ___importantEndTime = DateTime.Now;
            thread1.Start();

            nonImportantEndTime = DateTime.Now;
            thread2.Start();

            Console.ReadLine();
        }

        private static void ShowDiffInterval()
        {
            TimeSpan diff = nonImportantEndTime - ___importantEndTime;
            Console.WriteLine("T1 - T2 = " + diff.TotalMilliseconds + " milliseconds");
        }

        private static readonly int MaxIteration = 10000;     // ONE MILLION

        private static void Work1(object obj)
        {
            for (int i = 0; i < MaxIteration; ++i)
            {
                Console.WriteLine(Thread.CurrentThread.Name + " is working at " + i);

                // By using YIELD method, curent thread NOTIFIES os that
                // it CAN READILY allow another to run on the current processor
                // (which should be its position)
                // Notice that: "Not ensure happening at all cases!"
                Thread.Yield();
            }

            ___importantEndTime = DateTime.Now;
            ShowDiffInterval();
        }

        private static void Work2(object obj)
        {
            for (int i = 0; i < MaxIteration; ++i)
            {
                Console.WriteLine(Thread.CurrentThread.Name + " is working at " + i);
            }

            nonImportantEndTime = DateTime.Now;
            ShowDiffInterval();
        }
    }
}
