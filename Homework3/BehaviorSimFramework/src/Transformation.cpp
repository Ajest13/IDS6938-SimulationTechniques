//////////////////////////////////////////////////////////////////////////
// Transformation.cpp -- Source file for useful Classes about 3D transformations
//
// Liming Zhao
// 11/02/2007
// University of Pennsylvania

#include "StdAfx.h" // Only needed in MFC

#include "Transformation.h"

/****************************************************************
*																*
*		    vec2 Member functions								*
*																*
****************************************************************/

// CONSTRUCTORS

vec2::vec2() 
{
}

vec2::vec2(const float x, const float y)
{
	n[VX] = x; n[VY] = y; 
}

vec2::vec2(const vec2& v)
{ 
	n[VX] = v.n[VX]; n[VY] = v.n[VY]; 
}

// ASSIGNMENT OPERATORS

vec2& vec2::operator = (const vec2& v)
{ 
	n[VX] = v.n[VX]; n[VY] = v.n[VY]; return *this; 
}

vec2& vec2::operator += ( const vec2& v )
{ 
	n[VX] += v.n[VX]; n[VY] += v.n[VY]; return *this; 
}

vec2& vec2::operator -= ( const vec2& v )
{ 
	n[VX] -= v.n[VX]; n[VY] -= v.n[VY]; return *this; 
}

vec2& vec2::operator *= ( const float d )
{ 
	n[VX] *= d; n[VY] *= d; return *this; 
}

vec2& vec2::operator /= ( const float d )
{ 
	float d_inv = 1.0f/d; n[VX] *= d_inv; n[VY] *= d_inv; return *this; 
}

float& vec2::operator [] ( int i) 
{
	assert(!(i < VX || i > VY));		// subscript check
	return n[i];
}

float vec2::operator [] ( int i) const 
{
	assert(!(i < VX || i > VY));
	return n[i];
}


// SPECIAL FUNCTIONS

float vec2::Length() const
{ 
	return sqrt(SqrLength()); 
}

float vec2::SqrLength() const
{ 
	return n[VX]*n[VX] + n[VY]*n[VY]; 
}

vec2& vec2::Normalize() // it is up to caller to avoid divide-by-zero
{ 
	*this /= Length(); return *this; 
}

// FRIENDS

vec2 operator - (const vec2& a)
{ 
	return vec2(-a.n[VX],-a.n[VY]); 
}

vec2 operator + (const vec2& a, const vec2& b)
{ 
	return vec2(a.n[VX]+ b.n[VX], a.n[VY] + b.n[VY]); 
}

vec2 operator - (const vec2& a, const vec2& b)
{ 
	return vec2(a.n[VX]-b.n[VX], a.n[VY]-b.n[VY]); 
}

vec2 operator * (const vec2& a, const float d)
{ 
	return vec2(d*a.n[VX], d*a.n[VY]); 
}

vec2 operator * (const float d, const vec2& a)
{ 
	return a*d; 
}

float operator * (const vec2& a, const vec2& b)
{ 
	return (a.n[VX]*b.n[VX] + a.n[VY]*b.n[VY]); 
}

vec2 operator / (const vec2& a, const float d)
{ 
	float d_inv = 1.0f/d; return vec2(a.n[VX]*d_inv, a.n[VY]*d_inv); 
}

vec3 operator ^ (const vec2& a, const vec2& b)
{ 
	return vec3(0.0, 0.0, a.n[VX] * b.n[VY] - b.n[VX] * a.n[VY]); 
}

int operator == (const vec2& a, const vec2& b)
{ 
	return (a.n[VX] == b.n[VX]) && (a.n[VY] == b.n[VY]); 
}

int operator != (const vec2& a, const vec2& b)
{ 
	return !(a == b); 
}

vec2 Prod(const vec2& a, const vec2& b)
{ 
	return vec2(a.n[VX] * b.n[VX], a.n[VY] * b.n[VY]); 
}

float Dot(const vec2& a, const vec2& b)
{
	return a*b;
}


/****************************************************************
*																*
*		    vec3 Member functions								*
*																*
****************************************************************/

// CONSTRUCTORS

vec3::vec3() 
{
}

