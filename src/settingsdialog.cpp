/* ----------------------------------------------------------------------
FFaudioConverter
Copyright (C) 2018  Elias Martin (Bleuzen)
https://github.com/Bleuzen/FFaudioConverter
supgesu@gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
---------------------------------------------------------------------- */

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QDebug>
#include <QFileDialog>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    // Disable resize
    setFixedSize(width(), height());

    // Init settings elements
    ui->comboBox_OutputFormat->addItem("mp3", "mp3");
    ui->comboBox_OutputFormat->addItem("ogg vorbis", "ogg");
    ui->comboBox_OutputFormat->addItem("opus", "opus");
    ui->comboBox_OutputFormat->addItem("flac", "flac");
    ui->comboBox_OutputFormat->addItem("wav", "wav");

    ui->comboBox_Quality->addItem(tr("Extreme"), "extreme");
    ui->comboBox_Quality->addItem(tr("High"), "high");
    ui->comboBox_Quality->addItem(tr("Medium"), "medium");

    ui->comboBox_OutputSamplerate->addItem(tr("Keep"), "");
    ui->comboBox_OutputSamplerate->addItem("44100 Hz", "44100");
    ui->comboBox_OutputSamplerate->addItem("48000 Hz", "48000");
    ui->comboBox_OutputSamplerate->addItem("96000 Hz", "96000");

    // Set settings in GUI
    LoadSettings();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_buttonBox_accepted()
{
    SaveSettings();
}

void SettingsDialog::SaveSettings()
{
    Settings::FFmpegBinary = ui->lineEdit_FFmpegBinary->text().trimmed();
    Settings::OutputFormat = ui->comboBox_OutputFormat->currentData().toString();
    Settings::Quality = ui->comboBox_Quality->currentData().toString();
    Settings::OutputDirectory = ui->lineEdit_OutputDirectory->text().trimmed();
    Settings::OutputSamplerate = ui->comboBox_OutputSamplerate->currentData().toString();
    Settings::SkipExistingFiles = ui->checkBox_SkipExistingFiles->isChecked();
    Settings::Threads = ui->spinBox_Threads->value();

    QSettings settings;

    settings.setValue("FFmpegBinary", Settings::FFmpegBinary);
    settings.setValue("OutputFormat", Settings::OutputFormat);
    settings.setValue("Quality", Settings::Quality);
    settings.setValue("OutputDirectory", Settings::OutputDirectory);
    settings.setValue("OutputSamplerate", Settings::OutputSamplerate);
    settings.setValue("SkipExistingFiles", Settings::SkipExistingFiles);
    settings.setValue("Threads", Settings::Threads);

    qDebug() << "Settings saved";
}

void SettingsDialog::LoadSettings()
{
    ui->lineEdit_FFmpegBinary->setText(Settings::FFmpegBinary);
    ui->comboBox_OutputFormat->setCurrentIndex(ui->comboBox_OutputFormat->findData(Settings::OutputFormat));
    ui->comboBox_Quality->setCurrentIndex(ui->comboBox_Quality->findData(Settings::Quality));
    ui->lineEdit_OutputDirectory->setText(Settings::OutputDirectory);
    ui->comboBox_OutputSamplerate->setCurrentIndex(ui->comboBox_OutputSamplerate->findData(Settings::OutputSamplerate));
    ui->checkBox_SkipExistingFiles->setChecked(Settings::SkipExistingFiles);
    ui->spinBox_Threads->setValue(Settings::Threads);
}

void SettingsDialog::on_toolButton_SelectOutputDirectory_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), Settings::OutputDirectory, QFileDialog::ShowDirsOnly| QFileDialog::DontResolveSymlinks);
    if(!Util::isNullOrEmpty(dir)) {
        ui->lineEdit_OutputDirectory->setText(dir);
    }
}
