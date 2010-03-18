namespace TerraControl
{
    partial class Form1
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
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxControllerTime = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.textBoxTemp = new System.Windows.Forms.TextBox();
            this.textBoxHumidity = new System.Windows.Forms.TextBox();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.dataGridView2 = new System.Windows.Forms.DataGridView();
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
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(23, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(95, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Mikrocontrollerzeit:";
            // 
            // textBoxControllerTime
            // 
            this.textBoxControllerTime.Location = new System.Drawing.Point(124, 12);
            this.textBoxControllerTime.Name = "textBoxControllerTime";
            this.textBoxControllerTime.ReadOnly = true;
            this.textBoxControllerTime.Size = new System.Drawing.Size(100, 20);
            this.textBoxControllerTime.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(57, 76);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(64, 13);
            this.label2.TabIndex = 4;
            this.label2.Text = "Temperatur:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(57, 107);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(64, 13);
            this.label3.TabIndex = 5;
            this.label3.Text = "Luftfeuchte:";
            // 
            // textBoxTemp
            // 
            this.textBoxTemp.Location = new System.Drawing.Point(124, 73);
            this.textBoxTemp.Name = "textBoxTemp";
            this.textBoxTemp.ReadOnly = true;
            this.textBoxTemp.Size = new System.Drawing.Size(100, 20);
            this.textBoxTemp.TabIndex = 6;
            // 
            // textBoxHumidity
            // 
            this.textBoxHumidity.Location = new System.Drawing.Point(124, 100);
            this.textBoxHumidity.Name = "textBoxHumidity";
            this.textBoxHumidity.ReadOnly = true;
            this.textBoxHumidity.Size = new System.Drawing.Size(100, 20);
            this.textBoxHumidity.TabIndex = 7;
            // 
            // serialPort1
            // 
            this.serialPort1.BaudRate = 38400;
            // 
            // dataGridView2
            // 
            this.dataGridView2.AllowUserToAddRows = false;
            this.dataGridView2.AllowUserToDeleteRows = false;
            this.dataGridView2.AllowUserToOrderColumns = true;
            this.dataGridView2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)
                        | System.Windows.Forms.AnchorStyles.Left)
                        | System.Windows.Forms.AnchorStyles.Right)));
            this.dataGridView2.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView2.Location = new System.Drawing.Point(12, 236);
            this.dataGridView2.Name = "dataGridView2";
            this.dataGridView2.RowHeadersVisible = false;
            this.dataGridView2.ShowEditingIcon = false;
            this.dataGridView2.ShowRowErrors = false;
            this.dataGridView2.Size = new System.Drawing.Size(536, 236);
            this.dataGridView2.TabIndex = 14;
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // button1
            // 
            this.button1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.button1.Location = new System.Drawing.Point(407, 497);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(141, 23);
            this.button1.TabIndex = 19;
            this.button1.Text = "Programmieren";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.program_Click);
            // 
            // tbTD
            // 
            this.tbTD.Location = new System.Drawing.Point(261, 73);
            this.tbTD.Name = "tbTD";
            this.tbTD.Size = new System.Drawing.Size(100, 20);
            this.tbTD.TabIndex = 22;
            this.tbTD.Validating += new System.ComponentModel.CancelEventHandler(this.temp_Validating);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(277, 57);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(69, 13);
            this.label7.TabIndex = 21;
            this.label7.Text = "Sollwert Tag:";
            // 
            // tbHD
            // 
            this.tbHD.Location = new System.Drawing.Point(261, 104);
            this.tbHD.Name = "tbHD";
            this.tbHD.Size = new System.Drawing.Size(100, 20);
            this.tbHD.TabIndex = 20;
            this.tbHD.Validating += new System.ComponentModel.CancelEventHandler(this.humidity_Validating);
            // 
            // tbTN
            // 
            this.tbTN.Location = new System.Drawing.Point(403, 73);
            this.tbTN.Name = "tbTN";
            this.tbTN.Size = new System.Drawing.Size(100, 20);
            this.tbTN.TabIndex = 25;
            this.tbTN.Validating += new System.ComponentModel.CancelEventHandler(this.temp_Validating);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(413, 57);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(79, 13);
            this.label4.TabIndex = 24;
            this.label4.Text = "Sollwert Nacht:";
            // 
            // tbHN
            // 
            this.tbHN.Location = new System.Drawing.Point(403, 104);
            this.tbHN.Name = "tbHN";
            this.tbHN.Size = new System.Drawing.Size(100, 20);
            this.tbHN.TabIndex = 23;
            this.tbHN.Validating += new System.ComponentModel.CancelEventHandler(this.humidity_Validating);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(144, 57);
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
            this.checkBoxUseTime.Location = new System.Drawing.Point(261, 14);
            this.checkBoxUseTime.Name = "checkBoxUseTime";
            this.checkBoxUseTime.Size = new System.Drawing.Size(155, 17);
            this.checkBoxUseTime.TabIndex = 27;
            this.checkBoxUseTime.Text = "Computerzeit uebernehmen";
            this.checkBoxUseTime.UseVisualStyleBackColor = true;
            // 
            // tbDB
            // 
            this.tbDB.Location = new System.Drawing.Point(124, 156);
            this.tbDB.Name = "tbDB";
            this.tbDB.Size = new System.Drawing.Size(100, 20);
            this.tbDB.TabIndex = 28;
            this.tbDB.Validating += new System.ComponentModel.CancelEventHandler(this.time_Validating);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(29, 159);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(92, 13);
            this.label6.TabIndex = 29;
            this.label6.Text = "Beginn Tageszeit:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(34, 185);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(84, 13);
            this.label8.TabIndex = 31;
            this.label8.Text = "Ende Tageszeit:";
            // 
            // tbDE
            // 
            this.tbDE.Location = new System.Drawing.Point(124, 182);
            this.tbDE.Name = "tbDE";
            this.tbDE.Size = new System.Drawing.Size(100, 20);
            this.tbDE.TabIndex = 30;
            this.tbDE.Validating += new System.ComponentModel.CancelEventHandler(this.time_Validating);
            // 
            // checkBox1
            // 
            this.checkBox1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.checkBox1.AutoSize = true;
            this.checkBox1.Checked = true;
            this.checkBox1.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBox1.Location = new System.Drawing.Point(12, 503);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(117, 17);
            this.checkBox1.TabIndex = 32;
            this.checkBox1.Text = "Werte aktualisieren";
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(560, 532);
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
            this.Controls.Add(this.dataGridView2);
            this.Controls.Add(this.textBoxHumidity);
            this.Controls.Add(this.textBoxTemp);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBoxControllerTime);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "TerraControl";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView2)).EndInit();
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
        private System.Windows.Forms.DataGridView dataGridView2;
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
    }
}

