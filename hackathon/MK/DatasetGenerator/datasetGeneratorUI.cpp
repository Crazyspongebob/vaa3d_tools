#include <iostream>

#include <qabstractitemview.h>
#include <qitemselectionmodel.h>
#include <qfilesystemmodel.h>
#include <queue>

#include "ui_DatasetGenerator.h"
#include "datasetGeneratorUI.h"
#include "Dataset_Generator_plugin.h"

using namespace std;

DatasetGeneratorUI::DatasetGeneratorUI(QWidget* parent, V3DPluginCallback2* callback): QDialog(parent), ui(new Ui::DatasetGeneratorUI)
{
	ui->setupUi(this);
	
	this->dirModel = new QDirModel(this);
	this->dirModel->setReadOnly(false);
	ui->treeView->setModel(this->dirModel);
	ui->treeView->hideColumn(1);
	ui->treeView->hideColumn(2);
	ui->treeView->hideColumn(3);
	ui->treeView->setCurrentIndex(this->dirModel->index(QDir::currentPath()));

	ui->checkBox_4->setEnabled(true);
	ui->checkBox_11->setEnabled(true);
	ui->checkBox_12->setEnabled(true);
	ui->checkBox_13->setEnabled(true);

	procSteps = new QStringListModel(this);
	procSteps3D = new QStringListModel(this);
	listViewSteps = new QStandardItemModel(this);
	listViewSteps3D = new QStandardItemModel(this);
	this->procItems2D << "Crop" << "Maximum Intensity Projection" << "Minimum Intensity Projection";
	this->procItems3D << "Crop";
	procSteps->setStringList(this->procItems2D);
	procSteps3D->setStringList(this->procItems3D);	
	ui->comboBox->setModel(procSteps);
	ui->comboBox_2->setModel(procSteps3D);
	ui->listView->setModel(listViewSteps);
	ui->listView_2->setModel(listViewSteps3D);
	
	valPer = new QStringListModel(this);
	this->valPercentage << "5%" << "10%" << "15%" << "20%";
	valPer->setStringList(this->valPercentage);
	ui->comboBox_3->setModel(valPer);

	ui->lineEdit_20->setText("0.1");

	connect(&DatasetOperator, SIGNAL(progressBarReporter(QString, int)), this, SLOT(progressBarUpdater(QString, int)));

	DatasetOperator.OperatorCallback = callback;
	this->show();
}

DatasetGeneratorUI::~DatasetGeneratorUI()
{
	delete ui;
}

void DatasetGeneratorUI::progressBarUpdater(QString taskName, int percentage)
{
	ui->progressBar->setAlignment(Qt::AlignCenter);
	ui->progressBar->setFormat(taskName + QString::number(percentage) + "%");
	ui->progressBar->setValue(percentage);
}

void DatasetGeneratorUI::selectClicked()
{
	QModelIndexList indexList = ui->treeView->selectionModel()->selectedIndexes();
	QModelIndex selectedEntry = *(indexList.begin());
	QString wholePath = this->dirModel->fileInfo(selectedEntry).absoluteFilePath();

	QObject* signalSender = sender();
	QString pushButtonName = signalSender->objectName();
	if (pushButtonName == "pushButton_2") ui->lineEdit_7->setText(wholePath);
	else if (pushButtonName == "pushButton_3")
	{	
		ui->lineEdit_8->setText(wholePath);
		if (ui->checkBox_14->isChecked()) ui->lineEdit_27->setText(wholePath);
	}
	else if (pushButtonName == "pushButton_17") ui->lineEdit_26->setText(wholePath);
	else if (pushButtonName == "pushButton_16")
	{
		if (!ui->checkBox_14->isChecked()) ui->lineEdit_27->setText(wholePath);
	}
	else if (pushButtonName == "pushButton_7")
	{
		ui->lineEdit_15->setText(wholePath);
	}
	else if (pushButtonName == "pushButton_9")
	{
		if (ui->checkBox_14->isChecked() && ui->checkBox_11->isChecked())
		{
			ui->groupBox->setChecked(true);
			ui->lineEdit_16->setText(wholePath);
		}
		ui->lineEdit_17->setText(wholePath);
	}
	else if (pushButtonName == "pushButton_10")
	{
		ui->lineEdit_19->setText(wholePath);
		ui->lineEdit_21->setText(wholePath);
	}
	else if (pushButtonName == "pushButton_14")
	{
		ui->lineEdit_22->setText(wholePath);
	}
	else if (pushButtonName == "pushButton_15")
	{
		ui->lineEdit_24->setText(wholePath);
	}
	else if (pushButtonName == "pushButton_12")
	{
		wholePath = wholePath + "/";
		ui->lineEdit_21->setText(wholePath);
	}
}

