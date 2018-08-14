#pragma once

#include <windows.h>
#include <atlstr.h>
#include <stdio.h>
#include <iostream>

namespace bmptoepaperGUI {

  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;
  using namespace System::IO;

  /// <summary>
  /// Summary for MyForm
  /// </summary>
  public ref class MyForm : public System::Windows::Forms::Form
  {
  public:
    MyForm(void)
    {
      InitializeComponent();
    }

  protected:
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    ~MyForm()
    {
      if (components)
      {
        delete components;
      }
    }
  private: System::Windows::Forms::PictureBox^  pictureBox1;
  private: System::Windows::Forms::Button^  browseBtn;

  private:
    /// <summary>
    /// Required designer variable.
    /// </summary>
    System::ComponentModel::Container ^components;
  private: System::Windows::Forms::GroupBox^  groupBox1;
  private: System::Windows::Forms::TextBox^  fileName;
  private: System::Windows::Forms::TextBox^  fileName2;
  private: System::Windows::Forms::PictureBox^  pictureBox2;
  private: System::Windows::Forms::ComboBox^  formatOptions;
  private: System::Windows::Forms::TextBox^  convertTo;
  private: System::Windows::Forms::ComboBox^  yelDrop;
  private: System::Windows::Forms::TextBox^  yelText;
  private: System::Windows::Forms::TextBox^  redText;
  private: System::Windows::Forms::ComboBox^  redDrop;
  private: System::Windows::Forms::TextBox^  bwText;
  private: System::Windows::Forms::ComboBox^  bwDrop;
  private: System::Windows::Forms::PictureBox^  pictureBox3;
  private: System::Windows::Forms::CheckBox^  InvertedCBox;
  private: System::Windows::Forms::Button^  convertButton;
  private: System::Windows::Forms::Panel^  panel1;
  private: System::Windows::Forms::RadioButton^  RTLButton;
  private: System::Windows::Forms::RadioButton^  LTRButton;
  private: System::Windows::Forms::Panel^  panel2;
  private: System::Windows::Forms::RadioButton^  BTTButton;
  private: System::Windows::Forms::RadioButton^  TTBButton;
  private: System::Windows::Forms::Panel^  mainSelectionPanel;
  private: System::Windows::Forms::Panel^  ePaperSettingsPanel;


           OpenFileDialog^ openFileDialog1;
  private: System::Windows::Forms::TextBox^  textBox1;
           Bitmap^ bitmap;
  private: System::Windows::Forms::Button^  previewbutton;
  private: System::Windows::Forms::CheckBox^  rleBox;
  private: System::Windows::Forms::CheckBox^  ArraySizeChkBox;

           Bitmap^ bitmapCopy;
           bool openStuff();

#pragma region Windows Form Designer generated code
           /// <summary>
           /// Required method for Designer support - do not modify
           /// the contents of this method with the code editor.
           /// </summary>
           void InitializeComponent(void)
           {
             System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
             this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
             this->browseBtn = (gcnew System::Windows::Forms::Button());
             this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
             this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
             this->fileName2 = (gcnew System::Windows::Forms::TextBox());
             this->fileName = (gcnew System::Windows::Forms::TextBox());
             this->formatOptions = (gcnew System::Windows::Forms::ComboBox());
             this->convertTo = (gcnew System::Windows::Forms::TextBox());
             this->yelDrop = (gcnew System::Windows::Forms::ComboBox());
             this->yelText = (gcnew System::Windows::Forms::TextBox());
             this->redText = (gcnew System::Windows::Forms::TextBox());
             this->redDrop = (gcnew System::Windows::Forms::ComboBox());
             this->bwText = (gcnew System::Windows::Forms::TextBox());
             this->bwDrop = (gcnew System::Windows::Forms::ComboBox());
             this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
             this->InvertedCBox = (gcnew System::Windows::Forms::CheckBox());
             this->convertButton = (gcnew System::Windows::Forms::Button());
             this->panel1 = (gcnew System::Windows::Forms::Panel());
             this->RTLButton = (gcnew System::Windows::Forms::RadioButton());
             this->LTRButton = (gcnew System::Windows::Forms::RadioButton());
             this->panel2 = (gcnew System::Windows::Forms::Panel());
             this->BTTButton = (gcnew System::Windows::Forms::RadioButton());
             this->TTBButton = (gcnew System::Windows::Forms::RadioButton());
             this->mainSelectionPanel = (gcnew System::Windows::Forms::Panel());
             this->rleBox = (gcnew System::Windows::Forms::CheckBox());
             this->ePaperSettingsPanel = (gcnew System::Windows::Forms::Panel());
             this->textBox1 = (gcnew System::Windows::Forms::TextBox());
             this->previewbutton = (gcnew System::Windows::Forms::Button());
             this->ArraySizeChkBox = (gcnew System::Windows::Forms::CheckBox());
             (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
             this->groupBox1->SuspendLayout();
             (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
             (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
             this->panel1->SuspendLayout();
             this->panel2->SuspendLayout();
             this->mainSelectionPanel->SuspendLayout();
             this->ePaperSettingsPanel->SuspendLayout();
             this->SuspendLayout();
             // 
             // pictureBox1
             // 
             this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
             this->pictureBox1->Location = System::Drawing::Point(0, 0);
             this->pictureBox1->Name = L"pictureBox1";
             this->pictureBox1->Size = System::Drawing::Size(180, 38);
             this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
             this->pictureBox1->TabIndex = 0;
             this->pictureBox1->TabStop = false;
             this->pictureBox1->Click += gcnew System::EventHandler(this, &MyForm::pictureBox1_Click);
             this->pictureBox1->MouseLeave += gcnew System::EventHandler(this, &MyForm::pictureBox1_MouseLeave);
             this->pictureBox1->MouseHover += gcnew System::EventHandler(this, &MyForm::pictureBox1_MouseHover);
             // 
             // browseBtn
             // 
             this->browseBtn->Location = System::Drawing::Point(19, 19);
             this->browseBtn->Name = L"browseBtn";
             this->browseBtn->Size = System::Drawing::Size(75, 23);
             this->browseBtn->TabIndex = 1;
             this->browseBtn->Text = L"Browse";
             this->browseBtn->UseVisualStyleBackColor = true;
             this->browseBtn->Click += gcnew System::EventHandler(this, &MyForm::browseBtn_Click);
             // 
             // groupBox1
             // 
             this->groupBox1->Controls->Add(this->pictureBox2);
             this->groupBox1->Controls->Add(this->fileName2);
             this->groupBox1->Controls->Add(this->fileName);
             this->groupBox1->Controls->Add(this->browseBtn);
             this->groupBox1->Location = System::Drawing::Point(12, 44);
             this->groupBox1->Name = L"groupBox1";
             this->groupBox1->Size = System::Drawing::Size(500, 98);
             this->groupBox1->TabIndex = 3;
             this->groupBox1->TabStop = false;
             this->groupBox1->Text = L"Browse for an image";
             // 
             // pictureBox2
             // 
             this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
             this->pictureBox2->Location = System::Drawing::Point(394, 13);
             this->pictureBox2->Name = L"pictureBox2";
             this->pictureBox2->Size = System::Drawing::Size(100, 79);
             this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
             this->pictureBox2->TabIndex = 4;
             this->pictureBox2->TabStop = false;
             // 
             // fileName2
             // 
             this->fileName2->BackColor = System::Drawing::SystemColors::Control;
             this->fileName2->BorderStyle = System::Windows::Forms::BorderStyle::None;
             this->fileName2->Location = System::Drawing::Point(6, 70);
             this->fileName2->Multiline = true;
             this->fileName2->Name = L"fileName2";
             this->fileName2->Size = System::Drawing::Size(364, 16);
             this->fileName2->TabIndex = 3;
             this->fileName2->Text = L"file name";
             this->fileName2->Visible = false;
             // 
             // fileName
             // 
             this->fileName->BackColor = System::Drawing::SystemColors::Control;
             this->fileName->BorderStyle = System::Windows::Forms::BorderStyle::None;
             this->fileName->Location = System::Drawing::Point(6, 48);
             this->fileName->Multiline = true;
             this->fileName->Name = L"fileName";
             this->fileName->Size = System::Drawing::Size(100, 16);
             this->fileName->TabIndex = 2;
             this->fileName->Text = L"file: ";
             this->fileName->Visible = false;
             // 
             // formatOptions
             // 
             this->formatOptions->FormattingEnabled = true;
             this->formatOptions->Items->AddRange(gcnew cli::array< System::Object^  >(1) { L"ePaper" });
             this->formatOptions->Location = System::Drawing::Point(65, 5);
             this->formatOptions->Name = L"formatOptions";
             this->formatOptions->Size = System::Drawing::Size(121, 21);
             this->formatOptions->TabIndex = 4;
             this->formatOptions->Text = L"ePaper";
             this->formatOptions->TextChanged += gcnew System::EventHandler(this, &MyForm::formatOptions_TextChanged);
             // 
             // convertTo
             // 
             this->convertTo->BackColor = System::Drawing::SystemColors::Control;
             this->convertTo->BorderStyle = System::Windows::Forms::BorderStyle::None;
             this->convertTo->Location = System::Drawing::Point(3, 5);
             this->convertTo->Name = L"convertTo";
             this->convertTo->Size = System::Drawing::Size(56, 13);
             this->convertTo->TabIndex = 5;
             this->convertTo->Text = L"Convert to:";
             // 
             // yelDrop
             // 
             this->yelDrop->FormattingEnabled = true;
             this->yelDrop->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"N/A", L"1-bit" });
             this->yelDrop->Location = System::Drawing::Point(85, 74);
             this->yelDrop->Name = L"yelDrop";
             this->yelDrop->Size = System::Drawing::Size(67, 21);
             this->yelDrop->TabIndex = 7;
             this->yelDrop->Text = L"N/A";
             this->yelDrop->TextUpdate += gcnew System::EventHandler(this, &MyForm::yelDrop_TextUpdate);
             // 
             // yelText
             // 
             this->yelText->BackColor = System::Drawing::SystemColors::Control;
             this->yelText->BorderStyle = System::Windows::Forms::BorderStyle::None;
             this->yelText->Location = System::Drawing::Point(3, 77);
             this->yelText->Name = L"yelText";
             this->yelText->Size = System::Drawing::Size(76, 13);
             this->yelText->TabIndex = 6;
             this->yelText->Text = L"Yellow:";
             // 
             // redText
             // 
             this->redText->BackColor = System::Drawing::SystemColors::Control;
             this->redText->BorderStyle = System::Windows::Forms::BorderStyle::None;
             this->redText->Location = System::Drawing::Point(3, 50);
             this->redText->Name = L"redText";
             this->redText->Size = System::Drawing::Size(76, 13);
             this->redText->TabIndex = 10;
             this->redText->Text = L"Red:";
             // 
             // redDrop
             // 
             this->redDrop->FormattingEnabled = true;
             this->redDrop->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"N/A", L"1-bit" });
             this->redDrop->Location = System::Drawing::Point(85, 47);
             this->redDrop->Name = L"redDrop";
             this->redDrop->Size = System::Drawing::Size(67, 21);
             this->redDrop->TabIndex = 9;
             this->redDrop->Text = L"N/A";
             this->redDrop->TextUpdate += gcnew System::EventHandler(this, &MyForm::redDrop_TextUpdate);
             // 
             // bwText
             // 
             this->bwText->BackColor = System::Drawing::SystemColors::Control;
             this->bwText->BorderStyle = System::Windows::Forms::BorderStyle::None;
             this->bwText->Location = System::Drawing::Point(3, 23);
             this->bwText->Name = L"bwText";
             this->bwText->Size = System::Drawing::Size(76, 13);
             this->bwText->TabIndex = 12;
             this->bwText->Text = L"Black/White:";
             // 
             // bwDrop
             // 
             this->bwDrop->FormattingEnabled = true;
             this->bwDrop->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"N/A", L"1-bit", L"4-bit" });
             this->bwDrop->Location = System::Drawing::Point(85, 20);
             this->bwDrop->Name = L"bwDrop";
             this->bwDrop->Size = System::Drawing::Size(67, 21);
             this->bwDrop->TabIndex = 11;
             this->bwDrop->Text = L"1-bit";
             this->bwDrop->TextUpdate += gcnew System::EventHandler(this, &MyForm::bwDrop_TextUpdate);
             // 
             // pictureBox3
             // 
             this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
             this->pictureBox3->Location = System::Drawing::Point(3, 32);
             this->pictureBox3->Name = L"pictureBox3";
             this->pictureBox3->Size = System::Drawing::Size(103, 112);
             this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::AutoSize;
             this->pictureBox3->TabIndex = 13;
             this->pictureBox3->TabStop = false;
             // 
             // InvertedCBox
             // 
             this->InvertedCBox->AutoSize = true;
             this->InvertedCBox->Location = System::Drawing::Point(121, 32);
             this->InvertedCBox->Name = L"InvertedCBox";
             this->InvertedCBox->Size = System::Drawing::Size(65, 17);
             this->InvertedCBox->TabIndex = 19;
             this->InvertedCBox->Text = L"Inverted";
             this->InvertedCBox->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
             this->InvertedCBox->UseVisualStyleBackColor = true;
             // 
             // convertButton
             // 
             this->convertButton->Enabled = false;
             this->convertButton->Location = System::Drawing::Point(431, 406);
             this->convertButton->Name = L"convertButton";
             this->convertButton->Size = System::Drawing::Size(75, 23);
             this->convertButton->TabIndex = 5;
             this->convertButton->Text = L"Convert";
             this->convertButton->UseVisualStyleBackColor = true;
             this->convertButton->Click += gcnew System::EventHandler(this, &MyForm::convertButton_Click);
             // 
             // panel1
             // 
             this->panel1->Controls->Add(this->RTLButton);
             this->panel1->Controls->Add(this->LTRButton);
             this->panel1->Location = System::Drawing::Point(3, 56);
             this->panel1->Name = L"panel1";
             this->panel1->Size = System::Drawing::Size(103, 23);
             this->panel1->TabIndex = 26;
             // 
             // RTLButton
             // 
             this->RTLButton->AutoSize = true;
             this->RTLButton->Location = System::Drawing::Point(72, 3);
             this->RTLButton->Name = L"RTLButton";
             this->RTLButton->Size = System::Drawing::Size(14, 13);
             this->RTLButton->TabIndex = 28;
             this->RTLButton->UseVisualStyleBackColor = true;
             // 
             // LTRButton
             // 
             this->LTRButton->AutoSize = true;
             this->LTRButton->Checked = true;
             this->LTRButton->Location = System::Drawing::Point(19, 3);
             this->LTRButton->Name = L"LTRButton";
             this->LTRButton->Size = System::Drawing::Size(14, 13);
             this->LTRButton->TabIndex = 27;
             this->LTRButton->TabStop = true;
             this->LTRButton->UseVisualStyleBackColor = true;
             // 
             // panel2
             // 
             this->panel2->Controls->Add(this->BTTButton);
             this->panel2->Controls->Add(this->TTBButton);
             this->panel2->Location = System::Drawing::Point(3, 121);
             this->panel2->Name = L"panel2";
             this->panel2->Size = System::Drawing::Size(103, 23);
             this->panel2->TabIndex = 29;
             // 
             // BTTButton
             // 
             this->BTTButton->AutoSize = true;
             this->BTTButton->Location = System::Drawing::Point(72, 3);
             this->BTTButton->Name = L"BTTButton";
             this->BTTButton->Size = System::Drawing::Size(14, 13);
             this->BTTButton->TabIndex = 28;
             this->BTTButton->UseVisualStyleBackColor = true;
             // 
             // TTBButton
             // 
             this->TTBButton->AutoSize = true;
             this->TTBButton->Checked = true;
             this->TTBButton->Location = System::Drawing::Point(19, 3);
             this->TTBButton->Name = L"TTBButton";
             this->TTBButton->Size = System::Drawing::Size(14, 13);
             this->TTBButton->TabIndex = 27;
             this->TTBButton->TabStop = true;
             this->TTBButton->UseVisualStyleBackColor = true;
             // 
             // mainSelectionPanel
             // 
             this->mainSelectionPanel->Controls->Add(this->ArraySizeChkBox);
             this->mainSelectionPanel->Controls->Add(this->rleBox);
             this->mainSelectionPanel->Controls->Add(this->panel2);
             this->mainSelectionPanel->Controls->Add(this->panel1);
             this->mainSelectionPanel->Controls->Add(this->pictureBox3);
             this->mainSelectionPanel->Controls->Add(this->convertTo);
             this->mainSelectionPanel->Controls->Add(this->formatOptions);
             this->mainSelectionPanel->Controls->Add(this->InvertedCBox);
             this->mainSelectionPanel->Location = System::Drawing::Point(12, 148);
             this->mainSelectionPanel->Name = L"mainSelectionPanel";
             this->mainSelectionPanel->Size = System::Drawing::Size(199, 155);
             this->mainSelectionPanel->TabIndex = 30;
             this->mainSelectionPanel->Visible = false;
             // 
             // rleBox
             // 
             this->rleBox->AutoSize = true;
             this->rleBox->Location = System::Drawing::Point(121, 51);
             this->rleBox->Name = L"rleBox";
             this->rleBox->Size = System::Drawing::Size(47, 17);
             this->rleBox->TabIndex = 30;
             this->rleBox->Text = L"RLE";
             this->rleBox->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
             this->rleBox->UseVisualStyleBackColor = true;
             // 
             // ePaperSettingsPanel
             // 
             this->ePaperSettingsPanel->Controls->Add(this->textBox1);
             this->ePaperSettingsPanel->Controls->Add(this->bwText);
             this->ePaperSettingsPanel->Controls->Add(this->yelDrop);
             this->ePaperSettingsPanel->Controls->Add(this->yelText);
             this->ePaperSettingsPanel->Controls->Add(this->bwDrop);
             this->ePaperSettingsPanel->Controls->Add(this->redDrop);
             this->ePaperSettingsPanel->Controls->Add(this->redText);
             this->ePaperSettingsPanel->Location = System::Drawing::Point(354, 148);
             this->ePaperSettingsPanel->Name = L"ePaperSettingsPanel";
             this->ePaperSettingsPanel->Size = System::Drawing::Size(158, 115);
             this->ePaperSettingsPanel->TabIndex = 31;
             this->ePaperSettingsPanel->Visible = false;
             // 
             // textBox1
             // 
             this->textBox1->BackColor = System::Drawing::SystemColors::Control;
             this->textBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
             this->textBox1->Location = System::Drawing::Point(85, 0);
             this->textBox1->Name = L"textBox1";
             this->textBox1->Size = System::Drawing::Size(100, 13);
             this->textBox1->TabIndex = 13;
             this->textBox1->Text = L"Bit Resolution:";
             // 
             // previewbutton
             // 
             this->previewbutton->Enabled = false;
             this->previewbutton->Location = System::Drawing::Point(350, 406);
             this->previewbutton->Name = L"previewbutton";
             this->previewbutton->Size = System::Drawing::Size(75, 23);
             this->previewbutton->TabIndex = 32;
             this->previewbutton->Text = L"Preview";
             this->previewbutton->UseVisualStyleBackColor = true;
             this->previewbutton->Visible = false;
             // 
             // ArraySizeChkBox
             // 
             this->ArraySizeChkBox->AutoSize = true;
             this->ArraySizeChkBox->Location = System::Drawing::Point(121, 70);
             this->ArraySizeChkBox->Name = L"ArraySizeChkBox";
             this->ArraySizeChkBox->Size = System::Drawing::Size(80, 17);
             this->ArraySizeChkBox->TabIndex = 31;
             this->ArraySizeChkBox->Text = L"2 Dim Array";
             this->ArraySizeChkBox->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
             this->ArraySizeChkBox->UseVisualStyleBackColor = true;
             // 
             // MyForm
             // 
             this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
             this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
             this->ClientSize = System::Drawing::Size(524, 441);
             this->Controls->Add(this->previewbutton);
             this->Controls->Add(this->ePaperSettingsPanel);
             this->Controls->Add(this->convertButton);
             this->Controls->Add(this->groupBox1);
             this->Controls->Add(this->pictureBox1);
             this->Controls->Add(this->mainSelectionPanel);
             this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
             this->Name = L"MyForm";
             this->Text = L"bmp to ePaper";
             (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
             this->groupBox1->ResumeLayout(false);
             this->groupBox1->PerformLayout();
             (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
             (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
             this->panel1->ResumeLayout(false);
             this->panel1->PerformLayout();
             this->panel2->ResumeLayout(false);
             this->panel2->PerformLayout();
             this->mainSelectionPanel->ResumeLayout(false);
             this->mainSelectionPanel->PerformLayout();
             this->ePaperSettingsPanel->ResumeLayout(false);
             this->ePaperSettingsPanel->PerformLayout();
             this->ResumeLayout(false);

           }
#pragma endregion

  private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void pictureBox1_MouseHover(System::Object^  sender, System::EventArgs^  e);
  private: System::Void pictureBox1_MouseLeave(System::Object^  sender, System::EventArgs^  e);
  private: System::Void browseBtn_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void formatOptions_TextChanged(System::Object^  sender, System::EventArgs^  e);
  private: System::Void convertButton_Click(System::Object^  sender, System::EventArgs^  e);
  private: System::Void bwDrop_TextUpdate(System::Object^  sender, System::EventArgs^  e);
  private: System::Void redDrop_TextUpdate(System::Object^  sender, System::EventArgs^  e);
  private: System::Void yelDrop_TextUpdate(System::Object^  sender, System::EventArgs^  e);
  };
}
