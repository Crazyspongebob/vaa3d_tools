#ifndef ANGLE_CALCULATE_H
#define ANGLE_CALCULATE_H

#include <QtGui>
#include <stdio.h>
#include <stdlib.h>
#include "v3d_interface.h"
#include "basic_surf_objs.h"

class GNFPlugin: public QObject, public V3DPluginInterface2_1
{
    Q_OBJECT
    Q_INTERFACES(V3DPluginInterface2_1);

public:
    float getPluginVersion() const {return 1.0f;}
    QStringList menulist() const;
    void domenu(const QString &menu_name, V3DPluginCallback2 &callback, QWidget *parent);
    QStringList funclist() const ;
    bool dofunc(const QString & func_name, const V3DPluginArgList & input, V3DPluginArgList & output, V3DPluginCallback2 & callback, QWidget * parent);
};

void global_neuron_feature(V3DPluginCallback &callback, QWidget *parent, int method_code);

#endif



