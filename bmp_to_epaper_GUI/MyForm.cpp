#include "MyForm.h"

#include "MyForm.h"
#include "ePaperModule.h"
#include "bmpToEPaper.h"
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void main(array<String^>^ args) {
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false);
  bmptoepaperGUI::MyForm form;
  Application::Run(%form);
}

  System::Void bmptoepaperGUI::MyForm::pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
    CString str = "www.crystalfontz.com";
    CString action = "open";
    ShellExecute(NULL, action, str, NULL, NULL, SW_SHOW);
    getchar();
  }

  System::Void bmptoepaperGUI::MyForm::pictureBox1_MouseHover(System::Object^  sender, System::EventArgs^  e) {
    pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
  }

  System::Void bmptoepaperGUI::MyForm::pictureBox1_MouseLeave(System::Object^  sender, System::EventArgs^  e) {
    pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
  }

  System::Void bmptoepaperGUI::MyForm::browseBtn_Click(System::Object^  sender, System::EventArgs^  e) {
    if (openStuff()) {
      fileName->Visible = true;
      fileName2->Visible = true;
      pictureBox2->Image = bitmap;
      mainSelectionPanel->Visible = true;
      ePaperSettingsPanel->Visible = true;
      convertButton->Enabled = true;
    }
  }

System::Void bmptoepaperGUI::MyForm::formatOptions_TextChanged(System::Object^  sender, System::EventArgs^  e) {
  ePaperSettingsPanel->Visible = false;

  if (formatOptions->Text == "ePaper") {
  }
}

System::Void bmptoepaperGUI::MyForm::convertButton_Click(System::Object^  sender, System::EventArgs^  e) {
  if (formatOptions->Text == "ePaper") {
    uint8_t redInt = 0;
    uint8_t yelInt = 0;
    uint8_t bwInt = 0;
    bool LTRBool = true;
    bool TTBBool = true;
    bool invBool = false;

    //check red bits
    if (redDrop->Text == "1-bit") {
      redInt = 1;
    }
    else if (redDrop->Text == "2-bit") {
      redInt = 4;
    }
    else {
      redInt = 0;
    }
    //check yellow bits
    if (yelDrop->Text == "1-bit") {
      yelInt = 1;
    }
    else if (yelDrop->Text == "2-bit") {
      yelInt = 4;
    }
    else {
      yelInt = 0;
    }
    //check black/white bits
    if (bwDrop->Text == "1-bit") {
      bwInt = 1;
    }
    else if (bwDrop->Text == "2-bit") {
      bwInt = 1;
    }
    else {
      bwInt = 0;
    }
    //check if the image reads left to right
    if (RTLButton->Checked == true) {
      LTRBool = false;
    }
    //check if the image reads top to bottom
    if (BTTButton->Checked == true) {
      TTBBool = false;
    }
    //check if the image should be inverted
    if (InvertedCBox->Checked == true) {
      invBool = true;
    }

    Module ePaperModule;
    ePaperModule.initializeDisplay(redInt, yelInt, bwInt, LTRBool, TTBBool, invBool);
    std::string pathLocation = msclr::interop::marshal_as<std::string>(openFileDialog1->FileName);
    processImage(ePaperModule, pathLocation);
    std::string message = "File saved to:\n" + pathLocation;
    MessageBox::Show(gcnew String(message.c_str()), "File Saved");

    CString action = "open";
    ShellExecute(NULL, action, (CString)getOutputFile(pathLocation.c_str()).c_str(), NULL, NULL, SW_SHOW);
  }
}
bool bmptoepaperGUI::MyForm::openStuff()
{
  bool opened = false;
  openFileDialog1 = gcnew OpenFileDialog;

  openFileDialog1->InitialDirectory = "V:\\_CFA - OTS\\CFAP(ePaper)\\CFAP400300C0 - 0420 = 4.2 BWY\\media\\";
  openFileDialog1->Filter = "bmp files (*.bmp)|*.bmp";
  openFileDialog1->FilterIndex = 2;
  openFileDialog1->RestoreDirectory = true;

  if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
    bitmap = gcnew Bitmap(openFileDialog1->FileName, true);
    if ((bitmap->FromFile(openFileDialog1->FileName)) != nullptr)
    {
      opened = true;
      fileName2->Text = openFileDialog1->SafeFileName;
    }
  }
  return opened;
}
System::Void bmptoepaperGUI::MyForm::bwDrop_TextUpdate(System::Object^  sender, System::EventArgs^  e) {
  
}
System::Void bmptoepaperGUI::MyForm::redDrop_TextUpdate(System::Object^  sender, System::EventArgs^  e) {

}
System::Void bmptoepaperGUI::MyForm::yelDrop_TextUpdate(System::Object^  sender, System::EventArgs^  e) {

}