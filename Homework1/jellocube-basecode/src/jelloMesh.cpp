#include "JelloMesh.h"
#include <GL/glut.h>
#include <algorithm>

// TODO
<<<<<<< HEAD
double JelloMesh::g_structuralKs = 2800.0; 
double JelloMesh::g_structuralKd = 6.0; 
double JelloMesh::g_attachmentKs = 2000;
double JelloMesh::g_attachmentKd = 6.0;
double JelloMesh::g_shearKs = 2500.0;
double JelloMesh::g_shearKd = 5.0;
double JelloMesh::g_bendKs = 2500.0;
double JelloMesh::g_bendKd = 6.0;
double JelloMesh::g_penaltyKs = 100000.0;
double JelloMesh::g_penaltyKd = 6.0;
=======

double JelloMesh::g_penaltyKs = 0.0;
double JelloMesh::g_penaltyKd = 0.0;
>>>>>>> afa748385af523b86a45c7f4cac8aa8b4b612f21

JelloMesh::JelloMesh() :     
    m_integrationType(JelloMesh::RK4), 
    m_cols(0), m_rows(0), m_stacks(0), m_width(0.0), m_height(0.0), m_depth(0.0)
{
    SetSize(1.0, 1.0, 1.0);

}

JelloMesh::~JelloMesh()
{
}

void JelloMesh::Reset()
{
    InitJelloMesh();
}

JelloMesh::Particle& JelloMesh::GetParticle(JelloMesh::ParticleGrid& grid, int i, int j, int k)
{
    return grid[i][j][k];
}

JelloMesh::Particle& JelloMesh::GetParticle(JelloMesh::ParticleGrid& grid, int idx)
{
    int i,j,k;
    GetCell(idx, i, j, k);
    return GetParticle(grid, i,j,k);
}

const JelloMesh::Particle& JelloMesh::GetParticle(const JelloMesh::ParticleGrid& grid, int i, int j, int k) const
{
    return grid[i][j][k];
}

const JelloMesh::Particle& JelloMesh::GetParticle(const JelloMesh::ParticleGrid& grid, int idx) const
{
    int i,j,k;
    GetCell(idx, i, j, k);
    return GetParticle(grid, i,j,k);
}




void JelloMesh::SetSize(float width, float height, float depth)
{
    m_width = width;
    m_height = height;
    m_depth = depth;
    InitJelloMesh();
}



int JelloMesh::GetIndex(int i, int j, int k) const
{
    int cols = j;
    int rows = i*(m_rows+1);
    int stacks = k*(m_cols+1)*(m_stacks+1);
    return cols + rows + stacks;
}

#define ROUND(x) (floor(x + 0.5))
#define FLOOR(x) (floor(x))
#define FRACT(x) (x - FLOOR(x))
void JelloMesh::GetCell(int idx, int& i, int &j, int& k) const
{
    float rows = m_rows+1;
    float cols = m_cols+1;
    float stacks = m_stacks+1;

    // derived from idx = cols*(rows*k + i) + j
    float tmp = FLOOR(idx/cols);
    j = (int) ROUND(cols*(FRACT(idx/cols)));
    i = (int) ROUND(rows*(FRACT(tmp/rows)));
    k = (int) FLOOR(tmp/rows);
}

