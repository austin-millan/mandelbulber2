/**
 * Mandelbulber v2, a 3D fractal generator       ,=#MKNmMMKmmßMNWy,
 *                                             ,B" ]L,,p%%%,,,§;, "K
 * Copyright (C) 2014 Krzysztof Marczak        §R-==%w["'~5]m%=L.=~5N
 *                                        ,=mm=§M ]=4 yJKA"/-Nsaj  "Bw,==,,
 * This file is part of Mandelbulber.    §R.r= jw",M  Km .mM  FW ",§=ß., ,TN
 *                                     ,4R =%["w[N=7]J '"5=],""]]M,w,-; T=]M
 * Mandelbulber is free software:     §R.ß~-Q/M=,=5"v"]=Qf,'§"M= =,M.§ Rz]M"Kw
 * you can redistribute it and/or     §w "xDY.J ' -"m=====WeC=\ ""%""y=%"]"" §
 * modify it under the terms of the    "§M=M =D=4"N #"%==A%p M§ M6  R' #"=~.4M
 * GNU General Public License as        §W =, ][T"]C  §  § '§ e===~ U  !§[Z ]N
 * published by the                    4M",,Jm=,"=e~  §  §  j]]""N  BmM"py=ßM
 * Free Software Foundation,          ]§ T,M=& 'YmMMpM9MMM%=w=,,=MT]M m§;'§,
 * either version 3 of the License,    TWw [.j"5=~N[=§%=%W,T ]R,"=="Y[LFT ]N
 * or (at your option)                   TW=,-#"%=;[  =Q:["V""  ],,M.m == ]N
 * any later version.                      J§"mr"] ,=,," =="""J]= M"M"]==ß"
 *                                          §= "=C=4 §"eM "=B:m\4"]#F,§~
 * Mandelbulber is distributed in            "9w=,,]w em%wJ '"~" ,=,,ß"
 * the hope that it will be useful,                 . "K=  ,=RMMMßM"""
 * but WITHOUT ANY WARRANTY;                            .'''
 * without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with Mandelbulber. If not, see <http://www.gnu.org/licenses/>.
 *
 * ###########################################################################
 *
 * Authors: Krzysztof Marczak (buddhi1980@gmail.com)
 *
 * MyDoubleSpinBox class - promoted QDoubleSpinBox widget with context menu
 */

#include "mydoublespinbox.h"
#include "../src/animation_flight.hpp"
#include "../src/animation_keyframes.hpp"
#include <QLineEdit>

void MyDoubleSpinBox::paintEvent(QPaintEvent *event)
{
	if (value() != GetDefault())
	{
		QFont f = font();
		f.setBold(true);
		setFont(f);
	}
	else
	{
		QFont f = font();
		f.setBold(false);
		setFont(f);
	}
	QDoubleSpinBox::paintEvent(event);
}

double MyDoubleSpinBox::GetDefault()
{
	if (parameterContainer && !gotDefault)
	{
		QString type = GetType(objectName());
		if (type == QString("spinbox3") || type == QString("spinboxd3"))
		{
			char lastChar = (parameterName.at(parameterName.length() - 1)).toLatin1();
			QString nameVect = parameterName.left(parameterName.length() - 2);
			CVector3 val = parameterContainer->GetDefault<CVector3>(nameVect);
			defaultValue = val.itemByName(lastChar);
			gotDefault = true;
			setToolTipText();
		}
		else if (type == QString("spinbox4") || type == QString("spinboxd4"))
		{
			char lastChar = (parameterName.at(parameterName.length() - 1)).toLatin1();
			QString nameVect = parameterName.left(parameterName.length() - 2);
			CVector4 val = parameterContainer->GetDefault<CVector4>(nameVect);
			defaultValue = val.itemByName(lastChar);
			gotDefault = true;
			setToolTipText();
		}
		else
		{
			defaultValue = parameterContainer->GetDefault<double>(parameterName);
			gotDefault = true;
			setToolTipText();
		}
	}
	return defaultValue;
}

void MyDoubleSpinBox::resetToDefault()
{
	setValue(defaultValue);
	emit valueChanged(defaultValue);
}

QString MyDoubleSpinBox::getDefaultAsString()
{
	return QString("%L1").arg(defaultValue, 0, 'g', 16);
}

QString MyDoubleSpinBox::getFullParameterName()
{
	QString parName = parameterName;
	QString type = GetType(objectName());
	if (type == QString("spinbox3") || type == QString("spinboxd3") || type == QString("spinbox4")
			|| type == QString("spinboxd4"))
		parName = parameterName.left(parameterName.length() - 2);
	return parName;
}

void MyDoubleSpinBox::contextMenuEvent(QContextMenuEvent *event)
{
	CommonMyWidgetWrapper::contextMenuEvent(event, lineEdit()->createStandardContextMenu());
}
