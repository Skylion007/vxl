#ifndef bxml_vtol_edge_2d_input_converter_h
#define bxml_vtol_edge_2d_input_converter_h
 
//-----------------------------------------------------------------------------
//
// Class : bxml_vtol_edge_2d_input_converter
//
// .SECTION Description:
//
//     A converter for reading an XML object and returning a bxml_generic_ptr. 
//  
// .NAME bxml_vtol_edge_2d_input_converter -  
// .LIBRARY SpatialObjectXML
// .HEADER SpatialObjects package
// .INCLUDE SpatialObjectXML/bxml_vtol_edge_2d_input_converter.h
// .FILE bxml_vtol_edge_2d_input_converter.C
//
// .SECTION Author:
//    Robert Kaucic -- Jun 2001
//
//-----------------------------------------------------------------------------

#include <vtol/vtol_zero_chain_sptr.h>
#include <vdgl/vdgl_digital_curve_sptr.h>
#include <bxml/bxml_input_converter.h>

class bxml_vtol_edge_2d_input_converter : public bxml_input_converter
{
public:
  bxml_vtol_edge_2d_input_converter();
  virtual ~bxml_vtol_edge_2d_input_converter();
  
  virtual bool extract_object_atrs(DOM_Node& node);
  virtual bool extract_from_dom(DOM_Node& node);

  virtual vcl_string get_id(DOM_Node& node);

  // construct new object
  bxml_generic_ptr construct_object();

protected:
  int new_or_ref;
  vcl_string _id;
  vtol_zero_chain_sptr _zc;
  vdgl_digital_curve_sptr _cur;

};
#endif





