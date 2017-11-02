#pragma once

// - - - - - -
// vector math - completely compatible with matrix objects
// - - - - - -

#include "Shared.hpp"

template<int dim>
class Vector : public Matrix<1, dim>
{
	public:
		Vector<dim>() : Matrix<1, dim>() { }
		Vector<dim>(const Matrix<1, dim>& m) : Matrix<1, dim>(m) { }
	
		Vector<dim> operator *(float s) const
		{
			Vector<dim> nVec;
			for(int i = 0; i < dim; i++)
			{ nVec[i] = (*this)[i] * s; }
			
			return nVec;
		}
		
		void operator *=(float s)
		{
			*this = *this * s;
		}
		
		float Dot(Vector<dim> v) const
		{
			float d = 0;
			for(int i = 0; i < dim; i++)
			{ d += (*this)[i] * v[i]; }
			
			return d;
		}
		
		float SqrMagnitude() const
		{
			return Dot(*this);
		}
		
		float Magnitude() const
		{
			float sqr = SqrMagnitude();
			return sqrtf(sqr);
		}
		
		Vector<dim> ClampMagnitude(float minMag, float maxMag) const
		{
			minMag = max(minMag, 0);
			maxMag = max(maxMag, 0);
			
			float mag = Magnitude();
			if(mag > 0)
			{
				if(mag < minMag)
				{
					float s = minMag / mag;
					return (*this * s);
				}
				if(mag > maxMag)
				{
					float s = maxMag / mag;
					return (*this * s);
				}
			}
			
			return *this;
		}
		
		Vector<dim> Normalize() const
		{
			float mag = Magnitude();
			if(mag > 0)
			{
				float s = 1 / mag;
				return (*this * s);
			}
			
			return *this;
		}
		
		Vector<dim> Project(Vector<dim> v) const
		{
			Vector<dim> p;
			float dot = dot(v);
			
			for(int i = 0; i < cNum; i++)
			{ p[i] = (dot / v.sqrMagnitude()) * v[i]; }
			
			return p;
		}
		
		static Vector<dim> Lerp(Vector<dim> a, Vector<dim> b, float t)
		{
			t = Clamp(t, 0, 1);
			
			Vector<dim> v = b - a;
			v *= t;
			
			return a + v;
		}
};

class Vector2 : public Vector<2>
{
	public:
		Vector2() : Vector<2>() { }
		Vector2(const Vector<2>& v) : Vector<2>(v) { }
		Vector2(const Matrix<1, 2>& m) : Vector<2>(m) { }
		
		Vector2(float x, float y)
		{
			(*this)[0] = x;
			(*this)[1] = y;
		}
		
		Vector2(float degrees)
		{
			float rad = (float)(degrees / (180.0f / M_PI));
			(*this)[0] = (float)(cos(rad));
			(*this)[1] = (float)(sin(rad));
		}
		
		float ToAngle() const
		{
			float x = (*this)[0];
			float y = (*this)[1];
			float rad = (float)(atan2(y, x));
			
			return (float)(rad * (180.0f / M_PI));
		}
};

class Vector3 : public Vector<3>
{
	public:
		Vector3() : Vector<3>() { }
		Vector3(const Vector<3>& v) : Vector<3>(v) { }
		Vector3(const Matrix<1, 3>& m) : Vector<3>(m) { }
		
		Vector3(float x, float y, float z)
		{
			(*this)[0] = x;
			(*this)[1] = y;
			(*this)[2] = z;
		}

		Vector3 Cross(Vector3 v) const
		{
			float x = ((*this)[1] * v[2]) - ((*this)[2] * v[1]);
			float y = ((*this)[2] * v[0]) - ((*this)[0] * v[2]);
			float z = ((*this)[0] * v[1]) - ((*this)[1] * v[0]);
			
			return Vector3(x, y, z);
		}
};

class Vector4 : public Vector<4>
{
	public:
		Vector4() : Vector<4>() { }
		Vector4(const Vector<4>& v) : Vector<4>(v) { }
		Vector4(const Matrix<1, 4>& m) : Vector<4>(m) { }
		
		Vector4(float x, float y, float z, float w)
		{
			(*this)[0] = x;
			(*this)[1] = y;
			(*this)[2] = z;
			(*this)[3] = w;
		}
};