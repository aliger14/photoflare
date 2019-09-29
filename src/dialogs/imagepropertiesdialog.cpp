/*
    This file is part of Photoflare.

    Photoflare is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Photoflare is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Photoflare.  If not, see <https://www.gnu.org/licenses/>.
*/

// ImageProperties dialog class for the Photoflare application.

#include "imagepropertiesdialog.h"
#include "ui_imagepropertiesdialog.h"

imagePropertiesDialog::imagePropertiesDialog(QWidget *parent) :
    QDialog(parent)
  , ui(new Ui::imagePropertiesDialog)
{
    ui->setupUi(this);
    setFixedSize(size());

    ui->imageNameLabel->setText("Untitled");
    ui->folderLabel->setText("<Not saved>");
    ui->fileSizeLabel->setText("<Not saved>");
    ui->dateLabel->setText("<Not saved>");
    ui->colorCountLabel->setText("1");
}

imagePropertiesDialog::~imagePropertiesDialog()
{
    delete ui;
}

void imagePropertiesDialog::setImageName(QString imageName)
{
    ui->imageNameLabel->setText(imageName);
}

void imagePropertiesDialog::setFolder(QString folder)
{
    ui->folderLabel->setText(folder);
}

void imagePropertiesDialog::setSize(QSize size)
{
    float ppi = 96.00f;
    ui->sizeLabel->setText(QString("%1 x %2 pixels ==> %3 x %4 inches (%5 dpi)")
                                .arg(size.width())
                                .arg(size.height())
                                .arg(QString().setNum(size.width() / ppi,'f',2))
                                .arg(QString().setNum(size.height() / ppi,'f',2))
                                .arg(QString().setNum(ppi,'f',2)));
}

void imagePropertiesDialog::setColorCount(QImage image)
{
    QHash<int,char> hash;
    for(int i=0; i<image.width(); i++)
        for(int j=0; j<image.height(); j++)
            hash.insert(image.pixel(i,j),0);

    ui->colorCountLabel->setText(QString("%1").arg(hash.size()));
}

QString sizeToString(qint64 size)
{
    float num = size;
    QStringList list;
    list << "KB" << "MB" << "GB" << "TB";

    QStringListIterator i(list);
    QString unit("bytes");

    while(num >= 1024.0 && i.hasNext())
    {
        unit = i.next();
        num /= 1024.0;
    }

    return QString().setNum(num,'f',2) + " " + unit;
}

void imagePropertiesDialog::setFileSize(qint64 fileSize)
{
    ui->fileSizeLabel->setText(sizeToString(fileSize));
}

void imagePropertiesDialog::setDate(QString date)
{
    ui->dateLabel->setText(date);
}

void imagePropertiesDialog::setMemorySize(qint64 memorySize)
{
    ui->memorySizeLabel->setText(sizeToString(memorySize));
}

void imagePropertiesDialog::setTotalSize(qint64 totalSize)
{
    ui->totalSizeLabel->setText(sizeToString(totalSize));
}