void JelloMesh::InitJelloMesh()
{
<<<<<<< HEAD
	m_vsprings.clear();

	if (m_width < 0.01 || m_height < 0.01 || m_depth < 0.01) return;
	if (m_cols < 1 || m_rows < 1 || m_stacks < 1) return;

	// Init particles
	float wcellsize = m_width / m_cols;
	float hcellsize = m_height / m_rows;
	float dcellsize = m_depth / m_stacks;

	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				float x = -m_width*0.5f + wcellsize*i;
				float y = 0.5 + hcellsize*j;
				float z = -m_depth*0.5f + dcellsize*k;
				m_vparticles[i][j][k] = Particle(GetIndex(i, j, k), vec3(x, y, z)); 
			}
		}
	}

	// Setup structural springs
	ParticleGrid& g = m_vparticles;
	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				if (j < m_cols) AddStructuralSpring(GetParticle(g, i, j, k), GetParticle(g, i, j + 1, k));
				if (i < m_rows) AddStructuralSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j, k));
				if (k < m_stacks) AddStructuralSpring(GetParticle(g, i, j, k), GetParticle(g, i, j, k + 1));
			}
		}
	}
	// Setup shear springs
	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				if (j < m_cols && i < m_rows) AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j + 1, k));
				if (j > 0 && i < m_rows) AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j - 1, k));				
				
				if (j < m_cols && k < m_stacks) AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i, j + 1, k + 1));
				if (j > 0 && k < m_stacks) AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i, j - 1, k + 1));
				
				if (i < m_rows && k < m_stacks) AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i + 1, j, k + 1));
				if (i > 0 && k < m_stacks) AddShearSpring(GetParticle(g, i, j, k), GetParticle(g, i - 1, j, k + 1));
			}
		}
	}

	// Setup bend springs
	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
			if (i < m_rows - 3) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i + 4, j, k));
			if (j < m_cols - 3) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i, j + 4, k));
			if (k < m_stacks - 3) AddBendSpring(GetParticle(g, i, j, k), GetParticle(g, i, j, k + 4));
			}
		}
	}

    // Init mesh geometry
    m_mesh.clear();
    m_mesh.push_back(FaceMesh(*this,XLEFT));
    m_mesh.push_back(FaceMesh(*this,XRIGHT));
    m_mesh.push_back(FaceMesh(*this,YTOP));
    m_mesh.push_back(FaceMesh(*this,YBOTTOM));
    m_mesh.push_back(FaceMesh(*this,ZFRONT));
    m_mesh.push_back(FaceMesh(*this,ZBACK));
}

void JelloMesh::AddStructuralSpring(Particle& p1, Particle& p2)
{
    double restLen = (p1.position - p2.position).Length();
    m_vsprings.push_back(Spring(STRUCTURAL, p1.index, p2.index, g_structuralKs, g_structuralKd, restLen));
=======

	float x, y, z;
	x = y = z = 0.0f;
	m_vparticles.resize(10);
    for (int i = 0; i <10; i++)
    {
		m_vparticles[i][j][k] = Particle(GetIndex(i, j, k), vec3(x, y, z));
    }

>>>>>>> afa748385af523b86a45c7f4cac8aa8b4b612f21
}


void JelloMesh::SetIntegrationType(JelloMesh::IntegrationType type)
{
    m_integrationType = type;
}

JelloMesh::IntegrationType JelloMesh::GetIntegrationType() const
{
    return m_integrationType;
}

void JelloMesh::SetDrawFlags(unsigned int flags)
{
    m_drawflags = flags;
}

unsigned int JelloMesh::GetDrawFlags() const
{
    return m_drawflags;
}


void JelloMesh::DrawCollisionNormals()
{
    const ParticleGrid& g = m_vparticles;
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    for(unsigned int i = 0; i < m_vcollisions.size(); i++)
    {
       Intersection intersection = m_vcollisions[i];
       //if (isInterior(intersection.m_p)) continue;

       const Particle& pt = GetParticle(g, intersection.m_p);
       vec3 normal = intersection.m_normal;
       vec3 end = pt.position + 0.2 * normal;
       glVertex3f(pt.position[0], pt.position[1], pt.position[2]);
       glVertex3f(end[0], end[1], end[2]);
    }     
    glEnd();
}