vec3::vec3(const float x, const float y, const float z)
{ 
	n[VX] = x; n[VY] = y; n[VZ] = z; 
}

vec3::vec3(const vec3& v)
{ 
	n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VZ]; 
}

// ASSIGNMENT OPERATORS

vec3& vec3::operator = (const vec3& v)
{ 
	n[VX] = v.n[VX]; n[VY] = v.n[VY]; n[VZ] = v.n[VZ]; return *this; 
}

vec3& vec3::operator += ( const vec3& v )
{ 
	n[VX] += v.n[VX]; n[VY] += v.n[VY]; n[VZ] += v.n[VZ]; return *this; 
}

vec3& vec3::operator -= ( const vec3& v )
{ 
	n[VX] -= v.n[VX]; n[VY] -= v.n[VY]; n[VZ] -= v.n[VZ]; return *this; 
}

vec3& vec3::operator *= ( const float d )
{ 
	n[VX] *= d; n[VY] *= d; n[VZ] *= d; return *this; 
}

vec3& vec3::operator /= ( const float d )
{ 
	float d_inv = 1.0f/d; n[VX] *= d_inv; n[VY] *= d_inv; n[VZ] *= d_inv;
	return *this; 
}

float& vec3::operator [] ( int i) {
	assert(! (i < VX || i > VZ));
	return n[i];
}

float vec3::operator [] ( int i) const {
	assert(! (i < VX || i > VZ));
	return n[i];
}


// SPECIAL FUNCTIONS

float vec3::Length() const
{  
	return sqrt(SqrLength()); 
}

float vec3::SqrLength() const
{  
	return n[VX]*n[VX] + n[VY]*n[VY] + n[VZ]*n[VZ]; 
}

vec3& vec3::Normalize() // it is up to caller to avoid divide-by-zero
{ 
	*this /= Length(); return *this; 
}

vec3 vec3::Cross(vec3 &v) const
{
	vec3 tmp;
	tmp[0] = n[1] * v.n[2] - n[2] * v.n[1];
	tmp[1] = n[2] * v.n[0] - n[0] * v.n[2];
	tmp[2] = n[0] * v.n[1] - n[1] * v.n[0];
	return tmp;
}

// FRIENDS

vec3 operator - (const vec3& a)
{  
	return vec3(-a.n[VX],-a.n[VY],-a.n[VZ]); 
}

vec3 operator + (const vec3& a, const vec3& b)
{ 
	return vec3(a.n[VX]+ b.n[VX], a.n[VY] + b.n[VY], a.n[VZ] + b.n[VZ]); 
}

vec3 operator - (const vec3& a, const vec3& b)
{ 
	return vec3(a.n[VX]-b.n[VX], a.n[VY]-b.n[VY], a.n[VZ]-b.n[VZ]); 
}

vec3 operator * (const vec3& a, const float d)
{ 
	return vec3(d*a.n[VX], d*a.n[VY], d*a.n[VZ]); 
}

vec3 operator * (const float d, const vec3& a)
{ 
	return a*d; 
}

vec3 operator * (const mat3& a, const vec3& v) 
{
#define ROWCOL(i) a.v[i].n[0]*v.n[VX] + a.v[i].n[1]*v.n[VY] \
	+ a.v[i].n[2]*v.n[VZ]
	return vec3(ROWCOL(0), ROWCOL(1), ROWCOL(2));
#undef ROWCOL
}

float operator * (const vec3& a, const vec3& b)
{ 
	return (a.n[VX]*b.n[VX] + a.n[VY]*b.n[VY] + a.n[VZ]*b.n[VZ]); 
}

vec3 operator / (const vec3& a, const float d)
{ 
	float d_inv = 1.0f/d; 
	return vec3(a.n[VX]*d_inv, a.n[VY]*d_inv, a.n[VZ]*d_inv); 
}

vec3 operator ^ (const vec3& a, const vec3& b) 
{
	return vec3(a.n[VY]*b.n[VZ] - a.n[VZ]*b.n[VY],
		a.n[VZ]*b.n[VX] - a.n[VX]*b.n[VZ],
		a.n[VX]*b.n[VY] - a.n[VY]*b.n[VX]);
}

