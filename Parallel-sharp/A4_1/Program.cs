using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace A4_1
{
    class Program
    {
        static void Main(string[] args)
        {
            // Test 1: Print by non-static method
            Parallel.ForEach("1234567890", (c, state, i) =>
            {
                Console.Write(c);
            });

            Console.WriteLine();

            // Test 2: Print by static method
            Parallel.ForEach("1234567890", Work);

            Console.WriteLine();

            // Test 3: Find all primes
            var primes = new List<int>();

            Parallel.For(1, 10, (i) =>
            {
                Parallel.For(13, 23, (j) =>
                {
                    int value = i * j - 1;
                    if (isPrime(value) && !primes.Contains(value))
                        primes.Add(value);
                });
            });

            primes.Sort((x, y) => x.CompareTo(y));

            foreach (var p in primes)
            {
                Console.Write(p + " ");
            }
            Console.ReadLine();
        }

        private static bool isPrime(int value)
        {
            bool result = true;
            Parallel.For(2, (int)Math.Sqrt(value) + 1, (t) =>
            {
                if (value % t == 0)
                {
                    result = false;
                    //break;
                }
            });

            return result;
        }

        private static void Work(char arg1, ParallelLoopState arg2, long arg3)
        {
            Console.Write(arg1);
        }
    }
}
