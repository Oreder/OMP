using System;
using System.Threading;

namespace A3_1
{
    class Program
    {
        static void Main(string[] args)
        {
            Worker w1 = new Worker("John", 10);

            Thread workerThread1 = new Thread(w1.DoWork);

            workerThread1.Start("A");

            Worker w2 = new Worker("Marry", 15);

            Thread workerThread2 = new Thread(w2.DoWork);

            workerThread2.Start("B");

            Console.Read();
        }
    }
}
