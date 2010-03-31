using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text.RegularExpressions;
using System.Windows.Forms;
using System.IO;
using ZedGraph;
using System.Drawing;
using System.Xml.Serialization;
using System.Collections;
using System.Data;

namespace TerraControl
{

    public partial class MainForm : Form
    {
        private List<Timerswitch> timerList = new List<Timerswitch>();
        private List<Output> outputList = new List<Output>();
        private Dictionary<string, Output> output_map = new Dictionary<string, Output>();

        private BindingSource bsOutputs = new BindingSource();
        private BindingSource bsTimers = new BindingSource();

        private StreamWriter logfile = null;
        private ChartForm chartForm = new ChartForm();


        public MainForm()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            bsOutputs.DataSource = outputList;
            bsTimers.DataSource = timerList;


            dataGridViewTimers.DataSource = bsTimers;
            dataGridViewOutputs.DataSource = bsOutputs;
            serialPort1.ReadTimeout = 5000;


            dataGridViewTimers.Columns["Enabled"].ToolTipText = "Diese Zeitschaltuhr wird verwendet";
            dataGridViewTimers.Columns["Active"].ToolTipText = "Diese Zeitschaltuhr ist gerade eingeschaltet";
            dataGridViewTimers.Columns["OffTime"].DefaultCellStyle.Format = "HH:mm:ss";
            dataGridViewTimers.Columns["OffTime"].ToolTipText = "Zu dieser Zeit wird die Zeitschaltuhr ausgeschaltet";

            dataGridViewTimers.Columns["OnTime"].DefaultCellStyle.Format = "HH:mm:ss";
            dataGridViewTimers.Columns["OnTime"].ToolTipText = "Zu dieser Zeit wird die Zeitschaltuhr eingeschaltet";

            dataGridViewTimers.Columns.Remove("Output");

            var outputcol = new DataGridViewComboBoxColumn();
            outputcol.DataPropertyName = "Output";
            outputcol.DisplayMember = "Name";
            outputcol.ValueMember = "Number";
            outputcol.Name = "Ausgang";
            outputcol.ToolTipText = "Zeigt an, welcher Ausgang mit dieser Zeitschaltuhr verbunden ist";
            outputcol.DataSource = bsOutputs;

            dataGridViewTimers.Columns.Add(outputcol);

            bsTimers.DataError += new BindingManagerDataErrorEventHandler(bsTimers_DataError);
        }

        void bsTimers_DataError(object sender, BindingManagerDataErrorEventArgs e)
        {
            throw new NotImplementedException();
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


                readOutputs();
                readTimers();

                readFromController2("get tempsetpoint", tbTD, tbTN);
                readFromController2("get humiditysetpoint", tbHD, tbHN);
                readFromController2("get daytime", tbDB, tbDE);
                textBoxControllerTitle.Text = readFromController("get title");
                numericHystTemp.Text = readFromController("get hyst_temp");
                numericHystHum.Text = readFromController("get hyst_humidity");
                textBoxVersion.Text = readFromController("get version");

                timer1.Enabled = true;

                chartForm.Clear();

                checkBox1.Text = "Verbindung Trennen";
                checkBoxLog.Enabled = true;
                buttonGraph.Enabled = true;
                button1.Enabled = true;

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
            buttonGraph.Enabled = false;
            button1.Enabled = false;

            if (reason != "") MessageBox.Show("Fehler beim Lesen (1): " + reason);
        }

        private void readTimers()
        {
            serialPort1.WriteLine("get timers");

            bsTimers.Clear();
            string l;
            for (int i = 0; ; i++)
            {

                l = serialPort1.ReadLine();
                string[] words = l.Split(' ');

                if (words[0] != "+")
                {
                    if (words[0] != "OK") throw new TimeoutException(l);
                    break;
                }

                Timerswitch t = (Timerswitch)bsTimers.AddNew();
                t.Id = i;
                t.Active = words[5] == "1";
                t.OnTime = DateTime.Parse(words[1]);
                t.OffTime = DateTime.Parse(words[2]);
                t.Output = Convert.ToInt16(words[3]);
                t.Enabled = (words[4] == "1");
            }
        }

