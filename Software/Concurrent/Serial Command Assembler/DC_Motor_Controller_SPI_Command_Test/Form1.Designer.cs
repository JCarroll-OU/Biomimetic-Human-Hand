namespace DC_Motor_Controller_SPI_Command_Test
{
    partial class DC_Motor_Controller_PCB_Command_Assembler
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(DC_Motor_Controller_PCB_Command_Assembler));
            commandID = new ComboBox();
            commandID_label = new Label();
            targetID_label = new Label();
            targetID = new NumericUpDown();
            cmdParam = new NumericUpDown();
            cmdParam_label = new Label();
            commandPreview = new TextBox();
            commandView_label = new Label();
            comPort_label = new Label();
            comPort = new NumericUpDown();
            baudRate_label = new Label();
            baudRate = new NumericUpDown();
            sendCommand = new Button();
            commandConsole = new RichTextBox();
            controllerID = new NumericUpDown();
            controllerIDlabel = new Label();
            ((System.ComponentModel.ISupportInitialize)targetID).BeginInit();
            ((System.ComponentModel.ISupportInitialize)cmdParam).BeginInit();
            ((System.ComponentModel.ISupportInitialize)comPort).BeginInit();
            ((System.ComponentModel.ISupportInitialize)baudRate).BeginInit();
            ((System.ComponentModel.ISupportInitialize)controllerID).BeginInit();
            SuspendLayout();
            // 
            // commandID
            // 
            commandID.Font = new Font("Segoe UI", 10.2F, FontStyle.Regular, GraphicsUnit.Point, 0);
            commandID.FormattingEnabled = true;
            commandID.Items.AddRange(new object[] { "SERIAL_CMD_EMPTY", "SERIAL_CMD_SET_TARGET_ANGLE", "SERIAL_CMD_GET_TARGET_ANGLE", "SERIAL_CMD_GET_CURRENT_ANGLE", "SERIAL_CMD_SET_PID_ENABLE", "SERIAL_CMD_GET_PID_ENABLE", "SERIAL_CMD_PID_SET_P", "SERIAL_CMD_PID_GET_P", "SERIAL_CMD_PID_SET_I", "SERIAL_CMD_PID_GET_I", "SERIAL_CMD_PID_SET_D", "SERIAL_CMD_PID_GET_D", "SERIAL_CMD_SET_ANGLE_CONV_DEG_MIN", "SERIAL_CMD_GET_ANGLE_CONV_DEG_MIN", "SERIAL_CMD_SET_ANGLE_CONV_DEG_MAX", "SERIAL_CMD_GET_ANGLE_CONV_DEG_MAX", "SERIAL_CMD_SET_ANGLE_JOINT_DEG_MIN", "SERIAL_CMD_GET_ANGLE_JOINT_DEG_MIN", "SERIAL_CMD_SET_ANGLE_JOINT_DEG_MAX", "SERIAL_CMD_GET_ANGLE_JOINT_DEG_MAX", "SERIAL_CMD_SAVE_SETTINGS", "SERIAL_CMD_LOAD_SETTINGS", "SERIAL_CMD_SET_MOTOR_SPEED", "SERIAL_CMD_GET_MOTOR_SPEED", "SERIAL_CMD_HOMING_SEQUENCE" });
            commandID.Location = new Point(12, 40);
            commandID.Name = "commandID";
            commandID.Size = new Size(328, 31);
            commandID.TabIndex = 0;
            commandID.Text = "SERIAL_CMD_EMPTY";
            commandID.SelectedIndexChanged += commandID_SelectedIndexChanged;
            // 
            // commandID_label
            // 
            commandID_label.AutoSize = true;
            commandID_label.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            commandID_label.Location = new Point(12, 9);
            commandID_label.Name = "commandID_label";
            commandID_label.Size = new Size(131, 28);
            commandID_label.TabIndex = 1;
            commandID_label.Text = "Command ID:";
            // 
            // targetID_label
            // 
            targetID_label.AutoSize = true;
            targetID_label.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            targetID_label.Location = new Point(483, 9);
            targetID_label.Name = "targetID_label";
            targetID_label.Size = new Size(94, 28);
            targetID_label.TabIndex = 2;
            targetID_label.Text = "Target ID:";
            // 
            // targetID
            // 
            targetID.Font = new Font("Segoe UI", 10.2F, FontStyle.Regular, GraphicsUnit.Point, 0);
            targetID.Location = new Point(483, 41);
            targetID.Maximum = new decimal(new int[] { 4, 0, 0, 0 });
            targetID.Minimum = new decimal(new int[] { 1, 0, 0, 0 });
            targetID.Name = "targetID";
            targetID.Size = new Size(94, 30);
            targetID.TabIndex = 3;
            targetID.Value = new decimal(new int[] { 1, 0, 0, 0 });
            targetID.ValueChanged += targetID_ValueChanged;
            // 
            // cmdParam
            // 
            cmdParam.DecimalPlaces = 5;
            cmdParam.Font = new Font("Segoe UI", 10.2F, FontStyle.Regular, GraphicsUnit.Point, 0);
            cmdParam.Increment = new decimal(new int[] { 1, 0, 0, 131072 });
            cmdParam.Location = new Point(583, 40);
            cmdParam.Maximum = new decimal(new int[] { 4096, 0, 0, 0 });
            cmdParam.Minimum = new decimal(new int[] { 4096, 0, 0, int.MinValue });
            cmdParam.Name = "cmdParam";
            cmdParam.Size = new Size(159, 30);
            cmdParam.TabIndex = 4;
            cmdParam.ThousandsSeparator = true;
            cmdParam.Value = new decimal(new int[] { 123456, 0, 0, 327680 });
            cmdParam.ValueChanged += cmdParam_ValueChanged;
            // 
            // cmdParam_label
            // 
            cmdParam_label.AutoSize = true;
            cmdParam_label.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            cmdParam_label.Location = new Point(583, 9);
            cmdParam_label.Name = "cmdParam_label";
            cmdParam_label.Size = new Size(104, 28);
            cmdParam_label.TabIndex = 5;
            cmdParam_label.Text = "Parameter:";
            // 
            // commandPreview
            // 
            commandPreview.Font = new Font("Segoe UI", 10.2F, FontStyle.Regular, GraphicsUnit.Point, 0);
            commandPreview.Location = new Point(12, 108);
            commandPreview.Name = "commandPreview";
            commandPreview.ReadOnly = true;
            commandPreview.Size = new Size(730, 30);
            commandPreview.TabIndex = 6;
            // 
            // commandView_label
            // 
            commandView_label.AutoSize = true;
            commandView_label.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            commandView_label.Location = new Point(12, 74);
            commandView_label.Name = "commandView_label";
            commandView_label.Size = new Size(179, 28);
            commandView_label.TabIndex = 7;
            commandView_label.Text = "Command Preview:";
            // 
            // comPort_label
            // 
            comPort_label.AutoSize = true;
            comPort_label.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            comPort_label.Location = new Point(12, 144);
            comPort_label.Name = "comPort_label";
            comPort_label.Size = new Size(101, 28);
            comPort_label.TabIndex = 8;
            comPort_label.Text = "COM Port:";
            // 
            // comPort
            // 
            comPort.Font = new Font("Segoe UI", 10.2F, FontStyle.Regular, GraphicsUnit.Point, 0);
            comPort.Location = new Point(119, 144);
            comPort.Maximum = new decimal(new int[] { 9, 0, 0, 0 });
            comPort.Name = "comPort";
            comPort.Size = new Size(37, 30);
            comPort.TabIndex = 9;
            comPort.Value = new decimal(new int[] { 4, 0, 0, 0 });
            // 
            // baudRate_label
            // 
            baudRate_label.AutoSize = true;
            baudRate_label.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            baudRate_label.Location = new Point(162, 144);
            baudRate_label.Name = "baudRate_label";
            baudRate_label.Size = new Size(104, 28);
            baudRate_label.TabIndex = 10;
            baudRate_label.Text = "Baud Rate:";
            // 
            // baudRate
            // 
            baudRate.Font = new Font("Segoe UI", 10.2F, FontStyle.Regular, GraphicsUnit.Point, 0);
            baudRate.Increment = new decimal(new int[] { 1000, 0, 0, 0 });
            baudRate.Location = new Point(280, 147);
            baudRate.Maximum = new decimal(new int[] { 256000, 0, 0, 0 });
            baudRate.Minimum = new decimal(new int[] { 9600, 0, 0, 0 });
            baudRate.Name = "baudRate";
            baudRate.Size = new Size(197, 30);
            baudRate.TabIndex = 11;
            baudRate.Value = new decimal(new int[] { 19200, 0, 0, 0 });
            baudRate.ValueChanged += baudRate_ValueChanged;
            // 
            // sendCommand
            // 
            sendCommand.Location = new Point(483, 147);
            sendCommand.Name = "sendCommand";
            sendCommand.Size = new Size(259, 29);
            sendCommand.TabIndex = 12;
            sendCommand.Text = "Send command";
            sendCommand.UseVisualStyleBackColor = true;
            sendCommand.Click += sendCommand_Click;
            // 
            // commandConsole
            // 
            commandConsole.Font = new Font("Segoe UI", 10.2F, FontStyle.Regular, GraphicsUnit.Point, 0);
            commandConsole.Location = new Point(12, 183);
            commandConsole.Name = "commandConsole";
            commandConsole.ReadOnly = true;
            commandConsole.Size = new Size(730, 255);
            commandConsole.TabIndex = 13;
            commandConsole.Text = "";
            // 
            // controllerID
            // 
            controllerID.Font = new Font("Segoe UI", 10.2F, FontStyle.Regular, GraphicsUnit.Point, 0);
            controllerID.Location = new Point(346, 41);
            controllerID.Maximum = new decimal(new int[] { 12, 0, 0, 0 });
            controllerID.Minimum = new decimal(new int[] { 1, 0, 0, 0 });
            controllerID.Name = "controllerID";
            controllerID.Size = new Size(131, 30);
            controllerID.TabIndex = 15;
            controllerID.Value = new decimal(new int[] { 1, 0, 0, 0 });
            // 
            // controllerIDlabel
            // 
            controllerIDlabel.AutoSize = true;
            controllerIDlabel.Font = new Font("Segoe UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 0);
            controllerIDlabel.Location = new Point(346, 9);
            controllerIDlabel.Name = "controllerIDlabel";
            controllerIDlabel.Size = new Size(128, 28);
            controllerIDlabel.TabIndex = 14;
            controllerIDlabel.Text = "Controller ID:";
            // 
            // DC_Motor_Controller_PCB_Command_Assembler
            // 
            AutoScaleDimensions = new SizeF(8F, 20F);
            AutoScaleMode = AutoScaleMode.Font;
            BackColor = SystemColors.ControlLight;
            ClientSize = new Size(754, 450);
            Controls.Add(controllerID);
            Controls.Add(controllerIDlabel);
            Controls.Add(commandConsole);
            Controls.Add(sendCommand);
            Controls.Add(baudRate);
            Controls.Add(baudRate_label);
            Controls.Add(comPort);
            Controls.Add(comPort_label);
            Controls.Add(commandView_label);
            Controls.Add(commandPreview);
            Controls.Add(cmdParam_label);
            Controls.Add(cmdParam);
            Controls.Add(targetID);
            Controls.Add(targetID_label);
            Controls.Add(commandID_label);
            Controls.Add(commandID);
            FormBorderStyle = FormBorderStyle.FixedSingle;
            Icon = (Icon)resources.GetObject("$this.Icon");
            MaximizeBox = false;
            Name = "DC_Motor_Controller_PCB_Command_Assembler";
            Text = "DC Motor Controller PCB - Serial Command Assembler";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)targetID).EndInit();
            ((System.ComponentModel.ISupportInitialize)cmdParam).EndInit();
            ((System.ComponentModel.ISupportInitialize)comPort).EndInit();
            ((System.ComponentModel.ISupportInitialize)baudRate).EndInit();
            ((System.ComponentModel.ISupportInitialize)controllerID).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private ComboBox commandID;
        private Label commandID_label;
        private Label targetID_label;
        private NumericUpDown targetID;
        private NumericUpDown cmdParam;
        private Label cmdParam_label;
        private TextBox commandPreview;
        private Label commandView_label;
        private Label comPort_label;
        private NumericUpDown comPort;
        private Label baudRate_label;
        private NumericUpDown baudRate;
        private Button sendCommand;
        private RichTextBox commandConsole;
        private NumericUpDown controllerID;
        private Label controllerIDlabel;
    }
}
