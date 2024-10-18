using System;

namespace SafeZoneDetectorDemo
{
    class Program
    {
        static void Main(string[] args)
        {
            var detector = new SafeZoneDetector.Detector();

            if (detector.IsAnyVirtualEnvironment())
            {
                Console.WriteLine("Virtual environment detected!");
            }
            else
            {
                Console.WriteLine("No virtual environment detected.");
            }
            // wait for input
            Console.ReadLine();
        }
    }
}