void JelloMesh::DrawForces()
{
	glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    for (int i = 0; i < m_rows+1; i++)
    {
        for (int j = 0; j < m_cols+1; j++)
        {
            for (int k = 0; k < m_stacks+1; k++)
            {
                Particle p = m_vparticles[i][j][k];
               // if (isInterior(i,j,k)) continue;

                vec3 normal = p.force.Normalize();
                vec3 end = p.position + 0.1 * normal;
                glVertex3f(p.position[0], p.position[1], p.position[2]);
                glVertex3f(end[0], end[1], end[2]);
            }
        }
    }     
    glEnd();
	glEnable(GL_LIGHTING);
}



void JelloMesh::DrawParticles()
{
	glDisable(GL_LIGHTING);
	glPointSize(18.0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_NOTEQUAL, 0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glBegin(GL_POINTS);

	glColor4f(1.0, 1.0, 0.0, 0.99);
	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				Particle& p = GetParticle(m_vparticles, i, j, k);
				glVertex3f(p.position[0], p.position[1], p.position[2]);

			}
		}
	}
	glEnd();
	glEnable(GL_LIGHTING);


	glDisable(GL_POINT_SMOOTH);
	glBlendFunc(GL_NONE, GL_NONE);
	glDisable(GL_BLEND);


	return;
}

void JelloMesh::Draw(const vec3& eyePos)
{
	DrawParticles();
	DrawForces();
}

void JelloMesh::Update(double dt, const World& world, const vec3& externalForces)
{
    m_externalForces = externalForces;

	CheckForCollisions(m_vparticles, world);
	ComputeForces(m_vparticles);
	ResolveContacts(m_vparticles);
	ResolveCollisions(m_vparticles);

    switch (m_integrationType)
    {
    case EULER: EulerIntegrate(dt); break;
    case MIDPOINT: MidPointIntegrate(dt); break;
    case RK4: RK4Integrate(dt); break;
    }
}

void JelloMesh::CheckForCollisions(ParticleGrid& grid, const World& world)
{
    m_vcontacts.clear();
    m_vcollisions.clear();

    for (int i = 0; i < m_rows+1; i++)
    {
        for (int j = 0; j < m_cols+1; j++)
        {
            for (int k = 0; k < m_stacks+1; k++)
            {
                Particle& p = GetParticle(grid, i,j,k);

                // 1. Check collisions with world objects 
                for (unsigned int i = 0; i < world.m_shapes.size(); i++)
                {
                    Intersection intersection;

                    if (world.m_shapes[i]->GetType() == World::CYLINDER && 
                        CylinderIntersection(p, (World::Cylinder*) world.m_shapes[i], intersection))
                    {
                        m_vcontacts.push_back(intersection);
                    }

					else if (world.m_shapes[i]->GetType() == World::SPHERE &&
						SphereIntersection(p, (World::Sphere*) world.m_shapes[i], intersection))
					{
						m_vcontacts.push_back(intersection);
					}
                    else if (world.m_shapes[i]->GetType() == World::GROUND && 
                        FloorIntersection(p, intersection))
                    {
							m_vcontacts.push_back(intersection);
                    }
                }
            }
        }
    }
}

void JelloMesh::ComputeForces(ParticleGrid& grid)
{
    // Add external froces to all points
    for (int i = 0; i < m_rows+1; i++)
    {
        for (int j = 0; j < m_cols+1; j++)
        {
            for (int k = 0; k < m_stacks+1; k++)
            {
                Particle& p = GetParticle(grid, i,j,k);
                p.force = m_externalForces * p.mass;
				
            }
        }
    }

<<<<<<< HEAD
    // Update springs
    for(unsigned int i = 0; i < m_vsprings.size(); i++)
    {
        Spring& spring = m_vsprings[i];
        Particle& a = GetParticle(grid, spring.m_p1);
        Particle& b = GetParticle(grid, spring.m_p2);
		
		vec3 pdiff = a.position - b.position;
		vec3 vdiff = b.velocity - a.velocity;
		double dist = pdiff.Length();

		vec3 force = a.force + b.force;
		
		if (dist != 0) {
			force = -(spring.m_Ks *(dist - spring.m_restLen) + spring.m_Kd * ((vdiff * pdiff)/dist)) * (pdiff/dist);
			a.force += force;
			b.force += -force;
		}
    }
=======
    // Update Flocking
  // TODO


    
>>>>>>> afa748385af523b86a45c7f4cac8aa8b4b612f21
}

