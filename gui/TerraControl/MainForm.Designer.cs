namespace TerraControl
{
    partial class MainForm
    {
        /// <summary>
        /// Erforderliche Designervariable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Verwendete Ressourcen bereinigen.
        /// </summary>
        /// <param name="disposing">True, wenn verwaltete Ressourcen gelöscht werden sollen; andernfalls False.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Vom Windows Form-Designer generierter Code

        /// <summary>
        /// Erforderliche Methode für die Designerunterstützung.
        /// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxControllerTime = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.textBoxTemp = new System.Windows.Forms.TextBox();
            this.textBoxHumidity = new System.Windows.Forms.TextBox();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.dataGridViewTimers = new System.Windows.Forms.DataGridView();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.button1 = new System.Windows.Forms.Button();
            this.tbTD = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.tbHD = new System.Windows.Forms.TextBox();
            this.tbTN = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.tbHN = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.checkBoxUseTime = new System.Windows.Forms.CheckBox();
            this.tbDB = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.tbDE = new System.Windows.Forms.TextBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.textBoxControllerTitle = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.dataGridViewOutputs = new System.Windows.Forms.DataGridView();
            this.checkBoxLog = new System.Windows.Forms.CheckBox();
            this.buttonGraph = new System.Windows.Forms.Button();
            this.textBoxVersion = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.textBoxIsDayTime = new System.Windows.Forms.TextBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadConfigToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveConfigToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.quitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileDialogSettings = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialogSettings = new System.Windows.Forms.SaveFileDialog();
            this.saveFileDialogLog = new System.Windows.Forms.SaveFileDialog();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewTimers)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewOutputs)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(21, 86);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(95, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Mikrocontrollerzeit:";
            // 
            // textBoxControllerTime
            // 
            this.textBoxControllerTime.Location = new System.Drawing.Point(122, 83);
            this.textBoxControllerTime.Name = "textBoxControllerTime";
            this.textBoxControllerTime.ReadOnly = true;
            this.textBoxControllerTime.Size = new System.Drawing.Size(100, 20);
            this.textBoxControllerTime.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(55, 147);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(64, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Temperatur:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(55, 178);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(64, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Luftfeuchte:";
            // 
            // textBoxTemp
            // 
            this.textBoxTemp.Location = new System.Drawing.Point(122, 144);
            this.textBoxTemp.Name = "textBoxTemp";
            this.textBoxTemp.ReadOnly = true;
            this.textBoxTemp.Size = new System.Drawing.Size(100, 20);
            this.textBoxTemp.TabIndex = 6;
            // 
            // textBoxHumidity
            // 
            this.textBoxHumidity.Location = new System.Drawing.Point(122, 171);
            this.textBoxHumidity.Name = "textBoxHumidity";
            this.textBoxHumidity.ReadOnly = true;
            this.textBoxHumidity.Size = new System.Drawing.Size(100, 20);
            this.textBoxHumidity.TabIndex = 7;
            // 
            // serialPort1
            // 
            this.serialPort1.BaudRate = 38400;
            this.serialPort1.ReadTimeout = 3000;
            // 
            // dataGridViewTimers
            // 
            this.dataGridViewTimers.AllowUserToAddRows = false;
            this.dataGridViewTimers.AllowUserToDeleteRows = false;
            this.dataGridViewTimers.AllowUserToOrderColumns = true;
            this.dataGridViewTimers.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.dataGridViewTimers.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridViewTimers.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewTimers.Location = new System.Drawing.Point(12, 296);
            this.dataGridViewTimers.Name = "dataGridViewTimers";
            this.dataGridViewTimers.RowHeadersVisible = false;
            this.dataGridViewTimers.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewTimers.ShowEditingIcon = false;
            this.dataGridViewTimers.ShowRowErrors = false;
            this.dataGridViewTimers.Size = new System.Drawing.Size(874, 270);
            this.dataGridViewTimers.TabIndex = 14;
            // 
            // timer1
            // 
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // button1
            // 
            this.button1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.button1.Location = new System.Drawing.Point(745, 591);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(141, 23);
            this.button1.TabIndex = 19;
            this.button1.Text = "Programmieren";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.program_Click);
            // 
            // tbTD
            // 
            this.tbTD.Location = new System.Drawing.Point(259, 144);
            this.tbTD.Name = "tbTD";
            this.tbTD.Size = new System.Drawing.Size(100, 20);
            this.tbTD.TabIndex = 22;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(275, 128);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(69, 13);
            this.label7.TabIndex = 21;
            this.label7.Text = "Sollwert Tag:";
            // 
            // tbHD
            // 
            this.tbHD.Location = new System.Drawing.Point(259, 175);
            this.tbHD.Name = "tbHD";
            this.tbHD.Size = new System.Drawing.Size(100, 20);
            this.tbHD.TabIndex = 20;
            // 
            // tbTN
            // 
            this.tbTN.Location = new System.Drawing.Point(401, 144);
            this.tbTN.Name = "tbTN";
            this.tbTN.Size = new System.Drawing.Size(100, 20);
            this.tbTN.TabIndex = 25;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(411, 128);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(79, 13);
            this.label4.TabIndex = 24;
            this.label4.Text = "Sollwert Nacht:";
            // 
            // tbHN
            // 
            this.tbHN.Location = new System.Drawing.Point(401, 175);
            this.tbHN.Name = "tbHN";
            this.tbHN.Size = new System.Drawing.Size(100, 20);
            this.tbHN.TabIndex = 23;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(142, 128);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(41, 13);
            this.label5.TabIndex = 26;
            this.label5.Text = "Istwert:";
            // 
            // checkBoxUseTime
            // 
            this.checkBoxUseTime.AutoSize = true;
            this.checkBoxUseTime.Checked = true;
            this.checkBoxUseTime.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxUseTime.Location = new System.Drawing.Point(259, 85);
            this.checkBoxUseTime.Name = "checkBoxUseTime";
            this.checkBoxUseTime.Size = new System.Drawing.Size(155, 17);
            this.checkBoxUseTime.TabIndex = 27;
            this.checkBoxUseTime.Text = "Computerzeit uebernehmen";
            this.checkBoxUseTime.UseVisualStyleBackColor = true;
            // 
            // tbDB
            // 
            this.tbDB.Location = new System.Drawing.Point(122, 227);
            this.tbDB.Name = "tbDB";
            this.tbDB.Size = new System.Drawing.Size(100, 20);
            this.tbDB.TabIndex = 28;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(27, 230);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(92, 13);
            this.label6.TabIndex = 29;
            this.label6.Text = "Beginn Tageszeit:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(32, 256);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(84, 13);
            this.label8.TabIndex = 31;
            this.label8.Text = "Ende Tageszeit:";
            // 
            // tbDE
            // 
            this.tbDE.Location = new System.Drawing.Point(122, 253);
            this.tbDE.Name = "tbDE";
            this.tbDE.Size = new System.Drawing.Size(100, 20);
            this.tbDE.TabIndex = 30;
            // 
            // checkBox1
            // 
            this.checkBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.checkBox1.Appearance = System.Windows.Forms.Appearance.Button;
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(12, 591);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(65, 23);
            this.checkBox1.TabIndex = 32;
            this.checkBox1.Text = "Verbinden";
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // textBoxControllerTitle
            // 
            this.textBoxControllerTitle.Location = new System.Drawing.Point(122, 33);
            this.textBoxControllerTitle.Name = "textBoxControllerTitle";
            this.textBoxControllerTitle.Size = new System.Drawing.Size(100, 20);
            this.textBoxControllerTitle.TabIndex = 34;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(21, 36);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(74, 13);
            this.label9.TabIndex = 33;
            this.label9.Text = "Controller Titel";
            // 
            // dataGridViewOutputs
            // 
            this.dataGridViewOutputs.AllowUserToAddRows = false;
            this.dataGridViewOutputs.AllowUserToDeleteRows = false;
            this.dataGridViewOutputs.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.dataGridViewOutputs.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.dataGridViewOutputs.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridViewOutputs.Location = new System.Drawing.Point(552, 12);
            this.dataGridViewOutputs.Name = "dataGridViewOutputs";
            this.dataGridViewOutputs.ReadOnly = true;
            this.dataGridViewOutputs.RowHeadersVisible = false;
            this.dataGridViewOutputs.RowHeadersWidthSizeMode = System.Windows.Forms.DataGridViewRowHeadersWidthSizeMode.AutoSizeToDisplayedHeaders;
            this.dataGridViewOutputs.SelectionMode = System.Windows.Forms.DataGridViewSelectionMode.FullRowSelect;
            this.dataGridViewOutputs.ShowEditingIcon = false;
            this.dataGridViewOutputs.ShowRowErrors = false;
            this.dataGridViewOutputs.Size = new System.Drawing.Size(334, 278);
            this.dataGridViewOutputs.TabIndex = 35;
            // 
            // checkBoxLog
            // 
            this.checkBoxLog.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.checkBoxLog.Appearance = System.Windows.Forms.Appearance.Button;
            this.checkBoxLog.AutoSize = true;
            this.checkBoxLog.Enabled = false;
            this.checkBoxLog.Location = new System.Drawing.Point(192, 591);
            this.checkBoxLog.Name = "checkBoxLog";
            this.checkBoxLog.Size = new System.Drawing.Size(117, 23);
            this.checkBoxLog.TabIndex = 36;
            this.checkBoxLog.Text = "Aufzeichnung starten";
            this.checkBoxLog.UseVisualStyleBackColor = true;
            this.checkBoxLog.CheckedChanged += new System.EventHandler(this.checkBoxLog_CheckedChanged);
            // 
            // buttonGraph
            // 
            this.buttonGraph.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.buttonGraph.Location = new System.Drawing.Point(664, 591);
            this.buttonGraph.Name = "buttonGraph";
            this.buttonGraph.Size = new System.Drawing.Size(75, 23);
            this.buttonGraph.TabIndex = 37;
            this.buttonGraph.Text = "Verlauf";
            this.buttonGraph.UseVisualStyleBackColor = true;
            this.buttonGraph.Click += new System.EventHandler(this.buttonGraph_Click);
            // 
            // textBoxVersion
            // 
            this.textBoxVersion.Location = new System.Drawing.Point(122, 59);
            this.textBoxVersion.Name = "textBoxVersion";
            this.textBoxVersion.ReadOnly = true;
            this.textBoxVersion.Size = new System.Drawing.Size(242, 20);
            this.textBoxVersion.TabIndex = 38;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(21, 62);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(49, 13);
            this.label10.TabIndex = 39;
            this.label10.Text = "Firmware";
            // 
            // textBoxIsDayTime
            // 
            this.textBoxIsDayTime.Location = new System.Drawing.Point(479, 86);
            this.textBoxIsDayTime.Name = "textBoxIsDayTime";
            this.textBoxIsDayTime.Size = new System.Drawing.Size(22, 20);
            this.textBoxIsDayTime.TabIndex = 40;
            this.textBoxIsDayTime.Visible = false;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(898, 24);
            this.menuStrip1.TabIndex = 41;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.loadConfigToolStripMenuItem,
            this.saveConfigToolStripMenuItem,
            this.toolStripSeparator1,
            this.quitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // loadConfigToolStripMenuItem
            // 
            this.loadConfigToolStripMenuItem.Name = "loadConfigToolStripMenuItem";
            this.loadConfigToolStripMenuItem.Size = new System.Drawing.Size(139, 22);
            this.loadConfigToolStripMenuItem.Text = "Load Config";
            this.loadConfigToolStripMenuItem.Click += new System.EventHandler(this.loadConfigToolStripMenuItem_Click);
            // 
            // saveConfigToolStripMenuItem
            // 
            this.saveConfigToolStripMenuItem.Name = "saveConfigToolStripMenuItem";
            this.saveConfigToolStripMenuItem.Size = new System.Drawing.Size(139, 22);
            this.saveConfigToolStripMenuItem.Text = "Save Config";
            this.saveConfigToolStripMenuItem.Click += new System.EventHandler(this.saveConfigToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(136, 6);
            // 
            // quitToolStripMenuItem
            // 
            this.quitToolStripMenuItem.Name = "quitToolStripMenuItem";
            this.quitToolStripMenuItem.Size = new System.Drawing.Size(139, 22);
            this.quitToolStripMenuItem.Text = "Quit";
            // 
            // openFileDialogSettings
            // 
            this.openFileDialogSettings.DefaultExt = "xml";
            this.openFileDialogSettings.Filter = "Einstellungen|*.xml";
            this.openFileDialogSettings.Title = "Einstellungen Laden";
            // 
            // saveFileDialogSettings
            // 
            this.saveFileDialogSettings.DefaultExt = "xml";
            this.saveFileDialogSettings.Filter = "Einstellungen|*.xml";
            this.saveFileDialogSettings.Title = "Einstellungen Speichern";
            // 
            // saveFileDialogLog
            // 
            this.saveFileDialogLog.DefaultExt = "csv";
            this.saveFileDialogLog.Filter = "Log|*.csv";
            this.saveFileDialogLog.Title = "Log Speichern unter";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(898, 626);
            this.Controls.Add(this.textBoxIsDayTime);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.textBoxVersion);
            this.Controls.Add(this.buttonGraph);
            this.Controls.Add(this.checkBoxLog);
            this.Controls.Add(this.dataGridViewOutputs);
            this.Controls.Add(this.textBoxControllerTitle);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.tbDE);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.tbDB);
            this.Controls.Add(this.checkBoxUseTime);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.tbTN);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.tbHN);
            this.Controls.Add(this.tbTD);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.tbHD);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.dataGridViewTimers);
            this.Controls.Add(this.textBoxHumidity);
            this.Controls.Add(this.textBoxTemp);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBoxControllerTime);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.Text = "TerraControl GUI";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewTimers)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridViewOutputs)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBoxControllerTime;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBoxTemp;
        private System.Windows.Forms.TextBox textBoxHumidity;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.DataGridView dataGridViewTimers;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.TextBox tbTD;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox tbHD;
        private System.Windows.Forms.TextBox tbTN;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox tbHN;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.CheckBox checkBoxUseTime;
        private System.Windows.Forms.TextBox tbDB;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox tbDE;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.TextBox textBoxControllerTitle;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.DataGridView dataGridViewOutputs;
        private System.Windows.Forms.CheckBox checkBoxLog;
        private System.Windows.Forms.Button buttonGraph;
        private System.Windows.Forms.TextBox textBoxVersion;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox textBoxIsDayTime;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem loadConfigToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveConfigToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem quitToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog openFileDialogSettings;
        private System.Windows.Forms.SaveFileDialog saveFileDialogSettings;
        private System.Windows.Forms.SaveFileDialog saveFileDialogLog;
    }
}

