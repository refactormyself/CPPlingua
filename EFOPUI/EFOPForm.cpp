#include "EFOPForm.h"
#include <string>
#include "util.h"
#include "../EFOPLib/Environ.h"
#include "../EFOPLib/Rule.h"
#include "msclr/marshal_cppstd.h"
#include <iomanip>
#include <fstream>
#include "../EFOPLib/JsonUtil.h"


using namespace System;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;
using namespace System::Threading;

void MarshalString(String ^ s, std::string& os) {
	using namespace Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

void MarshalString(String ^ s, std::wstring& os) {
	using namespace Runtime::InteropServices;
	const wchar_t* chars =
		(const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(IntPtr((void*)chars));
}

[STAThread]
int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	EFOPUI::EFOPForm form;
	Application::Run(%form);
	return 0;
}

String^ basic_string2String(std::basic_string<char> txt)
{
	auto str = msclr::interop::marshal_as<String^>(txt);
	return  gcnew String(str);
}


void populate_tree(TreeNode% root, const std::vector<Efop::Membrane> & membranes)
{
	
	if (root.Text == "SKIN")
	{
		root.Tag = "SKIN";
		// get all membranes in the list with parent is null
		std::vector<Efop::Membrane> list{};
		for (auto membrane : membranes)
		{
			if (membrane.get_parent_label() == "SKIN")
			{
				list.push_back(membrane);
			}
		}
		
		for (Efop::Membrane mem : list)
		{
			String ^ label = basic_string2String(mem.get_label() + "(" + mem.get_current_state() + ")");
			String ^ tag = basic_string2String(mem.get_label());
			TreeNode child(label);
			child.Tag = tag;
			populate_tree(child, membranes);
			root.Nodes->Add(%child);
		}
	}
	else
	{		
		std::vector<Efop::Membrane> list{};
		for (auto membrane : membranes)
		{
			String ^ parent_label;
			
			if (membrane.get_parent_label() == "SKIN")
			{
				parent_label = "SKIN";
			}
			else
			{
				parent_label = basic_string2String(membrane.get_parent_label());
			}					

			if (parent_label->Equals(root.Tag))
			{
				list.push_back(membrane);
			}
		}
		
		for (Efop::Membrane mem : list)
		{			
			String ^ label = basic_string2String(mem.get_label() + "(" + mem.get_current_state() + ")");
			String ^ tag = basic_string2String(mem.get_label());
			TreeNode child(label);
			child.Tag = tag;
			populate_tree(child, membranes);
			root.Nodes->Add(%child);
		}
		
	}
}

void EFOPUI::EFOPForm::clear_form_data()
{
	textBoxMembrParent->Text = "";
	textBoxMembLabel->Text = "";
	textBoxMembMultiset->Text = "";
	rules_of_current_membrane->Clear();
	rules_source.ResetBindings(false);
	treeView->SelectedNode = nullptr;
}

void EFOPUI::EFOPForm::setup_edit_mode()
{
	clear_form_data();
	treeView->CheckBoxes = true;
	btnCreateMembrane->Text = "Cancel New Membrane";
	btnRunSimulation->Enabled = false;
	btnSaveModel->Enabled = false;
	btnSaveDetails->Visible = true;
	btnOpenModel->Enabled = false;
	textBoxMembRules->Visible = true;
	btnAddRule->Visible = true;
	grpBoxMembraneDetails->Enabled = true;
	treeView->ExpandAll();
	rules_of_current_membrane->Clear();

}

void EFOPUI::EFOPForm::setup_view_mode()
{
	clear_form_data();
	
	treeView->Enabled = true;
	treeView->CheckBoxes = false;
	btnCreateMembrane->Text = "Create New Membrane";
	btnRunSimulation->Enabled = true;
	btnSaveModel->Enabled = true;
	btnSaveDetails->Visible = false;
	btnOpenModel->Enabled = true;
	textBoxMembRules->Visible = false;
	btnAddRule->Visible = false; 
	grpBoxMembraneDetails->Enabled = false;
	treeView->ExpandAll();
	rules_of_current_membrane->Clear();

}

void EFOPUI::EFOPForm::set_edit_mode(bool edit)
{	
	if (edit)
	{
		setup_edit_mode();
	}
	else
	{
		setup_view_mode();
	}

	edit_state_ = edit;
}

System::Void EFOPUI::EFOPForm::EFOPForm_Load(System::Object ^ sender, System::EventArgs ^ e)
{
	//setup rules list box
	rules_source.DataSource = rules_of_current_membrane;
	listBoxRules->DataSource = %rules_source;

	set_edit_mode(false);
	
	auto node = treeView->Nodes->Add("SKIN");
	try
	{
		Efop::Environ& environment = Efop::Environ::Instance("");
		populate_tree(*node, environment.get_membranes());

		treeView->ExpandAll();		
	}
	catch (std::runtime_error& e)
	{
		std::string str = "There is an Error !!! \n";
		str += e.what();
		MessageBox::Show(msclr::interop::marshal_as<String^>(str));
	}
	
	return System::Void();
}

void EFOPUI::EFOPForm::update_eviron_multiset()
{
	labelEnvironValue->Text = msclr::interop::marshal_as<String^>(Efop::Environ::Instance("").get_current_state());
}

void  EFOPUI::EFOPForm::update_tree_view(const std::vector<Efop::Membrane> & membranes)
{	
	update_eviron_multiset();
	treeView->BeginUpdate();
	treeView->CollapseAll();

	treeView->Nodes->Clear();
	const auto node = treeView->Nodes->Add("SKIN");
	populate_tree(*node, membranes);

	treeView->ExpandAll();		
	treeView->EndUpdate();

}

System::Void EFOPUI::EFOPForm::btnOperation_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	auto node = treeView->Nodes->Add("SKIN");
	return System::Void();
}

