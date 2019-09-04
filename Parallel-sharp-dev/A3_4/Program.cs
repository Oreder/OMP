using System;
using System.Threading;

namespace A3_4
{
    class Program
    {
        static void Main(string[] args)
        {
            Thread.CurrentThread.Name = "Main";

            var lego = new Thread(Lego)
            {
                Name = "LeGo"
            };

            lego.Start();

            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine(Thread.CurrentThread.Name + " is running ...");
                Thread.Sleep(20);
            }

            Console.ReadLine();
        }

        private static void Lego(object obj)
        {
            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine(Thread.CurrentThread.Name + " is running ...");
                Thread.Sleep(50);
            }
        }
    }
}
