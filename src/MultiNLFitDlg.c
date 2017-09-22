#include <Origin.h>
#include <..\FittingProject\src\MultiNLFitDlg.h>

bool NLSFIniPraser::readIni(string pathToIni)
{
    INIFile iniFile(pathToIni);
    if(!tree_read_ini(mTreeIni, iniFile))
    	return false;
    return true;
}

bool NLSFIniPraser::getCategories(vector<string> &categories)
{    
	TreeNode treeNodeTmp = mTreeIni.FirstNode;
	while(treeNodeTmp.IsValid())
	{
		treeNodeTmp = mTreeIni.FirstNode.NextNode;
		if(treeNodeTmp.tagName == "Category")
		{
			treeNodeTmp = treeNodeTmp.FirstNode;    	// Start enumerating from the first node
			while(treeNodeTmp.IsValid())		// Checks if the tnTmp node is a valid node or not
			{
				if(treeNodeTmp.Text == "FitFunc" || treeNodeTmp.Text == "fitFunc" )
				{
					out_str("Tag name = " + treeNodeTmp.tagName + ", value = " + treeNodeTmp.Text);
					categories.Add(treeNodeTmp.tagName);
				}
				treeNodeTmp = treeNodeTmp.NextNode; // Forward visiting
			}
			return true;
		}
		treeNodeTmp = treeNodeTmp.NextNode;
	}
	return false;
}

bool NLSFIniPraser::getFunctions(string category, vector<string>& functions)
{
	TreeNode treeNodeTmp = mTreeIni.FirstNode;
	while(treeNodeTmp.IsValid())
	{
		treeNodeTmp = mTreeIni.FirstNode.NextNode;
		if(treeNodeTmp.tagName == category)
		{
			treeNodeTmp = treeNodeTmp.FirstNode;    	// Start enumerating from the first node
			while(treeNodeTmp.IsValid())		// Checks if the tnTmp node is a valid node or not
			{
				out_str("Tag name = " + treeNodeTmp.tagName + ", value = " + treeNodeTmp.Text);
				functions.Add(treeNodeTmp.tagName);
				treeNodeTmp = treeNodeTmp.NextNode; // Forward visiting
			}
			return true;
		}
		treeNodeTmp = treeNodeTmp.NextNode;
	}
	return false;
}

void OpenDlg()
{
	MultiNLFitDialog dlg;
	dlg.DoModal();
}

BOOL MultiNLFitDialog::OnInitDialog()
{
	mCategoryComboBox = GetItem(IDC_CATEGORYCOMBO);
	
	string pathToIni = nlf_get_ini_filepath(0, true);
	if(!mIniParser.readIni(pathToIni)) // read NLSF.ini file with categories and functions
	{
		out_str("Error. INI file was read!")
	}
		
	vector<string> categories;
	if(!mIniParser.getCategories(categories)) // get categories
	{
		out_str("Error. Categories was not found!");
	}
	
	for(int i = 0; i < categories.GetSize(); ++i)
	{
		mCategoryComboBox.AddString(categories[i]);
	}
	return true;
}

BOOL MultiNLFitDialog::OnOk()
{
	return true;
}