System::Void EFOPUI::EFOPForm::treeView_AfterSelect(System::Object ^ sender, System::Windows::Forms::TreeViewEventArgs ^ e)
{
	auto node = e->Node;
	
	if (is_edit())
	{
		if (!node->Checked)
		{
			node->Checked = true;
		}
	}
	else
	{
		if (e->Node->Text != "SKIN")
		{
			Efop::Membrane membrane = get_membrane(e->Node->Tag->ToString());
			if (!(membrane.get_label().empty() || membrane.get_label() == "SKIN"))
			{
				const auto text = membrane.get_parent_label();			
				textBoxMembrParent->Text = msclr::interop::marshal_as<String^>(text);
				textBoxMembLabel->Text = msclr::interop::marshal_as<String^>(membrane.get_label());
				textBoxMembMultiset->Text = msclr::interop::marshal_as<String^>(membrane.get_current_state());
				rules_of_current_membrane->Clear();
			
				for (auto rules_string : membrane.get_rules_strings())
				{
					rules_of_current_membrane->Add(msclr::interop::marshal_as<String^>(rules_string));
				}
				rules_source.ResetBindings(false);
			}
			else
			{
				textBoxMembrParent->Text = "";
				textBoxMembLabel->Text = "SKIN";
				textBoxMembMultiset->Text = "";
				rules_of_current_membrane->Clear();
			}
		}

	}
	return System::Void();
}

Efop::Membrane EFOPUI::EFOPForm::get_membrane(String^ str)
{
	std::string label{};
	MarshalString(str, label);
	return Efop::Environ::Instance("").get_membrane_labeled(label);
}

void EFOPUI::EFOPForm::add_membrane(const Efop::Membrane membrane)
{
	const auto all_membranes = Efop::Environ::Instance("").add_membrane(membrane);
	update_tree_view(all_membranes);
}

void EFOPUI::EFOPForm::delete_membrane(String^ label)
{
	auto reply = MessageBox::Show("YOU ARE ABOUT TO DELETE MEMBRANE \"" + label + "\" AND ITS CHILDREN.\n ARE YOU SURE ?",
		"EFOP Warning", MessageBoxButtons::YesNo);
	if (reply == ::DialogResult::Yes)
	{
		std::string lbl = msclr::interop::marshal_as<std::string>(label);
		const auto all_membranes = Efop::Environ::Instance("").delete_membrane_by_label(lbl);
		clear_form_data();
		update_tree_view(all_membranes);

	}
}

System::Void EFOPUI::EFOPForm::btnCreateMembrane_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	set_edit_mode(!is_edit());
	return System::Void();
}

