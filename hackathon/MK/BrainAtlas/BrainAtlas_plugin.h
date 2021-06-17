/* BrainAtlas_plugin.h
 * This is a test plugin, you can use it as a demo.
 * 2021-6-14 : by Mars Kuo
 */
 
#ifndef __BRAINATLAS_PLUGIN_H__
#define __BRAINATLAS_PLUGIN_H__

#include "BrainAtlasControlPanel.h"

#include <QtGui>
#include <v3d_interface.h>

class BrainAtlas_plugin : public QObject, public V3DPluginInterface2_1
{
	Q_OBJECT
	Q_INTERFACES(V3DPluginInterface2_1);

public:
	float getPluginVersion() const {return 1.1f;}

	QStringList menulist() const;
	void domenu(const QString &menu_name, V3DPluginCallback2 &callback, QWidget *parent);

	QStringList funclist() const ;
	bool dofunc(const QString &func_name, const V3DPluginArgList &input, V3DPluginArgList &output, V3DPluginCallback2 &callback, QWidget *parent);

	BrainAtlasControlPanel* ctrlPanelPtr;
};

#endif

