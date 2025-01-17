#ifndef UTILITIES_H
#define UTILITIES_H

#endif // UTILITIES_H

#include "v3d_interface.h"
#include "my_surf_objs.h"
#include "filter_dialog.h"
#include "math.h"
#include "v3d_basicdatatype.h"
#include "ImgProcessor.h"
#include "bits/stdc++.h"
#include "iostream"
#include "sys/stat.h"
#include "sys/types.h"
#include "dirent.h"
using namespace std;

#ifndef NODE_TILE_LENGTH
#define NODE_TILE_LENGTH 100
#endif

#ifndef zRATIO // This is the ratio of z resolution to x and y in IVSCC images.
#define zRATIO (0.28 / 0.1144)
#endif

#ifndef RESIZE_TILE_LENGTH
#define RESIZE_TILE_LENGTH 500
#endif

#ifndef X_TILE_LENGTH
#define X_TILE_LENGTH RESIZE_TILE_LENGTH
#endif
#ifndef Y_TILE_LENGTH
#define Y_TILE_LENGTH RESIZE_TILE_LENGTH
#endif
#ifndef Z_TILE_LENGTH
#define Z_TILE_LENGTH RESIZE_TILE_LENGTH / zRATIO
#endif
#ifndef RX
#define RX 0.2
#endif
#ifndef RY
#define RY 0.2
#endif
#ifndef RZ
#define RZ 1
#endif

// Objects
#ifndef BLOCK
#define BLOCK
struct block{
    QString name;
    XYZ small;
    XYZ large;
};
#endif

// File manipulation
inline bool exists_file (const std::string& name);
//inline bool exists_file_qs (QString name);
void read_directory(QString name, QList<QString> & files);
void my_mkdir(QString path);
const char * Qstring_to_char(QString qs);

// Generic functions
XYZ offset_XYZ(XYZ input, XYZ offset);
QList<CellAPO> offset_apo(QString input_apo, XYZ offset);
block offset_block(block input_block, XYZ offset);
void crop_img(QString image, block crop_block, QString outputdir_img, V3DPluginCallback2 & callback, QString output_format);
void crop_swc(QString input_swc, QString output_swc, block crop_block);
bool my_saveANO(QString ano_dir, QString fileNameHeader, QList<QString> suffix);
bool generate_2d_img(V3DPluginCallback & cb, QString raw_img, QString swc, V3DLONG in_sz[4], QString output_file);
NeuronTree neuronlist_2_neurontree(QList<NeuronSWC> neuronlist);

// For get_terminal
QList<int> get_tips(NeuronTree nt, bool include_root);
int get_soma(NeuronTree nt);
double node_dist(NeuronSWC a, NeuronSWC b, bool scale);

// functions for getting blocks