void DatasetGeneratorUI::checkboxToggled(bool checked)
{
	QObject* signalSender = sender();
	QString checkBoxName = signalSender->objectName();
	
	if (checked == true)
	{
		if (checkBoxName == "checkBox_2")
		{
			ui->checkBox_4->setEnabled(true);
			ui->groupBox_3->setEnabled(true);
		}
		else if (checkBoxName == "groupBox")
		{
			ui->pushButton_8->setEnabled(true);
		}
	}
	else
	{
		if (checkBoxName == "groupBox") ui->pushButton_8->setEnabled(false);
	}
}

void DatasetGeneratorUI::exclusiveToggle(bool checked)
{
	QObject* signalSender = sender();
	QString checkBoxName = signalSender->objectName();

	if (checked == true)
	{
		if (checkBoxName == "groupBox_4") ui->groupBox_3->setChecked(false);
		else if (checkBoxName == "groupBox_3") ui->groupBox_4->setChecked(false);
		else if (checkBoxName == "groupBox_6") ui->groupBox_7->setChecked(false);
		else if (checkBoxName == "groupBox_7") ui->groupBox_6->setChecked(false);
		else if (checkBoxName == "checkBox_11")
		{
			ui->checkBox_12->setChecked(false);
			ui->checkBox_13->setChecked(false);
		}
		else if (checkBoxName == "checkBox_12")
		{
			ui->checkBox_11->setChecked(false);
			ui->checkBox_13->setChecked(false);
		}
		else if (checkBoxName == "checkBox_13")
		{
			ui->checkBox_11->setChecked(false);
			ui->checkBox_12->setChecked(false);
		}
		else if (checkBoxName == "checkBox_14")
		{
			ui->pushButton_17->setEnabled(false);
			ui->lineEdit_26->setEnabled(false);
		}
	}
}

void DatasetGeneratorUI::associativeToggle(bool checked)
{
	QObject* signalSender = sender();
	QString checkBoxName = signalSender->objectName();

	if (checked == true)
	{
		if (checkBoxName == "checkBox_14")
		{
			ui->groupBox_9->setChecked(true);		
			ui->lineEdit_27->setText(ui->lineEdit_8->text());
		}
	}
	else
	{
		if (checkBoxName == "checkBox_14")
		{
			if (ui->checkBox_11->isChecked()) ui->groupBox_9->setChecked(false);
		}
	}
}

void DatasetGeneratorUI::preprocessingEdit()
{
	QObject* emitter = sender();
	QString emitterName = emitter->objectName();
	QString currItemName;
	if (emitterName == "pushButton") currItemName = ui->comboBox->currentText();
	else if (emitterName == "pushButton_4") currItemName = ui->comboBox_2->currentText();
	int listViewCount = ui->listView->model()->rowCount();
	int listViewCount3D = ui->listView_2->model()->rowCount();
	if (emitterName == "pushButton")
	{		
		QStandardItem* newItem = new QStandardItem(currItemName);
		newItem->setFlags(newItem->flags() ^ Qt::ItemIsDropEnabled); // XOR for allowing drop feature but not overwrite
		listViewSteps->appendRow(newItem);
	}
	else if (emitterName == "pushButton_5")
	{
		QModelIndexList selectedItems = ui->listView->selectionModel()->selectedRows();
		if (selectedItems.empty()) return;

		int rowNum = selectedItems.begin()->row();
		listViewSteps->removeRow(rowNum);
	}
	else if (emitterName == "pushButton_4")
	{
		QStandardItem* newItem = new QStandardItem(currItemName);
		newItem->setFlags(newItem->flags() ^ Qt::ItemIsDropEnabled); // XOR for allowing drop feature but not overwrite
		listViewSteps3D->appendRow(newItem);
	}
	else if (emitterName == "pushButton_6")
	{
		QModelIndexList selectedItems = ui->listView_2->selectionModel()->selectedRows();
		if (selectedItems.empty()) return;

		int rowNum = selectedItems.begin()->row();
		listViewSteps3D->removeRow(rowNum);
	}
}

