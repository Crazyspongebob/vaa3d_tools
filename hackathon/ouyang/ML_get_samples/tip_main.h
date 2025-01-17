#ifndef GET_TIP_BLOCK_H
#define GET_TIP_BLOCK_H

#include <v3d_interface.h>
#include "../../../released_plugins/v3d_plugins/neurontracing_vn2/app2/my_surf_objs.h"
//#include "prune_short_branch.h"
#include "../../../../vaa3d_tools/v3d_main/jba/newmat11/newmatap.h"
#include "../../../../vaa3d_tools/v3d_main/jba/newmat11/newmatio.h"
#include "../../../../v3d_external/released_plugins_more/v3d_plugins/blastneuron_plugin/pre_processing/align_axis.h"

//#include "../../../../vaa3d_tools/v3d_main/vrrenderer/Matrices.h"
//#include "newmatap.h"
//#include "newmatio.h"
//#include "../../PengXie/preprocess/pre_processing_main.h"
//#include "../../../../v3d_external/released_plugins_more/v3d_plugins/blastneuron_plugin/pre_processing/prune_short_branch.h"

struct block{
    QString name;
    XYZ small;
    XYZ large;
};
struct node_and_id{
    vector<MyMarker> all_nodes;
    vector<int> all_id;
    int total_signal;

};

void get_undertraced_sample(const V3DPluginArgList & input, V3DPluginArgList & output, V3DPluginCallback2 & callback);
void get_overtraced_sample(const V3DPluginArgList & input, V3DPluginArgList & output, V3DPluginCallback2 & callback);
QList<int> get_tips(NeuronTree nt, bool include_root);
block offset_block(block input_block, XYZ offset);
void crop_img(QString image, block crop_block, QString outputdir_img, V3DPluginCallback2 & callback, QString output_format,QString input_swc=0,int tipnum=0,XYZ tip=0,bool mark_others_or_not=0);
void crop_img_not_export(QString image, block crop_block, QString outputdir_img, V3DPluginCallback2 & callback,unsigned char * & cropped_image,QString output_format,QString input_swc=0,int tipnum=0,XYZ tip=0,bool mark_others_or_not=0);
void crop_swc(QString input_swc, QString output_swc, block crop_block);
bool crop_swc_cuboid(NeuronTree nt, QString qs_output,block input_block,bool export_or_not=1);
bool croped_swc_return(NeuronTree nt, QString qs_output,block input_block,QList<NeuronSWC> & croped_swc,bool export_or_not=TRUE);
bool in_cuboid(NeuronSWC node, XYZ small, XYZ large);
bool my_saveANO(QString ano_dir, QString fileNameHeader, QList<QString> suffix);
void printHelp(const V3DPluginArgList & input, V3DPluginArgList & output);
void printHelp1(const V3DPluginArgList & input, V3DPluginArgList & output);
void get2d_label_image(NeuronTree nt_crop_sorted,V3DLONG mysz,unsigned char * data1d_crop,V3DPluginCallback2 & callback,QString output_format,int tipnum,XYZ tip,QList<int>mark_other_nodes,bool mark_other_nodes_or_not);
void get_2d_image(const V3DPluginArgList & input, V3DPluginArgList & output, V3DPluginCallback2 & callback);
void get_3d_mask(const V3DPluginArgList & input, V3DPluginArgList & output, V3DPluginCallback2 & callback);
void get_tip_image(const V3DPluginArgList & input, V3DPluginArgList & output, V3DPluginCallback2 & callback);
void prune_terminal_nodes(const V3DPluginArgList & input, V3DPluginArgList & output, V3DPluginCallback2 & callback);
int find_tip(NeuronTree nt, long sz0, long sz1, long sz2);
QList<int> find_tip_and_itschild_length(NeuronTree nt,double max_length,int tip_index);
QList<int> find_tip_and_itspn(NeuronTree nt, long sz0, long sz1, long sz2);
double aver_ints_around_nodes(long mysz[4],unsigned char * data1d,int radius,NeuronTree nt,QList<int> all_nodes);
double get_circle_signal(vector<MyMarker> allmarkers, unsigned char * data1d,long sz0, long sz1, long sz2);
map<int,float> ratio_r(unsigned char *data1d_crop,QList<NeuronSWC> listswc,float R,float thresh,V3DLONG sz[4]);
node_and_id return_signal_in_circle_nodes(int radius, double ave_signal,V3DLONG mysz[4],unsigned char * data1d,MyMarker center_marker);
vector<MyMarker> get_in_circle_nodes(MyMarker center_marker, double circle_radius);
QList<int> get_tips(NeuronTree nt, bool include_root);
double* get_histogram(MyMarker center_marker,long mysz[4],unsigned char * data1d,int radius);
MyMarker node_to_center(node_and_id all_max_nodes,QList<NeuronSWC>  input_swc,long mysz[4],unsigned char * data1d);
node_and_id get_26_neib_id(MyMarker center_marker,long mysz[4],unsigned char * data1d,int radius);
QList<NeuronSWC> change_tip_xyz(QList<NeuronSWC>input_swc,int tip_node,MyMarker center);
NeuronTree neuronlist_2_neurontree(QList<NeuronSWC> neuronlist);
NeuronTree revise_radius(NeuronTree inputtree,float radius);
NeuronTree get_unfinished_fun(QList<int> tip_list,NeuronTree treeswc,int maximum);
NeuronTree get_overtraced_fun(QList<int> tip_list,NeuronTree sort_swc,int maximum);
NeuronTree get_off_signal_fun(QList<int> tip_list,NeuronTree sort_swc,int range);
void mean_shift_oyq(const V3DPluginArgList & input, V3DPluginArgList & output, V3DPluginCallback2 & callback);
QPair<vector<int>,int>  get_short_tips(NeuronTree nt, bool include_root);
bool export_list2file(const QList<NeuronSWC>& lN, QString fileSaveName);
void get_block(const V3DPluginArgList & input, V3DPluginArgList & output, V3DPluginCallback2 & callback);
void get_branch_block(const V3DPluginArgList & input, V3DPluginArgList & output, V3DPluginCallback2 & callback);
void find_short_branch_tips_func(const V3DPluginArgList & input, V3DPluginArgList & output, V3DPluginCallback2 & callback);
void find_short_branch_tips_menu(V3DPluginCallback2 &callback, QWidget *parent);
bool export_file2record(string swc_name,vector<int>input_num,double cur_per, QString fileSaveName);
void rotation(const V3DPluginArgList & input, V3DPluginArgList & output, V3DPluginCallback2 & callback);
vector<MyMarker> align_axis_marker(vector<MyMarker> input);
bool q_imagewarp_affine(const unsigned char *p_img_sub,const long *sz_img_sub,
        unsigned char *&p_img_affine,Matrix affinematrix,double* trans);
NeuronTree align_axis(NeuronTree input,double *& PC,double* & trans);
void prediction(const V3DPluginArgList & input, V3DPluginArgList & output, V3DPluginCallback2 & callback);
unsigned char * image_enhancement(V3DPluginCallback2 & callback,unsigned char* data1d,QString inimg_file,char * outimg_file2);
QString getAppPath();
#endif // GET_TIP_BLOCK_H
