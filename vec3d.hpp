#ifndef VEC3D_H
#define VEC3D_H

template <class V> 
class Vec3D {
	public:
		Vec3D() : x(0), y(0), z(0) { }
		Vec3D(V i, V j, V k) { x = i; y = j; z = k; }
		
		//I think this function could be improved. Can we do without a cpopy of v?
		Vec3D<V> operator!() { Vec3D<V> v(this->x, this->y, this->z); v.x = -v.x; v.y = -v.y; v.z = -v.z; return v; }
		Vec3D<V> &operator=(const Vec3D<V> &vec) { this->x = vec.x; this->y = vec.y; this->z = vec.z; return *this; }
		Vec3D<V> operator+(const Vec3D<V> &a) { Vec3D<V> v; v.x = x + a.x; v.y = y + a.y; v.z = z + a.z; return v; }
		Vec3D<V> operator*(const Vec3D<V> b) { return (x * b.x + y * b.y + z * b.z); }
		V x;
		V y;
		V z;
};

#endif