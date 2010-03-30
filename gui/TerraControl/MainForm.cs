using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using System.IO;
using ZedGraph;
using System.Drawing;
using System.Xml.Serialization;

namespace TerraControl
{

    public partial class MainForm : Form
    {
        private SerializableBindingList<Timerswitch> timerList = new SerializableBindingList<Timerswitch>();
        private SerializableBindingList<Output> outputList = new SerializableBindingList<Output>();
        private Dictionary<string, Output> output_map = new Dictionary<string, Output>();

        private StreamWriter logfile = null;
        private ChartForm chartForm = new ChartForm();

        public MainForm()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            dataGridViewTimers.DataSource = timerList;
            dataGridViewOutputs.DataSource = outputList;
            serialPort1.ReadTimeout = 5000;
        }

        private void connect()
        {
            try
            {
                serialPort1.Open();

                serialPort1.DiscardInBuffer();
                serialPort1.DiscardOutBuffer();

                serialPort1.Write("HELLO\r\n");
                string response = serialPort1.ReadLine();

                if (!response.StartsWith("OK")) throw new TimeoutException();


                readTimers();
                readOutputs();
                readFromController2("get tempsetpoint", tbTD, tbTN);
                readFromController2("get humiditysetpoint", tbHD, tbHN);
                readFromController2("get daytime", tbDB, tbDE);
                readFromController("get title", textBoxControllerTitle);
                readFromController("get version", textBoxVersion);

                timer1.Enabled = true;

                chartForm.Clear();

                checkBox1.Text = "Verbindung Trennen";
                checkBoxLog.Enabled = true;

            }
            catch (TimeoutException e)
            {
                disconnect(e.Message);
            }

        }

        private void disconnect(string reason)
        {
            serialPort1.Close();
            timer1.Stop();
            checkBox1.Checked = false;
            closeLog();

            checkBox1.Text = "Verbinden";
            checkBoxLog.Enabled = false;

            if (reason != "") MessageBox.Show("Fehler beim Lesen (1): " + reason);
        }

        private void readTimers()
        {
            serialPort1.Write("get timers\r\n");

            timerList.Clear();
            string l;
            for (int i = 0; ; i++)
            {

                l = serialPort1.ReadLine().Trim('\r');
                string[] words = l.Split(' ');

                if (words[0] != "+")
                {
                    if (words[0] != "OK") throw new TimeoutException(l);
                    break;
                }

                Timerswitch t = new Timerswitch();
                t.Id = i;
                t.Active = words[5] == "1";
                t.OnTime = words[1];
                t.OffTime = words[2];
                t.Output = Convert.ToInt16(words[3]);
                t.Enabled = (words[4] == "1");

                timerList.Add(t);
            }
        }

        private void readOutputs()
        {
            serialPort1.Write("get outputs\r\n");

            outputList.Clear();
            output_map.Clear();
            for (int i = 0; ; i++)
            {
                string l = serialPort1.ReadLine().Trim('\r');
                string[] words = l.Split(' ');

                if (words[0] != "+")
                {
                    if (words[0] != "OK") throw new TimeoutException(l);
                    break;
                }

                Output o = new Output();
                o.Active = (words[2] == "1");
                o.Name = words[1];
                o.Number = i;
                output_map.Add(words[1], o);
                outputList.Add(o);
            }
        }

        private void updateOutputs()
        {
            serialPort1.Write("get outputs\r\n");
            for (int i = 0; ; i++)
            {
                string l = serialPort1.ReadLine().Trim('\r');
                string[] words = l.Split(' ');

                if (words[0] != "+")
                {
                    if (words[0] != "OK") throw new TimeoutException();
                    break;
                }

                output_map[words[1]].Active = (words[2] == "1");
            }
        }

        private void readFromController(string cmd, TextBox target)
        {
            serialPort1.WriteLine(cmd + "\r");
            target.Text = serialPort1.ReadLine().Trim('\r');
            string response = serialPort1.ReadLine().Trim('\r');
            if (!response.StartsWith("OK")) throw new TimeoutException(response);
        }

        private void readFromController2(string cmd, TextBox target1, TextBox target2)
        {
            serialPort1.WriteLine(cmd + "\r");
            string text = serialPort1.ReadLine().Trim('\r');
            string response = serialPort1.ReadLine().Trim('\r');
            if (!response.StartsWith("OK")) throw new TimeoutException(response);

            string[] subs = text.Split(' ');
            target1.Text = subs[0];
            target2.Text = subs[1];
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            try
            {
                readFromController("get time", textBoxControllerTime);
                readFromController("get temp", textBoxTemp);
                readFromController("get humidity", textBoxHumidity);
                readFromController("get isdaytime", textBoxIsDayTime);

                updateOutputs();
                dataGridViewOutputs.Invalidate();
                if (logfile != null)
                {
                    logfile.Write(DateTime.Now.ToString() + ";");
                    logfile.Write(textBoxTemp.Text + ";");
                    logfile.Write(textBoxHumidity.Text + ";");
                    logfile.Write(textBoxIsDayTime.Text + ";");
                    foreach (Output o in outputList.AsList)
                    {
                        logfile.Write( (o.Active? "1" : "0") + ";");
                    }
                    logfile.WriteLine();
                    logfile.Flush();
                }

                chartForm.AddPoints(Double.Parse(textBoxTemp.Text),
                    textBoxIsDayTime.Text == "1" ? Double.Parse(tbTD.Text) : Double.Parse(tbTN.Text),
                    Double.Parse(textBoxHumidity.Text),
                    textBoxIsDayTime.Text == "1" ? Double.Parse(tbHD.Text) : Double.Parse(tbHN.Text));
            }
            catch (TimeoutException ex)
            {
                disconnect(ex.Message);
            }
        }

