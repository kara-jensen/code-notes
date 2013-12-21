﻿///////////////////////////////////////////////////////////////////////////////////////////////////
// COLLISIONS
///////////////////////////////////////////////////////////////////////////////////////////////////
/*
PERFECTLY ELASTIC COLLISION: collision with no loss of energy
COLLISION DETECTION: Detection/prediction of collision of objects
COLLISION RESOLUTION: Physics rules applied to the colliding objects as a result of the event
COLLISION EFFECTS: Events that arise as a result of the collision
CONSTRAINT BASED METHODS: Complex offline collision detection
IMPULSE BASED METHODS: Use impulse generated by collision to determine resulting velocities

OBJECT ALIGNED BOUNDING BOX: Box rotates with object and aligned to its axis
AXIS ALIGNED BOUNDING BOX: Box sides are aligned with the world axis

COLLISION DETECTION
Once proxies are tested, to obtain greater accuracies, A/B are colliding if:
 ---------
| u.n < 0 | angle Ɵ > 90
 ---------
 u = relative velocity of vertex Pᵃ of A colliding with B
 n = normal to the plane of collsion

///////////////////////////////////////////////////////////////////////////////////////////////////
// MOUSE MOVEMENT ALONG AXIS
///////////////////////////////////////////////////////////////////////////////////////////////////

• axis is any vector in 3D space that the mouse has to move along/away from
• invViewMatrix is camera world matrix
• Mouse direction aligned with axis if dot > 0.0f

D3DXVECTOR3 mouseDirection(-(position.x-previous.x), position.y-previous.y, 0.0f);
D3DXVec3Normalize(&mouseDirection, &mouseDirection);
mouseDirection.z = CAMERA_NEAR;
D3DXVec3TransformNormal(&mouseDirection, &mouseDirection, &invProjectionMatrix);
D3DXVec3TransformNormal(&mouseDirection, &mouseDirection, &invViewMatrix);
D3DXVec3Normalize(&mouseDirection, &mouseDirection);
D3DXVec3Normalize(&axis, &axis);
const float dot = D3DXVec3Dot(&axis, &mouseDirection);

///////////////////////////////////////////////////////////////////////////////////////////////////
// MOUSE RAY-CASTING
///////////////////////////////////////////////////////////////////////////////////////////////////

















///////////////////////////////////////////////////////////////////////////////////////////////////
//PLANE-POINT COLLISION [SAME SIDE TECHNIQUE]
///////////////////////////////////////////////////////////////////////////////////////////////////

Test what side of each edge the origin is on

   c
   /\         u = b - a
  /  \        v = c - a
 /    \       n = u X v (pointing out screen)
/______\
a       b

Test AB Side:
n X (b-a) = ABN = vector pointing from b-a to center
(p-a) . ABN > 0 then true

Test AC Side:
n X (c-a) = ACN = vector pointing from c-a outwards
(p-a) . ACN < 0 then true

Test CB Side:
n X (c-b) = CBN = vector pointing from c-b to center
(p-b) . CBN > 0 then true

///////////////////////////////////////////////////////////////////////////////////////////////////
//PLANE-POINT COLLISION [BARYCENTRIC TECHNIQUE]
///////////////////////////////////////////////////////////////////////////////////////////////////

// Convert world coordinates of p into barycentric coordinates
// Plane equation: d = su + tv where d = p - p0
// Dot by u/v to: d.v = (su + tv).v and d.u = (su + tv).u
// Rearrange to: s = (dv - t(vv)) / (uv) and t = (du - s(uu)) / (uv)
// Substitute each one into the other and find s,t

D3DXVECTOR3 u = p1 - p0;
D3DXVECTOR3 v = p2 - p0;
D3DXVECTOR3 d = p - p0;

const float uu = D3DXVec3Dot(&u, &u);
const float vv = D3DXVec3Dot(&v, &v);
const float uv = D3DXVec3Dot(&u, &v);
const float dv = D3DXVec3Dot(&d, &v);
const float du = D3DXVec3Dot(&d, &u);
const float t = ((uv * du) - (dv * uu)) / ((uv * uv) - (vv * uu));
const float s = ((dv * uv) - (du * vv)) / ((uv * uv) - (uu * vv));

// Determine if inside half of the plane (triangle)
const bool inside = t >= 0.0f && s >= 0.0f && t+s <= 1.0f;

///////////////////////////////////////////////////////////////////////////////////////////////////
// PLANE-RAY COLLISION
///////////////////////////////////////////////////////////////////////////////////////////////////

Ray: P₀(x,y,z) with d(dx,dy,dz)
Plane: n̂(a,b,c)

1) Determine if ray will intersect plane: if d.n̂ < 0 collision
2) Get t amount along ray:

C = A/cosƟ from trig
⁂ t = (P₁-P₀).n̂/cosƟ

a.b̂ = ‖a‖cosƟ from projection
⁂ d.n̂ = ‖d‖cosƟ
⁂ cosƟ = d.n̂/‖d‖
⁂ cosƟ = d.n̂

⁂ t = (P₁-P₀).n̂ / d.n̂

3) Find point of intersection: P = P₀ + td

///////////////////////////////////////////////////////////////////////////////////////////////////
// CIRCLE-POINT COLLISION ALGORITHM
///////////////////////////////////////////////////////////////////////////////////////////////////

float radius;
D3DXVECTOR3 position;
float maxX = position.x + radius;
float minX = position.x - radius;
float maxZ = position.z + radius;
float minZ = position.z - radius;

// Get indices at the min/max/position
int maxXIndex, maxZIndex, minXIndex, minZIndex, positionIndex;
int xDistance = maxXIndex - minXIndex;

for(int x = minXIndex; x <= maxXIndex; ++x)
{
    for(int z = minZIndex; z <= maxZIndex; ++z)
    {
        int index = (z * xDistance) + x;
        const D3DXVECTOR3& p = GetPosition(index);

        if(D3DXVec3Length(&(p - position)) < radius)
        {
            // inside the circle
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// SPHERE-SPHERE COLLISION ALGORITHM
///////////////////////////////////////////////////////////////////////////////////////////////////

D3DXVECTOR3 particleToParticle = particleB.GetPosition() - particleA.GetPosition();
const float length = D3DXVec3Length(&particleToParticle);
const float combinedRadius = particleA.GetRadius() + particleB.GetRadius();

if (length < combinedRadius)
{
    particleToParticle /= length;
    const D3DXVECTOR3 translation = particleToParticle*fabs(combinedRadius-length);
    particleA.ResolveCollision(-translation);
    particleB.ResolveCollision(translation);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// SPHERE-RAY COLLISION ALGORITHM
///////////////////////////////////////////////////////////////////////////////////////////////////









///////////////////////////////////////////////////////////////////////////////////////////////////
// CUBE-CUBE COLLISION ALGORITHM
///////////////////////////////////////////////////////////////////////////////////////////////////

if(BoxA->max.x < BoxB->min.x || BoxA->min.x > BoxB->max.x)
    return false;
if(BoxA->max.y < BoxB->min.y || BoxA->min.y > BoxB->max.y)
    return false;
if(BoxA->max.z < BoxB->min.z || BoxA->min.z > BoxB->max.z)
    return false;
else
    return true;

///////////////////////////////////////////////////////////////////////////////////////////////////
// LINE-INTERSECTION TECHNIQUE [CONVEX/CONCAVE]
///////////////////////////////////////////////////////////////////////////////////////////////////

• supports concave/convex shapes but slow and ineffecient
• For each outside edge of the model, create a line
• Test this array of lines against other model's array of lines for each line

Line1: P₁(t) = P₁(0) + t₁d₁
Line2: P₂(t) = P₂(0) + t₂d₂
where d = vector between start/end point of line
where t = 0->1 when on the line

Collision occurs if both t₁ and t₂ are between 0 and 1

P₁(0) + t₁d₁ = P₂(0) + t₂d₂

⁂ P₁(0)x + t₁d₁x = P₂(0)x + t₂d₂x
⁂ P₁(0)y + t₁d₁y = P₂(0)y + t₂d₂y

and rearrange to solve for t₁ and t₂

///////////////////////////////////////////////////////////////////////////////////////////////////
// GJK COLLISION ALGORITHM [CONVEX]
///////////////////////////////////////////////////////////////////////////////////////////////////

MINKOWSKI DIFFERENCE:
• Create from two convex hulls by subtracting all points of A from all points of B
• If contains the origin, both hulls are colliding
• As hulls get closer, Minkowski Difference hull gets closer to origin

GJK ALGORITHM:
• Doesn't require computing whole Minkowski Difference hull
• Builds a simplex inside the Minkowski Difference to see if it encloses the origin
• Uses a 'support' function to find the furthest point in the MD hull in a direction
  which helps create the simplex with the largest area enclosing the MD hull

CHOOSING THE INITIAL POINTS:
• Randomly choose a point in A and B and subract to get a direction between the two
• Find the point along that direction that is the furthest away (+ largest dot product)
• Generate the Minkowski Difference point of the chosen two points which is an edge point 
• Negate the direction

WHILE COLLISION IS NOT FOUND:
• Get a new edge point in the direction
• Check if this new point is past the origin (has a + dot product with it)
• If not past the origin, origin isn't inside the difference and collision cannot occur
• If line simplex: Cross the line and the last point to origin to get the next direction
• If a tri-plane simplex: Next direction is the normal that points towards the origin
• If a tetrahedron simplex: 
    - If origin is inside all three planes (the forth was checked as a tri plane) then collision
    - If origin is outside a plane, remove the furthest point
    - The next direction is the normal to the plane towards the origin

FINDING PENETRATION DEPTH
• Use Expanding Polytope Algorithm (EPA) with the terminating GJK simplex
• Find the triangle of simplex that is closest to the origin
• If the projected point of the origin does not lie within the triangle on the plane, find next closest
• Search along the triangle normal and find the Minkowski difference edge hull point
• If this point is close to the face, terminate as found
• If not close, extend the simplex to include this new point and continue loop
• Once closest face is found, penetration vector is face normal * distance to origin

///////////////////////////////////////////////////////////////////////////////////////////////////
//COLLISION RESOLUTION
///////////////////////////////////////////////////////////////////////////////////////////////////

 ---------------
| uᶠ.n = -euⁱ.n |
 ---------------
 uⁱ/uᶠ = relative velocity before/after collision
 n = plane of collision
 e = amount of energy lost during collision where 0 ≤ e ≤ 1
     e = 1; pefectly elastic collision
     e = 0; all energy lost and objects stop

 When storing object's mass, only store ¹/m
 For collisions involving large static objects, set objects mass to ¹/∞

==============================================================================
NON-ROTATING OBJECTS
==============================================================================
 -----------
| u = vᵃ-vᵇ | 
 -----------
 u = Relative velocity of vertex Pᵃ on A which collides with object B
 vᵃ,vᵇ = Linear velocity = Translational velocity

RESULT IN COLLISION: 

change in velocity for A and B
 --------------------------
| vᵃ(f) = vᵃ(i) + (¹/mᵃ)Jn |
| vᵇ(f) = vᵇ(i) - (¹/mᵇ)Jn |
 --------------------------
Use these values and uᶠ.n = -euⁱ.n to find equation for impulse(J) 

==============================================================================
ROTATING OBJECTS
==============================================================================

 -----------
| u = vᵃ-vᵇ | 
 -----------
 u = Relative velocity of vertex Pᵃ on A which collides with object B
 vᵃ/vᵇ = Linear velocity 
       = Translational(translation) + Tangential velocity(rotation)
         v = vᵗ + vᵀ = vᵗ + w X r

RESULT IN COLLISION: 

change in translational velocity for A and B
 --------------------------
| vᵗᵃ(f) = vᵃ(i) + (¹/mᵃ)Jn |
| vᵗᵇ(f) = vᵇ(i) - (¹/mᵇ)Jn |
 --------------------------
change in angular velocity for A and B
 --------------------------------
| wᵃ(f) = wᵃ(i) + (¹/iᵃ)(r X Jn) |
| wᵇ(f) = wᵇ(i) - (¹/iᵇ)(r X Jn) |
 --------------------------------
 Use these values to find equation for impulse(J)

 *///////////////////////////////////////////////////////////////////////////////////////////////////