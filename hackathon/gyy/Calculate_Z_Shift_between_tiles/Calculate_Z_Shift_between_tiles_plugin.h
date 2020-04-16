/* Calculate_Z_Shift_between_tiles_plugin.h
 * This is a test plugin, you can use it as a demo.
 * 2020-4-6 : by YourName
 */
 
#ifndef __CALCULATE_Z_SHIFT_BETWEEN_TILES_PLUGIN_H__
#define __CALCULATE_Z_SHIFT_BETWEEN_TILES_PLUGIN_H__

#include <QtGui>
#include <v3d_interface.h>

class TestPlugin : public QObject, public V3DPluginInterface2_1
{
	Q_OBJECT
	Q_INTERFACES(V3DPluginInterface2_1);

public:
	float getPluginVersion() const {return 1.1f;}

	QStringList menulist() const;
	void domenu(const QString &menu_name, V3DPluginCallback2 &callback, QWidget *parent);

	QStringList funclist() const ;
	bool dofunc(const QString &func_name, const V3DPluginArgList &input, V3DPluginArgList &output, V3DPluginCallback2 &callback, QWidget *parent);
};

#endif