int operator == (const vec3& a, const vec3& b)
{ 
	return (a.n[VX] == b.n[VX]) && (a.n[VY] == b.n[VY]) && (a.n[VZ] == b.n[VZ]);
}

int operator != (const vec3& a, const vec3& b)
{ 
	return !(a == b); 
}

vec3 Prod(const vec3& a, const vec3& b)
{ 
	return vec3(a.n[VX] * b.n[VX], a.n[VY] * b.n[VY], a.n[VZ] * b.n[VZ]); 
}

float Dot(const vec3& a, const vec3& b)
{
	return a*b;
}

/****************************************************************
*																*
*		    mat3 member functions								*
*																*
****************************************************************/

// CONSTRUCTORS

mat3::mat3() 
{
	v[0] = vec3(0.0,0.0,0.0);
	v[1] = v[2] = v[0];
}

mat3::mat3(const vec3& v0, const vec3& v1, const vec3& v2)
{ 
	v[0] = v0; v[1] = v1; v[2] = v2; 
}

mat3::mat3(const mat3& m)
{ 
	v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2]; 
}

// Static functions

mat3 mat3::Identity()
{
	return mat3(vec3(1.0, 0.0, 0.0),
		vec3(0.0, 1.0, 0.0),
		vec3(0.0, 0.0, 1.0));
}

mat3 mat3::Rotation3DRad(const vec3& axis, const float angleRad)
{
	float c = cos(angleRad), s = sin(angleRad), t = 1.0f - c;
	vec3 Axis = axis;
	Axis.Normalize();
	return mat3(vec3(t * Axis[VX] * Axis[VX] + c,
		t * Axis[VX] * Axis[VY] - s * Axis[VZ],
		t * Axis[VX] * Axis[VZ] + s * Axis[VY]),
		vec3(t * Axis[VX] * Axis[VY] + s * Axis[VZ],
		t * Axis[VY] * Axis[VY] + c,
		t * Axis[VY] * Axis[VZ] - s * Axis[VX]),
		vec3(t * Axis[VX] * Axis[VZ] - s * Axis[VY],
		t * Axis[VY] * Axis[VZ] + s * Axis[VX],
		t * Axis[VZ] * Axis[VZ] + c)
		);
}


// Rotation operations, matrix must be orthonormal
bool mat3::ToEulerAnglesZXY(vec3& angleRad) const
{
	angleRad[VX] = asin(v[2][1]);
	if ( angleRad[VX] > -M_PI_2 + EPSILON )
	{
		if ( angleRad[VX] < M_PI_2 - EPSILON )
		{
			angleRad[VZ] = atan2(-v[0][1], v[1][1]);
			angleRad[VY] = atan2(-v[2][0], v[2][2]);
			return true;
		}
		else
		{
			// WARNING.  Not a unique solution.
			angleRad[VY] = 0.0f;
			angleRad[VZ] = atan2(v[0][2], v[0][0]);
			return false;
		}
	}
	else
	{
		// WARNING.  Not a unique solution.
		angleRad[VY] = 0.0f;
		angleRad[VZ] = -atan2(v[0][2], v[0][0]);
		return false;
	}
}

mat3 mat3::FromEulerAnglesZXY(const vec3& angleRad)
{
	mat3 m = mat3::Rotation3DRad(axisZ, angleRad[VZ])
		* mat3::Rotation3DRad(axisX, angleRad[VX])
		* mat3::Rotation3DRad(axisY, angleRad[VY]);
	*this = m;
	return m;
}

// ASSIGNMENT OPERATORS

mat3& mat3::operator = ( const mat3& m )
{ 
	v[0] = m.v[0]; v[1] = m.v[1]; v[2] = m.v[2]; 
	return *this; 
}

mat3& mat3::operator += ( const mat3& m )
{ 
	v[0] += m.v[0]; v[1] += m.v[1]; v[2] += m.v[2]; 
	return *this; 
}

mat3& mat3::operator -= ( const mat3& m )
{ 
	v[0] -= m.v[0]; v[1] -= m.v[1]; v[2] -= m.v[2]; 
	return *this; 
}

