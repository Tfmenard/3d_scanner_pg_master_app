#include "RowDlg.h"



RowDlg::RowDlg()
{
}


RowDlg::~RowDlg()
{
}

void actionPerformed(const ActionEvent& event)
{
	std::string command = event.getActionCommand();

	if (command == "AddRow")
	{
		//CCameraControlDlg::AddRow();
	}
}