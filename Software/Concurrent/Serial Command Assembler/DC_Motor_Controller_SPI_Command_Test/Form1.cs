using System;
using System.Timers;
using System.IO.Ports;
using System.Runtime.InteropServices.ObjectiveC;
using System.Text;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace DC_Motor_Controller_SPI_Command_Test 
    // no longer SPI but whatever, this works in a very similar way
{
    public partial class DC_Motor_Controller_PCB_Command_Assembler : Form
    {
        SerialPort port = new SerialPort();
        int last_port = 0, last_baud = 0;
        System.Timers.Timer comsTimeout;
        int comsTimeout_delay_ms = 5000;

        public DC_Motor_Controller_PCB_Command_Assembler()
        {
            InitializeComponent();

            comsTimeout = new System.Timers.Timer(comsTimeout_delay_ms);
            comsTimeout.Elapsed += async (sender, e) => await SerialTimeout();
            comsTimeout.AutoReset = false;

            commandConsole.Text += "Available ports: \n";
            if (SerialPort.GetPortNames().Length == 0)
                commandConsole.Text += "\tNone\n";
            foreach (string s in SerialPort.GetPortNames())
                commandConsole.Text += "\t" + s + "\n";
            // set the current caret position to the end
            commandConsole.SelectionStart = commandConsole.Text.Length;
            // scroll it automatically
            commandConsole.ScrollToCaret();
            Assemble_Command();
        }

        private Task SerialTimeout()
        {
            commandConsole.Invoke(new Action(() =>
            {
                commandConsole.Text += "Error: No response\n";
                // set the current caret position to the end
                commandConsole.SelectionStart = commandConsole.Text.Length;
                // scroll it automatically
                commandConsole.ScrollToCaret();
            }));
            return Task.CompletedTask;
        }

        private void si_DataReceived(string data)
        {
            comsTimeout.Stop();
            commandConsole.Text += "Received response: " + data + "\n";
            // set the current caret position to the end
            commandConsole.SelectionStart = commandConsole.Text.Length;
            // scroll it automatically
            commandConsole.ScrollToCaret();
        }

        private void sp_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            string data = port.ReadTo("\n");
            this.BeginInvoke(si_DataReceived, new object[] { data });
        }

        private bool OpenSerialConnection()
        {
            if (!port.IsOpen)
            {
                try
                {
                    port.BaudRate = (int)baudRate.Value;
                    port.PortName = "COM" + ((int)comPort.Value).ToString();
                    port.DataReceived += new SerialDataReceivedEventHandler(sp_DataReceived);
                    port.Open();
                }
                catch (UnauthorizedAccessException ex)
                {
                    commandConsole.Text += "Error: " + ex.Message + "\n";
                    // set the current caret position to the end
                    commandConsole.SelectionStart = commandConsole.Text.Length;
                    // scroll it automatically
                    commandConsole.ScrollToCaret();
                    return false;
                }
                catch (Exception ex)
                {
                    commandConsole.Text += "Error: " + ex.Message + "\n";
                    // set the current caret position to the end
                    commandConsole.SelectionStart = commandConsole.Text.Length;
                    // scroll it automatically
                    commandConsole.ScrollToCaret();
                    return false;
                }
                commandConsole.Text += "Successfully established serial connection on " + port.PortName + "\n";
                // set the current caret position to the end
                commandConsole.SelectionStart = commandConsole.Text.Length;
                // scroll it automatically
                commandConsole.ScrollToCaret();
            }
            return true;
        }

        private void make_command(int cmdID, bool sendTrg, bool sendParam)
        {
            targetID.Visible = sendTrg;
            cmdParam.Visible = sendParam;
            int trgID = sendTrg ? (int)targetID.Value : 0;
            float param = sendParam ? (float)cmdParam.Value : 0.0f;
            commandPreview.Text =  Convert.ToString(controllerID.Value) + " "
                + Convert.ToString(cmdID) + " " + Convert.ToString(trgID)
                + " "  + Convert.ToString(param);
        }

        private void Assemble_Command()
        {
            if (commandID.Text == "SERIAL_CMD_EMPTY")
            {
                make_command(0, false, false);
            }
            else if (commandID.Text == "SERIAL_CMD_SET_TARGET_ANGLE")
            {
                make_command(1, true, true);
            }
            else if (commandID.Text == "SERIAL_CMD_GET_TARGET_ANGLE")
            {
                make_command(2, true, false);
            }
            else if (commandID.Text == "SERIAL_CMD_GET_CURRENT_ANGLE")
            {
                make_command(3, true, false);
            }
            else if (commandID.Text == "SERIAL_CMD_SET_PID_ENABLE")
            {
                make_command(4, true, true);
            }
            else if (commandID.Text == "SERIAL_CMD_SET_PID_ENABLE")
            {
                make_command(5, true, false);
            }
            else if (commandID.Text == "SERIAL_CMD_PID_SET_P")
            {
                make_command(6, true, true);
            }
            else if (commandID.Text == "SERIAL_CMD_PID_GET_P")
            {
                make_command(7, true, false);
            }
            else if (commandID.Text == "SERIAL_CMD_PID_SET_I")
            {
                make_command(8, true, true);
            }
            else if (commandID.Text == "SERIAL_CMD_PID_GET_I")
            {
                make_command(9, true, false);
            }
            else if (commandID.Text == "SERIAL_CMD_PID_SET_D")
            {
                make_command(10, true, true);
            }
            else if (commandID.Text == "SERIAL_CMD_PID_GET_D")
            {
                make_command(11, true, false);
            }
            else if (commandID.Text == "SERIAL_CMD_SET_ANGLE_CONV_DEG_MIN")
            { // Set min. deg value corresponding to min deg value for potentiometer readings
                make_command(12, true, true);
            }
            else if (commandID.Text == "SERIAL_CMD_GET_ANGLE_CONV_DEG_MIN")
            { // Set min. deg value corresponding to min deg value for potentiometer readings
                make_command(13, true, false);
            }
            else if (commandID.Text == "SERIAL_CMD_SET_ANGLE_CONV_DEG_MAX")
            { // Set max. deg value corresponding to min deg value for potentiometer readings
                make_command(14, true, true);
            }
            else if (commandID.Text == "SERIAL_CMD_GET_ANGLE_CONV_DEG_MAX")
            { // Set max. deg value corresponding to min deg value for potentiometer readings
                make_command(15, true, false);
            }
            else if (commandID.Text == "SERIAL_CMD_SET_ANGLE_JOINT_DEG_MIN")
            { 
                make_command(16, true, true);
            }
            else if (commandID.Text == "SERIAL_CMD_GET_ANGLE_JOINT_DEG_MIN")
            { 
                make_command(17, true, false);
            }
            else if (commandID.Text == "SERIAL_CMD_SET_ANGLE_JOINT_DEG_MAX")
            { 
                make_command(18, true, true);
            }
            else if (commandID.Text == "SERIAL_CMD_GET_ANGLE_JOINT_DEG_MAX")
            { 
                make_command(19, true, false);
            }
            else if (commandID.Text == "SERIAL_CMD_SAVE_SETTINGS")
            {
                make_command(20, false, false);
            }
            else if (commandID.Text == "SERIAL_CMD_LOAD_SETTINGS")
            {
                make_command(21, false, false);
            }
            else if (commandID.Text == "SERIAL_CMD_SET_MOTOR_SPEED")
            {
                make_command(22, true, true);
            }
            else if (commandID.Text == "SERIAL_CMD_GET_MOTOR_SPEED")
            {
                make_command(23, true, false);
            }
            else if (commandID.Text == "SERIAL_CMD_HOMING_SEQUENCE")
            {
                make_command(24, true, false);
            }
            else // this will cause the slave to ignore the
            {    // command since it cannot be identified
                make_command(25, false, false);
            }
        }

        private void commandID_SelectedIndexChanged(object sender, EventArgs e)
        {
            Assemble_Command();
        }

        private void targetID_ValueChanged(object sender, EventArgs e)
        {
            Assemble_Command();
        }

        private void cmdParam_ValueChanged(object sender, EventArgs e)
        {
            Assemble_Command();
        }

        private void sendCommand_Click(object sender, EventArgs e)
        {
            if (last_port != (int)comPort.Value || last_baud != (int)baudRate.Value)
            {
                last_port = (int)comPort.Value;
                last_baud = (int)baudRate.Value;
                port.Close(); // so that we reopen it with the new settings later
            }

            Assemble_Command();
            if (!OpenSerialConnection()) return;

            try
            {
                port.Write(commandPreview.Text + "\n");
            }
            catch (Exception ex)
            {
                commandConsole.Text += "Failed to send command: " + commandPreview.Text + "\n";
                commandConsole.Text += "Error message: " + ex.Message + "\n";
                // set the current caret position to the end
                commandConsole.SelectionStart = commandConsole.Text.Length;
                // scroll it automatically
                commandConsole.ScrollToCaret();
                return;
            }
            comsTimeout.Start();
            commandConsole.Text += "Successfully sent command: " + commandPreview.Text + "\n";
            // set the current caret position to the end
            commandConsole.SelectionStart = commandConsole.Text.Length;
            // scroll it automatically
            commandConsole.ScrollToCaret();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void Form1_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (port.IsOpen) // release control over serial port when closing the program
                port.Close(); // otherwise you might not be able to program using arduino IDE
        }

        private void baudRate_ValueChanged(object sender, EventArgs e)
        {

        }
    }
}