System::Void EFOPUI::EFOPForm::btnSaveDetails_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (String::IsNullOrEmpty(textBoxMembrParent->Text))
	{
		MessageBox::Show("All Membranes must have a parent. If this is a Root Membrane, set the parent to \"SKIN\"", "EFOP UI",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return System::Void();
	}
	
	if (textBoxMembrParent->Text == "SKIN" && !Efop::Environ::Instance("").get_membranes().empty())
	{
		MessageBox::Show("Only one Root Membrane is allowed. Please choose another parent", "EFOP UI",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return System::Void();
	}
	
	if (textBoxMembrParent->Text != "SKIN")
	{
		String^ text = textBoxMembrParent->Text;
		std::string parent_label = msclr::interop::marshal_as<std::string>(text);
		bool is_valid{ false };

		for (auto membrane : Efop::Environ::Instance("").get_membranes())
		{
			if (membrane.get_label() == parent_label)
			{
				is_valid = true;
				break;
			}
		}

		if (!is_valid)
		{
			MessageBox::Show("The selected Parent is not available. Please type in another one.", "EFOP UI",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
			return System::Void();
		}
	}

	if (String::IsNullOrEmpty(textBoxMembLabel->Text))
	{
		MessageBox::Show("Label cannot be empty and it must be unique", "EFOP UI",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return System::Void();
	}
		
	String^ label = textBoxMembLabel->Text;
	std::string membrane_label = msclr::interop::marshal_as<std::string>(label);
	String^ parent_lbl = textBoxMembrParent->Text;
	std::string parent_label = msclr::interop::marshal_as<std::string>(parent_lbl);
	String^ words = textBoxMembMultiset->Text;
	std::string multiset = msclr::interop::marshal_as<std::string>(words);
	std::vector<std::string> rule_strings{};
	std::vector<Efop::Rule> rules{};

	std::shared_ptr<Efop::Membrane> parent = nullptr;

	for (const auto & membrane : Efop::Environ::Instance("").get_membranes())
	{
		if (membrane_label == membrane.get_label())
		{
			MessageBox::Show("Label already exist, please use a different one.", "EFOP UI", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return System::Void();
		}
	}
		
	if (!String::IsNullOrEmpty(textBoxMembRules->Text))
	{
		MessageBox::Show("You need to click the \"+\" button to properly add a rule.\n" + 
			"Please add the rule or remove the text to continue", "EFOP UI",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		this->textBoxMembRules->Select();
		return System::Void();
	}

	try
	{

		//set rule_strings
		for (int i = 0; i < rules_of_current_membrane->Count; ++i)
		{
			auto clr_str = rules_of_current_membrane[i];
			const auto rule_string = msclr::interop::marshal_as<std::string>(clr_str);
			rules.push_back(Efop::Rule::parse_rule_string(rule_string));

		}

	}
	catch (const std::exception& ex)
	{
		String^ what = msclr::interop::marshal_as<String^>(ex.what());
		MessageBox::Show(what += "/n One of the Rule Strings has a syntax error.", "EFOP ERROR",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return System::Void();
	}
	
	// add_membrane(Efop::Membrane(membrane_label, parent, { multiset }, rule_strings));
	add_membrane(Efop::Membrane(membrane_label, parent_label, { multiset }, rules));

	set_edit_mode(false);
	return System::Void();
}


System::Void EFOPUI::EFOPForm::btnAddRule_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (!String::IsNullOrWhiteSpace(textBoxMembRules->Text))
	{
		rules_of_current_membrane->Add(textBoxMembRules->Text);
		rules_source.ResetBindings(false);
		textBoxMembRules->Text = "";
	}

	return System::Void();
}

System::Void EFOPUI::EFOPForm::EFOPForm_KeyUp(System::Object ^ sender, System::Windows::Forms::KeyEventArgs ^ e)
{
	if (e->KeyCode == Keys::Delete)
	{
		
		if (treeView->Focused)
		{
			// Show testDialog as a modal dialog and determine if DialogResult = OK.
			if (this->ShowDialog(this) == ::DialogResult::OK)
			{
				this->labelEnvironValue->Text = "@ TreeView Something is to be deleted";
			}
			else
			{
				this->labelEnvironValue->Text = "@ TreeView Deletion now Cancelled";
			}
			return System::Void();
		}

		if (listBoxRules->Focused)
		{
			// Show testDialog as a modal dialog and determine if DialogResult = OK.
			if (this->ShowDialog(this) == ::DialogResult::OK)
			{
				this->labelEnvironValue->Text = "@ listBox1 Something is to be deleted";
			}
			else
			{
				this->labelEnvironValue->Text = "@ listBox1Deletion now Cancelled";
			}
			return System::Void();
		}

	}

	return System::Void();
}

System::Void EFOPUI::EFOPForm::EFOPForm_KeyPress(System::Object ^ sender, System::Windows::Forms::KeyPressEventArgs ^ e)
{
	return System::Void();
}

System::Void EFOPUI::EFOPForm::EFOPForm_KeyDown(System::Object ^ sender, System::Windows::Forms::KeyEventArgs ^ e)
{
	return System::Void();
}

System::Void EFOPUI::EFOPForm::treeView_KeyUp(System::Object ^ sender, System::Windows::Forms::KeyEventArgs ^ e)
{
	if (treeView->SelectedNode != nullptr)
	{
		auto node = treeView->SelectedNode->Tag->ToString();
		if ((e->KeyCode == Keys::Delete) && (node != "SKIN") )
		{
			delete_membrane(node);
		}
	}
	return System::Void();
}

System::Void EFOPUI::EFOPForm::treeView_AfterCheck(System::Object ^ sender, System::Windows::Forms::TreeViewEventArgs ^ e)
{		
	if (!e->Node->IsSelected)
	{
		treeView->SelectedNode = e->Node;
	}

	textBoxMembrParent->Text = e->Node->Tag->ToString();
	textBoxMembLabel->Select();

	treeView->Enabled = false;
	
	return System::Void();
}

System::Void EFOPUI::EFOPForm::listBoxRules_KeyUp(System::Object ^ sender, System::Windows::Forms::KeyEventArgs ^ e)
{
	 
	if ((e->KeyCode == Keys::Delete) && (listBoxRules->SelectedIndex > -1))
	{
		rules_of_current_membrane->RemoveAt(listBoxRules->SelectedIndex);
		rules_source.ResetBindings(false);
	}
	return System::Void();
}

System::Void EFOPUI::EFOPForm::btnRunSimulation_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	

	Efop::Environ::Instance("").simulate("");
	update_tree_view(Efop::Environ::Instance("").get_membranes());
	return System::Void();

}

System::Void EFOPUI::EFOPForm::btnSaveModel_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	SaveFileDialog ^ saveFileDialog1 = gcnew SaveFileDialog();
	saveFileDialog1->Filter =
		"Json File|*.json|All files|*.*";
	saveFileDialog1->Title = "Save an Model as a json File";
	saveFileDialog1->DefaultExt = "json";
	// saveFileDialog1->CheckFileExists = true;
	saveFileDialog1->ShowDialog();
	
	if (saveFileDialog1->FileName != "")
	{
		const nlohmann::json json_string = Efop::save_environ_json();

		const auto name = saveFileDialog1->FileName;
		const std::string filename = msclr::interop::marshal_as<std::string>(name);
		std::ofstream o(filename);
		o << std::setw(4) << json_string << std::endl;	
		MessageBox::Show("Model Saved.");			
	}
	return System::Void();
}

System::Void EFOPUI::EFOPForm::btnOpenModel_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	OpenFileDialog ^ openFileDialog1 = gcnew OpenFileDialog();
	openFileDialog1->Filter = "Json File|*.json";
	openFileDialog1->Title = "Select a Model File";

	try
	{
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			const auto name = openFileDialog1->FileName;
			const std::string filename = msclr::interop::marshal_as<std::string>(name);
				
			Efop::load_environ_json(filename);
		}
	}
	catch (const std::exception& ex)
	{
		String^ what = msclr::interop::marshal_as<String^>(ex.what());
		MessageBox::Show(what, "EFOP ERROR OPENING FILE",
			MessageBoxButtons::OK, MessageBoxIcon::Error);
		return System::Void();
	}

	const auto all_membranes = Efop::Environ::Instance("").get_membranes();
	update_tree_view(all_membranes);
	return System::Void();
}
