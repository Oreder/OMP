using System;
using System.Threading;

namespace A3_5
{
    class Program
    {
        private static DateTime time1;
        private static DateTime time2;

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
            time1 = DateTime.Now;
            thread1.Start();
            
            time2 = DateTime.Now;
            thread2.Start();

            Console.ReadLine();
        }

        private static void ShowDiffInterval()
        {
            TimeSpan diff = time2 - time1;
            Console.WriteLine("T1 - T2 = " + diff.TotalMilliseconds + " milliseconds");
        }

        private static readonly int MaxIteration = 1000000;     // ONE MILLION

        private static void Work1(object obj)
        {
            for (int i = 0; i < MaxIteration; ++i)
            {
                Console.WriteLine(Thread.CurrentThread.Name + " is working at " + i);
            }

            time1 = DateTime.Now;
            ShowDiffInterval();
        }
    
        private static void Work2(object obj)
        {
            for (int i = 0; i < MaxIteration; ++i)
            {
                Console.WriteLine(Thread.CurrentThread.Name + " is working at " + i);
            }

            time2 = DateTime.Now;
            ShowDiffInterval();
        }
    }
}
