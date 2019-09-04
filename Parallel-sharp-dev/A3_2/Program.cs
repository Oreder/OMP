using System;
using System.Threading;

namespace A3_2
{
    class Program
    {
        static void Main(string[] args)
        {
            // Way 1: Create a new ThreadStart to wrap a static method (WITHOUT PARAMETERS)
            // We use ThreadStart as a delegated object to execute a method 
            ThreadStart threadStart1 = new ThreadStart(Work);

            // Create a thread to wrap threadStart1
            Thread thread1 = new Thread(threadStart1);

            // Now run thread
            thread1.Start();

            // Way 2: Create a new ThreadStart to wrap a non-static method
            // Remember that ThreadStart can only wrap a non-parameter method
            var p = new Person("Perry");
            ThreadStart threadStart2 = new ThreadStart(p.Run);

            // Next step let create a new thread to wrap it
            Thread thread2 = new Thread(threadStart2);

            // Start thread
            thread2.Start();

            Console.WriteLine("Main thread ends");
            Console.ReadLine();
        }

        private static void Work()
        {
            for (int i = 0; i < 10; ++i)
            {
                Console.WriteLine("*");
                //Thread.Sleep(100);
            }
        }
    }
}
