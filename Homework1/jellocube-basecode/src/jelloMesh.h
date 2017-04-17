#ifndef jelloMesh_H_
#define jelloMesh_H_

#include <vector>
#include <map>
#include "vec.h"
#include "World.h"

class JelloMesh
{
public:
    JelloMesh();
    virtual ~JelloMesh();

    // Update our JelloMesh (handles collisions and forces)
    virtual void Update(double dt, 
        const World& world,
        const vec3& externalForces = vec3(0.0, -9.8, 0));


    // Draw our JelloMesh
    virtual void Draw(const vec3& eyePos);

    // Reset to the initial state
    virtual void Reset();

    // Set/Get our JelloMesh resolution


    // Set/Get our JelloMesh size (in world coordinates)
    virtual void SetSize(float width, float height, float depth);


    // Set/Get our numerical integration type
    enum IntegrationType { EULER, MIDPOINT, RK4 };
    virtual void SetIntegrationType(IntegrationType type);
    virtual IntegrationType GetIntegrationType() const;

    // Set/Get our draw flags
    virtual void SetDrawFlags(unsigned int flags);
    virtual unsigned int GetDrawFlags() const;


    int GetIndex(int i, int j, int k) const;
    void GetCell(int idx, int& i, int &j, int &k) const;


protected:

    class Particle;

    friend class TestJelloMesh;

    typedef std::vector<std::vector<std::vector<Particle>>> ParticleGrid;
    Particle& GetParticle(ParticleGrid& grid, int i, int j, int k);
    Particle& GetParticle(ParticleGrid& grid, int idx);
    const Particle& GetParticle(const ParticleGrid& grid, int i, int j, int k) const;
    const Particle& GetParticle(const ParticleGrid& grid, int idx) const;


    bool isInterior(int idx) const;
    bool isInterior(int i, int j, int k) const;

    virtual void InitJelloMesh();


    class Intersection;
	virtual void CheckForCollisions(ParticleGrid& grid, const World& world);
	virtual void ResolveCollisions(ParticleGrid& grid);
	virtual void ResolveContacts(ParticleGrid& grid);
    virtual bool FloorIntersection(Particle& p, Intersection& intersection);
    virtual bool CylinderIntersection(Particle& p, World::Cylinder* cylinder, Intersection& intersection);
	virtual bool SphereIntersection(Particle& p, World::Sphere* sphere, JelloMesh::Intersection& result);

    virtual void ComputeForces(ParticleGrid& grid);
	virtual void EulerIntegrate(double dt);
	virtual void MidPointIntegrate(double dt);
	virtual void RK4Integrate(double dt);

	virtual void DrawParticles();



    void DrawCollisionNormals();
    void DrawForces();

protected:

    int m_cols, m_rows, m_stacks;
    float m_width, m_height, m_depth;
    unsigned int m_drawflags;
    vec3 m_externalForces;
	vec3 m_floatyForces;

    IntegrationType m_integrationType;

    ParticleGrid m_vparticles;


    std::vector<Intersection> m_vcontacts;
    std::vector<Intersection> m_vcollisions;

public:


    static double g_penaltyKs;
    static double g_penaltyKd;

    static const unsigned int MESH = 0x10;
    static const unsigned int NORMALS = 0x100;
    static const unsigned int FORCES = 0x1000;

protected:

    class Particle
    {
    public:
        Particle();
        Particle(const Particle& p);
        Particle& operator=(const Particle& p);
        Particle(int idx, const vec3& pos, const vec3& vel = vec3(0,0,0), double m = 1);

        int index;
        vec3 position;
        vec3 velocity;
        vec3 force;
        double mass;

        static Particle EMPTY;
    };

    

    enum IntersectionType { CONTACT, COLLISION };
    class Intersection
    {
    public:
        Intersection();
        Intersection(const Intersection& p);
        Intersection& operator=(const Intersection& p);
        Intersection(IntersectionType type, int p, const vec3& normal, double d = 0);

        int m_p;
        vec3 m_normal;
        double m_distance;
        IntersectionType m_type;
    };
};

#endif