using System;
using Trik;
using Trik.Devices;
using Trik.Collections;
using System.Threading;

namespace robotParking
{
    class Algo
    {
        bool initialized = false;

        Model model = new Model();
        PowerMotor rightWheel;
        Trik.Sensors.Encoder rightEncoder;

        PowerMotor leftWheel;
        Trik.Sensors.Encoder leftEncoder;

        Trik.Sensors.AnalogSensor infraredSensor;

        long dist;

        long err;

        double k;

        bool placeFound = false;

        PowerMotor wheel1;
        PowerMotor wheel2;
        Trik.Sensors.Encoder encoder1;
        Trik.Sensors.Encoder encoder2;

        int signLeft = -1;
        int signRight = -1;

        int hole = 40;

        private void ini()
        {
            if (initialized) return;
            rightWheel = model.Motor[Motor.M4];
            rightEncoder = model.Encoder[Encoder.B4];

            leftWheel = model.Motor[Motor.M3];
            leftEncoder = model.Encoder[Encoder.B2];

            infraredSensor = model.AnalogSensor[Sensor.A1];

            initialized = true;
        }

        private void dbg(string str)
        {
            Console.WriteLine("Debug: " + str);
        }

        private void alongTheWall()
        {
            //dbg("alongTheWall begin");
            var v = 70;
            k = 1.2;
            dist = infraredSensor.Read();
            while (true)
            {
                int sensor = infraredSensor.Read();
                //dbg("infrared: " + sensor.ToString());
                err = (dist - sensor)/10;
                //dbg("err: " + err.ToString());
                if (!(err <= hole - 20))//!!!!
                {
                    break;
                }
                int u = Convert.ToInt32(k * err);//
                leftWheel.SetPower(signLeft*(v + u));
                rightWheel.SetPower(signRight*(v - u));
                Thread.Sleep(20);
            }
            //dbg("alongTheWall end");
        }

        public void goForward()
        {
            ini();
            //dbg("goForward begin");
            leftEncoder.Reset();
            rightEncoder.Reset();
            leftWheel.SetPower(signLeft*100);
            rightWheel.SetPower(signRight*100);

            //dbg("goForward motor runs " + rightEncoder.Read());
            Thread.Sleep(30);
            while (!(rightEncoder.Read() < 64650))//!!!
            {
                //dbg("encoder: " + rightEncoder.Read().ToString());
                if (((dist - infraredSensor.Read()) / 10) <= hole - 20) return;
                Thread.Sleep(40); //!!! hole detection
            }
            //dbg("goForward end");
            placeFound = true;
        }

        public void parking()
        {
            ini();
            //dbg("parking begin");
            wheel1 = leftWheel;
            wheel2 = rightWheel;
            encoder1 = leftEncoder;
            encoder2 = rightEncoder;
            dbg("first half");
            halfParking();
            dbg("middleMovement");
            middleMovement();
            dbg("second half");
            halfParking();
            dbg("end");
            //dbg("parking end");
        }

        private int encoderAbs(int t)
        {
            return Math.Abs((t >30000 ? (65535 - t) : t));
        }

        private void halfParking()
        {
            //dbg("halfParking begin");
            wheel2.Stop();
            encoder1.Reset();//
            wheel1.SetPower(signLeft*(-100));//!!!
            dbg(encoder1.Read().ToString());
            while (encoderAbs(encoder1.Read()) < 666)//!!!
            {
                dbg(encoder1.Read().ToString());
                Thread.Sleep(50);
            }
            wheel1.Stop();
            //dbg("halfParking end");
        }

        private void middleMovement()
        {
            //dbg("middleMovement begin");
            leftWheel.SetPower(signLeft*(-100));
            rightWheel.SetPower(signRight*(-100));
            Thread.Sleep(500);//700
            wheel1 = rightWheel;
            wheel2 = leftWheel;
            encoder1 = rightEncoder;
            encoder2 = leftEncoder;
            wheel1.Stop();
            wheel2.Stop();
            //dbg("middleMovement end");
        }

        public void start()
        {
            ini();

	        while (true) {
		        if (placeFound) {
			        break;
		        }
		        alongTheWall();
		        goForward();
	        }
	        parking();
        }

        public void test()
        {
            ini();
            dbg("test");
            dbg("lft -100");
            leftWheel.SetPower(-100);
            Thread.Sleep(500);
            dbg("lft 100");
            leftWheel.SetPower(100);
            Thread.Sleep(500);
            leftWheel.SetPower(0);
            dbg("rght -100");
            rightWheel.SetPower(-100);
            Thread.Sleep(500);
            dbg("rght 100");
            rightWheel.SetPower(100);
            Thread.Sleep(500);
            rightWheel.SetPower(0);
            leftEncoder.Reset();
            rightEncoder.Reset();
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Algo a = new Algo();
            //a.test();
            a.start();
            //a.goForward();
            //a.parking();
	        return;
        }
    }
}
