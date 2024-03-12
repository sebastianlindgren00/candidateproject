﻿namespace Stitcher_GUI
{
    partial class stitcher_form
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(stitcher_form));
            this.left_input_groupbox = new System.Windows.Forms.GroupBox();
            this.cubemapComboBox = new System.Windows.Forms.ComboBox();
            this.label19 = new System.Windows.Forms.Label();
            this.browse_bottom_L_button = new System.Windows.Forms.Button();
            this.input_bottom_L_textbox = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.browse_top_L_button = new System.Windows.Forms.Button();
            this.input_top_L_textbox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.browse_right_L_button = new System.Windows.Forms.Button();
            this.input_right_L_textbox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.browse_left_L_button = new System.Windows.Forms.Button();
            this.input_left_L_textbox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.setting_groupBox = new System.Windows.Forms.GroupBox();
            this.dome_diameter_units_label = new System.Windows.Forms.Label();
            this.eye_separation_units_label = new System.Windows.Forms.Label();
            this.domeDiameterInput = new System.Windows.Forms.TextBox();
            this.dome_diameter_label = new System.Windows.Forms.Label();
            this.eyeSeparationInput = new System.Windows.Forms.TextBox();
            this.eye_separation_label = new System.Windows.Forms.Label();
            this.stereo_checkBox = new System.Windows.Forms.CheckBox();
            this.transform_groupbox = new System.Windows.Forms.GroupBox();
            this.label10 = new System.Windows.Forms.Label();
            this.bottom_transform_comboBox = new System.Windows.Forms.ComboBox();
            this.label11 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.top_transform_comboBox = new System.Windows.Forms.ComboBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.right_transform_comboBox = new System.Windows.Forms.ComboBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.left_transform_comboBox = new System.Windows.Forms.ComboBox();
            this.LeftTransformLabel = new System.Windows.Forms.Label();
            this.right_input_groupbox = new System.Windows.Forms.GroupBox();
            this.browse_bottom_R_button = new System.Windows.Forms.Button();
            this.input_bottom_R_textbox = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.browse_top_R_button = new System.Windows.Forms.Button();
            this.input_top_R_textbox = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.browse_right_R_button = new System.Windows.Forms.Button();
            this.input_right_R_textbox = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.browse_left_R_button = new System.Windows.Forms.Button();
            this.input_left_R_textbox = new System.Windows.Forms.TextBox();
            this.label15 = new System.Windows.Forms.Label();
            this.output_groupBox = new System.Windows.Forms.GroupBox();
            this.cubicCheckBox = new System.Windows.Forms.CheckBox();
            this.compressionTrackBar = new System.Windows.Forms.TrackBar();
            this.CompressionLabel = new System.Windows.Forms.Label();
            this.start_index_textBox = new System.Windows.Forms.TextBox();
            this.start_button = new System.Windows.Forms.Button();
            this.label17 = new System.Windows.Forms.Label();
            this.format_comboBox = new System.Windows.Forms.ComboBox();
            this.formatLabel = new System.Windows.Forms.Label();
            this.FileNameTextBox = new System.Windows.Forms.TextBox();
            this.filename = new System.Windows.Forms.Label();
            this.browseRightOutputPathButton = new System.Windows.Forms.Button();
            this.right_output_path_textbox = new System.Windows.Forms.TextBox();
            this.RightOutputPathLabel = new System.Windows.Forms.Label();
            this.browseLeftOutputPathButton = new System.Windows.Forms.Button();
            this.left_output_path_textbox = new System.Windows.Forms.TextBox();
            this.LeftOutputPathLabel = new System.Windows.Forms.Label();
            this.alpha_checkBox = new System.Windows.Forms.CheckBox();
            this.resolution_comboBox = new System.Windows.Forms.ComboBox();
            this.label16 = new System.Windows.Forms.Label();
            this.Sequence_groupBox = new System.Windows.Forms.GroupBox();
            this.input_stopindex_textBox = new System.Windows.Forms.TextBox();
            this.label18 = new System.Windows.Forms.Label();
            this.input_startindex_textBox = new System.Windows.Forms.TextBox();
            this.input_startindex_label = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.FXAACheckBox = new System.Windows.Forms.CheckBox();
            this.samples = new System.Windows.Forms.Label();
            this.MSAA_ComboBox = new System.Windows.Forms.ComboBox();
            this.MSAALabel = new System.Windows.Forms.Label();
            this.left_input_groupbox.SuspendLayout();
            this.setting_groupBox.SuspendLayout();
            this.transform_groupbox.SuspendLayout();
            this.right_input_groupbox.SuspendLayout();
            this.output_groupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.compressionTrackBar)).BeginInit();
            this.Sequence_groupBox.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // left_input_groupbox
            // 
            this.left_input_groupbox.Controls.Add(this.cubemapComboBox);
            this.left_input_groupbox.Controls.Add(this.label19);
            this.left_input_groupbox.Controls.Add(this.browse_bottom_L_button);
            this.left_input_groupbox.Controls.Add(this.input_bottom_L_textbox);
            this.left_input_groupbox.Controls.Add(this.label4);
            this.left_input_groupbox.Controls.Add(this.browse_top_L_button);
            this.left_input_groupbox.Controls.Add(this.input_top_L_textbox);
            this.left_input_groupbox.Controls.Add(this.label3);
            this.left_input_groupbox.Controls.Add(this.browse_right_L_button);
            this.left_input_groupbox.Controls.Add(this.input_right_L_textbox);
            this.left_input_groupbox.Controls.Add(this.label2);
            this.left_input_groupbox.Controls.Add(this.browse_left_L_button);
            this.left_input_groupbox.Controls.Add(this.input_left_L_textbox);
            this.left_input_groupbox.Controls.Add(this.label1);
            this.left_input_groupbox.Location = new System.Drawing.Point(20, 108);
            this.left_input_groupbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.left_input_groupbox.Name = "left_input_groupbox";
            this.left_input_groupbox.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.left_input_groupbox.Size = new System.Drawing.Size(760, 305);
            this.left_input_groupbox.TabIndex = 0;
            this.left_input_groupbox.TabStop = false;
            this.left_input_groupbox.Text = "Input";
            // 
            // cubemapComboBox
            // 
            this.cubemapComboBox.FormattingEnabled = true;
            this.cubemapComboBox.Items.AddRange(new object[] {
            "256x256",
            "512x512",
            "1024x1024",
            "2048x2048",
            "3072x3072",
            "4096x4096",
            "8192x8192"});
            this.cubemapComboBox.Location = new System.Drawing.Point(189, 42);
            this.cubemapComboBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.cubemapComboBox.Name = "cubemapComboBox";
            this.cubemapComboBox.Size = new System.Drawing.Size(140, 28);
            this.cubemapComboBox.TabIndex = 13;
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(27, 46);
            this.label19.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(151, 20);
            this.label19.TabIndex = 12;
            this.label19.Text = "Cubemap resolution";
            // 
            // browse_bottom_L_button
            // 
            this.browse_bottom_L_button.Location = new System.Drawing.Point(688, 225);
            this.browse_bottom_L_button.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.browse_bottom_L_button.Name = "browse_bottom_L_button";
            this.browse_bottom_L_button.Size = new System.Drawing.Size(48, 35);
            this.browse_bottom_L_button.TabIndex = 11;
            this.browse_bottom_L_button.Text = "...";
            this.browse_bottom_L_button.UseVisualStyleBackColor = true;
            this.browse_bottom_L_button.Click += new System.EventHandler(this.browse_bottom_L_button_Click);
            // 
            // input_bottom_L_textbox
            // 
            this.input_bottom_L_textbox.Location = new System.Drawing.Point(94, 226);
            this.input_bottom_L_textbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.input_bottom_L_textbox.Name = "input_bottom_L_textbox";
            this.input_bottom_L_textbox.Size = new System.Drawing.Size(580, 26);
            this.input_bottom_L_textbox.TabIndex = 10;
            this.input_bottom_L_textbox.TextChanged += new System.EventHandler(this.input_bottom_L_textbox_TextChanged);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(28, 231);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(61, 20);
            this.label4.TabIndex = 9;
            this.label4.Text = "Bottom";
            // 
            // browse_top_L_button
            // 
            this.browse_top_L_button.Location = new System.Drawing.Point(688, 183);
            this.browse_top_L_button.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.browse_top_L_button.Name = "browse_top_L_button";
            this.browse_top_L_button.Size = new System.Drawing.Size(48, 35);
            this.browse_top_L_button.TabIndex = 8;
            this.browse_top_L_button.Text = "...";
            this.browse_top_L_button.UseVisualStyleBackColor = true;
            this.browse_top_L_button.Click += new System.EventHandler(this.browse_top_L_button_Click);
            // 
            // input_top_L_textbox
            // 
            this.input_top_L_textbox.Location = new System.Drawing.Point(94, 185);
            this.input_top_L_textbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.input_top_L_textbox.Name = "input_top_L_textbox";
            this.input_top_L_textbox.Size = new System.Drawing.Size(580, 26);
            this.input_top_L_textbox.TabIndex = 7;
            this.input_top_L_textbox.TextChanged += new System.EventHandler(this.input_top_L_textbox_TextChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(28, 189);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(36, 20);
            this.label3.TabIndex = 6;
            this.label3.Text = "Top";
            // 
            // browse_right_L_button
            // 
            this.browse_right_L_button.Location = new System.Drawing.Point(688, 138);
            this.browse_right_L_button.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.browse_right_L_button.Name = "browse_right_L_button";
            this.browse_right_L_button.Size = new System.Drawing.Size(48, 35);
            this.browse_right_L_button.TabIndex = 5;
            this.browse_right_L_button.Text = "...";
            this.browse_right_L_button.UseVisualStyleBackColor = true;
            this.browse_right_L_button.Click += new System.EventHandler(this.browse_right_L_button_Click);
            // 
            // input_right_L_textbox
            // 
            this.input_right_L_textbox.Location = new System.Drawing.Point(94, 140);
            this.input_right_L_textbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.input_right_L_textbox.Name = "input_right_L_textbox";
            this.input_right_L_textbox.Size = new System.Drawing.Size(580, 26);
            this.input_right_L_textbox.TabIndex = 4;
            this.input_right_L_textbox.TextChanged += new System.EventHandler(this.input_right_L_textbox_TextChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(28, 145);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(47, 20);
            this.label2.TabIndex = 3;
            this.label2.Text = "Right";
            // 
            // browse_left_L_button
            // 
            this.browse_left_L_button.Location = new System.Drawing.Point(688, 95);
            this.browse_left_L_button.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.browse_left_L_button.Name = "browse_left_L_button";
            this.browse_left_L_button.Size = new System.Drawing.Size(48, 35);
            this.browse_left_L_button.TabIndex = 2;
            this.browse_left_L_button.Text = "...";
            this.browse_left_L_button.UseVisualStyleBackColor = true;
            this.browse_left_L_button.Click += new System.EventHandler(this.browse_left_L_button_Click);
            // 
            // input_left_L_textbox
            // 
            this.input_left_L_textbox.Location = new System.Drawing.Point(94, 97);
            this.input_left_L_textbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.input_left_L_textbox.Name = "input_left_L_textbox";
            this.input_left_L_textbox.Size = new System.Drawing.Size(580, 26);
            this.input_left_L_textbox.TabIndex = 1;
            this.input_left_L_textbox.TextChanged += new System.EventHandler(this.input_left_L_textbox_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(28, 102);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(37, 20);
            this.label1.TabIndex = 0;
            this.label1.Text = "Left";
            // 
            // setting_groupBox
            // 
            this.setting_groupBox.Controls.Add(this.dome_diameter_units_label);
            this.setting_groupBox.Controls.Add(this.eye_separation_units_label);
            this.setting_groupBox.Controls.Add(this.domeDiameterInput);
            this.setting_groupBox.Controls.Add(this.dome_diameter_label);
            this.setting_groupBox.Controls.Add(this.eyeSeparationInput);
            this.setting_groupBox.Controls.Add(this.eye_separation_label);
            this.setting_groupBox.Controls.Add(this.stereo_checkBox);
            this.setting_groupBox.Location = new System.Drawing.Point(788, 18);
            this.setting_groupBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.setting_groupBox.Name = "setting_groupBox";
            this.setting_groupBox.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.setting_groupBox.Size = new System.Drawing.Size(358, 177);
            this.setting_groupBox.TabIndex = 1;
            this.setting_groupBox.TabStop = false;
            this.setting_groupBox.Text = "Settings";
            // 
            // dome_diameter_units_label
            // 
            this.dome_diameter_units_label.AutoSize = true;
            this.dome_diameter_units_label.Location = new System.Drawing.Point(254, 140);
            this.dome_diameter_units_label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.dome_diameter_units_label.Name = "dome_diameter_units_label";
            this.dome_diameter_units_label.Size = new System.Drawing.Size(58, 20);
            this.dome_diameter_units_label.TabIndex = 7;
            this.dome_diameter_units_label.Text = "meters";
            // 
            // eye_separation_units_label
            // 
            this.eye_separation_units_label.AutoSize = true;
            this.eye_separation_units_label.Location = new System.Drawing.Point(254, 91);
            this.eye_separation_units_label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.eye_separation_units_label.Name = "eye_separation_units_label";
            this.eye_separation_units_label.Size = new System.Drawing.Size(35, 20);
            this.eye_separation_units_label.TabIndex = 6;
            this.eye_separation_units_label.Text = "mm";
            // 
            // domeDiameterInput
            // 
            this.domeDiameterInput.Location = new System.Drawing.Point(162, 135);
            this.domeDiameterInput.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.domeDiameterInput.MaxLength = 64;
            this.domeDiameterInput.Name = "domeDiameterInput";
            this.domeDiameterInput.Size = new System.Drawing.Size(84, 26);
            this.domeDiameterInput.TabIndex = 5;
            this.domeDiameterInput.Text = "14.80";
            this.domeDiameterInput.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.domeDiameterInput.TextChanged += new System.EventHandler(this.domeDiameterInput_TextChanged);
            // 
            // dome_diameter_label
            // 
            this.dome_diameter_label.AutoSize = true;
            this.dome_diameter_label.Location = new System.Drawing.Point(21, 140);
            this.dome_diameter_label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.dome_diameter_label.Name = "dome_diameter_label";
            this.dome_diameter_label.Size = new System.Drawing.Size(118, 20);
            this.dome_diameter_label.TabIndex = 4;
            this.dome_diameter_label.Text = "Dome diameter";
            // 
            // eyeSeparationInput
            // 
            this.eyeSeparationInput.Location = new System.Drawing.Point(162, 86);
            this.eyeSeparationInput.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.eyeSeparationInput.MaxLength = 64;
            this.eyeSeparationInput.Name = "eyeSeparationInput";
            this.eyeSeparationInput.Size = new System.Drawing.Size(84, 26);
            this.eyeSeparationInput.TabIndex = 3;
            this.eyeSeparationInput.Text = "65.00";
            this.eyeSeparationInput.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.eyeSeparationInput.TextChanged += new System.EventHandler(this.eyeSeparationInput_TextChanged);
            // 
            // eye_separation_label
            // 
            this.eye_separation_label.AutoSize = true;
            this.eye_separation_label.Location = new System.Drawing.Point(21, 91);
            this.eye_separation_label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.eye_separation_label.Name = "eye_separation_label";
            this.eye_separation_label.Size = new System.Drawing.Size(115, 20);
            this.eye_separation_label.TabIndex = 2;
            this.eye_separation_label.Text = "Eye separation";
            // 
            // stereo_checkBox
            // 
            this.stereo_checkBox.AutoSize = true;
            this.stereo_checkBox.Location = new System.Drawing.Point(27, 42);
            this.stereo_checkBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.stereo_checkBox.Name = "stereo_checkBox";
            this.stereo_checkBox.Size = new System.Drawing.Size(202, 24);
            this.stereo_checkBox.TabIndex = 1;
            this.stereo_checkBox.Text = "Stereoscopic (3D) input";
            this.stereo_checkBox.UseVisualStyleBackColor = true;
            this.stereo_checkBox.CheckedChanged += new System.EventHandler(this.stereo_checkBox_CheckedChanged);
            // 
            // transform_groupbox
            // 
            this.transform_groupbox.Controls.Add(this.label10);
            this.transform_groupbox.Controls.Add(this.bottom_transform_comboBox);
            this.transform_groupbox.Controls.Add(this.label11);
            this.transform_groupbox.Controls.Add(this.label8);
            this.transform_groupbox.Controls.Add(this.top_transform_comboBox);
            this.transform_groupbox.Controls.Add(this.label9);
            this.transform_groupbox.Controls.Add(this.label6);
            this.transform_groupbox.Controls.Add(this.right_transform_comboBox);
            this.transform_groupbox.Controls.Add(this.label7);
            this.transform_groupbox.Controls.Add(this.label5);
            this.transform_groupbox.Controls.Add(this.left_transform_comboBox);
            this.transform_groupbox.Controls.Add(this.LeftTransformLabel);
            this.transform_groupbox.Location = new System.Drawing.Point(1155, 18);
            this.transform_groupbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.transform_groupbox.Name = "transform_groupbox";
            this.transform_groupbox.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.transform_groupbox.Size = new System.Drawing.Size(392, 345);
            this.transform_groupbox.TabIndex = 2;
            this.transform_groupbox.TabStop = false;
            this.transform_groupbox.Text = "Transform";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(308, 189);
            this.label10.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(67, 20);
            this.label10.TabIndex = 11;
            this.label10.Text = "degrees";
            // 
            // bottom_transform_comboBox
            // 
            this.bottom_transform_comboBox.FormattingEnabled = true;
            this.bottom_transform_comboBox.Items.AddRange(new object[] {
            "0",
            "90",
            "180",
            "270"});
            this.bottom_transform_comboBox.Location = new System.Drawing.Point(212, 185);
            this.bottom_transform_comboBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.bottom_transform_comboBox.Name = "bottom_transform_comboBox";
            this.bottom_transform_comboBox.Size = new System.Drawing.Size(85, 28);
            this.bottom_transform_comboBox.TabIndex = 10;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(34, 189);
            this.label11.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(176, 20);
            this.label11.TabIndex = 9;
            this.label11.Text = "Bottom camera rotation";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(308, 149);
            this.label8.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(67, 20);
            this.label8.TabIndex = 8;
            this.label8.Text = "degrees";
            // 
            // top_transform_comboBox
            // 
            this.top_transform_comboBox.FormattingEnabled = true;
            this.top_transform_comboBox.Items.AddRange(new object[] {
            "0",
            "90",
            "180",
            "270"});
            this.top_transform_comboBox.Location = new System.Drawing.Point(212, 145);
            this.top_transform_comboBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.top_transform_comboBox.Name = "top_transform_comboBox";
            this.top_transform_comboBox.Size = new System.Drawing.Size(85, 28);
            this.top_transform_comboBox.TabIndex = 7;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(34, 149);
            this.label9.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(151, 20);
            this.label9.TabIndex = 6;
            this.label9.Text = "Top camera rotation";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(308, 109);
            this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(67, 20);
            this.label6.TabIndex = 5;
            this.label6.Text = "degrees";
            // 
            // right_transform_comboBox
            // 
            this.right_transform_comboBox.FormattingEnabled = true;
            this.right_transform_comboBox.Items.AddRange(new object[] {
            "0",
            "90",
            "180",
            "270"});
            this.right_transform_comboBox.Location = new System.Drawing.Point(212, 105);
            this.right_transform_comboBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.right_transform_comboBox.Name = "right_transform_comboBox";
            this.right_transform_comboBox.Size = new System.Drawing.Size(85, 28);
            this.right_transform_comboBox.TabIndex = 4;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(34, 109);
            this.label7.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(162, 20);
            this.label7.TabIndex = 3;
            this.label7.Text = "Right camera rotation";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(308, 69);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(67, 20);
            this.label5.TabIndex = 2;
            this.label5.Text = "degrees";
            // 
            // left_transform_comboBox
            // 
            this.left_transform_comboBox.FormattingEnabled = true;
            this.left_transform_comboBox.Items.AddRange(new object[] {
            "0",
            "90",
            "180",
            "270"});
            this.left_transform_comboBox.Location = new System.Drawing.Point(212, 65);
            this.left_transform_comboBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.left_transform_comboBox.Name = "left_transform_comboBox";
            this.left_transform_comboBox.Size = new System.Drawing.Size(85, 28);
            this.left_transform_comboBox.TabIndex = 1;
            // 
            // LeftTransformLabel
            // 
            this.LeftTransformLabel.AutoSize = true;
            this.LeftTransformLabel.Location = new System.Drawing.Point(34, 69);
            this.LeftTransformLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.LeftTransformLabel.Name = "LeftTransformLabel";
            this.LeftTransformLabel.Size = new System.Drawing.Size(152, 20);
            this.LeftTransformLabel.TabIndex = 0;
            this.LeftTransformLabel.Text = "Left camera rotation";
            // 
            // right_input_groupbox
            // 
            this.right_input_groupbox.Controls.Add(this.browse_bottom_R_button);
            this.right_input_groupbox.Controls.Add(this.input_bottom_R_textbox);
            this.right_input_groupbox.Controls.Add(this.label12);
            this.right_input_groupbox.Controls.Add(this.browse_top_R_button);
            this.right_input_groupbox.Controls.Add(this.input_top_R_textbox);
            this.right_input_groupbox.Controls.Add(this.label13);
            this.right_input_groupbox.Controls.Add(this.browse_right_R_button);
            this.right_input_groupbox.Controls.Add(this.input_right_R_textbox);
            this.right_input_groupbox.Controls.Add(this.label14);
            this.right_input_groupbox.Controls.Add(this.browse_left_R_button);
            this.right_input_groupbox.Controls.Add(this.input_left_R_textbox);
            this.right_input_groupbox.Controls.Add(this.label15);
            this.right_input_groupbox.Location = new System.Drawing.Point(18, 422);
            this.right_input_groupbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.right_input_groupbox.Name = "right_input_groupbox";
            this.right_input_groupbox.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.right_input_groupbox.Size = new System.Drawing.Size(760, 269);
            this.right_input_groupbox.TabIndex = 12;
            this.right_input_groupbox.TabStop = false;
            this.right_input_groupbox.Text = "Right eye input";
            // 
            // browse_bottom_R_button
            // 
            this.browse_bottom_R_button.Location = new System.Drawing.Point(688, 191);
            this.browse_bottom_R_button.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.browse_bottom_R_button.Name = "browse_bottom_R_button";
            this.browse_bottom_R_button.Size = new System.Drawing.Size(48, 35);
            this.browse_bottom_R_button.TabIndex = 11;
            this.browse_bottom_R_button.Text = "...";
            this.browse_bottom_R_button.UseVisualStyleBackColor = true;
            this.browse_bottom_R_button.Click += new System.EventHandler(this.browse_bottom_R_button_Click);
            // 
            // input_bottom_R_textbox
            // 
            this.input_bottom_R_textbox.Location = new System.Drawing.Point(94, 192);
            this.input_bottom_R_textbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.input_bottom_R_textbox.Name = "input_bottom_R_textbox";
            this.input_bottom_R_textbox.Size = new System.Drawing.Size(580, 26);
            this.input_bottom_R_textbox.TabIndex = 10;
            this.input_bottom_R_textbox.TextChanged += new System.EventHandler(this.input_bottom_R_textbox_TextChanged);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(28, 197);
            this.label12.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(61, 20);
            this.label12.TabIndex = 9;
            this.label12.Text = "Bottom";
            // 
            // browse_top_R_button
            // 
            this.browse_top_R_button.Location = new System.Drawing.Point(688, 149);
            this.browse_top_R_button.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.browse_top_R_button.Name = "browse_top_R_button";
            this.browse_top_R_button.Size = new System.Drawing.Size(48, 35);
            this.browse_top_R_button.TabIndex = 8;
            this.browse_top_R_button.Text = "...";
            this.browse_top_R_button.UseVisualStyleBackColor = true;
            this.browse_top_R_button.Click += new System.EventHandler(this.browse_top_R_button_Click);
            // 
            // input_top_R_textbox
            // 
            this.input_top_R_textbox.Location = new System.Drawing.Point(94, 151);
            this.input_top_R_textbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.input_top_R_textbox.Name = "input_top_R_textbox";
            this.input_top_R_textbox.Size = new System.Drawing.Size(580, 26);
            this.input_top_R_textbox.TabIndex = 7;
            this.input_top_R_textbox.TextChanged += new System.EventHandler(this.input_top_R_textbox_TextChanged);
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(28, 155);
            this.label13.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(36, 20);
            this.label13.TabIndex = 6;
            this.label13.Text = "Top";
            // 
            // browse_right_R_button
            // 
            this.browse_right_R_button.Location = new System.Drawing.Point(688, 105);
            this.browse_right_R_button.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.browse_right_R_button.Name = "browse_right_R_button";
            this.browse_right_R_button.Size = new System.Drawing.Size(48, 35);
            this.browse_right_R_button.TabIndex = 5;
            this.browse_right_R_button.Text = "...";
            this.browse_right_R_button.UseVisualStyleBackColor = true;
            this.browse_right_R_button.Click += new System.EventHandler(this.browse_right_R_button_Click);
            // 
            // input_right_R_textbox
            // 
            this.input_right_R_textbox.Location = new System.Drawing.Point(94, 106);
            this.input_right_R_textbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.input_right_R_textbox.Name = "input_right_R_textbox";
            this.input_right_R_textbox.Size = new System.Drawing.Size(580, 26);
            this.input_right_R_textbox.TabIndex = 4;
            this.input_right_R_textbox.TextChanged += new System.EventHandler(this.input_right_R_textbox_TextChanged);
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(28, 111);
            this.label14.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(47, 20);
            this.label14.TabIndex = 3;
            this.label14.Text = "Right";
            // 
            // browse_left_R_button
            // 
            this.browse_left_R_button.Location = new System.Drawing.Point(688, 62);
            this.browse_left_R_button.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.browse_left_R_button.Name = "browse_left_R_button";
            this.browse_left_R_button.Size = new System.Drawing.Size(48, 35);
            this.browse_left_R_button.TabIndex = 2;
            this.browse_left_R_button.Text = "...";
            this.browse_left_R_button.UseVisualStyleBackColor = true;
            this.browse_left_R_button.Click += new System.EventHandler(this.browse_left_R_button_Click);
            // 
            // input_left_R_textbox
            // 
            this.input_left_R_textbox.Location = new System.Drawing.Point(94, 63);
            this.input_left_R_textbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.input_left_R_textbox.Name = "input_left_R_textbox";
            this.input_left_R_textbox.Size = new System.Drawing.Size(580, 26);
            this.input_left_R_textbox.TabIndex = 1;
            this.input_left_R_textbox.TextChanged += new System.EventHandler(this.input_left_R_textbox_TextChanged);
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(28, 68);
            this.label15.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(37, 20);
            this.label15.TabIndex = 0;
            this.label15.Text = "Left";
            // 
            // output_groupBox
            // 
            this.output_groupBox.Controls.Add(this.cubicCheckBox);
            this.output_groupBox.Controls.Add(this.compressionTrackBar);
            this.output_groupBox.Controls.Add(this.CompressionLabel);
            this.output_groupBox.Controls.Add(this.start_index_textBox);
            this.output_groupBox.Controls.Add(this.start_button);
            this.output_groupBox.Controls.Add(this.label17);
            this.output_groupBox.Controls.Add(this.format_comboBox);
            this.output_groupBox.Controls.Add(this.formatLabel);
            this.output_groupBox.Controls.Add(this.FileNameTextBox);
            this.output_groupBox.Controls.Add(this.filename);
            this.output_groupBox.Controls.Add(this.browseRightOutputPathButton);
            this.output_groupBox.Controls.Add(this.right_output_path_textbox);
            this.output_groupBox.Controls.Add(this.RightOutputPathLabel);
            this.output_groupBox.Controls.Add(this.browseLeftOutputPathButton);
            this.output_groupBox.Controls.Add(this.left_output_path_textbox);
            this.output_groupBox.Controls.Add(this.LeftOutputPathLabel);
            this.output_groupBox.Controls.Add(this.alpha_checkBox);
            this.output_groupBox.Controls.Add(this.resolution_comboBox);
            this.output_groupBox.Controls.Add(this.label16);
            this.output_groupBox.Location = new System.Drawing.Point(788, 375);
            this.output_groupBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.output_groupBox.Name = "output_groupBox";
            this.output_groupBox.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.output_groupBox.Size = new System.Drawing.Size(760, 315);
            this.output_groupBox.TabIndex = 13;
            this.output_groupBox.TabStop = false;
            this.output_groupBox.Text = "Output";
            // 
            // cubicCheckBox
            // 
            this.cubicCheckBox.AutoSize = true;
            this.cubicCheckBox.Checked = true;
            this.cubicCheckBox.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cubicCheckBox.Location = new System.Drawing.Point(303, 85);
            this.cubicCheckBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.cubicCheckBox.Name = "cubicCheckBox";
            this.cubicCheckBox.Size = new System.Drawing.Size(196, 24);
            this.cubicCheckBox.TabIndex = 24;
            this.cubicCheckBox.Text = "Use cubic interpolation";
            this.cubicCheckBox.UseVisualStyleBackColor = true;
            // 
            // compressionTrackBar
            // 
            this.compressionTrackBar.AutoSize = false;
            this.compressionTrackBar.Location = new System.Drawing.Point(618, 95);
            this.compressionTrackBar.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.compressionTrackBar.Maximum = 9;
            this.compressionTrackBar.Name = "compressionTrackBar";
            this.compressionTrackBar.Size = new System.Drawing.Size(120, 31);
            this.compressionTrackBar.TabIndex = 23;
            this.compressionTrackBar.Value = 7;
            // 
            // CompressionLabel
            // 
            this.CompressionLabel.AutoSize = true;
            this.CompressionLabel.Location = new System.Drawing.Point(512, 100);
            this.CompressionLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.CompressionLabel.Name = "CompressionLabel";
            this.CompressionLabel.Size = new System.Drawing.Size(102, 20);
            this.CompressionLabel.TabIndex = 22;
            this.CompressionLabel.Text = "Compression";
            // 
            // start_index_textBox
            // 
            this.start_index_textBox.Location = new System.Drawing.Point(120, 95);
            this.start_index_textBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.start_index_textBox.MaxLength = 8;
            this.start_index_textBox.Name = "start_index_textBox";
            this.start_index_textBox.Size = new System.Drawing.Size(70, 26);
            this.start_index_textBox.TabIndex = 21;
            this.start_index_textBox.Text = "0";
            this.start_index_textBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.start_index_textBox.TextChanged += new System.EventHandler(this.start_index_textBox_TextChanged);
            // 
            // start_button
            // 
            this.start_button.BackColor = System.Drawing.Color.LightGreen;
            this.start_button.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.start_button.Location = new System.Drawing.Point(618, 255);
            this.start_button.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.start_button.Name = "start_button";
            this.start_button.Size = new System.Drawing.Size(134, 46);
            this.start_button.TabIndex = 14;
            this.start_button.Text = "Start!";
            this.start_button.UseVisualStyleBackColor = false;
            this.start_button.Click += new System.EventHandler(this.start_button_Click);
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(26, 100);
            this.label17.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(85, 20);
            this.label17.TabIndex = 20;
            this.label17.Text = "Start index";
            // 
            // format_comboBox
            // 
            this.format_comboBox.FormattingEnabled = true;
            this.format_comboBox.Items.AddRange(new object[] {
            "png",
            "tga"});
            this.format_comboBox.Location = new System.Drawing.Point(621, 46);
            this.format_comboBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.format_comboBox.Name = "format_comboBox";
            this.format_comboBox.Size = new System.Drawing.Size(110, 28);
            this.format_comboBox.TabIndex = 19;
            this.format_comboBox.SelectedIndexChanged += new System.EventHandler(this.format_comboBox_SelectedIndexChanged);
            // 
            // formatLabel
            // 
            this.formatLabel.AutoSize = true;
            this.formatLabel.Location = new System.Drawing.Point(554, 51);
            this.formatLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.formatLabel.Name = "formatLabel";
            this.formatLabel.Size = new System.Drawing.Size(60, 20);
            this.formatLabel.TabIndex = 18;
            this.formatLabel.Text = "Format";
            // 
            // FileNameTextBox
            // 
            this.FileNameTextBox.Location = new System.Drawing.Point(120, 142);
            this.FileNameTextBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.FileNameTextBox.Name = "FileNameTextBox";
            this.FileNameTextBox.Size = new System.Drawing.Size(400, 26);
            this.FileNameTextBox.TabIndex = 17;
            this.FileNameTextBox.TextChanged += new System.EventHandler(this.FileNameTextBox_TextChanged);
            // 
            // filename
            // 
            this.filename.AutoSize = true;
            this.filename.Location = new System.Drawing.Point(26, 146);
            this.filename.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.filename.Name = "filename";
            this.filename.Size = new System.Drawing.Size(74, 20);
            this.filename.TabIndex = 16;
            this.filename.Text = "Filename";
            // 
            // browseRightOutputPathButton
            // 
            this.browseRightOutputPathButton.Location = new System.Drawing.Point(532, 232);
            this.browseRightOutputPathButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.browseRightOutputPathButton.Name = "browseRightOutputPathButton";
            this.browseRightOutputPathButton.Size = new System.Drawing.Size(48, 35);
            this.browseRightOutputPathButton.TabIndex = 15;
            this.browseRightOutputPathButton.Text = "...";
            this.browseRightOutputPathButton.UseVisualStyleBackColor = true;
            this.browseRightOutputPathButton.Click += new System.EventHandler(this.browseRightOutputPathButton_Click);
            // 
            // right_output_path_textbox
            // 
            this.right_output_path_textbox.Location = new System.Drawing.Point(120, 234);
            this.right_output_path_textbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.right_output_path_textbox.Name = "right_output_path_textbox";
            this.right_output_path_textbox.Size = new System.Drawing.Size(400, 26);
            this.right_output_path_textbox.TabIndex = 14;
            this.right_output_path_textbox.TextChanged += new System.EventHandler(this.right_output_path_textbox_TextChanged);
            // 
            // RightOutputPathLabel
            // 
            this.RightOutputPathLabel.AutoSize = true;
            this.RightOutputPathLabel.Location = new System.Drawing.Point(28, 240);
            this.RightOutputPathLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.RightOutputPathLabel.Name = "RightOutputPathLabel";
            this.RightOutputPathLabel.Size = new System.Drawing.Size(83, 20);
            this.RightOutputPathLabel.TabIndex = 13;
            this.RightOutputPathLabel.Text = "Right path";
            // 
            // browseLeftOutputPathButton
            // 
            this.browseLeftOutputPathButton.Location = new System.Drawing.Point(532, 185);
            this.browseLeftOutputPathButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.browseLeftOutputPathButton.Name = "browseLeftOutputPathButton";
            this.browseLeftOutputPathButton.Size = new System.Drawing.Size(48, 35);
            this.browseLeftOutputPathButton.TabIndex = 12;
            this.browseLeftOutputPathButton.Text = "...";
            this.browseLeftOutputPathButton.UseVisualStyleBackColor = true;
            this.browseLeftOutputPathButton.Click += new System.EventHandler(this.browseLeftOutputPathButton_Click);
            // 
            // left_output_path_textbox
            // 
            this.left_output_path_textbox.Location = new System.Drawing.Point(120, 186);
            this.left_output_path_textbox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.left_output_path_textbox.Name = "left_output_path_textbox";
            this.left_output_path_textbox.Size = new System.Drawing.Size(400, 26);
            this.left_output_path_textbox.TabIndex = 4;
            this.left_output_path_textbox.TextChanged += new System.EventHandler(this.left_output_path_textbox_TextChanged);
            // 
            // LeftOutputPathLabel
            // 
            this.LeftOutputPathLabel.AutoSize = true;
            this.LeftOutputPathLabel.Location = new System.Drawing.Point(26, 192);
            this.LeftOutputPathLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.LeftOutputPathLabel.Name = "LeftOutputPathLabel";
            this.LeftOutputPathLabel.Size = new System.Drawing.Size(42, 20);
            this.LeftOutputPathLabel.TabIndex = 3;
            this.LeftOutputPathLabel.Text = "Path";
            // 
            // alpha_checkBox
            // 
            this.alpha_checkBox.AutoSize = true;
            this.alpha_checkBox.Location = new System.Drawing.Point(303, 49);
            this.alpha_checkBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.alpha_checkBox.Name = "alpha_checkBox";
            this.alpha_checkBox.Size = new System.Drawing.Size(167, 24);
            this.alpha_checkBox.TabIndex = 2;
            this.alpha_checkBox.Text = "Use alpha channel";
            this.alpha_checkBox.UseVisualStyleBackColor = true;
            // 
            // resolution_comboBox
            // 
            this.resolution_comboBox.FormattingEnabled = true;
            this.resolution_comboBox.Items.AddRange(new object[] {
            "512x512",
            "1024x1024",
            "2048x2048",
            "4096x4096",
            "6144x6144",
            "8192x8192"});
            this.resolution_comboBox.Location = new System.Drawing.Point(120, 46);
            this.resolution_comboBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.resolution_comboBox.Name = "resolution_comboBox";
            this.resolution_comboBox.Size = new System.Drawing.Size(140, 28);
            this.resolution_comboBox.TabIndex = 1;
            this.resolution_comboBox.SelectedIndexChanged += new System.EventHandler(this.resolution_comboBox_SelectedIndexChanged);
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(26, 51);
            this.label16.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(85, 20);
            this.label16.TabIndex = 0;
            this.label16.Text = "Resolution";
            // 
            // Sequence_groupBox
            // 
            this.Sequence_groupBox.Controls.Add(this.input_stopindex_textBox);
            this.Sequence_groupBox.Controls.Add(this.label18);
            this.Sequence_groupBox.Controls.Add(this.input_startindex_textBox);
            this.Sequence_groupBox.Controls.Add(this.input_startindex_label);
            this.Sequence_groupBox.Location = new System.Drawing.Point(20, 18);
            this.Sequence_groupBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Sequence_groupBox.Name = "Sequence_groupBox";
            this.Sequence_groupBox.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.Sequence_groupBox.Size = new System.Drawing.Size(760, 80);
            this.Sequence_groupBox.TabIndex = 15;
            this.Sequence_groupBox.TabStop = false;
            this.Sequence_groupBox.Text = "Sequence";
            // 
            // input_stopindex_textBox
            // 
            this.input_stopindex_textBox.Location = new System.Drawing.Point(342, 32);
            this.input_stopindex_textBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.input_stopindex_textBox.MaxLength = 8;
            this.input_stopindex_textBox.Name = "input_stopindex_textBox";
            this.input_stopindex_textBox.Size = new System.Drawing.Size(73, 26);
            this.input_stopindex_textBox.TabIndex = 3;
            this.input_stopindex_textBox.Text = "0";
            this.input_stopindex_textBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.input_stopindex_textBox.TextChanged += new System.EventHandler(this.input_stopindex_textBox_TextChanged);
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(248, 38);
            this.label18.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(84, 20);
            this.label18.TabIndex = 2;
            this.label18.Text = "Stop index";
            // 
            // input_startindex_textBox
            // 
            this.input_startindex_textBox.Location = new System.Drawing.Point(123, 34);
            this.input_startindex_textBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.input_startindex_textBox.MaxLength = 8;
            this.input_startindex_textBox.Name = "input_startindex_textBox";
            this.input_startindex_textBox.Size = new System.Drawing.Size(73, 26);
            this.input_startindex_textBox.TabIndex = 1;
            this.input_startindex_textBox.Text = "0";
            this.input_startindex_textBox.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.input_startindex_textBox.TextChanged += new System.EventHandler(this.input_startindex_textBox_TextChanged);
            // 
            // input_startindex_label
            // 
            this.input_startindex_label.AutoSize = true;
            this.input_startindex_label.Location = new System.Drawing.Point(28, 38);
            this.input_startindex_label.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.input_startindex_label.Name = "input_startindex_label";
            this.input_startindex_label.Size = new System.Drawing.Size(85, 20);
            this.input_startindex_label.TabIndex = 0;
            this.input_startindex_label.Text = "Start index";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.FXAACheckBox);
            this.groupBox1.Controls.Add(this.samples);
            this.groupBox1.Controls.Add(this.MSAA_ComboBox);
            this.groupBox1.Controls.Add(this.MSAALabel);
            this.groupBox1.Location = new System.Drawing.Point(790, 205);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.groupBox1.Size = new System.Drawing.Size(356, 162);
            this.groupBox1.TabIndex = 16;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Anti-aliasing";
            // 
            // FXAACheckBox
            // 
            this.FXAACheckBox.AutoSize = true;
            this.FXAACheckBox.Location = new System.Drawing.Point(24, 74);
            this.FXAACheckBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.FXAACheckBox.Name = "FXAACheckBox";
            this.FXAACheckBox.Size = new System.Drawing.Size(78, 24);
            this.FXAACheckBox.TabIndex = 15;
            this.FXAACheckBox.Text = "FXAA";
            this.FXAACheckBox.UseVisualStyleBackColor = true;
            // 
            // samples
            // 
            this.samples.AutoSize = true;
            this.samples.Location = new System.Drawing.Point(250, 37);
            this.samples.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.samples.Name = "samples";
            this.samples.Size = new System.Drawing.Size(68, 20);
            this.samples.TabIndex = 14;
            this.samples.Text = "samples";
            // 
            // MSAA_ComboBox
            // 
            this.MSAA_ComboBox.DisplayMember = "(none)";
            this.MSAA_ComboBox.FormattingEnabled = true;
            this.MSAA_ComboBox.Items.AddRange(new object[] {
            "1",
            "2",
            "4",
            "8",
            "16"});
            this.MSAA_ComboBox.Location = new System.Drawing.Point(159, 32);
            this.MSAA_ComboBox.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.MSAA_ComboBox.Name = "MSAA_ComboBox";
            this.MSAA_ComboBox.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.MSAA_ComboBox.Size = new System.Drawing.Size(84, 28);
            this.MSAA_ComboBox.TabIndex = 13;
            // 
            // MSAALabel
            // 
            this.MSAALabel.AutoSize = true;
            this.MSAALabel.Location = new System.Drawing.Point(20, 37);
            this.MSAALabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.MSAALabel.Name = "MSAALabel";
            this.MSAALabel.Size = new System.Drawing.Size(55, 20);
            this.MSAALabel.TabIndex = 12;
            this.MSAALabel.Text = "MSAA";
            // 
            // stitcher_form
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1560, 700);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.Sequence_groupBox);
            this.Controls.Add(this.output_groupBox);
            this.Controls.Add(this.right_input_groupbox);
            this.Controls.Add(this.transform_groupbox);
            this.Controls.Add(this.setting_groupBox);
            this.Controls.Add(this.left_input_groupbox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.MaximizeBox = false;
            this.Name = "stitcher_form";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "Stitcher";
            this.left_input_groupbox.ResumeLayout(false);
            this.left_input_groupbox.PerformLayout();
            this.setting_groupBox.ResumeLayout(false);
            this.setting_groupBox.PerformLayout();
            this.transform_groupbox.ResumeLayout(false);
            this.transform_groupbox.PerformLayout();
            this.right_input_groupbox.ResumeLayout(false);
            this.right_input_groupbox.PerformLayout();
            this.output_groupBox.ResumeLayout(false);
            this.output_groupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.compressionTrackBar)).EndInit();
            this.Sequence_groupBox.ResumeLayout(false);
            this.Sequence_groupBox.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox left_input_groupbox;
        private System.Windows.Forms.Button browse_bottom_L_button;
        private System.Windows.Forms.TextBox input_bottom_L_textbox;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button browse_top_L_button;
        private System.Windows.Forms.TextBox input_top_L_textbox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button browse_right_L_button;
        private System.Windows.Forms.TextBox input_right_L_textbox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button browse_left_L_button;
        private System.Windows.Forms.TextBox input_left_L_textbox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox setting_groupBox;
        private System.Windows.Forms.Label dome_diameter_units_label;
        private System.Windows.Forms.Label eye_separation_units_label;
        private System.Windows.Forms.TextBox domeDiameterInput;
        private System.Windows.Forms.Label dome_diameter_label;
        private System.Windows.Forms.TextBox eyeSeparationInput;
        private System.Windows.Forms.Label eye_separation_label;
        private System.Windows.Forms.CheckBox stereo_checkBox;
        private System.Windows.Forms.GroupBox transform_groupbox;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.ComboBox right_transform_comboBox;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox left_transform_comboBox;
        private System.Windows.Forms.Label LeftTransformLabel;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.ComboBox bottom_transform_comboBox;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.ComboBox top_transform_comboBox;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.GroupBox right_input_groupbox;
        private System.Windows.Forms.Button browse_bottom_R_button;
        private System.Windows.Forms.TextBox input_bottom_R_textbox;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Button browse_top_R_button;
        private System.Windows.Forms.TextBox input_top_R_textbox;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Button browse_right_R_button;
        private System.Windows.Forms.TextBox input_right_R_textbox;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Button browse_left_R_button;
        private System.Windows.Forms.TextBox input_left_R_textbox;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.GroupBox output_groupBox;
        private System.Windows.Forms.CheckBox alpha_checkBox;
        private System.Windows.Forms.ComboBox resolution_comboBox;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.TextBox left_output_path_textbox;
        private System.Windows.Forms.Label LeftOutputPathLabel;
        private System.Windows.Forms.Button browseRightOutputPathButton;
        private System.Windows.Forms.TextBox right_output_path_textbox;
        private System.Windows.Forms.Label RightOutputPathLabel;
        private System.Windows.Forms.Button browseLeftOutputPathButton;
        private System.Windows.Forms.ComboBox format_comboBox;
        private System.Windows.Forms.Label formatLabel;
        private System.Windows.Forms.TextBox FileNameTextBox;
        private System.Windows.Forms.Label filename;
        private System.Windows.Forms.Button start_button;
        private System.Windows.Forms.TextBox start_index_textBox;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.GroupBox Sequence_groupBox;
        private System.Windows.Forms.TextBox input_stopindex_textBox;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.TextBox input_startindex_textBox;
        private System.Windows.Forms.Label input_startindex_label;
        private System.Windows.Forms.TrackBar compressionTrackBar;
        private System.Windows.Forms.Label CompressionLabel;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.CheckBox FXAACheckBox;
        private System.Windows.Forms.Label samples;
        private System.Windows.Forms.ComboBox MSAA_ComboBox;
        private System.Windows.Forms.Label MSAALabel;
        private System.Windows.Forms.ComboBox cubemapComboBox;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.CheckBox cubicCheckBox;
    }
}

