#pragma once

//auto & s = oneAppData().settings();

#define SAVE_LINE_THIS_GUI(var)  s.setValue(#var, var->text())
#define LOAD_LINE_THIS_GUI(var)  var->setText(s.value(#var).toString())

#define SAVE_BOOL_THIS_GUI(var)  s.setValue(#var, var->isChecked())
#define LOAD_BOOL_THIS_GUI(var)  var->setChecked(s.value(#var).toBool())

#define SAVE_SLDR_THIS_GUI(var)  s.setValue(#var, var->value())
#define LOAD_SLDR_THIS_GUI(var)  var->setValue(s.value(#var).toInt())

#define SAVE_POS__THIS_GUI       s.setValue("pos", this->pos())
#define LOAD_POS__THIS_GUI       this->move(s.value("pos", QPoint(0, 0)).toPoint())

#define SAVE_SIZE_THIS_GUI       s.setValue("size", this->size())
#define LOAD_SIZE_THIS_GUI       this->resize(s.value("size", QSize(400, 300)).toSize())