        private void readOutputs()
        {
            serialPort1.WriteLine("get outputs");
            bsOutputs.Clear();
            output_map.Clear();
            for (int i = 0; ; i++)
            {
                string l = serialPort1.ReadLine();
                string[] words = l.Split(' ');

                if (words[0] != "+")
                {
                    if (words[0] != "OK") throw new TimeoutException(l);
                    break;
                }

                Output o = (Output)bsOutputs.AddNew();
                o.Active = (words[2] == "1");
                o.Name = words[1];
                o.Number = i;
                output_map.Add(words[1], o);

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

        private string readFromController(string cmd)
        {
            string text;
            serialPort1.WriteLine(cmd);
            text = serialPort1.ReadLine();
            if (!text.StartsWith("+ ")) throw new TimeoutException(text);
            string val = text.Substring(2);

            text = serialPort1.ReadLine();
            if (!text.StartsWith("OK")) throw new TimeoutException(text);

            return val;
        }


        private void readFromController2(string cmd, Control target1, Control target2)
        {
            serialPort1.WriteLine(cmd);
            string text = serialPort1.ReadLine();
            if (!text.StartsWith("+ ")) throw new TimeoutException(text);

            string[] subs = text.Split(' ');
            target1.Text = subs[1];
            target2.Text = subs[2];

            text = serialPort1.ReadLine();
            if (!text.StartsWith("OK")) throw new TimeoutException(text);

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            try
            {
                textBoxControllerTime.Text = readFromController("get time");
                textBoxTemp.Text = readFromController("get temp");
                textBoxHumidity.Text = readFromController("get humidity");
                textBoxIsDayTime.Text = readFromController("get isdaytime");

                updateOutputs();
                dataGridViewOutputs.Invalidate();
                if (logfile != null)
                {
                    logfile.Write(DateTime.Now.ToString() + ";");
                    logfile.Write(textBoxTemp.Text + ";");
                    logfile.Write(textBoxHumidity.Text + ";");
                    logfile.Write(textBoxIsDayTime.Text + ";");
                    foreach (Output o in outputList)
                    {
                        logfile.Write((o.Active ? "1" : "0") + ";");
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

                writeToController(String.Format("set hyst_humidity {0}", numericHystHum.Text));
                writeToController(String.Format("set hyst_temp {0}", numericHystTemp.Text));

                if (checkBoxUseTime.Checked)
                    writeToController(String.Format("set time {0}:{1}:{2}",
                        DateTime.Now.Hour,
                            DateTime.Now.Minute,
                                DateTime.Now.Second));


                foreach (Timerswitch s in timerList)
                {
                    writeToController(String.Format("set timer {0} {1} {2} {3} {4} ",
                            s.Id, s.OnTime.ToString("HH:mm:ss"), s.OffTime.ToString("HH:mm:ss"), s.Output, s.Enabled ? "1" : "0"));
                }


                serialPort1.WriteLine("commit\r");
                string response = serialPort1.ReadLine().Trim('\r');
                if (!response.StartsWith("OK")) throw new TimeoutException(response);


                readTimers();
                readFromController2("get tempsetpoint", tbTD, tbTN);
                readFromController2("get humiditysetpoint", tbHD, tbHN);
                readFromController2("get daytime", tbDB, tbDE);
                textBoxControllerTitle.Text = readFromController("get title");
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
                    foreach (Output o in outputList)
                    {
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

                settings.outputs = outputList;
                settings.timers = timerList;

                settings.name = textBoxControllerTitle.Text;
                settings.tempsetpoint = new string[2] { tbTD.Text, tbTN.Text };
                settings.humsetpoint = new string[2] { tbHD.Text, tbHN.Text };


                XmlSerializer xml = new XmlSerializer(typeof(Settings));
                xml.Serialize(t, settings);
            }
        }

        private void quitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            new AboutBox().ShowDialog();
        }
    }

    public class Timerswitch
    {
        private int id;
        private bool enabled;
        private bool active;
        private DateTime onTime;
        private DateTime offTime;
        private int output;


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
        public DateTime OnTime
        {
            get { return onTime; }
            set { onTime = value; }
        }

        [DisplayName("Ausschaltzeitpunkt")]
        public DateTime OffTime
        {
            get { return offTime; }
            set { offTime = value; }
        }

        [DisplayName("Ausgang")]
        [TypeConverter(typeof(OutputConverter))]
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

    public class OutputConverter : System.ComponentModel.TypeConverter
    {
        private ArrayList values;
        public OutputConverter()
        {
            // Initializes the standard values list with defaults.
            values = new ArrayList(new string[] { "Lampe1", "Lampe2" });
        }

        // Indicates this converter provides a list of standard values.
        public override bool GetStandardValuesSupported(System.ComponentModel.ITypeDescriptorContext context)
        {
            return true;
        }

        // Returns a StandardValuesCollection of standard value objects.
        public override System.ComponentModel.TypeConverter.StandardValuesCollection GetStandardValues(System.ComponentModel.ITypeDescriptorContext context)
        {
            // Passes the local integer array.
            StandardValuesCollection svc =
                new StandardValuesCollection(values);
            return svc;
        }

        // Returns true for a sourceType of string to indicate that 
        // conversions from string to integer are supported. (The 
        // GetStandardValues method requires a string to native type 
        // conversion because the items in the drop-down list are 
        // translated to string.)
        public override bool CanConvertFrom(System.ComponentModel.ITypeDescriptorContext context, System.Type sourceType)
        {
            if (sourceType == typeof(string))
                return true;
            else
                return base.CanConvertFrom(context, sourceType);
        }

        // If the type of the value to convert is string, parses the string 
        // and returns the integer to set the value of the property to. 
        // This example first extends the integer array that supplies the 
        // standard values collection if the user-entered value is not 
        // already in the array.
        public override object ConvertFrom(System.ComponentModel.ITypeDescriptorContext context, System.Globalization.CultureInfo culture, object value)
        {
            if (value.GetType() == typeof(string))
            {
                // Parses the string to get the integer to set to the property.
                int newVal = int.Parse((string)value);

                // Tests whether new integer is already in the list.
                if (!values.Contains(newVal))
                {
                    // If the integer is not in list, adds it in order.
                    values.Add(newVal);
                    values.Sort();
                }
                // Returns the integer value to assign to the property.
                return newVal;
            }
            else
                return base.ConvertFrom(context, culture, value);
        }
    }
}