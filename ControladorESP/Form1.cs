using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using WebSocketSharp;
using System.Windows.Input;

namespace LEDCONTROL
{
    
    public partial class Form1 : Form
    {
        bool painel = false;
        bool flag = true;
        WebSocket ws = new WebSocket(@"ws://192.168.4.1:81/");
        
        public Form1()
        {
            InitializeComponent();
            
           // ws.OnMessage += (sender, e) =>
               // Console.WriteLine("Laputa says: " + e.Data);

            ws.Connect();
        }

        public void button1_Click(object sender, EventArgs e)
        {
            ws.Send("LEDOn");
        }

        private void panel1_MouseMove(object sender, MouseEventArgs e)
        {
            
            
              
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {

            

        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void panel1_Paint_1(object sender, PaintEventArgs e)
        {

        }

        private void button2_Click(object sender, EventArgs e)
        {
            
        }

        private void panel1_DragEnter(object sender, DragEventArgs e)
        {

        }

        private void panel1_MouseMove_1(object sender, MouseEventArgs e)
        {
            Point local = new Point(e.X, e.Y);
            String msg = "";
            String R = "";
            String L = "";
                       
            if (painel == true)
            {
                
                local.Offset(e.X - 255, e.Y - 255);
                
                int X = local.X;
                int Y = (local.Y)*(-1);
                msg = "X" + X + "<>" + "Y" + Y;
                textBox2.Text = msg;

                moverChecker(X, Y);

                int sinal = 1;
                                
                if (Y < 0) sinal = -1;
                if (Y >= 0) sinal = 1;

                if (X < 0) {
                    R = "R" + ((Y * sinal + X * (-1)) * sinal);
                    L = "L" + Y;
                }

                if (X >= 0)
                {
                    L = "L" + ((Y * sinal + X) * sinal);
                    R = "R" + Y;
                }
                    ws.Send(R);
                    ws.Send(L);
                    textBox1.Text = L + "<>" + R;
            }
                      
        }

        private void panel1_MouseDown_1(object sender, MouseEventArgs e)
        {
            painel = !painel;
            ws.Send("R0");
            ws.Send("L0");
            textBox1.Text = "L0 <> R0";
        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            ws.Send("{X=250,Y=-250}");
        }

        public void moverChecker(int x, int y)
        {

            

        }
    }
}