void JelloMesh::ResolveContacts(ParticleGrid& grid)
{
    for (unsigned int i = 0; i < m_vcontacts.size(); i++)
    {
       const Intersection& contact = m_vcontacts[i];
       Particle& p = GetParticle(grid, contact.m_p);
	   double dist = contact.m_distance;
	   vec3 normal = contact.m_normal; 
	   vec3 diff = -dist * normal;

	   p.force = g_penaltyKs * (dist * normal) + g_penaltyKd * (diff/dist);
    } 
}

void JelloMesh::ResolveCollisions(ParticleGrid& grid)
{
    for(unsigned int i = 0; i < m_vcollisions.size(); i++)
    {
        Intersection result = m_vcollisions[i];
        Particle& pt = GetParticle(grid, result.m_p);
        vec3 normal = result.m_normal;
        float dist = result.m_distance;
		double r = 0.75;

		//pt.position += dist * normal;
		pt.velocity += pt.velocity - 2 * (pt.velocity * normal) * normal * r;
	}
}

bool JelloMesh::FloorIntersection(Particle& p, Intersection& intersection)
{
	if (p.position.n[1] <= 0.0)
	{
		intersection.m_p = p.index;
		intersection.m_distance = -p.position[1];
		intersection.m_type = CONTACT;   
		intersection.m_normal = vec3(0.0, 1.0, 0.0);
		return true;
	}
	else if (p.position[1] < 0.0 + 0.05)
	{
		intersection.m_p = p.index;
		intersection.m_distance = 0.05 - p.position[1];
		intersection.m_type = COLLISION;
		intersection.m_normal = vec3(0.0, 1.0, 0.0);
		return true;
	}
	else
		return false;
}
bool JelloMesh::CylinderIntersection(Particle& p, World::Cylinder* cylinder, //Modifications made using Julie's WolframAlpha link posted on piazza
                                 JelloMesh::Intersection& result)
{
    vec3 cylinderStart = cylinder->start;
    vec3 cylinderEnd = cylinder->end;
    vec3 cylinderAxis = cylinderEnd - cylinderStart;
	vec3 cylinderDiff = cylinderStart - p.position;
	double time = -(cylinderDiff * cylinderAxis)/(cylinderAxis.Length()*cylinderAxis.Length());
	double cylinderRadius = cylinder->r;
	vec3 point = cylinderStart + time * cylinderAxis;
	vec3 normal = p.position - point;
	double dist = normal.Length();
	normal = normal.Normalize();
	

	if (dist < cylinderRadius)
	{
		result.m_p = p.index;
		result.m_distance = cylinderRadius - dist;
		result.m_type = CONTACT;
		result.m_normal = normal.Normalize();
		return true;
	}

	else if (dist < cylinderRadius + 0.05)
	{
		result.m_p = p.index;
		result.m_distance = dist - (cylinderRadius + 0.05);
		result.m_type = COLLISION;
		result.m_normal = normal.Normalize();
		return true;
	}
	return false;
}

bool JelloMesh::SphereIntersection(Particle& p, World::Sphere* sphere,
							JelloMesh::Intersection& result)
{
	vec3 ptMid = sphere->pos;
	double sphereRadius = sphere->r;
	vec3 normal = p.position - ptMid;
	double dist = normal.Length();

	if (dist < sphereRadius)
	{
		result.m_distance = sphereRadius - dist;
		result.m_p = p.index;
		result.m_normal = normal.Normalize();
		result.m_type = CONTACT;
		return true;

	}
	if (dist < sphereRadius + 0.05)
	{
		result.m_distance = dist - (sphereRadius + 0.05);
		result.m_p = p.index;
		result.m_normal = normal.Normalize();
		result.m_type = COLLISION;
		return true;

	}
	return false;
}
void JelloMesh::EulerIntegrate(double dt)
{	
	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				Particle& p = GetParticle(m_vparticles, i, j, k);

				p.velocity = p.velocity + dt * p.force * 1/p.mass;

				p.position = p.position + dt * p.velocity;
			}
		}
	}
}

