// This is gel/mrc/vpgl/vsph/vsph_spherical_coord.cxx
#include "vsph_spherical_coord.h"
#include <vcl_complex.h>
#include <vcl_cmath.h>

#include <vgl/io/vgl_io_point_3d.h>


#define RADIUS_THRESH 0.0001



vsph_spherical_coord::vsph_spherical_coord(vgl_point_3d<double> origin, double radius)
: radius_(radius), origin_(origin)
{
}

void vsph_spherical_coord::spherical_coord(vgl_point_3d<double> cp, vsph_sph_point_3d& sp)
{
  double radius=0.0, theta=0.0, phi=0.0;

  // move the point to the spherical coordinate system
  double x = cp.x() - origin_.x();
  double y = cp.y() - origin_.y();
  double z = cp.z() - origin_.z();

  radius = vcl_sqrt(x*x+y*y+z*z);

  // if radius is zero, the rsult does not make sense
  if (vcl_abs(radius) < RADIUS_THRESH) {
    sp.set(0.0,0.0,0.0);
    return;
  }

  phi = vcl_atan2(y,x);
  theta = vcl_acos(z/radius);
  sp.set(radius, theta, phi);
}

vgl_point_3d<double> vsph_spherical_coord::cart_coord(vsph_sph_point_3d const& p) const
{

  double x,y,z;
  x = radius_*vcl_sin(p.theta_)*vcl_cos(p.phi_);
  y = radius_*vcl_sin(p.theta_)*vcl_sin(p.phi_);
  z = radius_*vcl_cos(p.theta_);
  // translate the point based on the origin
  vgl_point_3d<double> c(x+origin_.x(),y+origin_.y(),z+origin_.z());
  return c;
}

bool vsph_spherical_coord::move_point(vsph_sph_point_3d& p)
{
  // if it is already on the sphere
  if (vcl_abs(p.radius_ - radius_) < 0.01)
    return false;

  // create a new point with the right radius
  p.set(radius_, p.theta_, p.phi_);
  return true;
}

void vsph_spherical_coord::print(vcl_ostream& os) const
{
  os << " vsph_spherical_coord:[radius=" <<radius_ << ", origin=" << origin_ << "] ";
}

void vsph_spherical_coord::b_read(vsl_b_istream& is)
{
  short version;
  vsl_b_read(is, version);
  switch (version) {
    case 1:
      vsl_b_read(is, radius_);
      vsl_b_read(is, origin_);
      break;
    default:
      vcl_cerr << "I/O ERROR: vsl_b_read(vsl_b_istream&, vsph_spherical_coord&)\n"
               << "           Unknown version number "<< version << '\n';
      is.is().clear(vcl_ios::badbit); // Set an unrecoverable IO error on stream
      break;
  }
}

void vsph_spherical_coord::b_write(vsl_b_ostream& os)
{
  vsl_b_write(os, version());
  vsl_b_write(os, radius_); 
  vsl_b_write(os, origin_);
}

vcl_ostream& operator<<(vcl_ostream& os, vsph_spherical_coord const& p)
{
  p.print(os);
  return os;
}

vcl_ostream& operator<<(vcl_ostream& os, vsph_spherical_coord_sptr const& p)
{
  p->print(os);
  return os;
}
