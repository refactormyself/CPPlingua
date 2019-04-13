#pragma once
#include "../EFOPLib/Membrane.h"

namespace EFOPUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Summary for EFOPForm
	/// </summary>
	public ref class EFOPForm : public System::Windows::Forms::Form
	{
	public:
		EFOPForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		bool is_edit() { return edit_state_; }
		void set_edit_mode(bool state);
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~EFOPForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::SplitContainer^  splitContainer1;
	protected:
	private: System::Windows::Forms::GroupBox^  grpBoxMembraneDetails;
	private: System::Windows::Forms::TextBox^  textBoxMembRules;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  textBoxMembMultiset;
	private: System::Windows::Forms::Label^  label3;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBoxMembLabel;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  btnSaveDetails;

	private: System::Windows::Forms::TreeView^  treeView;
	private: System::Windows::Forms::Button^  btnSaveModel;
	private: System::Windows::Forms::Button^  btnRunSimulation;
	private: System::Windows::Forms::Button^  btnCreateMembrane;
	private: System::Windows::Forms::Label^  labelEnvironValue;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  textBoxModelString;

	private: System::Windows::Forms::TextBox^  textBoxMembrParent;
	private: System::Windows::Forms::ListBox^  listBoxRules;

	private: System::Windows::Forms::Button^  btnAddRule;

	private: System::Windows::Forms::ListBox^  listBox2;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Button^  btnOpenModel;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label9;
	private: System::ComponentModel::IContainer^  components;




	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->splitContainer1 = (gcnew System::Windows::Forms::SplitContainer());
			this->btnOpenModel = (gcnew System::Windows::Forms::Button());
			this->labelEnvironValue = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->btnSaveModel = (gcnew System::Windows::Forms::Button());
			this->btnRunSimulation = (gcnew System::Windows::Forms::Button());
			this->btnCreateMembrane = (gcnew System::Windows::Forms::Button());
			this->grpBoxMembraneDetails = (gcnew System::Windows::Forms::GroupBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->listBox2 = (gcnew System::Windows::Forms::ListBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->listBoxRules = (gcnew System::Windows::Forms::ListBox());
			this->btnAddRule = (gcnew System::Windows::Forms::Button());
			this->textBoxModelString = (gcnew System::Windows::Forms::TextBox());
			this->textBoxMembrParent = (gcnew System::Windows::Forms::TextBox());
			this->textBoxMembRules = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->textBoxMembMultiset = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBoxMembLabel = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->btnSaveDetails = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->treeView = (gcnew System::Windows::Forms::TreeView());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->BeginInit();
			this->splitContainer1->Panel1->SuspendLayout();
			this->splitContainer1->Panel2->SuspendLayout();
			this->splitContainer1->SuspendLayout();
			this->grpBoxMembraneDetails->SuspendLayout();
			this->SuspendLayout();
			// 
			// splitContainer1
			// 
			this->splitContainer1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->splitContainer1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->splitContainer1->Location = System::Drawing::Point(0, 0);
			this->splitContainer1->Margin = System::Windows::Forms::Padding(3, 5, 3, 5);
			this->splitContainer1->Name = L"splitContainer1";
			// 
			// splitContainer1.Panel1
			// 
			this->splitContainer1->Panel1->Controls->Add(this->btnOpenModel);
			this->splitContainer1->Panel1->Controls->Add(this->labelEnvironValue);
			this->splitContainer1->Panel1->Controls->Add(this->label5);
			this->splitContainer1->Panel1->Controls->Add(this->btnSaveModel);
			this->splitContainer1->Panel1->Controls->Add(this->btnRunSimulation);
			this->splitContainer1->Panel1->Controls->Add(this->btnCreateMembrane);
			this->splitContainer1->Panel1->Controls->Add(this->grpBoxMembraneDetails);
			this->splitContainer1->Panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &EFOPForm::splitContainer1_Panel1_Paint);
			// 
			// splitContainer1.Panel2
			// 
			this->splitContainer1->Panel2->Controls->Add(this->treeView);
			this->splitContainer1->Size = System::Drawing::Size(769, 578);
			this->splitContainer1->SplitterDistance = 370;
			this->splitContainer1->SplitterWidth = 5;
			this->splitContainer1->TabIndex = 0;
			// 
			// btnOpenModel
			// 
			this->btnOpenModel->Location = System::Drawing::Point(49, 136);
			this->btnOpenModel->Name = L"btnOpenModel";
			this->btnOpenModel->Size = System::Drawing::Size(279, 36);
			this->btnOpenModel->TabIndex = 6;
			this->btnOpenModel->Text = L"Open Model From FIle";
			this->btnOpenModel->UseVisualStyleBackColor = true;
			this->btnOpenModel->Click += gcnew System::EventHandler(this, &EFOPForm::btnOpenModel_Click);
			// 
			// labelEnvironValue
			// 
			this->labelEnvironValue->AutoSize = true;
			this->labelEnvironValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->labelEnvironValue->ForeColor = System::Drawing::Color::White;
			this->labelEnvironValue->Location = System::Drawing::Point(206, 176);
			this->labelEnvironValue->Name = L"labelEnvironValue";
			this->labelEnvironValue->Size = System::Drawing::Size(26, 18);
			this->labelEnvironValue->TabIndex = 5;
			this->labelEnvironValue->Text = L"__";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::Color::White;
			this->label5->Location = System::Drawing::Point(7, 177);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(202, 20);
			this->label5->TabIndex = 4;
			this->label5->Text = L"Current Enviroment Value: ";
			this->label5->Click += gcnew System::EventHandler(this, &EFOPForm::label5_Click);
			// 
			// btnSaveModel
			// 
			this->btnSaveModel->Location = System::Drawing::Point(49, 94);
			this->btnSaveModel->Name = L"btnSaveModel";
			this->btnSaveModel->Size = System::Drawing::Size(279, 36);
			this->btnSaveModel->TabIndex = 3;
			this->btnSaveModel->Text = L"Save Model\'s Current State";
			this->btnSaveModel->UseVisualStyleBackColor = true;
			this->btnSaveModel->Click += gcnew System::EventHandler(this, &EFOPForm::btnSaveModel_Click);
			// 
			// btnRunSimulation
			// 
			this->btnRunSimulation->Location = System::Drawing::Point(49, 51);
			this->btnRunSimulation->Name = L"btnRunSimulation";
			this->btnRunSimulation->Size = System::Drawing::Size(279, 36);
			this->btnRunSimulation->TabIndex = 2;
			this->btnRunSimulation->Text = L"Run Simulation";
			this->btnRunSimulation->UseVisualStyleBackColor = true;
			this->btnRunSimulation->Click += gcnew System::EventHandler(this, &EFOPForm::btnRunSimulation_Click);
			// 
			// btnCreateMembrane
			// 
			this->btnCreateMembrane->Location = System::Drawing::Point(49, 8);
			this->btnCreateMembrane->Name = L"btnCreateMembrane";
			this->btnCreateMembrane->Size = System::Drawing::Size(279, 36);
			this->btnCreateMembrane->TabIndex = 1;
			this->btnCreateMembrane->Text = L"New Membrane";
			this->btnCreateMembrane->UseVisualStyleBackColor = true;
			this->btnCreateMembrane->Click += gcnew System::EventHandler(this, &EFOPForm::btnCreateMembrane_Click);
			// 
			// grpBoxMembraneDetails
			// 
			this->grpBoxMembraneDetails->Controls->Add(this->label10);
			this->grpBoxMembraneDetails->Controls->Add(this->label8);
			this->grpBoxMembraneDetails->Controls->Add(this->label7);
			this->grpBoxMembraneDetails->Controls->Add(this->listBox2);
			this->grpBoxMembraneDetails->Controls->Add(this->button1);
			this->grpBoxMembraneDetails->Controls->Add(this->listBoxRules);
			this->grpBoxMembraneDetails->Controls->Add(this->btnAddRule);
			this->grpBoxMembraneDetails->Controls->Add(this->textBoxModelString);
			this->grpBoxMembraneDetails->Controls->Add(this->textBoxMembrParent);
			this->grpBoxMembraneDetails->Controls->Add(this->textBoxMembRules);
			this->grpBoxMembraneDetails->Controls->Add(this->label4);
			this->grpBoxMembraneDetails->Controls->Add(this->textBoxMembMultiset);
			this->grpBoxMembraneDetails->Controls->Add(this->label3);
			this->grpBoxMembraneDetails->Controls->Add(this->textBoxMembLabel);
			this->grpBoxMembraneDetails->Controls->Add(this->label1);
			this->grpBoxMembraneDetails->Controls->Add(this->btnSaveDetails);
			this->grpBoxMembraneDetails->Controls->Add(this->label2);
			this->grpBoxMembraneDetails->Controls->Add(this->label6);
			this->grpBoxMembraneDetails->Controls->Add(this->label9);
			this->grpBoxMembraneDetails->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->grpBoxMembraneDetails->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->grpBoxMembraneDetails->Location = System::Drawing::Point(0, 199);
			this->grpBoxMembraneDetails->Margin = System::Windows::Forms::Padding(3, 5, 3, 5);
			this->grpBoxMembraneDetails->Name = L"grpBoxMembraneDetails";
			this->grpBoxMembraneDetails->Padding = System::Windows::Forms::Padding(3, 5, 3, 5);
			this->grpBoxMembraneDetails->Size = System::Drawing::Size(368, 377);
			this->grpBoxMembraneDetails->TabIndex = 0;
			this->grpBoxMembraneDetails->TabStop = false;
			this->grpBoxMembraneDetails->Text = L"Details";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Segoe UI", 7.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(5, 230);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(101, 12);
			this->label10->TabIndex = 18;
			this->label10->Text = L"Sample Rule syntax :";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(6, 257);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(61, 13);
			this->label8->TabIndex = 16;
			this->label8->Text = L"a:[a->OUT]";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(7, 243);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(39, 13);
			this->label7->TabIndex = 15;
			this->label7->Text = L"a:[bab]";
			// 
			// listBox2
			// 
			this->listBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->listBox2->FormattingEnabled = true;
			this->listBox2->ItemHeight = 17;
			this->listBox2->Location = System::Drawing::Point(123, 121);
			this->listBox2->Name = L"listBox2";
			this->listBox2->Size = System::Drawing::Size(231, 70);
			this->listBox2->TabIndex = 13;
			this->listBox2->Visible = false;
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(334, 90);
			this->button1->Margin = System::Windows::Forms::Padding(3, 5, 3, 5);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(18, 24);
			this->button1->TabIndex = 12;
			this->button1->Text = L"+";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Visible = false;
			// 
			// listBoxRules
			// 
			this->listBoxRules->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->listBoxRules->FormattingEnabled = true;
			this->listBoxRules->ItemHeight = 17;
			this->listBoxRules->Location = System::Drawing::Point(121, 233);
			this->listBoxRules->Name = L"listBoxRules";
			this->listBoxRules->Size = System::Drawing::Size(231, 104);
			this->listBoxRules->TabIndex = 11;
			this->listBoxRules->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &EFOPForm::listBoxRules_KeyUp);
			// 
			// btnAddRule
			// 
			this->btnAddRule->Location = System::Drawing::Point(334, 201);
			this->btnAddRule->Margin = System::Windows::Forms::Padding(3, 5, 3, 5);
			this->btnAddRule->Name = L"btnAddRule";
			this->btnAddRule->Size = System::Drawing::Size(18, 26);
			this->btnAddRule->TabIndex = 10;
			this->btnAddRule->Text = L"+";
			this->btnAddRule->UseVisualStyleBackColor = true;
			this->btnAddRule->Click += gcnew System::EventHandler(this, &EFOPForm::btnAddRule_Click);
			// 
			// textBoxModelString
			// 
			this->textBoxModelString->Location = System::Drawing::Point(113, 342);
			this->textBoxModelString->Name = L"textBoxModelString";
			this->textBoxModelString->Size = System::Drawing::Size(118, 25);
			this->textBoxModelString->TabIndex = 6;
			this->textBoxModelString->Text = L"1:ae(a={<bab>,<a-#OUT>})[2:cc(c={<bab-#IN1>})|3:aab]";
			this->textBoxModelString->Visible = false;
			// 
			// textBoxMembrParent
			// 
			this->textBoxMembrParent->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBoxMembrParent->Location = System::Drawing::Point(125, 25);
			this->textBoxMembrParent->Margin = System::Windows::Forms::Padding(3, 5, 3, 5);
			this->textBoxMembrParent->Name = L"textBoxMembrParent";
			this->textBoxMembrParent->Size = System::Drawing::Size(121, 25);
			this->textBoxMembrParent->TabIndex = 9;
			// 
			// textBoxMembRules
			// 
			this->textBoxMembRules->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBoxMembRules->Location = System::Drawing::Point(123, 202);
			this->textBoxMembRules->Margin = System::Windows::Forms::Padding(3, 5, 3, 5);
			this->textBoxMembRules->Name = L"textBoxMembRules";
			this->textBoxMembRules->Size = System::Drawing::Size(205, 25);
			this->textBoxMembRules->TabIndex = 8;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(2, 207);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(110, 17);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Membrane Rules:";
			// 
			// textBoxMembMultiset
			// 
			this->textBoxMembMultiset->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBoxMembMultiset->Location = System::Drawing::Point(125, 90);
			this->textBoxMembMultiset->Margin = System::Windows::Forms::Padding(3, 5, 3, 5);
			this->textBoxMembMultiset->Name = L"textBoxMembMultiset";
			this->textBoxMembMultiset->Size = System::Drawing::Size(203, 25);
			this->textBoxMembMultiset->TabIndex = 6;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(2, 93);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(125, 17);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Membrane Multiset:";
			// 
			// textBoxMembLabel
			// 
			this->textBoxMembLabel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->textBoxMembLabel->Location = System::Drawing::Point(125, 57);
			this->textBoxMembLabel->Margin = System::Windows::Forms::Padding(3, 5, 3, 5);
			this->textBoxMembLabel->Name = L"textBoxMembLabel";
			this->textBoxMembLabel->Size = System::Drawing::Size(121, 25);
			this->textBoxMembLabel->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(2, 60);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(110, 17);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Membrane Label:";
			// 
			// btnSaveDetails
			// 
			this->btnSaveDetails->Location = System::Drawing::Point(265, 343);
			this->btnSaveDetails->Margin = System::Windows::Forms::Padding(3, 5, 3, 5);
			this->btnSaveDetails->Name = L"btnSaveDetails";
			this->btnSaveDetails->Size = System::Drawing::Size(87, 29);
			this->btnSaveDetails->TabIndex = 0;
			this->btnSaveDetails->Text = L"Save Details";
			this->btnSaveDetails->UseVisualStyleBackColor = true;
			this->btnSaveDetails->Click += gcnew System::EventHandler(this, &EFOPForm::btnSaveDetails_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(2, 28);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(120, 17);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Parent Membrane: ";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(4, 283);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(118, 13);
			this->label6->TabIndex = 14;
			this->label6->Text = L"a:[bab,a->IN2,a->OUT]";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Segoe UI", 8.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(5, 270);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(56, 13);
			this->label9->TabIndex = 17;
			this->label9->Text = L"a:[a->IN2]";
			// 
			// treeView
			// 
			this->treeView->BackColor = System::Drawing::SystemColors::InactiveCaptionText;
			this->treeView->Dock = System::Windows::Forms::DockStyle::Fill;
			this->treeView->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->treeView->ForeColor = System::Drawing::SystemColors::HotTrack;
			this->treeView->Location = System::Drawing::Point(0, 0);
			this->treeView->Name = L"treeView";
			this->treeView->Size = System::Drawing::Size(392, 576);
			this->treeView->TabIndex = 0;
			this->treeView->AfterCheck += gcnew System::Windows::Forms::TreeViewEventHandler(this, &EFOPForm::treeView_AfterCheck);
			this->treeView->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &EFOPForm::treeView_AfterSelect);
			this->treeView->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &EFOPForm::treeView_KeyUp);
			// 
			// EFOPForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 17);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ControlDarkDark;
			this->ClientSize = System::Drawing::Size(769, 578);
			this->Controls->Add(this->splitContainer1);
			this->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Margin = System::Windows::Forms::Padding(3, 5, 3, 5);
			this->Name = L"EFOPForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"P-SYSTEM SIMULATOR";
			this->Load += gcnew System::EventHandler(this, &EFOPForm::EFOPForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &EFOPForm::EFOPForm_KeyDown);
			this->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &EFOPForm::EFOPForm_KeyPress);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &EFOPForm::EFOPForm_KeyUp);
			this->splitContainer1->Panel1->ResumeLayout(false);
			this->splitContainer1->Panel1->PerformLayout();
			this->splitContainer1->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer1))->EndInit();
			this->splitContainer1->ResumeLayout(false);
			this->grpBoxMembraneDetails->ResumeLayout(false);
			this->grpBoxMembraneDetails->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion


	private:
		bool edit_state_ = false;
		void clear_form_data();
		void setup_edit_mode();
		void setup_view_mode();
		List<String^>^ rules_of_current_membrane = gcnew List<String^>();
		Efop::Membrane get_membrane(String^ str);
		BindingSource rules_source{};
		void add_membrane(Efop::Membrane membrane);
		void update_tree_view(const std::vector<Efop::Membrane> & membrane);
		void delete_membrane(String^ label);

		System::Void splitContainer1_Panel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		}

		System::Void EFOPForm_Load(System::Object^  sender, System::EventArgs^  e);
		void update_eviron_multiset();
		System::Void btnOperation_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void treeView_AfterSelect(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e);
		System::Void btnCreateMembrane_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnSaveDetails_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnAddRule_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void EFOPForm_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);
		System::Void EFOPForm_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e);
		System::Void EFOPForm_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);


		System::Void treeView_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

		System::Void treeView_AfterCheck(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e);
		System::Void listBoxRules_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e);

		System::Void btnRunSimulation_Click(System::Object^  sender, System::EventArgs^  e);

		System::Void btnSaveModel_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnOpenModel_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) {
}
};
}