        private void writeToController(string command)
        {
            serialPort1.WriteLine(command + "\r");
            string response = serialPort1.ReadLine().Trim('\r');
            if (!response.StartsWith("OK")) throw new TimeoutException(response);
        }

        private void program_Click(object sender, EventArgs e)
        {
            bool t1e = timer1.Enabled;
            timer1.Enabled = false;
            try
            {

                writeToController(String.Format("set humiditysetpoint {0} {1}", tbHD.Text, tbHN.Text));
                writeToController(String.Format("set tempsetpoint {0} {1}", tbTD.Text, tbTN.Text));

                writeToController(String.Format("set daytime {0} {1}", tbDB.Text, tbDE.Text));
                writeToController(String.Format("set title {0}", textBoxControllerTitle.Text));


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


                serialPort1.WriteLine("commit\r");
                string response = serialPort1.ReadLine().Trim('\r');
                if (!response.StartsWith("OK")) throw new TimeoutException(response);


                readTimers();
                readFromController2("get tempsetpoint", tbTD, tbTN);
                readFromController2("get humiditysetpoint", tbHD, tbHN);
                readFromController2("get daytime", tbDB, tbDE);
                readFromController("get title", textBoxControllerTitle);
                timer1.Enabled = t1e;

            }
            catch (TimeoutException ex)
            {
                disconnect(ex.Message);
                throw;
            }
        }

        private void temp_Validating(object sender, CancelEventArgs e)
        {

        }

        private void time_Validating(object sender, CancelEventArgs e)
        {

        }

        private void humidity_Validating(object sender, CancelEventArgs e)
        {

        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            timer1.Enabled = checkBox1.Checked;
            if (checkBox1.Checked)
            {
                checkBox1.Text = "Verbindung wird hergestellt";
                connect();
            }
            else
            {
                disconnect("");
            }
        }

        private void checkBoxLog_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBoxLog.Checked)
            {
                if (saveFileDialogLog.ShowDialog() == DialogResult.OK)
                {
                    logfile = File.CreateText(saveFileDialogLog.FileName);
                    logfile.Write("timestamp;temp;humidity;isdaytime;");
                    foreach ( Output o in outputList.AsList) {
                        logfile.Write(o.Name + ";");
                    }
                    logfile.WriteLine();
                    checkBoxLog.Text = "Aufzeichnung beenden";
                }
            }
            else
            {
                closeLog();
            }
        }

        private void closeLog()
        {
            checkBoxLog.Checked = false;
            if (logfile != null)
            {
                logfile.Close();
                logfile = null;
            }
            checkBoxLog.Text = "Aufzeichnung starten";
        }

        private void buttonGraph_Click(object sender, EventArgs e)
        {
            chartForm.ShowDialog();
        }

        private void loadConfigToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void saveConfigToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (saveFileDialogSettings.ShowDialog() == DialogResult.OK)
            {
                var t = File.CreateText(saveFileDialogSettings.FileName);
                Settings settings = new Settings();

                settings.outputs = outputList.AsList;
                settings.timers = timerList.AsList;

                settings.name = textBoxControllerTitle.Text;
                settings.tempsetpoint = new string[2] { tbTD.Text, tbTN.Text };
                settings.humsetpoint = new string[2] { tbHD.Text, tbHN.Text };


                XmlSerializer xml = new XmlSerializer(typeof(Settings));
                xml.Serialize(t, settings);
            }


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


        public Timerswitch()
        {
        }

        [DisplayName("Nummer")]
        [ReadOnly(true)]
        public int Id
        {
            get { return id; }
            set { id = value; }

        }

        [DisplayName("Aktiv")]
        [ReadOnly(true)]
        public bool Active
        {
            get { return active; }
            set { active = value; }
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


    public class Output
    {
        private int number;
        private string name;
        private bool active;


        public Output()
        {
        }

        [DisplayName("Nummer")]
        [ReadOnly(true)]
        public int Number
        {
            get { return number; }
            set { number = value; }
        }

        [DisplayName("Name")]
        [ReadOnly(true)]
        public string Name
        {
            get { return name; }
            set { name = value; }
        }


        [DisplayName("Aktiv")]
        [ReadOnly(true)]
        public bool Active
        {
            get { return active; }
            set { active = value; }
        }

    }

}