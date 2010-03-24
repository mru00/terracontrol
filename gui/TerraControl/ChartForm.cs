using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using ZedGraph;

namespace TerraControl
{

    public partial class ChartForm : Form
    {
        private long index = 0;

        public LineItem tempCurve, humCurve, tempSPCurve, humSPCurve;

        public ChartForm()
        {
            InitializeComponent();

            var z = zedGraphControl1;
            GraphPane p = z.GraphPane;

            tempCurve = AddCurve("Temperatur - Ist", Color.Red);
            tempSPCurve = AddCurve("Temperatur - Soll", Color.LightSalmon);
            humCurve = AddCurve("Feuchtigkeit - Ist ", Color.Blue);
            humSPCurve = AddCurve("Feuchtigkeit - Soll", Color.LightBlue);

            p.Title.Text = "Verlauf von Temperatur und Feuchtigkeit";

            p.XAxis.Title.Text = "Zeit [s]";

            p.YAxis.Title.Text = "Temperatur [%], Luftfeuchte [%]";
        }

        public void Clear()
        {
            tempCurve.Clear();
            humCurve.Clear();
            tempSPCurve.Clear();
            humSPCurve.Clear();
        }

        public void AddPoints(double temp, double tempSP, double hum, double humSP)
        {
            AddPoint(tempCurve, temp);
            AddPoint(humCurve, hum);
            AddPoint(tempSPCurve, tempSP);
            AddPoint(humSPCurve, humSP);

            index++;
            if (Visible)
            {
                zedGraphControl1.AxisChange();
                zedGraphControl1.Invalidate();
            }
        }

        private LineItem AddCurve(string title, Color color)
        {
            var z = zedGraphControl1;
            var p = z.GraphPane;
            var c = p.AddCurve(title, new double[0], new double[0], color, SymbolType.None);

            return c;
        }

        private void AddPoint(LineItem line, double val)
        {
            line.AddPoint(index, val);
            if (line.NPts == 1000) line.RemovePoint(0);
        }

    }
}