void JelloMesh::MidPointIntegrate(double dt)
{
	double halfdt = 0.5 * dt;
	ParticleGrid target = m_vparticles;
	ParticleGrid& source = m_vparticles;


	ParticleGrid accum1 = m_vparticles;
	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				Particle& s = GetParticle(source, i, j, k);

				Particle& k1 = GetParticle(accum1, i, j, k);
				k1.force = halfdt * s.force * 1 / s.mass;
				k1.velocity = halfdt * s.velocity;

				Particle& t = GetParticle(target, i, j, k);
				t.velocity = s.velocity + k1.force;
				t.position = s.position + k1.velocity;
			}
		}
	}

	ComputeForces(target);
	
	ParticleGrid accum2 = m_vparticles;
	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				Particle& t = GetParticle(target, i, j, k);
				Particle& k2 = GetParticle(accum2, i, j, k);

				k2.force = halfdt * t.force * 1 / t.mass;
				k2.velocity = halfdt * t.velocity;

				Particle& s = GetParticle(source, i, j, k);
				t.velocity = s.velocity + k2.force;
				t.position = s.position + k2.velocity;
			}
		}
	}
	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				Particle& p = GetParticle(m_vparticles, i, j, k);
				Particle& k1 = GetParticle(accum1, i, j, k);
				Particle& k2 = GetParticle(accum2, i, j, k);

				p.velocity = p.velocity + dt * ((0.5 * p.force + 0.5 * k1.force) * 1/p.mass);

				p.position = p.position + dt * (0.5 * p.velocity + 0.5 * k1.velocity);
			}
		}
	}
}

