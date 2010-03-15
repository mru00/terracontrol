using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Design;
using System.Text.RegularExpressions;

namespace TerraControl
{

    public partial class Form1 : Form
    {
        private IList<Timerswitch> timerList = new BindingList<Timerswitch>();
        private bool connected = false;
        String[] Outputs = new String[1] {
            "Licht1"
        };


        public Form1()
        {
            InitializeComponent();
        }

        private void checkedListBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            dataGridView2.DataSource = timerList;
            serialPort1.ReadTimeout = 1000;
            serialPort1.Open();

            connect();
        }

        private void connect()
        {
            try
            {
                serialPort1.Write("HELLO\r\n");
                string response = serialPort1.ReadLine();

                if (!response.StartsWith("OK")) throw new TimeoutException();

                connected = true;

                readTimers();
                readFromController2("get tempsetpoint", tbTD, tbTN);
                readFromController2("get humiditysetpoint", tbHD, tbHN);
                readFromController2("get daytime", tbDB, tbDE);
            }
            catch (TimeoutException)
            {
                connected = false;
            }

        }

        private void readTimers()
        {
            serialPort1.Write("get timers\r\n");

            try
            {
                timerList.Clear();
                string l;
                for (int i = 0; ; i++)
                {

                    l = serialPort1.ReadLine();
                    if (l.StartsWith("OK")) break;

                    string[] words = l.Split(' ');

                    Timerswitch t = new Timerswitch(i, words[4] == "1");
                    t.OnTime = words[0];
                    t.OffTime = words[1];
                    t.Output = Convert.ToInt16(words[2]);
                    t.Enabled = words[3] == "1";

                    timerList.Add(t);
                }
            }
            catch (TimeoutException)
            {
            }
        }

        private void readFromController(string cmd, TextBox target)
        {
            serialPort1.WriteLine(cmd + "\r");
            target.Text = serialPort1.ReadLine();
            string response = serialPort1.ReadLine();
            if (!response.StartsWith("OK"))
            {
                timer1.Enabled = false;
                checkBox1.Checked = false;
                MessageBox.Show("Fehler beim Lesen (1): " + response);
            }
        }

        private void readFromController2(string cmd, TextBox target1, TextBox target2)
        {
            serialPort1.WriteLine(cmd + "\r");
            string text = serialPort1.ReadLine();
            string response = serialPort1.ReadLine();
            if (!response.StartsWith("OK"))
            {
                timer1.Enabled = false;
                checkBox1.Checked = false;
                MessageBox.Show("Fehler beim Lesen (2): " + response);
            }

            string[] subs = text.Split(' ');
            target1.Text = subs[0];
            target2.Text = subs[1];
        }


        private void timer1_Tick(object sender, EventArgs e)
        {
            if (!connected) connect();

            try
            {
                readFromController("get time", textBoxControllerTime);
                readFromController("get temp", textBoxTemp);
                readFromController("get humidity", textBoxHumidity);
            }
            catch (TimeoutException)
            {
                connected = false;
            }
        }

        private void writeToController(string command)
        {
            string response = "dumb";
            serialPort1.WriteLine(command + "\r");
            try
            {
                response = serialPort1.ReadLine();
            }
            catch (TimeoutException)
            {
            }

            if (!response.StartsWith("OK"))
            {
                MessageBox.Show("Programmieren schiefgegangen: " + command + "\n" + response);
            }
        }



        private void program_Click(object sender, EventArgs e)
        {
            bool t1e = timer1.Enabled;
            timer1.Enabled = true;

            writeToController(String.Format("set humiditysetpoint {0} {1}", tbHD.Text, tbHN.Text));
            writeToController(String.Format("set tempsetpoint {0} {1}", tbTD.Text, tbTN.Text));

            writeToController(String.Format("set daytime {0} {1}", tbDB.Text, tbDE.Text));

            if (checkBoxUseTime.Checked)
                writeToController(String.Format("set time {0}:{1}:{2}",
                    DateTime.Now.Hour,
                        DateTime.Now.Minute,
                            DateTime.Now.Second));


            foreach (Timerswitch s in timerList)
            {
                writeToController(String.Format("set timer {0} {1} {2} {3} {4} ",
                        s.Id, s.OnTime, s.OffTime, s.Output, s.Enabled ? "1" : "0"));
            }

            readTimers();

            timer1.Enabled = t1e;
        }


        private void temp_Validating(object sender, CancelEventArgs e)
        {
            try
            {
                int n = int.Parse(((TextBox)sender).Text);
                if (n < 20 || n > 40)
                {
                    e.Cancel = true;
                    MessageBox.Show("Wert zwischen 20 und 40 Eingeben.");
                }
            }
            catch (FormatException)
            {
                e.Cancel = true;
                MessageBox.Show("Zahl eingeben, ohne Einheit.");
            }
        }


        private void time_Validating(object sender, CancelEventArgs e)
        {
            Regex re = new Regex("[0-9][0-9]+:[0-9][0-9]+:[0-9][0-9]+");
            if (!re.IsMatch(((TextBox)sender).Text))
            {
                e.Cancel = true;
                MessageBox.Show("Zeit in hh:mm:ss eingeben.");
            }
        }




        private void humidity_Validating(object sender, CancelEventArgs e)
        {
            try
            {
                int n = int.Parse(((TextBox)sender).Text);
                if (n < 20 || n > 40)
                {
                    e.Cancel = true;
                    MessageBox.Show("Wert zwischen 20 und 40 Eingeben.");
                }
            }
            catch (FormatException)
            {
                e.Cancel = true;
                MessageBox.Show("Zahl eingeben, ohne Einheit.");
            }
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            timer1.Enabled = checkBox1.Checked;
        }

        private void toolTip1_Popup(object sender, PopupEventArgs e)
        {

        }
    }

    public class Timerswitch
    {
        private bool enabled;
        private bool active;
        private string onTime = "00:00:00";
        private string offTime = "00:00:00";
        private int output;
        private int id;


        public Timerswitch(int id, bool active)
        {
            this.id = id;
            this.active = active;

        }

        [DisplayName("Nummer")]
        public int Id
        {
            get { return id; }
        }

        [DisplayName("Aktiv")]
        public bool Active
        {
            get { return active; }
        }


        [DisplayName("Freigegeben")]
        public bool Enabled
        {
            get { return enabled; }
            set { enabled = value; }
        }

        [DisplayName("Einschaltzeitpunkt")]
        public string OnTime
        {
            get { return onTime; }
            set { onTime = value; }
        }

        [DisplayName("Ausschaltzeitpunkt")]
        public string OffTime
        {
            get { return offTime; }
            set { offTime = value; }
        }

        [DisplayName("Ausgang")]
        public int Output
        {
            get { return output; }
            set { output = value; }
        }

    }

}