using System;
using System.Threading;

namespace A3_3
{
    class Program
    {
        static void Main(string[] args)
        {
            // first thread
            var thread1 = new Thread(
                delegate ()
                {
                    for (int i = 0; i < 10; ++i)
                    {
                        Console.WriteLine("#1 Something " + i + " works in delegate()");
                        Thread.Sleep(10);
                    }
                }
            );

            thread1.Start();

            // second thread
            var thread2 = new Thread(
                delegate (object value)
                {
                    for (int i = 0; i < 10; ++i)
                    {
                        Console.WriteLine("#2 Something " + i + " works in delegate(object)" + value);
                        Thread.Sleep(10);
                    }
                }
            );

            thread2.Start("...");

            Console.WriteLine("Main thread done.");
            Console.ReadLine();

        }
    }
}