void JelloMesh::RK4Integrate(double dt)
{
	double halfdt = 0.5 * dt;
	ParticleGrid target = m_vparticles;  // target is a copy!
	ParticleGrid& source = m_vparticles;  // source is a ptr!

	// Step 1
	ParticleGrid accum1 = m_vparticles;
	for (int i = 0; i < m_rows + 1; i++)
	{
		for (int j = 0; j < m_cols + 1; j++)
		{
			for (int k = 0; k < m_stacks + 1; k++)
			{
				Particle& s = GetParticle(source, i, j, k);

				Particle& k1 = GetParticle(accum1, i, j, k);
				k1.force = halfdt * s.force * 1 / s.mass;
				k1.velocity = halfdt * s.velocity;

				Particle& t = GetParticle(target, i, j, k);
				t.velocity = s.velocity + k1.force;
				t.position = s.position + k1.velocity;
			}
		}
	}

    ComputeForces(target);

    // Step 2
    ParticleGrid accum2 = m_vparticles;
    for (int i = 0; i < m_rows+1; i++)
    {
        for (int j = 0; j < m_cols+1; j++)
        {
            for (int k = 0; k < m_stacks+1; k++)
            {
                Particle& t = GetParticle(target, i,j,k);
                Particle& k2 = GetParticle(accum2, i,j,k);

                k2.force = halfdt * t.force * 1/t.mass;
                k2.velocity = halfdt * t.velocity;

                Particle& s = GetParticle(source, i,j,k);
                t.velocity = s.velocity + k2.force;
                t.position = s.position + k2.velocity;
            }
        }
    }

    ComputeForces(target);

    // Step 3
    ParticleGrid accum3 = m_vparticles;
    for (int i = 0; i < m_rows+1; i++)
    {
        for (int j = 0; j < m_cols+1; j++)
        {
            for (int k = 0; k < m_stacks+1; k++)
            {
            Particle& t = GetParticle(target, i,j,k);
            Particle& k3 = GetParticle(accum3, i,j,k);

            k3.force = dt * t.force * 1/t.mass;
            k3.velocity = dt * t.velocity;

            Particle& s = GetParticle(source, i,j,k);
            t.velocity = s.velocity + k3.force;
            t.position = s.position + k3.velocity;
            }
        }
    }
    ComputeForces(target);

    // Step 4
    ParticleGrid accum4 = m_vparticles;
    for (int i = 0; i < m_rows+1; i++)
    {
        for (int j = 0; j < m_cols+1; j++)
        {
            for (int k = 0; k < m_stacks+1; k++)
            {
                Particle& t = GetParticle(target, i,j,k);
                Particle& k4 = GetParticle(accum4, i,j,k);

                k4.force = dt * t.force * 1/t.mass;
                k4.velocity = dt * t.velocity;
            }
        }
    }

    // Put it all together
    double asixth = 1/6.0;
    double athird = 1/3.0;
    for (int i = 0; i < m_rows+1; i++)
    {
        for (int j = 0; j < m_cols+1; j++)
        {
            for (int k = 0; k < m_stacks+1; k++)
            {
                Particle& p = GetParticle(m_vparticles, i,j,k);
                Particle& k1 = GetParticle(accum1, i,j,k);
                Particle& k2 = GetParticle(accum2, i,j,k);
                Particle& k3 = GetParticle(accum3, i,j,k);
                Particle& k4 = GetParticle(accum4, i,j,k);
                
                p.velocity = p.velocity + asixth * k1.force + 
                    athird * k2.force + athird * k3.force + asixth * k4.force;

                p.position = p.position + asixth * k1.velocity + 
                    athird * k2.velocity + athird * k3.velocity + asixth * k4.velocity;
            }
        }
    }
}





//---------------------------------------------------------------------
// Particle
//---------------------------------------------------------------------

JelloMesh::Particle JelloMesh::Particle::EMPTY;

JelloMesh::Particle::Particle(int idx, const vec3& p, const vec3& v, double m)
{
    index = idx;
    position = p;
    velocity = v;
    force = vec3(0,0,0);
    mass = m;
}

JelloMesh::Particle::Particle() : index(-1), position(0,0,0), velocity(0,0,0), force(0,0,0), mass(1.0)
{
}

JelloMesh::Particle::Particle(const JelloMesh::Particle& p) : 
    index(p.index), position(p.position), velocity(p.velocity), force(p.force), mass(p.mass)
{
}

JelloMesh::Particle& JelloMesh::Particle::operator=(const JelloMesh::Particle& p)
{
    if (&p == this) return *this;

    index = p.index;
    position = p.position;
    velocity = p.velocity;
    force = p.force;
    mass = p.mass;
    return *this;
}

//---------------------------------------------------------------------
// Intersection
//---------------------------------------------------------------------

JelloMesh::Intersection::Intersection() : 
    m_p(-1), m_normal(0,0,0), m_distance(0) , m_type(CONTACT)
{
}

JelloMesh::Intersection::Intersection(const JelloMesh::Intersection& p) :
    m_p(p.m_p), m_normal(p.m_normal), m_distance(p.m_distance), m_type(p.m_type)
{
}

JelloMesh::Intersection& JelloMesh::Intersection::operator=(const JelloMesh::Intersection& p)
{
    if (&p == this) return *this;
    m_p = p.m_p;
    m_normal = p.m_normal;
    m_distance = p.m_distance;
    m_type = p.m_type;
    return *this;
}

JelloMesh::Intersection::Intersection(IntersectionType type, int p, const vec3& normal, double d) :
    m_p(p), m_normal(normal), m_distance(d), m_type(type)
{
}


//---------------------------------------------------------------------
// Drawing
//---------------------------------------------------------------------