void DatasetGeneratorUI::okClicked()
{
	/* ====================== Create data list =============================== */
	if (ui->groupBox_2->isChecked()) // Create list from existing list.
	{
		taskFromUI newTask;
		newTask.createList = true;
		newTask.createPatch = false;
		newTask.source = ui->lineEdit_19->text().toStdString();
		newTask.outputFileName = ui->lineEdit_21->text().toStdString();
		newTask.subsetRatio = ui->lineEdit_20->text().toDouble();
		newTask.listOp = subset;
		
		DatasetOperator.taskQueu.push(newTask);
	}
	if (ui->groupBox_8->isChecked()) // Create cross validation sets.
	{
		taskFromUI newTask;
		newTask.createList = true;
		newTask.createPatch = false;
		newTask.source = ui->lineEdit_22->text().toStdString();
		newTask.outputDirName = ui->lineEdit_24->text().toStdString();
		newTask.foldNum = ui->lineEdit_23->text().toInt();
		newTask.listOp = crossVal;

		DatasetOperator.taskQueu.push(newTask);
	}
	if (ui->groupBox_9->isChecked() && (!ui->checkBox_14->isChecked())) // Create new list from patch folder.
	{
		taskFromUI newTask;
		newTask.label = ui->lineEdit_25->text().toStdString();
		newTask.createList = true;
		newTask.createPatch = false;
		if (ui->checkBox->isChecked())
		{
			QString valPer = ui->comboBox_3->currentText();
			QStringList valPerParse = valPer.split("%");
			newTask.subsetRatio = (valPerParse[0].toDouble()) / 100;
		}
		else newTask.subsetRatio = 0;
		newTask.source = ui->lineEdit_26->text().toStdString();
		newTask.outputDirName = ui->lineEdit_27->text().toStdString();
		newTask.listOp = newList;

		DatasetOperator.taskQueu.push(newTask);
	}

	/* ======================= Create patches based on neuronstructure file ======================= */
	if (ui->checkBox_2->isChecked()) 
	{
		if (!ui->groupBox_6->isChecked() && !ui->groupBox_7->isChecked())
		{ }

		if (ui->groupBox_6->isChecked()) // single neuron structure file => single image stack or terafly
		{
			taskFromUI newTask;
			newTask.createList = false;
			newTask.createPatch = true;
			newTask.source = ui->lineEdit_7->text().toStdString();
			newTask.outputDirName = ui->lineEdit_8->text().toStdString();

			newTask.neuronStrucFileName = ui->lineEdit_15->text().toStdString(); 
			if (ui->checkBox_4->isChecked()) // from terafly
			{
				if (ui->groupBox_4->isChecked())
				{
					newTask.patchOp = teraTo2D;

					for (int i = 0; i < listViewSteps->rowCount(); ++i)
					{
						QStandardItem* thisItem = listViewSteps->item(i);
						if (thisItem->text() == "Crop") newTask.opSeq.push_back(Crop);
						else if (thisItem->text() == "Maximum Intensity Projection") newTask.opSeq.push_back(MIP);
						else if (thisItem->text() == "Minimum Intensity Projection") newTask.opSeq.push_back(mIP);
					}
					if (ui->checkBox_7->isChecked()) newTask.dimSelection = xy;
					else if (ui->checkBox_8->isChecked()) newTask.dimSelection = yz;
					else if (ui->checkBox_9->isChecked()) newTask.dimSelection = xz;
					newTask.sideX = ui->lineEdit_9->text().toInt();
					newTask.sideY = ui->lineEdit_10->text().toInt();
					newTask.sideZ = ui->lineEdit_11->text().toInt();

					DatasetOperator.taskQueu.push(newTask);
				}
				else if (ui->groupBox_3->isChecked())
				{
					newTask.patchOp = teraTo3D;

					for (int i = 0; i < listViewSteps3D->rowCount(); ++i)
					{
						QStandardItem* thisItem = listViewSteps3D->item(i);
						if (thisItem->text() == "Crop") newTask.opSeq.push_back(Crop);
					}
					newTask.sideX = ui->lineEdit_13->text().toInt();
					newTask.sideY = ui->lineEdit_12->text().toInt();
					newTask.sideZ = ui->lineEdit_14->text().toInt();

					DatasetOperator.taskQueu.push(newTask);
				}
			}
			else // from non-terafly image stack
			{
				if (ui->groupBox_4->isChecked())
				{
					newTask.patchOp = stackTo2D;

					for (int i = 0; i < listViewSteps->rowCount(); ++i)
					{
						QStandardItem* thisItem = listViewSteps->item(i);
						if (thisItem->text() == "Crop") newTask.opSeq.push_back(Crop);
						else if (thisItem->text() == "Maximum Intensity Projection") newTask.opSeq.push_back(MIP);
						else if (thisItem->text() == "Minimum Intensity Projection") newTask.opSeq.push_back(mIP);
					}
					if (ui->checkBox_7->isChecked()) newTask.dimSelection = xy;
					else if (ui->checkBox_8->isChecked()) newTask.dimSelection = yz;
					else if (ui->checkBox_9->isChecked()) newTask.dimSelection = xz;
					newTask.sideX = ui->lineEdit_9->text().toInt();
					newTask.sideY = ui->lineEdit_10->text().toInt();
					newTask.sideZ = ui->lineEdit_11->text().toInt();

					DatasetOperator.taskQueu.push(newTask);
				}
				else if (ui->groupBox_3->isChecked())
				{
					newTask.patchOp = stackTo3D;

					for (int i = 0; i < listViewSteps3D->rowCount(); ++i)
					{
						QStandardItem* thisItem = listViewSteps3D->item(i);
						if (thisItem->text() == "Crop") newTask.opSeq.push_back(Crop);
					}
					newTask.sideX = ui->lineEdit_13->text().toInt();
					newTask.sideY = ui->lineEdit_12->text().toInt();
					newTask.sideZ = ui->lineEdit_14->text().toInt();

					DatasetOperator.taskQueu.push(newTask);
				}
			}

			// -- Determine if data lists are going to be created at the same time or not --
			if (ui->checkBox_14->isChecked())
			{
				taskFromUI newTask2;
				newTask2.createList = true;
				newTask2.createPatch = false;
				newTask2.listOp = newList;
				newTask2.label = ui->lineEdit_25->text().toStdString();
				if (newTask.patchOp == teraTo2D) newTask2.source = ui->lineEdit_8->text().toStdString() + "/terafly_patches_2D";
				newTask2.outputDirName = ui->lineEdit_8->text().toStdString();

				if (ui->checkBox->isChecked())
				{
					QString valPer = ui->comboBox_3->currentText();
					QStringList valPerParse = valPer.split("%");
					newTask2.subsetRatio = (valPerParse[0].toDouble()) / 100;
				}
				else newTask2.subsetRatio = 0;

				DatasetOperator.taskQueu.push(newTask2);
			}
			// -----------------------------------------------------------------------------
		}
		else if (ui->groupBox_7->isChecked()) // multiple neuron structure file => multiple image stacks but no terafly allowed
		{ }
		/* ================ END of [Create patches based on neuronstructure file] ================ */
	}

	DatasetOperator.taskQueuDispatcher();
}