mat3& mat3::operator *= ( const float d )
{ 
	v[0] *= d; v[1] *= d; v[2] *= d; 
	return *this; 
}

mat3& mat3::operator /= ( const float d )
{ 
	v[0] /= d; v[1] /= d; v[2] /= d; 
	return *this; 
}

vec3& mat3::operator [] ( int i) 
{
	assert(! (i < VX || i > VZ));
	return v[i];
}

const vec3& mat3::operator [] ( int i) const 
{
	assert(!(i < VX || i > VZ));
	return v[i];
}

// SPECIAL FUNCTIONS

mat3 mat3::Transpose() const 
{
	return mat3(vec3(v[0][0], v[1][0], v[2][0]),
		vec3(v[0][1], v[1][1], v[2][1]),
		vec3(v[0][2], v[1][2], v[2][2]));
}

// FRIENDS

mat3 operator - (const mat3& a)
{ 
	return mat3(-a.v[0], -a.v[1], -a.v[2]); 
}

mat3 operator + (const mat3& a, const mat3& b)
{ 
	return mat3(a.v[0] + b.v[0], a.v[1] + b.v[1], a.v[2] + b.v[2]); 
}

mat3 operator - (const mat3& a, const mat3& b)
{ 
	return mat3(a.v[0] - b.v[0], a.v[1] - b.v[1], a.v[2] - b.v[2]); 
}

mat3 operator * (const mat3& a, const mat3& b) 
{
#define ROWCOL(i, j) \
	a.v[i].n[0]*b.v[0][j] + a.v[i].n[1]*b.v[1][j] + a.v[i].n[2]*b.v[2][j]
	return mat3(vec3(ROWCOL(0,0), ROWCOL(0,1), ROWCOL(0,2)),
		vec3(ROWCOL(1,0), ROWCOL(1,1), ROWCOL(1,2)),
		vec3(ROWCOL(2,0), ROWCOL(2,1), ROWCOL(2,2)));
#undef ROWCOL // (i, j)
}

mat3 operator * (const mat3& a, const float d)
{ 
	return mat3(a.v[0] * d, a.v[1] * d, a.v[2] * d); 
}

mat3 operator * (const float d, const mat3& a)
{ 
	return a*d; 
}

mat3 operator / (const mat3& a, const float d)
{ 
	return mat3(a.v[0] / d, a.v[1] / d, a.v[2] / d); 
}

int operator == (const mat3& a, const mat3& b)
{ 
	return (a.v[0] == b.v[0]) && (a.v[1] == b.v[1]) && (a.v[2] == b.v[2]); 
}

int operator != (const mat3& a, const mat3& b)
{ 
	return !(a == b); 
}

/****************************************************************
*																*
*		    Transform member functions							*
*																*
****************************************************************/

// Constructors
Transform::Transform()
{
	Identity();
}

Transform::Transform(const vec3& translation, const mat3& rotation)
{
	m_translation = translation;
	m_rotation = rotation;
}

Transform::Transform(const vec3& translation)
{
	m_translation = translation;
	m_rotation = mat3::Identity();
}

Transform::Transform(const mat3& rotation)
{
	m_translation = vec3(0.0f, 0.0f, 0.0f);
	m_rotation = rotation;
}

Transform::Transform(const Transform& transform)
{
	m_translation = transform.m_translation;
	m_rotation = transform.m_rotation;
}

// Destructor
Transform::~Transform(void)
{
}

// Member functions
void Transform::Identity()
{
	m_translation = vec3(0.0f, 0.0f, 0.0f);
	m_rotation = mat3::Identity();
}

Transform Transform::Inverse() const
{
	Transform tmp;
	tmp.m_rotation = m_rotation.Transpose();
	tmp.m_translation = tmp.m_rotation * m_translation * -1.0;
	return tmp;
}

Transform& Transform::operator = (const Transform& source)
{
	m_translation = source.m_translation;
	m_rotation = source.m_rotation;
	return *this;
}

Transform operator * (const Transform& t1, const Transform& t2)
{
	Transform tmp;
	tmp.m_rotation = t1.m_rotation * t2.m_rotation;
	tmp.m_translation = t1.m_translation + t1.m_rotation * t2.m_translation;
	return tmp;
}